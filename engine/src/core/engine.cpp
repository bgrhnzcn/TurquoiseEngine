#include "core/engine.hpp"
#include "GLFW/glfw3.h"
#include "core/asset/model_loader.hpp"
#include "core/input/input.hpp"
#include "core/math/math.hpp"
#include "core/render/program.hpp"
#include "core/render/shader.hpp"
#include "core/util/logger.hpp"
#include "core/util/time.hpp"
#include "core/window.hpp"
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <memory>
#include <numbers>
#include <filesystem>

namespace trq
{

auto Engine::init(std::filesystem::path assetPath) -> void
{
	const ktp::Logger& logger = ktp::Logger::getLogger("Initialization");

	auto& storage	  = storageRegistry_.get< MeshDataStorage >();
	auto& meshStorage = storageRegistry_.get< MeshStorage >();

	window_ = std::make_unique< Window >(800u, 600u, "GameTitle");

	logger.info("Window creation completed successfully!");

	// IMGUI
	::IMGUI_CHECKVERSION();
	imgui_ = ImGui::CreateContext();
	::ImGui_ImplGlfw_InitForOpenGL(window_->nativeHandler(), true);
	::ImGui_ImplOpenGL3_Init();
	// IMGUI

	logger.info("AssetPath: {}", assetPath.string());

	std::vector< MeshData > meshes =
		ModelLoader::loadModel(assetPath/"TestModels.fbx");

	std::vector< MeshDataStorage::HandleType > dataHandles;

	for (MeshData& mesh : meshes)
		dataHandles.push_back(storage.insert(std::move(mesh)));

	for (auto handle : dataHandles)
		logger.debug("Handle: {}", handle.getIndex());

	std::vector< MeshStorage::HandleType > meshHandles;

	for (const MeshData& data : meshes)
		meshHandles.push_back(meshStorage.insert(Mesh(data)));

	for (auto handle : meshHandles)
		logger.debug("Handle: {}", handle.getIndex());
}

auto Engine::run(std::filesystem::path assetPath) -> void
{
	Shader simple_vert =
		Shader::FromFile(assetPath.string() + "/vertex.glsl", Shader::VERTEX, "simple_vert");
	Shader simple_frag = Shader::FromFile(assetPath.string() + "/fragment.glsl",
										  Shader::FRAGMENT, "simple_frag");

	Program shaderFill(simple_vert.nativeHandler(), simple_frag.nativeHandler(),
					   "simple_shader");

	auto& storage = getRegistry().get< trq::MeshStorage >();

	Vec4 bgColor;
	while (!window_->shouldClose())
	{
		::glClearColor(bgColor.x, bgColor.y, bgColor.z, bgColor.w);
		::glClear(GL_COLOR_BUFFER_BIT);

		::ImGui_ImplOpenGL3_NewFrame();
		::ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("TestWindow");

		ImGui::Text("Background Color:");
		ImGui::ColorPicker4("Color", reinterpret_cast< float* >(&bgColor));

		ImGui::End();

		ImGui::Render();
		::ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// TODO: Create renderer and move render specific (OpenGL or Vulkan)
		// codes to there.
		Time::tick();

		auto def	= trq::Mat4::Identity();
		auto axis	= trq::Vec3(1.f, 1.f, 0.f);
		auto scale	= trq::Mat4::Scale({0.2f, 0.2f, 0.2f});
		auto rotate = trq::Mat4::Rotate(trq::Time::frameCount,
										trq::math::normalize(axis));
		auto pers	= trq::Mat4::Perspective(std::numbers::pi / 2.f, 1.f, 0.1f, 100.f);
		auto translate = trq::Mat4::Identity();

		auto model = (translate * (rotate * (scale * def)));
		shaderFill.use();
		shaderFill.setUniform("u_model", model);
		shaderFill.setUniform("u_projection", pers);

		for (auto handle : storage.getAllHandles())
		{
			auto res = storage.get(handle);
			if (res.has_value())
				(*res)->draw();
		}
		::glfwSwapBuffers(window_->nativeHandler());
		Input::inputUpdate_();
		::glfwPollEvents();
	}
}

auto Engine::shutdown() -> void
{
	isShutdown_ = true;
	::ImGui_ImplOpenGL3_Shutdown();
	::ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext(imgui_);
	window_->setClose();
	::glfwTerminate();
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
