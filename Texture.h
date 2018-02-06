// STL
#ifndef TEXTURE_H
#define TEXTURE_H

class Texture{

private:

	float x;
	float y;
	float z;

public:
	Texture(){};
	Texture(float xcoor, float ycoor, float zcoor);
	Texture(float xcoor, float ycoor);
	float getX();
	float getY();
	float getZ();
	void setX(float xcoor);
	void setY(float ycoor);
	void setZ(float zcoor);

};
#endif