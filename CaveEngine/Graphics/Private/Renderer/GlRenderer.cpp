#include <cstdio>
#include <cstdlib>
#include <vector>

#include "Renderer/GlRenderer.h"

#include "lodepng.h"

namespace cave
{
	namespace Renderer
	{
		GLFLOAT3::GLFLOAT3(const GLFLOAT3&& other)
			: x(other.x)
			, y(other.y)
			, z(other.z)
		{
		}

		GLFLOAT3& GLFLOAT3::operator=(const GLFLOAT3&& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;

			return *this;
		}

		constexpr GLFLOAT3::GLFLOAT3(float inX, float inY, float inZ)
			: x(inX)
			, y(inY)
			, z(inZ)
		{
		}

		GLFLOAT3::GLFLOAT3(float* array)
			: x(array[0])
			, y(array[1])
			, z(array[2])
		{
		}

		struct SimpleVertex
		{
			GLFLOAT3 position;
		};

		//--------------------------------------------------------------------------------------
		// Global Variables
		//--------------------------------------------------------------------------------------
		// HINSTANCE gHInstance = nullptr;
		// HWND gHWindow = nullptr;
		GLFWwindow* gWindow = nullptr;
		// D3D_DRIVER_TYPE gDriverType = D3D_DRIVER_TYPE_NULL;
		// D3D_FEATURE_LEVEL gFeatureLevel = D3D_FEATURE_LEVEL_11_0;
		// ID3D11Device* gD3dDevice = nullptr;
		// ID3D11Device1* gD3dDevice1 = nullptr;
		// ID3D11DeviceContext* gImmediateContext = nullptr;
		// ID3D11DeviceContext1* gImmediateContext1 = nullptr;
		// IDXGISwapChain* gSwapChain = nullptr;
		// IDXGISwapChain1* gSwapChain1 = nullptr;
		// ID3D11RenderTargetView* gRenderTargetView = nullptr;
		// ID3D11VertexShader* gVertexShader = nullptr;
		// ID3D11PixelShader* gPixelShader = nullptr;
		// ID3D11InputLayout* gVertexLayout = nullptr;
		// ID3D11Buffer* gVertexBuffer = nullptr;
		GLuint gProgram = 0u;

		uint8_t* gBackground = nullptr;
		uint32_t gBackgroundWidth = 0u;
		uint32_t gBackgroundHeight = 0u;
		uint32_t gBackgroundSampler = 0u;
		// std::vector<uint8_t> gBackground;

		GLuint gVertexArrayObjects[VERTEX_ARRAY_OBJECTS_COUNT];
		GLuint gBuffers[BUFFER_COUNT];
		GLuint gTextures[TEXTURE_COUNT];

		const GLuint gNumVertices = 3;

		//--------------------------------------------------------------------------------------
		// Forward declarations
		//--------------------------------------------------------------------------------------
		void CleanupDevice();
		int32_t CompileShaderFromFile(ShaderInfo* shaders);
		void ErrorCallback(int errorCode, const char* description);
		int32_t InitWindow(const char* title);
		int32_t InitDevice();
		GLuint LoadShaders(ShaderInfo* shaders);
		static const GLchar* ReadShader(const char* filename);
		void Render();

