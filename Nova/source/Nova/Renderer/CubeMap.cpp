#include "CubeMap.h"
#include "NovaPch.h"
#include "Nova/Platform/Opengl/OpenGLCubeMap.h"

namespace Nova
{
    std::shared_ptr<CubeMap> CubeMap::Create(const std::vector<std::string>& faces)
    {
        return std::make_shared<OpenGLCubeMap>(faces);
    }
}
