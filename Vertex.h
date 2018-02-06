#ifndef __VERTEX_H__
#define __VERTEX_H__

class Vertex{

public:
	Vertex();
  float xcoor;
  float ycoor;
  float zcoor;

  float getX();
  float getY();
  float getZ();
  void setX(float x);
  void setY(float y);
  void setZ(float z);



};
#endif