#ifndef TEXTURE_H
#define TEXTURE_H

#include "Image.h"

#include <string>
#include <map>
#include <memory>
#include <glad/glad.h>

class Texture{
public:
    // Constructor
    Texture();
    // Destructor
    ~Texture();
    // Loads and sets up an actual texture
    void LoadTexture(const std::string filepath);
    // slot tells us which slot we want to bind to.
    // We can have multiple slots. By default, we
    // will set our slot to 0 if it is not specified.
    void Bind(unsigned int slot=0) const;
    // Be done with our texture
    void Unbind();
private:
    // Store a unique ID for the texture
    GLuint m_TextureID;
    // Filepath to the image loaded
    std::string m_filepath;
    // PPM Image
    std::shared_ptr<Image> m_image;
    //image cache
    static std::map<std::string,std::shared_ptr<Image>> cache;
};




#endif
