
#include "Normal.h"
#include <vector>
using namespace std;



	float Normal::getX(){return x;};
	float Normal::getY(){return y;};
	float Normal::getZ(){return z;};
	void Normal::setX(float xcoor){x = xcoor;};
	void Normal::setY(float ycoor){y = ycoor;};
	void Normal::setZ(float zcoor){z = zcoor;};
	void Normal::calculateNormal(Vertex one, Vertex two, Vertex three){
		  vector<float> normal;
		  vector<float> U;
		  vector<float> V;
		  U.push_back(two.xcoor-one.xcoor);
		  U.push_back(two.ycoor-one.ycoor);
		  U.push_back(two.zcoor-one.zcoor);
		  V.push_back(three.xcoor-one.xcoor);
		  V.push_back(three.ycoor-one.ycoor);
		  V.push_back(three.zcoor-one.zcoor);
		  
		setX((U[1]*V[2])-(U[2]*V[2]));
		setY((U[2]*V[0])-(U[0]*V[2]));
		setZ((U[0]*V[1])-(U[1]*V[0]));
		 
}