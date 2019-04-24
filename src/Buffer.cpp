#include "Buffer.h"
#include <iostream>

Buffer::Buffer() {}

Buffer::~Buffer() {
  // TODO: glDeleteBuffers
}

void Buffer::Bind() {
  // Bind to our vertex array
  glBindVertexArray(m_VAOId);
  // Bind to our vertex information
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexPositionBuffer);
  // Bind to the elements we are drawing
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObject);
}

// Note: Calling Unbind is rarely done, if you need
// to draw something else then just bind to new buffer.
void Buffer::Unbind() {
  // Bind to our vertex array
  glBindVertexArray(0);
  // Bind to our vertex information
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  // Bind to the elements we are drawing
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Buffer::CreateBufferLayout(unsigned int stride, unsigned int vcount,
                                unsigned int icount, float* vdata,
                                unsigned int* idata) {
  m_stride = stride;

  static_assert(sizeof(GLfloat) == sizeof(float),
                "GLFloat and gloat are not the same size on this architecture");

  // VertexArrays
  glGenVertexArrays(1, &m_VAOId);

  glBindVertexArray(m_VAOId);

  // Vertex Buffer Object (VBO)
  glGenBuffers(1, &m_vertexPositionBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexPositionBuffer);
  glBufferData(GL_ARRAY_BUFFER, vcount * sizeof(float), vdata, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  // Finally pass in our vertex data
  glVertexAttribPointer(
      0,         // Attribute 0, match in shader
      3,         // size (Number of components)
      GL_FLOAT,  // Type of data
      GL_FALSE,  // Is the data normalized
      sizeof(float) *
          m_stride,  // Stride - Amount of bytes between each vertex.
      0              // Offset into our data.
  );

  // Adding a new glVertexAttrib
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * m_stride,
                        (char*)(sizeof(float) * 3));

  // Another Vertex Buffer Object (VBO)
  // (index buffer)
  static_assert(sizeof(unsigned int) == sizeof(GLuint),
                "Gluint not same size!");

  glGenBuffers(1, &m_indexBufferObject);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObject);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, icount * sizeof(unsigned int), idata,
               GL_STATIC_DRAW);
}

// A normal map layout needs the following attributes
//
// positions
// normals
// texcoords
// tangent
// bitangent
void Buffer::CreateBufferNormalMapLayout(unsigned int stride,
                                         unsigned int vcount,
                                         unsigned int icount, float* vdata,
                                         unsigned int* idata) {
  m_stride = stride;

  static_assert(sizeof(GLfloat) == sizeof(float),
                "GLFloat and gloat are not the same size on this architecture");

  // VertexArrays
  glGenVertexArrays(1, &m_VAOId);

  glBindVertexArray(m_VAOId);

  // Vertex Buffer Object (VBO)
  glGenBuffers(1, &m_vertexPositionBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexPositionBuffer);
  glBufferData(GL_ARRAY_BUFFER, vcount * sizeof(float), vdata, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  // Finally pass in our vertex data
  glVertexAttribPointer(
      0,         // Attribute 0, match in shader
      3,         // size (Number of components)
      GL_FLOAT,  // Type of data
      GL_FALSE,  // Is the data normalized
      sizeof(float) *
          m_stride,  // Stride - Amount of bytes between each vertex.
      0              // Offset into our data.
  );

  // Add three floats for normal coordinates
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * m_stride,
                        (char*)(sizeof(float) * 3));

  // Add two floats for texture coordinates
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * m_stride,
                        (char*)(sizeof(float) * 6));

  // Add three floats for tangent coordinates
  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * m_stride,
                        (char*)(sizeof(float) * 8));

  // Add three floats for bi-tangent coordinates
  glEnableVertexAttribArray(4);
  glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(float) * m_stride,
                        (char*)(sizeof(float) * 11));

  // Another Vertex Buffer Object (VBO)
  // (index buffer)
  static_assert(sizeof(unsigned int) == sizeof(GLuint),
                "Gluint not same size!");

  // Setup an index buffer
  glGenBuffers(1, &m_indexBufferObject);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObject);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, icount * sizeof(unsigned int), idata,
               GL_STATIC_DRAW);
}

void Buffer::CreateBufferTextureLayout(unsigned int stride, unsigned int vcount,
                                       unsigned int icount, float* vdata,
                                       unsigned int* idata) {
  m_stride = stride;

  static_assert(sizeof(GLfloat) == sizeof(float),
                "GLFloat and gloat are not the same size on this architecture");

  // VertexArrays
  glGenVertexArrays(1, &m_VAOId);

  glBindVertexArray(m_VAOId);

  // Vertex Buffer Object (VBO)
  glGenBuffers(1, &m_vertexPositionBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexPositionBuffer);
  glBufferData(GL_ARRAY_BUFFER, vcount * sizeof(float), vdata, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  // Finally pass in our vertex data
  glVertexAttribPointer(
      0,         // Attribute 0, match in shader
      3,         // size (Number of components)
      GL_FLOAT,  // Type of data
      GL_FALSE,  // Is the data normalized
      sizeof(float) *
          m_stride,  // Stride - Amount of bytes between each vertex.
      0              // Offset into our data.
  );

  // Add two floats for texture coordinates
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, sizeof(float) * m_stride,
                        (char*)(sizeof(float) * 3));

  // Another Vertex Buffer Object (VBO)
  // (index buffer)
  static_assert(sizeof(unsigned int) == sizeof(GLuint),
                "Gluint not same size!");

  glGenBuffers(1, &m_indexBufferObject);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObject);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, icount * sizeof(unsigned int), idata,
               GL_STATIC_DRAW);
}