		//--------------------------------------------------------------------------------------
		// Clean up the objects we've created
		//--------------------------------------------------------------------------------------
		void CleanupDevice()
		{
			glDeleteTextures(TEXTURE_COUNT, &gTextures[TEXTURE]);

			if (gBackground)
			{
				free(gBackground);
			}

			glfwDestroyWindow(gWindow);

			glfwTerminate();
			// if (gImmediateContext)
			// {
			// 	gImmediateContext->ClearState();
			// }

			// if (gVertexBuffer)
			// {
			// 	gVertexBuffer->Release();
			// }
			// if (gVertexLayout)
			// {
			// 	gVertexLayout->Release();
			// }
			// if (gVertexShader)
			// {
			// 	gVertexShader->Release();
			// }
			// if (gPixelShader)
			// {
			// 	gPixelShader->Release();
			// }
			// if (gRenderTargetView)
			// {
			// 	gRenderTargetView->Release();
			// }
			// if (gSwapChain1)
			// {
			// 	gSwapChain1->Release();
			// }
			// if (gSwapChain)
			// {
			// 	gSwapChain->Release();
			// }
			// if (gImmediateContext1)
			// {
			// 	gImmediateContext1->Release();
			// }
			// if (gImmediateContext)
			// {
			// 	gImmediateContext->Release();
			// }
			// if (gD3dDevice1)
			// {
			// 	gD3dDevice1->Release();
			// }
			// if (gD3dDevice)
			// {
			// 	gD3dDevice->Release();
			// }
		}

		//--------------------------------------------------------------------------------------
		// Helper for compiling shaders with D3DCompile
		//
		// With VS 11, we could load up prebuilt .cso files instead...
		//--------------------------------------------------------------------------------------
		int32_t CompileShaderFromFile(ShaderInfo* shaders)
		{
			gProgram = LoadShaders(shaders);
			glUseProgram(gProgram);

			return GLFW_NO_ERROR;
		}

		//--------------------------------------------------------------------------------------
		// Destroy Renderer
		//--------------------------------------------------------------------------------------
		void Destroy()
		{
			CleanupDevice();
		}

		void ErrorCallback(int errorCode, const char* description)
		{
			LOGE(eLogChannel::GRAPHICS, std::cerr, description);
		}

		bool GlfwWindowShouldClose()
		{
			return static_cast<bool>(glfwWindowShouldClose(gWindow));
		}

		//--------------------------------------------------------------------------------------
		// Initialize Renderer
		//--------------------------------------------------------------------------------------
		int32_t Init(const char* title)
		{
			glfwSetErrorCallback(ErrorCallback);

			glfwInit();

			int error = InitWindow(title);
			if (FAILED(error))
			{
				return error;
			}

			error = InitDevice();
			if (FAILED(error))
			{
				Destroy();
				return error;
			}

			return error;
		}

