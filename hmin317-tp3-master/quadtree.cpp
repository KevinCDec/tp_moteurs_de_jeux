#include "quadtree.h"



quadtree::quadtree(int d, QVector3D topleft, int planeSize, QImage img) :
    depth(d)
{
    float x = topleft.x();
    float y = topleft.y();
    float z = topleft.z();
    int dm = d-1;
    float vectunit = planeSize/(pow(2,dm));
    int imgheightunit = img.height()/(pow(2,dm));
    int imgwitdthunit = img.width()/(pow(2,dm));


    this->vertices[0]={topleft,QVector2D(z/3,1.0f)};
    float imgpoint = img.pixelColor(x,y+imgheightunit).blue()*3.0/255.0;
    this->vertices[1]={QVector3D(x,y+vectunit,imgpoint),QVector2D(imgpoint/3,1.0f)};
    imgpoint = img.pixelColor(x+imgwitdthunit,y).blue()*3.0/255.0;
    this->vertices[2]={QVector3D(x+vectunit,y,imgpoint),QVector2D(imgpoint/3,1.0f)};
    imgpoint = img.pixelColor(x+imgwitdthunit,y+imgheightunit).blue()*3.0/255.0;
    this->vertices[3]={QVector3D(x+vectunit,y+vectunit,imgpoint),QVector2D(imgpoint/3,1.0f)};

    this->indices[0]=0;
    this->indices[1]=1;
    this->indices[2]=2;
    this->indices[3]=1;
    this->indices[4]=3;
    this->indices[5]=2;



}

quadtree::quadtree(int d, QVector3D topleft, int planeSize) :
    depth(d)
{
    QImage img;
    img.load(":/heightmap-1.png");
    if(img.isNull()){
        qInfo("img est null !");
    }

    float x = topleft.x();
    float y = topleft.y();
    float z = topleft.z();
    int dm = d-1;
    float vectunit = planeSize/(pow(2,dm));
    int imgheightunit = (img.height()-1)/(pow(2,dm));
    int imgwitdthunit = (img.width()-1)/(pow(2,dm));

    this->vertices[0]={topleft,QVector2D(0.0f,1.0f)};

//    this->vertices[1]=QVector3D(0.0f,1.0f,1.0f)/*,QVector2D(imgpoint/3,1.0f)*/;
//    this->vertices[2]=QVector3D(1.0f,0.0f,1.0f)/*,QVector2D(imgpoint/3,1.0f)*/;
//    this->vertices[3]=QVector3D(1.0f,1.0f,1.0f)/*,QVector2D(imgpoint/3,1.0f)*/;

    float imgpoint = img.pixelColor(x,y+imgheightunit).blue()*3.0f/255.0f;
    this->vertices[1]={QVector3D(x,y+1.0f,z),QVector2D(0.0f,1.0f)};
    imgpoint = img.pixelColor(x+imgwitdthunit,y).blue()*3.0f/255.0f;
    this->vertices[2]={QVector3D(x+1.0f,y,z),QVector2D(0.0f,1.0f)};
    imgpoint = img.pixelColor(x+imgwitdthunit,y+imgheightunit).blue()*3.0f/255.0f;
    this->vertices[3]={QVector3D(x+1.0f,y+1.0f,z),QVector2D(0.0f,1.0f)};

//    float imgpoint = img.pixelColor(x,y+imgheightunit).blue()*3.0/255.0;
//    this->vertices[1]={QVector3D(x,y+vectunit,imgpoint),QVector2D(imgpoint/3,1.0f)};
//    imgpoint = img.pixelColor(x+imgwitdthunit,y).blue()*3.0/255.0;
//    this->vertices[2]={QVector3D(x+vectunit,y,imgpoint),QVector2D(imgpoint/3,1.0f)};
//    imgpoint = img.pixelColor(x+imgwitdthunit,y+imgheightunit).blue()*3.0/255.0;
//    this->vertices[3]={QVector3D(x+vectunit,y+vectunit,imgpoint),QVector2D(imgpoint/3,1.0f)};

    this->indices[0]=0;
    this->indices[1]=1;
    this->indices[2]=2;
    this->indices[3]=1;
    this->indices[4]=3;
    this->indices[5]=2;

}

unsigned short* quadtree::getIndices(){
    return this->indices;
}

VertexData* quadtree::getVertices(){
    return this->vertices;
}
