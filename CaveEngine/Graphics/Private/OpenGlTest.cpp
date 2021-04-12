//#include "OpenGlTest.h"
//
//namespace cave
//{
//	static const GLchar* ReadShader(const char* filename);
//
//	GLuint LoadShaders(ShaderInfo* shaders)
//	{
//		if (shaders == nullptr)
//		{
//			return 0;
//		}
//
//		GLuint program = glCreateProgram();
//
//		ShaderInfo* entry = shaders;
//		while (entry->type != GL_NONE)
//		{
//			GLuint shader = glCreateShader(entry->type);
//
//			entry->shader = shader;
//
//			const GLchar* source = ReadShader(entry->filename);
//			if (source == nullptr)
//			{
//				for (entry = shaders; entry->type != GL_NONE; ++entry)
//				{
//					glDeleteShader( entry->shader );
//					entry->shader = 0;
//				}
//
//				return 0;
//			}
//
//			glShaderSource(shader, 1, &source, nullptr);
//			delete [] source;
//
//			glCompileShader(shader);
//
//			GLint compiled;
//			glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
//			if (!compiled)
//			{
//#ifdef _DEBUG
//				GLsizei len;
//				glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &len );
//
//				GLchar* log = new GLchar[len+1];
//				glGetShaderInfoLog( shader, len, &len, log );
//				std::cerr << "Shader compilation failed: " << log << std::endl;
//				LOGA(eLogChannel::GRAPHICS, std::cout, "Shader Compilation Failed: %s", log)
//				delete [] log;
//#endif /* DEBUG */
//
//				return 0;
//			}
//
//			glAttachShader(program, shader);
//			
//			++entry;
//		}
//
//		glLinkProgram(program);
//
//		GLint linked;
//		glGetProgramiv(program, GL_LINK_STATUS, &linked);
//		if (!linked)
//		{
//#ifdef _DEBUG
//			GLsizei len;
//			glGetProgramiv( program, GL_INFO_LOG_LENGTH, &len );
//
//			GLchar* log = new GLchar[len+1];
//			glGetProgramInfoLog( program, len, &len, log );
//			LOGA(eLogChannel::GRAPHICS, std::cout, "Shader Linking Failed: %s", log)
//			delete [] log;
//#endif /* DEBUG */
//
//			for (entry = shaders; entry->type != GL_NONE; ++entry)
//			{
//				glDeleteShader(entry->shader);
//				entry->shader = 0;
//			}
//			
//			return 0;
//		}
//
//		return program;
//	}
//
//	static const GLchar* ReadShader(const char* filename)
//	{
//#ifdef WIN32
//		FILE* infile;
//		fopen_s( &infile, filename, "rb" );
//#else
//		FILE* infile = fopen(filename, "rb");
//#endif // WIN32
//
//		if (!infile)
//		{
//#ifdef _DEBUG
//			LOGA(eLogChannel::GRAPHICS, std::cout, "Unable to open file '%s' ", filename)
//#endif /* DEBUG */
//			return NULL;
//		}
//
//		fseek(infile, 0, SEEK_END);
//		int len = ftell(infile);
//		fseek(infile, 0, SEEK_SET);
//
//		GLchar* source = new GLchar[len + 1];
//
//		fread(source, 1, len, infile);
//		fclose(infile);
//
//		source[len] = 0;
//
//		return const_cast<const GLchar*>(source);
//	}
//} // namespace cave
