/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "geometryengine.h"

#include <QVector2D>
#include <QVector3D>

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};

//! [0]
GeometryEngine::GeometryEngine(int s)
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initPlaneGeometry(s);

}

GeometryEngine::~GeometryEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}
//! [0]


//!
void GeometryEngine::initPlaneGeometry(int s)
{

    int planeSize=8;
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
    qInfo( "Debut initPlane" );

    VertexData vertices[(s)*(s)];

    GLushort indices[(s-1)*(s-1)*2*3];
    int k = 0;
    int l = 0;

    int maxFor = (s)*(s-1); //Il parcourt toute la ligne, ignore la dernière colonne, et ne fait pas la dernière ligne
    int modCheck = s-1; //la dernière colonne

    QImage img;
    img.load(":/heightmap-1.png");
    if(img.isNull()){
        qInfo("img est null !");
    }


    for (int i=0; i<maxFor;i++){
        if (i<s){
            for (int j = 0; j<s;j++){

                float iif = (float)i*planeSize/(s-1)-planeSize/2;
                float jjf = (float)j*planeSize/(s-1)-planeSize/2;
                float zzf = img.pixelColor(j,i).blue()*3.0/255.0;
//                qInfo( "zzf : %f",zzf);

                vertices[l]={QVector3D(jjf, iif, zzf), QVector2D(zzf/3,1.0f)};
                l++;

            }

        }

            if(!(i%s==modCheck)){

//                qInfo( "Indice : %d",i);
                // . . puis   .
                // .        . .
                indices[k+0]=i;
                indices[k+1]=i+1;
                indices[k+2]=i+s;
                indices[k+3]=i+1;
                indices[k+4]=i+s+1;
                indices[k+5]=i+s;



//                qInfo( "Valeur 0 : %d",indices[k]);
//                qInfo( "Valeur 1 : %d",indices[k+1]);
//                qInfo( "Valeur 2 : %d",indices[k+2]);
//                qInfo( "Valeur 3 : %d",indices[k+3]);
//                qInfo( "Valeur 4 : %d",indices[k+4]);
//                qInfo( "Valeur 5 : %d",indices[k+5]);
                k+=6;

            } else {
//                qInfo( "Indice skipped : %d",i);
            }
        }




    //        qInfo( "i s : %d",i%s);
    //        qInfo( "i s : %d",modCheck);



    //! [1]
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, s*s * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, (s-1)*(s-1)*2*3 * sizeof(GLushort));
    //! [1]

}


//! [2]
void GeometryEngine::drawPlaneGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

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

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLES, 1000000, GL_UNSIGNED_SHORT, 0);
}
//! [2]
