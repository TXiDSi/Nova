#include "Nova/Core/Log.h"
#include "OpenGLCubeMap.h"
#include "Nova/Renderer/Shader.h"
#include "stb_image.h"
#include "glad/glad.h"

namespace Nova
{
	OpenGLCubeMap::OpenGLCubeMap(const std::vector<std::string>& faces):m_Texture(0)
	{
        m_Texture = loadCubemap(faces);
	}

	void OpenGLCubeMap::Bind(unsigned int solt)
	{
        glBindTextureUnit(solt, m_Texture);
	}


	unsigned int OpenGLCubeMap::GetTextureID()
	{
		return m_Texture;
	}

    unsigned int OpenGLCubeMap::loadCubemap(std::vector<std::string> faces)
    {
        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

        int width, height, nrChannels;
        for (unsigned int i = 0; i < faces.size(); i++)
        {
            unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                    0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
                );
                stbi_image_free(data);
            }
            else
            {
                NOVA_CORE_ASSERT(false, "Cubemap texture failed to load at path: " + faces[i]);
                stbi_image_free(data);
            }
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        return textureID;
    }
}


