// STL

#include "Face.h"



Vertex	Face::getV1(){return one;};
Vertex	Face::getV2(){return two;};
Vertex	Face::getV3(){return three;};
Vertex	Face::getV4(){return four;};
Normal	Face::getNormal(){return normal;};
Texture	Face::getT1(){return texture1;};
Texture	Face::getT2(){return texture2;};
Texture	Face::getT3(){return texture3;};
Texture Face::getT4(){return texture4;};
bool Face::isTriangle(){if(triangle){return true;} return false;};
bool Face::isTexture(){if(texture){return true;}return false;};

void	Face::setV1(Vertex v1){ one =v1;};
void	Face::setV2(Vertex v2){ two=v2;};
void	Face::setV3(Vertex v3){ three=v3;};
void	Face::setV4(Vertex v4){ four=v4;};
void	Face::setNormal(Normal n){ normal=n;};
void	Face::setT1(Texture t1){ texture1=t1;};
void	Face::setT2(Texture t2){ texture2=t2;};
void	Face::setT3(Texture t3){ texture3=t3;};
void Face::setT4(Texture t4){ texture4=t4;};
void Face::setIsTriangle(bool t){triangle=t;};
void Face::setIsTexture(bool t){texture=t;};



