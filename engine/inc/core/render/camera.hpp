#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "core/math/mat4.hpp"
#include "core/math/vec3.hpp"
#include "core/math/vec4.hpp"
#include "core/render/camera_settings.hpp"

namespace trq
{

class Camera
{
  public:
	Camera();
	~Camera() = default;

  public:
	auto getPosition() -> Vec3;
	auto getRotation() -> Vec3;
	auto getForward() -> Vec3;
	auto getUp() -> Vec3;
	auto getRight() -> Vec3;
	auto getProjection() -> ProjectionType;
	auto getViewport() -> Viewport;
	auto getFov() -> float;
	auto getBackgroundColor() -> Vec4;
	auto getRenderTarget() -> int;
	auto getCameraMatrix() -> Mat4;

  public:
	auto setPosition(Vec3 position) -> void;
	auto setRotation(Vec3 rotation) -> void;
	auto setProjection(ProjectionType projection) -> void;
	auto setViewport(Viewport viewport) -> void;
	auto setFov(float fovDegree) -> void;
	auto setBackgroundColor(Vec4 color) -> void;
	auto setRenderTarget(int target) -> void;

  public:
	auto updateMatrices() -> void;

  private:
	auto updateRotationMatrix() -> void;

  private:
	// Camera Properties
	Vec3 position_ = {0.f, 0.f, 10.f};
	Vec3 rotation_ = {0.f, 0.f, 0.f};

	// Projection Properties
	ProjectionType projection_ = ProjectionType::Perspective;
	Viewport viewport_ = {.x = 0.f, .y = 0.f, .width = 1.f, .height = 1.f};
	float fov_		   = 90.f;
	float far_		   = 300.f;
	float near_		   = 0.1f;

	// Drawing Properties
	Vec4 backgroundColor_ = {0.f, 0.f, 0.f, 1.f};
	int renderTarget_	  = 0;

	// Caches
	Mat4 rotationMatrix_   = Mat4::Identity();
	Mat4 projectionMatrix_ = Mat4::Identity();
	Mat4 viewMatrix_	   = Mat4::Identity();
	bool isReBuild_		   = true;

	// Default Directions
	Vec3 forward_ = {0.f, 0.f, -1.f};
	Vec3 up_	  = {0.f, 1.f, 0.f};
	Vec3 right_	  = {1.f, 0.f, 0.f};
};

} // namespace trq

#endif // !CAMERA_HPP
