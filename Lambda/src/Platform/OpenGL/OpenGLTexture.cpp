#include "lmpch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

#include "glad/glad.h"



namespace Lambda
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_Path(path)
	{
		int width, height, channels;
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
	}

	void OpenGLTexture2D::Bind() const
	{
	}
}
