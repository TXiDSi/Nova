#pragma once

#include <memory>
#include "Nova/Renderer/Buffer.h"

namespace Nova {

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static std::shared_ptr<VertexArray> Create();
	};

}
