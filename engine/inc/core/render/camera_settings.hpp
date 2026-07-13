#ifndef CAMERA_SETTINGS_HPP
#define CAMERA_SETTINGS_HPP

enum class ProjectionType
{
	Ortographic,
	Perspective
};

struct Viewport
{
	float x = 0.f;
	float y = 0.f;
	float width = 1.f;
	float height = 1.f;
};

#endif // !CAMERA_SETTINGS_HPP
