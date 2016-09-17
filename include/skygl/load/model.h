#pragma once

#include <skygl/basic/common.h>
#include <skygl/basic/types.h>
#include <skygl/basic/error.h>
#include <skygl/calc/math.h>
#include <skygl/gl/gl.h>
#include <skygl/gl/buffer.h>
#include <skygl/gl/shader.h>
#include <skygl/gl/texture.h>

#include <vector>

#include <boost/noncopyable.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

NS_SKY_GL_BEG

struct Vertex {
    Vec3 position;
    Vec3 normal;
    Vec2 texCoords;
    Vec3 tangent;
    Vec3 bitangent;
};

class Mesh {
public:
    using Vertices = std::vector<Vertex>;
    using Indices = std::vector<UInt>;
    using Textures = std::vector<Texture2DPtr>;
    using TexturesMap = std::map<String, std::vector<Texture2DPtr>>;
private:
    Vertices vertices;
    Indices indices;
    TexturesMap textures;
    VertexArray VAO;
    ArrayBuffer VBO;
    ElementBuffer EBO;
public:
    Mesh(Vertices v, Indices i, TexturesMap t)
        : vertices(std::move(v))
        , indices(std::move(i))
        , textures(std::move(t))
    {
        setup();
    }
    template <typename Func>
    void setupVAO(Func&& f) {
        SKY_BIND(VAO) {
            f(_);
        }
    }
    void draw(KProgramRef shader, UInt instance = 1, UInt id = 0) {
        for (auto& p : textures) {
            auto& name = p.first;
            auto& texs = p.second;
            for (SizeT i = 0; i < texs.size(); ++i) {
                texs[i]->active(id);
                auto uniformName = "textures[" + std::to_string(i) + "]." + name;
                shader.uniform(uniformName, static_cast<Int>(id));
                id++;
            }
        }
        SKY_BIND(VAO) {
            if (instance == 1) {
                glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
            } else {
                glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, instance);
            }
        }
        for (auto& p : textures) {
            for (auto& t : p.second) {
                t->unbind();
            }
        }
    }
private:
    void setup() {
        SKY_BIND(VAO) {
            _.buffer(EBO).data(indices);
            _.buffer(VBO).data(vertices);
            _.attrib(0).has<Float>(3).stride(sizeof(Vertex)).offset(offsetof(Vertex, position));
            _.attrib(1).has<Float>(3).stride(sizeof(Vertex)).offset(offsetof(Vertex, normal));
            _.attrib(2).has<Float>(2).stride(sizeof(Vertex)).offset(offsetof(Vertex, texCoords));
            _.attrib(3).has<Float>(3).stride(sizeof(Vertex)).offset(offsetof(Vertex, tangent));
            _.attrib(4).has<Float>(3).stride(sizeof(Vertex)).offset(offsetof(Vertex, bitangent));
        }
    }
};

class Model: private boost::noncopyable {
private:
    using Meshes = std::vector<Mesh>;
    Meshes meshes;
public:
    Model() = default;
    Model(KStringRef path) {
        load(path);
    }
    template <typename Func>
    void setupVAO(Func&& f) {
        for (auto& m : meshes) {
            m.setupVAO(std::forward<Func>(f));
        }
    }
    void draw(KProgramRef shader, UInt instance = 1, UInt id = 0) {
        for (auto& m : meshes) {
            m.draw(shader, instance, id);
        }
    }
    void load(KStringRef path) {
        Assimp::Importer importer;
        auto scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
        if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            throw GLException("Model::load", importer.GetErrorString());
        }
        auto directory = path.substr(0, path.find_last_of('/'));
        processNode(scene->mRootNode, scene, directory);
    }
private:
    void processNode(aiNode* node, const aiScene* scene, KStringRef dir) {
        for (UInt i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            processMesh(mesh, scene, dir);
        }
        for (UInt i = 0; i < node->mNumChildren; i++) {
            processNode(node->mChildren[i], scene, dir);
        }
    }
    void processMesh(aiMesh* mesh, const aiScene* scene, KStringRef dir) {
        Mesh::Vertices vertices;
        Mesh::Indices indices;
        Mesh::TexturesMap textures;
        for (UInt i = 0; i < mesh->mNumVertices; i++) {
            Vertex v;
            auto& mv = mesh->mVertices[i];
            v.position = {mv.x, mv.y, mv.z};
            auto& mn = mesh->mNormals[i];
            v.normal = {mn.x, mn.y, mn.z};
            if (mesh->mTextureCoords[0]) {
                auto& mt = mesh->mTextureCoords[0][i];
                v.texCoords = {mt.x, mt.y};
            } else {
                v.texCoords = {0, 0};
            }
            auto& mt = mesh->mTangents[i];
            v.tangent = {mt.x, mt.y, mt.z};
            auto& mb = mesh->mBitangents[i];
            v.bitangent = {mb.x, mb.y, mb.z};
            vertices.push_back(v);
        }
        for(UInt i = 0; i < mesh->mNumFaces; i++) {
            auto& face = mesh->mFaces[i];
            for (UInt j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        for (auto& p : std::initializer_list<std::pair<aiTextureType, String>> {
            { aiTextureType_AMBIENT,  "ambient"  },
            { aiTextureType_DIFFUSE,  "diffuse"  },
            { aiTextureType_SPECULAR, "specular" },
            { aiTextureType_NORMALS,  "normals"  },
            { aiTextureType_HEIGHT,   "height"   },
        }) {
            auto& type = p.first;
            auto& name = p.second;
            textures[name] = loadMaterialTextures(material, type, name, dir);
        }
        meshes.emplace_back(std::move(vertices), std::move(indices), std::move(textures));
    }
    Mesh::Textures loadMaterialTextures(aiMaterial* mat, aiTextureType type, KStringRef typeName, KStringRef dir) {
        Mesh::Textures textures;
        for (UInt i = 0; i < mat->GetTextureCount(type); i++) {
            aiString str;
            mat->GetTexture(type, i, &str);
            Texture2DPtr p = std::make_shared<Texture2D>();
            p->bind()
                .param(GL_TEXTURE_WRAP_S, GL_REPEAT)
                .param(GL_TEXTURE_WRAP_T, GL_REPEAT)
                .param(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
                .param(GL_TEXTURE_MAG_FILTER, GL_LINEAR)
                .load(Image(dir + "/" + str.C_Str()))
                .genMipmap()
            .unbind();
            textures.push_back(p);
        }
        return textures;
    }
};

NS_SKY_GL_END
