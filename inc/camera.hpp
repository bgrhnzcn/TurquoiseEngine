#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "vec3.hpp"

class Camera
{
  private:
	Vec3 position  = {0.f, 0.f, 10.f};
	Vec3 direction = {0.f, 0.f, -1.f};
	float fov = 90.f;

	float getFov();
	Vec3 getPosition();
	Vec3 getDirection();
};

#endif // !CAMERA_HPP
