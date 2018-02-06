#include "Vertex.h"
Vertex::Vertex(){

}

void Vertex::setX(float x){
	xcoor=x;

}

void Vertex::setY(float y){
	ycoor=y;

}
void Vertex::setZ(float z){
	zcoor=z;

}

float Vertex::getX(){
	return xcoor;
}

float Vertex::getY(){
	return ycoor;
}

float Vertex::getZ(){
	return zcoor;
}

