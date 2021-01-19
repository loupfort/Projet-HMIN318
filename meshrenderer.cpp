#include <iostream>
#include "stdio.h"
#include <QVector2D>
#include <QVector3D>
#include <QImage>
#include <vector>
using namespace std;

#include "Transform.h"
#include "Mesh.h"
#include "GameComponent.h"

#include <QOpenGLFunctions_3_1>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#include <QString>
#include "MeshRenderer.h"



MeshRenderer::MeshRenderer(const QString& filename,char* pathTexture): GameComponent(), indexBuf(QOpenGLBuffer::IndexBuffer){

	mesh=Mesh(filename);
	initializeOpenGLFunctions();

  	// Generate 2 VBOs
   	arrayBuf.create();
   	indexBuf.create();

   	arrayBuf.bind();
   	arrayBuf.allocate(&mesh.points[0], mesh.points.size() * sizeof(VertexData));
    
    nbIndices=mesh.triangles.size();
    // Transfer index data to VBO 1
   	indexBuf.bind();
   	indexBuf.allocate(&mesh.triangles[0], nbIndices * sizeof(GLushort));	

    //init texture

    texture = new QOpenGLTexture(QImage(pathTexture).mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);

}

MeshRenderer::MeshRenderer(float sizeX,float sizeY,float sizeZ,char* pathTexture): GameComponent(), indexBuf(QOpenGLBuffer::IndexBuffer){

	mesh=Mesh(sizeX,sizeY,sizeZ);
	initializeOpenGLFunctions();

	// Generate 2 VBOs
   	arrayBuf.create();
   	indexBuf.create();

   	arrayBuf.bind();
   	arrayBuf.allocate(&mesh.points[0], mesh.points.size() * sizeof(VertexData));
    
    nbIndices=mesh.triangles.size();
    // Transfer index data to VBO 1
   	indexBuf.bind();
   	indexBuf.allocate(&mesh.triangles[0], nbIndices * sizeof(GLushort));	

        //init texture

    texture = new QOpenGLTexture(QImage(pathTexture).mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);

}

MeshRenderer::MeshRenderer(float sizeX,float sizeY,char* pathTexture): GameComponent(), indexBuf(QOpenGLBuffer::IndexBuffer){

	mesh=Mesh(sizeX,sizeY);
	initializeOpenGLFunctions();

	// Generate 2 VBOs
   	arrayBuf.create();
   	indexBuf.create();

   	arrayBuf.bind();
   	arrayBuf.allocate(&mesh.points[0], mesh.points.size() * sizeof(VertexData));
    
    nbIndices=mesh.triangles.size();
    // Transfer index data to VBO 1
   	indexBuf.bind();
   	indexBuf.allocate(&mesh.triangles[0], nbIndices * sizeof(GLushort));	

        //init texture

    texture = new QOpenGLTexture(QImage(pathTexture).mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);

}

MeshRenderer::~MeshRenderer(){
   	arrayBuf.destroy();
   	indexBuf.destroy();
}

void MeshRenderer::input(){

}

void MeshRenderer::update(){

}

void MeshRenderer::render(QOpenGLShaderProgram *program,QMatrix4x4 mvp){

  texture->bind();

  	program->setUniformValue("mvp_matrix",mvp);
    program->setUniformValue("texture", 0);

   	// Offset for position
   	quintptr offset = 0;

   	// Tell OpenGL which VBOs to use
   	arrayBuf.bind();
   	indexBuf.bind();

    // Tell OpenGL programmable pipeline how to locate vertex position data
   	int vertexLocation = program->attributeLocation("a_position");
   	program->enableAttributeArray(vertexLocation);
   	program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

   
    // Offset for texture coordinate
    offset += sizeof(QVector3D);
    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));
    
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
   	glDrawElements(GL_TRIANGLES, nbIndices, GL_UNSIGNED_SHORT, 0);
}