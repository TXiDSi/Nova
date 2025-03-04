#pragma once

#include <iostream>
#include <vector>

namespace Nova {

	enum class ShaderDataType
	{
		None = 0, Float, Int, Bool
	};

	

	
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetPoint(unsigned int index, int size,
			ShaderDataType type, bool normalized, int stride, int offset) = 0;

		static std::shared_ptr<VertexBuffer> Create(const void* vertices, unsigned int size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static std::shared_ptr <IndexBuffer> Create(unsigned int* indices, unsigned int size);
	};

}