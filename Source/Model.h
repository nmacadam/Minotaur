#pragma once
#include <vector>
#include <assimp/scene.h>

#include "Mesh.h"

class Model
{
public:
	Model();
	Model(std::string path);
	~Model();
    void Draw(Shader* shader);
	//static Model load(std::string path);
	
private:
    /*  Model Data  */
	std::vector<Mesh> meshes;
	std::string directory;

	std::vector<Texture> textures_loaded;
    /*  Functions   */
    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
	                                          std::string typeName);
};

