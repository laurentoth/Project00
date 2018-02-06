// STL
#ifndef FACE_H
#define FACE_H



#include "Vertex.h"
#include "Normal.h"
#include "Texture.h"


class Face{
private:
  Vertex one;
  Vertex two;
  Vertex three;
  Vertex four;
  Normal normal;
  Texture texture1;
  Texture texture2;
  Texture texture3;
  Texture texture4;
  bool triangle;
  bool texture;

public:
	Face(){};
Vertex	getV1();
Vertex	getV2();
Vertex	getV3();
Vertex	getV4();
Normal	getNormal();
Texture	getT1();
Texture	getT2();
Texture	getT3();
Texture getT4();
bool isTriangle();
bool isTexture();

void	setV1(Vertex v1);
void	setV2(Vertex v2);
void	setV3(Vertex v3);
void	setV4(Vertex v1);
void	setNormal(Normal n);
void	setT1(Texture t1);
void	setT2(Texture t2);
void	setT3(Texture t3);
void setT4(Texture t4);
void setIsTriangle(bool t);
void setIsTexture(bool t);

};
#endif
