//
//  Mesh.hpp
//  4.Assimp
//
//  Created by txh on 2017/6/6.
//  Copyright © 2017年 txh. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp
#pragma once
// Std. Includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;
// GL Includes
#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Texture.hpp"

struct Vertex {
    // Position
    glm::vec3 Position;
    // Normal
    glm::vec3 Normal;
    // TexCoords
    glm::vec2 TexCoords;
};

//struct Texture {
//    GLuint id;
//    string type;
//    aiString path;
//};

class Mesh {
public:
    /*  Mesh Data  */
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;

    
    Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures):vao(new VertexArray)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        this->setupMesh();
    }
    
    // Render the mesh
    void Draw(shared_ptr<Shader> shader)
    {
        // Bind appropriate textures
        GLuint diffuseNr = 1;
        GLuint specularNr = 1;
        for(GLuint i = 0; i < this->textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            stringstream ss;
            string number;
            string name = this->textures[i].getType();
            if(name == "texture_diffuse")
                ss << diffuseNr++; // Transfer GLuint to stream
            else if(name == "texture_specular")
                ss << specularNr++; // Transfer GLuint to stream
            number = ss.str();
            shader->setUniform1i((name + number).c_str(), i);
            glBindTexture(GL_TEXTURE_2D, this->textures[i].getID());
        }
        
        
        vao->bind();
        glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);

        for (GLuint i = 0; i < this->textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
    
private:
    shared_ptr<VertexArray> vao;
    void setupMesh()
    {
        vao->setBuffer(&this->vertices[0], this->vertices.size() * sizeof(Vertex));
        vao->setElementBuffer( &this->indices[0], this->indices.size() * sizeof(GLuint));
        vao->setBufferAttrib(0, 3, sizeof(Vertex), (GLvoid*)0);
        vao->setBufferAttrib(1, 3, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
        vao->setBufferAttrib(2, 2, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));
        
    }
};




#endif /* Mesh_hpp */
