#include "core/render/camera.hpp"
#include <X11/extensions/randr.h>

namespace trq
{

Camera::Camera()
{
}

auto Camera::getPosition() -> Vec3
{
	return position_;
}
auto Camera::getRotation() -> Vec3
{
	return rotation_;
}
auto Camera::getForward() -> Vec3
{
	// XYZ
	Vec4 result =
		rotationMatrix_ * Vec4(forward_.x, forward_.y, forward_.z, 0.f);

	return Vec3(result.x, result.y, result.z);
}
auto Camera::getUp() -> Vec3
{
	// XYZ
	Vec4 result = rotationMatrix_ * Vec4(up_.x, up_.y, up_.z, 0.f);

	return Vec3(result.x, result.y, result.z);
}
auto Camera::getRight() -> Vec3
{
	// XYZ
	Vec4 result = rotationMatrix_ * Vec4(right_.x, right_.y, right_.z, 0.f);

	return Vec3(result.x, result.y, result.z);
}
auto Camera::getProjection() -> ProjectionType
{
	return projection_;
}
auto Camera::getViewport() -> Viewport
{
	return viewport_;
}
auto Camera::getFov() -> float
{
	return fov_;
}
auto Camera::getBackgroundColor() -> Vec4
{
	return backgroundColor_;
}
auto Camera::getRenderTarget() -> int
{
	return renderTarget_;
}

auto Camera::getCameraMatrix() -> Mat4
{
	return projectionMatrix_ * viewMatrix_;
}

auto Camera::setPosition(Vec3 position) -> void
{
	position_  = position;
	isReBuild_ = true;
}

auto Camera::setRotation(Vec3 rotation) -> void
{
	rotation_  = rotation;
	isReBuild_ = true;
	updateRotationMatrix();
}

auto Camera::setProjection(ProjectionType projection) -> void
{
	projection_ = projection;
	isReBuild_	= true;
}

auto Camera::setViewport(Viewport viewport) -> void
{
	viewport_  = viewport;
	isReBuild_ = true;
}

auto Camera::setFov(float fovDegree) -> void
{
	fov_	   = fovDegree;
	isReBuild_ = true;
}

auto Camera::setBackgroundColor(Vec4 color) -> void
{
	backgroundColor_ = color;
}

auto Camera::setRenderTarget(int target) -> void
{
	renderTarget_ = target;
}

auto Camera::updateMatrices() -> void
{
	if (!isReBuild_)
		return;

	viewMatrix_ = Mat4::Translate(position_ * -1) * rotationMatrix_.transpose();
	if (projection_ == ProjectionType::Perspective)
	{
		projectionMatrix_ = Mat4::Perspective(
			fov_, viewport_.width / viewport_.height, near_, far_);
	}
	// TODO: Will update matrices to new configurations.
}

auto Camera::updateRotationMatrix() -> void
{
	Mat4 rotationX = Mat4::Rotate(rotation_.x, Vec3(1.f, 0.f, 0.f));
	Mat4 rotationY = Mat4::Rotate(rotation_.y, Vec3(0.f, 1.f, 0.f));
	Mat4 rotationZ = Mat4::Rotate(rotation_.z, Vec3(0.f, 0.f, 1.f));

	rotationMatrix_ = rotationX * rotationY * rotationZ;
}

} // namespace trq