		//--------------------------------------------------------------------------------------
		// Create OpenGL device and swap chain
		//--------------------------------------------------------------------------------------
		// Used to set up data for use later in the program
			// vertext information
			// image data
		// Specify shaders
		// Shader Plumbing
		int32_t InitDevice()
		{
			int32_t error = GLFW_NO_ERROR;

			// GLFWmonitor* primary = glfwGetPrimaryMonitor();
			// const GLFWvidmode* rect = glfwGetVideoMode(primary);
			// int32_t width = rect->width;
			// int32_t height = rect->height;
			// Create vertex buffer
			
			// SimpleVertex vertices[] = {
			// 	GLFLOAT3(0.0f, 0.5f, 0.5f),
			// 	GLFLOAT3(0.5f, -0.5f, 0.5f),
			// 	GLFLOAT3(-0.5f, -0.5f, 0.5f),
			// };

			// static const float vertices[] = {
			// 	 0.0f,  0.5f, 0.5f,
			// 	 0.5f, -0.5f, 0.5f,
			// 	-0.5f, -0.5f, 0.5f,

			// 	0.5f, 1.0f,
			// 	1.0f, 0.0f,
			// 	0.0f, 0.0f,
			// };

			static const float vertices[] = {
				 0.0f,  0.5f, 0.5f,		0.5f, 1.0f,
				 0.5f, -0.5f, 0.5f,		1.0f, 0.0f,
				-0.5f, -0.5f, 0.5f,		0.0f, 0.0f,
			};

			glCreateBuffers(BUFFER_COUNT, gBuffers);
			glBindBuffer(GL_ARRAY_BUFFER, BUFFER_COUNT);

			// Preparing to Send Data to OpenGL
			// All data must be stored in buffer objects (chunks of memory managed by OpenGL)
			// Common way is to specify the data at the same time as you specify the buffer's size
			glNamedBufferStorage(gBuffers[ARRAY_BUFFER], sizeof(vertices), vertices, 0);
			
			size_t projectDirLength = strlen(PROJECT_DIR);
			size_t shaderFileNameLength = strlen("/CaveEngine/Graphics/Shader/triangles.vert");
			char vertexShaderFile[projectDirLength + shaderFileNameLength + 1] = { '\0', };
			char fragmentShaderFile[projectDirLength + shaderFileNameLength + 1] = { '\0', };
			strncpy(vertexShaderFile, PROJECT_DIR, projectDirLength);
			strncat(vertexShaderFile, "/CaveEngine/Graphics/Shader/triangles.vert", shaderFileNameLength);
			strncpy(fragmentShaderFile, PROJECT_DIR, projectDirLength);
			strncat(fragmentShaderFile, "/CaveEngine/Graphics/Shader/triangles.frag", shaderFileNameLength);
			
			ShaderInfo shaders[] = {
				{ GL_VERTEX_SHADER, vertexShaderFile },
				{ GL_FRAGMENT_SHADER, fragmentShaderFile },
				{ GL_NONE, nullptr }
			};

			error = CompileShaderFromFile(shaders);
			if (FAILED(error))
			{
				LOGE(eLogChannel::GRAPHICS, std::cout, "The shader files cannot be compiled.");
				return error;
			}

			// uint32_t width = 0u;
			// uint32_t height = 0u;
			// error = lodepng_decode24_file(&gBackground, &width, &height, "Graphics/Resource/brick_2.png");
			error = lodepng_decode24_file(&gBackground, &gBackgroundWidth, &gBackgroundHeight, "Graphics/Resource/brick_2.png");
			if (error != 0)
			{
				LOGEF(eLogChannel::GRAPHICS, std::cout, "The png file cannot be loaded. Error Code: %u", error);
				return error;
			}

			// LOGDF(eLogChannel::GRAPHICS, std::cout, "vector size: %lu", gBackground.size());
			LOGDF(eLogChannel::GRAPHICS, std::cout, "image width: %u", gBackgroundWidth);
			LOGDF(eLogChannel::GRAPHICS, std::cout, "image height: %u", gBackgroundHeight);
			glCreateTextures(GL_TEXTURE_2D, TEXTURE_COUNT, &gTextures[TEXTURE]);
			LOGDF(eLogChannel::GRAPHICS, std::cout, "texture index: %u", gTextures[TEXTURE]);
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glCreateTextures error code: 0x%x", glGetError());

			glBindTextureUnit(0, gTextures[TEXTURE]);

			if (glGetUniformLocation(gProgram, "tex") < 0)
			{
				LOGEF(eLogChannel::GRAPHICS, std::cerr, "Failed to get uniform location: %s, error code: 0x%x", "tex", glGetError());
			}

			glTextureParameteri(gTextures[TEXTURE], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glTextureParameteri error code: 0x%x", glGetError());
			glTextureParameteri(gTextures[TEXTURE], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTextureParameteri(gTextures[TEXTURE], GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTextureParameteri(gTextures[TEXTURE], GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glTextureParameteri error code: 0x%x", glGetError());

			LOGEF(eLogChannel::GRAPHICS, std::cerr, "Width: %u Height: %u", gBackgroundWidth, gBackgroundHeight);
			glTextureStorage2D(gTextures[TEXTURE], 1, GL_RGB8, gBackgroundWidth, gBackgroundHeight);
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glTextureStorage2D error code: 0x%x", glGetError());
			glTextureSubImage2D(gTextures[TEXTURE], 0, 0, 0, gBackgroundWidth, gBackgroundHeight, GL_BGR, GL_UNSIGNED_BYTE, gBackground);
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glTextureSubImage2D error code: 0x%x", glGetError());
			// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, gBackgroundWidth, gBackgroundHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, gBackground);
			glGenerateTextureMipmap(gTextures[TEXTURE]);
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glGenerateTextureMipmap error code: 0x%x", glGetError());

			GLint texLocation = glGetUniformLocation(gProgram, "tex");
			LOGDF(eLogChannel::GRAPHICS, std::cout, "texture location: %u", texLocation);
			
			if (texLocation >= 0)
			{
				glUniform1i(texLocation, 0);
			}

			// glCreateSamplers(1, &gBackgroundSampler);
			// LOGDF(eLogChannel::GRAPHICS, std::cout, "sampler: %u", gBackgroundSampler);
			// glBindSampler(gBackgroundIndex, gBackgroundSampler);
			free(gBackground);
			gBackground = nullptr;
			
			glGenVertexArrays(VERTEX_ARRAY_OBJECTS_COUNT, gVertexArrayObjects);
			glBindVertexArray(gVertexArrayObjects[TRIANGLES]);
			glBindBuffer(GL_ARRAY_BUFFER, gBuffers[ARRAY_BUFFER]);
			// glVertexAttribPointer(V_POSITION, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
			glVertexAttribPointer(V_POSITION, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), BUFFER_OFFSET(0));
			glEnableVertexAttribArray(V_POSITION);

			glVertexAttribPointer(V_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), BUFFER_OFFSET(3 * sizeof(float)));
			glEnableVertexAttribArray(V_TEX_COORD);

			return GLFW_NO_ERROR;
		}

		//--------------------------------------------------------------------------------------
		// Register class and create window
		//--------------------------------------------------------------------------------------
		int32_t InitWindow(const char* title)
		{
			// Register class

			// Create window
			gWindow = glfwCreateWindow(800, 600, title, nullptr, nullptr);
			if (gWindow == nullptr)
			{
				return glfwGetError(nullptr);
			}

			glfwMakeContextCurrent(gWindow);
			gl3wInit();

			int32_t error = glfwGetError(nullptr);
			return error;
		}

		//--------------------------------------------------------------------------------------
		// Render a frame
		//--------------------------------------------------------------------------------------
		void Render()
		{
			static const float midnightBlue[] = { 0.098039225f, 0.098039225f, 0.439215720f, 0.000000000f };

			glClearBufferfv(GL_COLOR, 0, midnightBlue);

			glBindTextureUnit(GL_TEXTURE_2D, gTextures[TEXTURE]);

			glBindVertexArray(gVertexArrayObjects[TRIANGLES]);

			// Sending Data to OpenGL
				// Drawing == transferring vertex data to the OpenGL server
				// vertex == bundle of data values that are processed together
					// almost always includes positional data
					// values needed to determine the pixel's final color
			glDrawArrays(GL_TRIANGLES, 0, gNumVertices);
			// glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, 0);

			glfwSwapBuffers(gWindow);
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
#ifdef __Debug__
				GLsizei len;
				glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &len );

				GLchar* log = new GLchar[len+1];
				glGetShaderInfoLog( shader, len, &len, log );
				std::cerr << "Shader compilation failed: " << log << std::endl;
				LOGAF(eLogChannel::GRAPHICS, std::cout, "%s Compilation Failed: %s", entry->filename, log);
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
#ifdef __Debug__
				GLsizei len;
				glGetProgramiv( program, GL_INFO_LOG_LENGTH, &len );

				GLchar* log = new GLchar[len+1];
				glGetProgramInfoLog( program, len, &len, log );
				LOGAF(eLogChannel::GRAPHICS, std::cout, "Shader Linking Failed: %s", log);
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
#ifdef __WIN32__
			FILE* infile;
			fopen_s( &infile, filename, "rb" );
#else
			FILE* infile = fopen(filename, "rb");
#endif // __WIN32__

			if (!infile)
			{
#ifdef _DEBUG
				LOGAF(eLogChannel::GRAPHICS, std::cout, "Unable to open file '%s' ", filename);
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
	}
}