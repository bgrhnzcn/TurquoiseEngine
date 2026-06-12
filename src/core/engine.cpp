#include "core/engine.hpp"
#include "core/asset/model_loader.hpp"
#include "core/input/input.hpp"
#include "core/render/program.hpp"
#include "core/render/shader.hpp"
#include "core/render/vertex.hpp"
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

	const Vertex vertices[] = {
		// FRONT FACE (Normal: 0, 0, 1)
		{{-0.5f, -0.5f, 0.5f},
		 {0.0f, 0.0f, 1.0f},
		 {0.0f, 0.0f, 0.0f}}, // Bottom-Left
		{{0.5f, -0.5f, 0.5f},
		 {0.0f, 0.0f, 1.0f},
		 {1.0f, 0.0f, 0.0f}}, // Bottom-Right
		{{0.5f, 0.5f, 0.5f},
		 {0.0f, 0.0f, 1.0f},
		 {1.0f, 1.0f, 0.0f}}, // Top-Right
		{{-0.5f, 0.5f, 0.5f},
		 {0.0f, 0.0f, 1.0f},
		 {0.0f, 1.0f, 0.0f}}, // Top-Left

		// BACK FACE (Normal: 0, 0, -1)
		{{0.5f, -0.5f, -0.5f},
		 {0.0f, 0.0f, -1.0f},
		 {0.0f, 0.0f, 0.0f}}, // Bottom-Left
		{{-0.5f, -0.5f, -0.5f},
		 {0.0f, 0.0f, -1.0f},
		 {1.0f, 0.0f, 0.0f}}, // Bottom-Right
		{{-0.5f, 0.5f, -0.5f},
		 {0.0f, 0.0f, -1.0f},
		 {1.0f, 1.0f, 0.0f}}, // Top-Right
		{{0.5f, 0.5f, -0.5f},
		 {0.0f, 0.0f, -1.0f},
		 {0.0f, 1.0f, 0.0f}}, // Top-Left

		// LEFT FACE (Normal: -1, 0, 0)
		{{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
		{{-0.5f, -0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
		{{-0.5f, 0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}},
		{{-0.5f, 0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},

		// RIGHT FACE (Normal: 1, 0, 0)
		{{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
		{{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
		{{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}},
		{{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},

		// TOP FACE (Normal: 0, 1, 0)
		{{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
		{{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
		{{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}},
		{{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},

		// BOTTOM FACE (Normal: 0, -1, 0)
		{{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
		{{0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
		{{0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}},
		{{-0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}}};

	const unsigned int indices[] = {
		0,	1,	2,	2,	3,	0,	// Front
		4,	5,	6,	6,	7,	4,	// Back
		8,	9,	10, 10, 11, 8,	// Left
		12, 13, 14, 14, 15, 12, // Right
		16, 17, 18, 18, 19, 16, // Top
		20, 21, 22, 22, 23, 20	// Bottom
	};

	::GLuint vao;
	::glGenVertexArrays(1, &vao);
	::glBindVertexArray(vao);

	::GLuint vbo;
	::glGenBuffers(1, &vbo);
	::glBindBuffer(GL_ARRAY_BUFFER, vbo);
	::glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices,
				   GL_STATIC_DRAW);

	::GLuint ebo;
	::glGenBuffers(1, &ebo);
	::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	::glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices,
				   GL_STATIC_DRAW);

	::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	::glEnableVertexAttribArray(0);

	::glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
							(::GLvoid*)offsetof(Vertex, nor));
	::glEnableVertexAttribArray(1);

	::glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
							(::GLvoid*)offsetof(Vertex, tex));
	::glEnableVertexAttribArray(2);

	Shader simple_vert =
		Shader::FromFile("assets/vertex.glsl", Shader::VERTEX, "simple_vert");
	Shader simple_frag = Shader::FromFile("assets/fragment.glsl",
										  Shader::FRAGMENT, "simple_frag");

	Program shaderFill(simple_vert.nativeHandler(), simple_frag.nativeHandler(),
					   "simple_shader");
}

auto Engine::run() -> void
{
	while (!window_->shouldClose())
	{
		// TODO: Create renderer and move render specific (OpenGL or Vulkan)
		// codes to there.
		Time::tick();
		::glClear(GL_COLOR_BUFFER_BIT);

		// auto def	   = lib::Mat4::Identity();
		// lib::Vec3 axis = lib::Vec3(1, 1, 0);
		// float sin	   = (std::sin(lib::Time::currTime / 50) + 1) / 2;
		// auto scale	   = lib::Mat4::Scale({0.5f, 0.5f, 0.5f});
		// auto rotate =
		//	lib::Mat4::Rotate(lib::Time::currTime, lib::normalize(axis));
		// auto pers = lib::Mat4::Perspective(std::numbers::pi / 2, 1, 0.1,
		// 100); auto translate = lib::Mat4::Identity();

		// auto model	= (translate * (rotate * (scale * def)));
		// auto normal = model;
		// shaderFill.use();
		// shaderFill.setUniform("u_model", model);
		// shaderFill.setUniform("u_perspective", pers);
		// shaderFill.setUniform("u_normal", normal);
		// shaderFill.setUniform("u_cameraDir", lib::Vec3(0, 0, -1));
		//::glBindVertexArray(vao);

		//::glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		// shaderFill.setUniform("u_color", lib::Vec4(0.4, 0.3, 0.8, 1));
		//::glEnable(GL_POLYGON_OFFSET_FILL);
		//::glPolygonOffset(1.0f, 1.0f);
		//::glDrawElements(GL_TRIANGLES, sizeof(indices) / 4, GL_UNSIGNED_INT,
		//				 : 0); :glDisable(GL_POLYGON_OFFSET_FILL);

		//::glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		////shaderFill.setUniform("u_color", lib::Vec4(0, 0, 0, 1));
		////::glDrawElements(GL_TRIANGLES, sizeof(indices) / 4, GL_UNSIGNED_INT,
		////				 : 0); :glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
