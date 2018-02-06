#include "Texture.h"


	Texture::Texture(float xcoor, float ycoor, float zcoor){
		x=xcoor; 
		y=ycoor;
		 z=zcoor;};

	Texture::Texture(float xcoor, float ycoor)
	{x=xcoor;
	 y=ycoor;};

	float Texture::getX(){return x;};
	float Texture::getY(){return y;};
	float Texture::getZ(){return z;};
	void Texture::setX(float xcoor){x = xcoor;};
	void Texture::setY(float ycoor){y = ycoor;};
	void Texture::setZ(float zcoor){z = zcoor;};