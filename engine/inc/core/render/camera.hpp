#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "core/math/vec3.hpp"
#include "core/math/vec4.hpp"
#include "core/math/mat4.hpp"
#include "core/render/camera_settings.hpp"

namespace trq
{

class Camera
{
  public:
	Camera();
	~Camera() = default;

public:
	auto setPosition(Vec3 position) -> void;
	auto setRotation(Vec3 rotation) -> void;
	auto setProjection(ProjectionType projection) -> void;
	auto setViewport(Viewport viewport) -> void;
	auto setFov(float fovDegree) -> void;
	auto setBackgroundColor(Vec4 color) -> void;
	auto setRenderTarget(int target) -> void;

  private:
	  auto updateMatrices() -> void;

  private:
	// Camera Properties
	Vec3 position_  = {0.f, 0.f, 10.f};
	Vec3 rotation_ = { 0.f, 0.f, 0.f };
	
	// Projection Properties
	ProjectionType projection_ = ProjectionType::Perspective;
	Viewport viewport_ = { .x = 0.f, .y = 0.f, .width = 1.f, .height = 1.f };
	float fov_ = 90.f;
	
	// Drawing Properties
	Vec4 backgroundColor_ = {0.f, 0.f, 0.f, 1.f};
	int renderTarget_ = 0;

	// Caches
	Mat4 projectionMatrix_ = { 1.f };
	Mat4 viewMatrix_ = { 1.f };
	bool isReBuild_ = true;
};

} // namespace trq

#endif // !CAMERA_HPP
