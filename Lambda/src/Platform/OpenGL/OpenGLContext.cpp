#include "lmpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Lambda {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		LM_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		LM_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		LM_CORE_ASSERT(status, "Failed to initialize Glad!");

		LM_CORE_INFO("OpenGL Info:");
		LM_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		LM_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		LM_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

#ifdef LM_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		LM_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Lambda requires at least OpenGL version 4.5!");
#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		LM_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}