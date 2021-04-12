#include "OpenGlTest.h"

namespace cave
{
	static const GLchar* ReadShader(const char* filename);

	void GlfwErrorCallback(int error, const char* message)
	{
		GlfwErrorInterpretor(error);
		LOGE(eLogChannel::GRAPHICS, std::cout, message);
	}

	void GlfwErrorInterpretor(int error)
	{
		const char* errorMessage = "NULL";
		switch (error)
		{
		case 0:
			errorMessage = "GLFW_NO_ERROR";
			break;
		case 0x00010001:
			errorMessage = "GLFW_NOT_INITIALIZED";
			break;
		case 0x00010002:
			errorMessage = "GLFW_NO_CURRENT_CONTEXT";
			break;
		case 0x00010003:
			errorMessage = "GLFW_INVALID_ENUM";
			break;
		case 0x00010004:
			errorMessage = "GLFW_INVALID_VALUE";
			break;
		case 0x00010005:
			errorMessage = "GLFW_OUT_OF_MEMORY";
			break;
		case 0x00010006:
			errorMessage = "GLFW_API_UNAVAILABLE";
			break;
		case 0x00010007:
			errorMessage = "GLFW_VERSION_UNAVAILABLE";
			break;
		case 0x00010008:
			errorMessage = "GLFW_PLATFORM_ERROR";
			break;
		case 0x00010009:
			errorMessage = "GLFW_FORMAT_UNAVAILABLE";
			break;
		case 0x0001000A:
			errorMessage = "GLFW_NO_WINDOW_CONTEXT";
			break;
		default:
			assert(false);
			break;
		}

		if (error == 0)
		{
			LOGIF(eLogChannel::GRAPHICS, std::cout, "error code: %x, error message: %s", error, errorMessage);
		}
		else
		{
			LOGEF(eLogChannel::GRAPHICS, std::cout, "error code: %x, error message: %s", error, errorMessage);
		}
	}

	int GlfwTestMain(int argc, char* argv[])
	{
		glfwSetErrorCallback(GlfwErrorCallback);
		int errorCode = glfwInit();
		GlfwErrorInterpretor(errorCode);
		if (errorCode == GLFW_NOT_INITIALIZED)
		{
			return -1;
		}

		GLFWwindow* window = glfwCreateWindow(640, 480, "MyTitle", nullptr, nullptr);

		if (window == nullptr)
		{
			LOGE(eLogChannel::GRAPHICS, std::cout, "GLFWwindow creation failed");

			glfwTerminate();

			return -1;
		}

		// glfwMakeContextCurrent(window);
		// gl3wInit();

		// InitGame();

		// while (!glfwWindowShouldClose(window))
		// {
		// 	Draw();
		// 	glfwSwapBuffers(window);
		// 	glfwPollEvents();
		// }

		glfwDestroyWindow(window);

		glfwTerminate();

		return 0;
	}

	GLuint LoadShaders(ShaderInfo* shaders)
	{
		if (shaders == nullptr)
		{
			return 0;
		}

		GLuint program = glCreateProgram();

		ShaderInfo* entry = shaders;
		while (entry->type != GL_NONE)
		{
			GLuint shader = glCreateShader(entry->type);

			entry->shader = shader;

			const GLchar* source = ReadShader(entry->filename);
			if (source == nullptr)
			{
				for (entry = shaders; entry->type != GL_NONE; ++entry)
				{
					glDeleteShader( entry->shader );
					entry->shader = 0;
				}

				return 0;
			}

			glShaderSource(shader, 1, &source, nullptr);
			delete [] source;

			glCompileShader(shader);

			GLint compiled;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
			if (!compiled)
			{
#ifdef _DEBUG
				GLsizei len;
				glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &len );

				GLchar* log = new GLchar[len+1];
				glGetShaderInfoLog( shader, len, &len, log );
				std::cerr << "Shader compilation failed: " << log << std::endl;
				LOGA(eLogChannel::GRAPHICS, std::cout, "Shader Compilation Failed: %s", log)
				delete [] log;
#endif /* DEBUG */

				return 0;
			}

			glAttachShader(program, shader);
			
			++entry;
		}

		glLinkProgram(program);

		GLint linked;
		glGetProgramiv(program, GL_LINK_STATUS, &linked);
		if (!linked)
		{
#ifdef _DEBUG
			GLsizei len;
			glGetProgramiv( program, GL_INFO_LOG_LENGTH, &len );

			GLchar* log = new GLchar[len+1];
			glGetProgramInfoLog( program, len, &len, log );
			LOGA(eLogChannel::GRAPHICS, std::cout, "Shader Linking Failed: %s", log)
			delete [] log;
#endif /* DEBUG */

			for (entry = shaders; entry->type != GL_NONE; ++entry)
			{
				glDeleteShader(entry->shader);
				entry->shader = 0;
			}
			
			return 0;
		}

		return program;
	}

	static const GLchar* ReadShader(const char* filename)
	{
#ifdef WIN32
		FILE* infile;
		fopen_s( &infile, filename, "rb" );
#else
		FILE* infile = fopen(filename, "rb");
#endif // WIN32

		if (!infile)
		{
#ifdef _DEBUG
			LOGA(eLogChannel::GRAPHICS, std::cout, "Unable to open file '%s' ", filename)
#endif /* DEBUG */
			return NULL;
		}

		fseek(infile, 0, SEEK_END);
		int len = ftell(infile);
		fseek(infile, 0, SEEK_SET);

		GLchar* source = new GLchar[len + 1];

		fread(source, 1, len, infile);
		fclose(infile);

		source[len] = 0;

		return const_cast<const GLchar*>(source);
	}
} // namespace cave
