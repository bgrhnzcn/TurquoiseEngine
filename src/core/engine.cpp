#include "core/engine.hpp"
#include "core/asset/model_loader.hpp"
#include "core/input/input.hpp"
#include "core/math/math.hpp"
#include "core/render/program.hpp"
#include "core/render/shader.hpp"
#include "core/util/logger.hpp"
#include "core/util/time.hpp"
#include "core/window.hpp"
#include <memory>

namespace trq
{

auto Engine::init() -> void
{
	const ktp::Logger& logger = ktp::Logger::getLogger("Initialization");

	auto& storage	  = storageRegistry_.get< trq::MeshDataStorage >();
	auto& meshStorage = storageRegistry_.get< trq::MeshStorage >();

	window_ = std::make_unique< Window >(800u, 600u, "GameTitle");

	logger.info("Window creation completed successfully!");

	std::vector< trq::MeshData > meshes =
		trq::ModelLoader::loadModel("assets/TestModels.fbx");

	std::vector< MeshDataStorage::HandleType > dataHandles;

	for (trq::MeshData& mesh : meshes)
		dataHandles.push_back(storage.insert(std::move(mesh)));

	for (auto handle : dataHandles)
		logger.debug("Handle: {}", handle.getIndex());

	std::vector< MeshStorage::HandleType > meshHandles;

	for (const MeshData& data : meshes)
		meshHandles.push_back(meshStorage.insert(Mesh(data)));

	for (auto handle : meshHandles)
		logger.debug("Handle: {}", handle.getIndex());
}

auto Engine::run() -> void
{
	Shader simple_vert =
		Shader::FromFile("assets/vertex.glsl", Shader::VERTEX, "simple_vert");
	Shader simple_frag = Shader::FromFile("assets/fragment.glsl",
										  Shader::FRAGMENT, "simple_frag");

	Program shaderFill(simple_vert.nativeHandler(), simple_frag.nativeHandler(),
					   "simple_shader");

	auto& storage = getRegistry().get< trq::MeshStorage >();

	while (!window_->shouldClose())
	{
		// TODO: Create renderer and move render specific (OpenGL or Vulkan)
		// codes to there.
		Time::tick();
		::glClear(GL_COLOR_BUFFER_BIT);

		auto def	= trq::Mat4::Identity();
		auto axis	= trq::Vec3(1, 1, 0);
		auto scale	= trq::Mat4::Scale({0.2f, 0.2f, 0.2f});
		auto rotate = trq::Mat4::Rotate(trq::Time::frameCount,
										trq::math::normalize(axis));
		auto pers	= trq::Mat4::Perspective(std::numbers::pi / 2, 1, 0.1, 100);
		auto translate = trq::Mat4::Identity();

		auto model = (translate * (rotate * (scale * def)));
		shaderFill.use();
		shaderFill.setUniform("u_model", model);
		shaderFill.setUniform("u_projection", pers);

		for (auto handle : storage.getAllHandles())
		{
			auto res = storage.get(handle);
			if (res.has_value())
				res->draw();
		}
		this->update();
		::glfwSwapBuffers(window_->nativeHandler());
		Input::inputUpdate_();
		::glfwPollEvents();
	}
}

auto Engine::shutdown() -> void
{
	isShutdown_ = true;
	window_->setClose();
}

auto Engine::shouldShutdown() -> bool
{
	return isShutdown_;
}

auto Engine::getRegistry() -> StorageRegistry&
{
	return storageRegistry_;
}

} // namespace trq
