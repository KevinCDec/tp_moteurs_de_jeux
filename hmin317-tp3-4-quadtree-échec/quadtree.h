#ifndef QUADTREE_H
#define QUADTREE_H

#include <QImage>
#include <QVector3D>
#include <QVector2D>

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};


class quadtree
{
public:
    quadtree(int d, QVector3D topleft, int planeSize, QImage img);
    quadtree(int d, QVector3D topleft, int planeSize);
    unsigned short* getIndices();
    //    QVector3D* getVectors();
    VertexData* getVertices();

protected:
    int depth;
    VertexData vertices [4];
    unsigned short indices [6];

private:

};

#endif // QUADTREE_H
