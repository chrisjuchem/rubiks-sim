#include "Image.h"
#include <fstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <memory>

Image::Image(std::string filepath) : m_filepath(filepath){
	  
}


// Destructor
Image::~Image (){
    // Delete our pixel data.	
    // Note: We could actually do this sooner
    // in our rendering process.
    if(m_PixelData!=NULL){
        delete[] m_PixelData;
    }
}

// Little function for loading the pixel data
// from a PPM image.
// TODO: Expects a very specific version of PPM!
//
// flip - Will flip the pixels upside down in the data
//        If you use this be consistent.
void Image::loadPPM(bool flip){

  // Open an input file stream for reading a file
  std::ifstream ppmFile(m_filepath.c_str());
  // If our file successfully opens, begin to process it.
  if (ppmFile.is_open()){

    magicNumber = nextToken(ppmFile);
    m_width = nextIntToken(ppmFile);
    m_height = nextIntToken(ppmFile);
    int maxVal = nextIntToken(ppmFile);

    int entries = this->m_width * this->m_height * 3;
    m_PixelData = new unsigned char[entries];

    for (int i = 0; ppmFile && i < entries; i++) {
        m_PixelData[i] = (unsigned char)(nextIntToken(ppmFile) * 255 / maxVal);
    }


    ppmFile.close();
  }
  else{
      std::cout << "Unable to open ppm file:" << m_filepath << std::endl;
  } 

    // Flip all of the pixels
    if(flip){
        // Copy all of the data to a temporary stack-allocated array
        unsigned char* copyData = new unsigned char[m_width*m_height*3];
        for(int i =0; i < m_width*m_height*3; ++i){
            copyData[i]=m_PixelData[i];
        }
        //memcpy(copyData,m_PixelData,(m_width*m_height*3)*sizeof(unsigned char));
        unsigned int pos = (m_width*m_height*3)-1;
        for(int i =0; i < m_width*m_height*3; i+=3){
            m_PixelData[pos]=copyData[i+2];
            m_PixelData[pos-1]=copyData[i+1];
            m_PixelData[pos-2]=copyData[i];
            pos-=3;
        }
        delete[] copyData;
    }
}

int Image::nextIntToken(std::ifstream& file) {
  return std::stoi(nextToken(file));
}

std::string Image::nextToken(std::ifstream& file) {
  std::string token;
  file >> token;
  while (token[0] == '#') {
    std::getline(file, token);  // throwing away the rest of the line
    file >> token;
  }
  return token;
}

void Image::setPixel(int x, int y, int r, int g, int b){
  if(x > m_width || y > m_height){
    return;
  }
  else{
    /*std::cout << "modifying pixel at " 
              << x << "," << y << "from (" <<
              (int)color[x*y] << "," << (int)color[x*y+1] << "," <<
(int)color[x*y+2] << ")";*/

    m_PixelData[(x*3)+m_height*(y*3)] = r;
    m_PixelData[(x*3)+m_height*(y*3)+1] = g;
    m_PixelData[(x*3)+m_height*(y*3)+2] = b;

/*    std::cout << " to (" << (int)color[x*y] << "," << (int)color[x*y+1] << ","
<< (int)color[x*y+2] << ")" << std::endl;*/

  }
}

void Image::printPixels(){
    for(int x = 0; x <  m_width*m_height*3; ++x){
        std::cout << " " << (int)m_PixelData[x];
    }
    std::cout << "\n";
}

unsigned char* Image::getPixelData(){
    return m_PixelData;
}
