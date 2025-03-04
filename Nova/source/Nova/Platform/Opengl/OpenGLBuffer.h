#pragma once
#include <iostream>
#include "Nova/Renderer/Buffer.h"

namespace Nova {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(const void* vertices, unsigned int size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void SetPoint(unsigned int index, int size,
			ShaderDataType type, bool normalized, int stride, int offset) override;

	private:
		unsigned int m_RendererID;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int* indices, unsigned int count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual unsigned int GetCount() const { return m_Count; }
	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
	};

}
