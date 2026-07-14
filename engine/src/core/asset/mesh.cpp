#include "core/asset/mesh.hpp"
#include "core/render/program.hpp"
#include <glad/gl.h>

namespace trq
{

Mesh::Mesh(Mesh&& other) noexcept
	: vao_(other.vao_), vbo_(other.vbo_), ebo_(other.ebo_),
	  elemCount_(other.elemCount_)
{
	other.vao_		 = 0;
	other.vbo_		 = 0;
	other.ebo_		 = 0;
	other.elemCount_ = 0;
}

auto Mesh::operator=(Mesh&& other) noexcept -> Mesh&
{
	if (&other != this)
	{
		if (vbo_ != 0)
			::glDeleteBuffers(1, &vbo_);
		if (ebo_ != 0)
			::glDeleteBuffers(1, &ebo_);
		if (vao_ != 0)
			::glDeleteVertexArrays(1, &vao_);

		vao_	   = other.vao_;
		vbo_	   = other.vbo_;
		ebo_	   = other.ebo_;
		elemCount_ = other.elemCount_;

		other.vao_		 = 0;
		other.vbo_		 = 0;
		other.ebo_		 = 0;
		other.elemCount_ = 0;
	}
	return *this;
}

Mesh::~Mesh()
{
	::glDeleteBuffers(1, &vbo_);
	::glDeleteBuffers(1, &ebo_);
	::glDeleteVertexArrays(1, &vao_);
}
Mesh::Mesh(const MeshData& data)
{
	elemCount_ = data.indices_.size();
	::glGenVertexArrays(1, &vao_);
	::glBindVertexArray(vao_);

	::glGenBuffers(1, &vbo_);
	::glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	::glBufferData(GL_ARRAY_BUFFER, data.vertices_.size() * sizeof(Vertex),
				   data.vertices_.data(), GL_STATIC_DRAW);

	::glGenBuffers(1, &ebo_);
	::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
	::glBufferData(GL_ELEMENT_ARRAY_BUFFER, elemCount_ * sizeof(std::uint32_t),
				   data.indices_.data(), GL_STATIC_DRAW);

	::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	::glEnableVertexAttribArray(0);

	::glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
							(::GLvoid*)offsetof(Vertex, nor));
	::glEnableVertexAttribArray(1);

	::glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
							(::GLvoid*)offsetof(Vertex, tex));
	::glEnableVertexAttribArray(2);
	::glBindVertexArray(0);
}

auto Mesh::draw(Program program) -> void
{
	program.use();
	::glBindVertexArray(vao_);
	::glDrawElements(GL_TRIANGLES, elemCount_, GL_UNSIGNED_INT, nullptr);
}

auto Mesh::drawWireframe() -> void
{
	// TODO: Debug wireframe draw.
}

} // namespace trq
