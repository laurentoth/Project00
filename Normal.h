#ifndef NORMAL_H
#define NORMAL_H
#include "Vertex.h"

class Normal{



private:

	float x;
	float y;
	float z;



public:
	Normal(){};
	Normal(float xcoor, float ycoor, float zcoor){};
	float getX();
	float getY();
	float getZ();
	void setX(float xcoor);
	void setY(float ycoor);
	void setZ(float zcoor);
	void calculateNormal(Vertex one, Vertex two, Vertex three);

};
#endif