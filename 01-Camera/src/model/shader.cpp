#include "shader.h"


Shader::~Shader() {
    // Cleanup resources if necessary
}

void Shader::initialize() {
    loadShadersAndCreateProgram();
    bindAttributesAndLink();
    shaderObjectErrorChecking();
}

void Shader::loadShadersAndCreateProgram() {
    createAndCompileShader(readShader(pVSFileName), GL_VERTEX_SHADER);
    createAndCompileShader(readShader(pFSFileName), GL_FRAGMENT_SHADER);
}

GLuint Shader::getObject() {
    return shaderProgramObject;
}

void Shader::bindAttributesAndLink() {
    glBindAttribLocation(shaderProgramObject, ASM_ATTRIBUTE_POSITION, "a_position");
    glBindAttribLocation(shaderProgramObject, ASM_ATTRIBUTE_COLOR, "a_color");
    glLinkProgram(shaderProgramObject);
}

char* Shader::readShader(const char* fileName) {
	    FILE *fp;
		long size = 0;
		char* shaderContent;
		
		fp = fopen(fileName, "rb");
		if(fp == NULL) {
			return "";
		}
		fseek(fp, 0L, SEEK_END);
		size = ftell(fp)+1;
		fclose(fp);

		fp = fopen(fileName, "r");
		shaderContent =  (char*)memset(malloc(size), '\0', size);
		fread(shaderContent, 1, size-1, fp);
		fclose(fp);

		return shaderContent;
}

void Shader::unitializeShader() {
	fclose(file);
    // Shader unintialization code
    if (shaderProgramObject)
		{

			glUseProgram(shaderProgramObject);

			GLsizei numAttachedShaders;
			glGetProgramiv(shaderProgramObject, GL_ATTACHED_SHADERS, &numAttachedShaders);

			GLuint* shaderObjects = NULL;
			shaderObjects = (GLuint*)malloc(numAttachedShaders * sizeof(GLuint));

			// filling this empty buffer 
			glGetAttachedShaders(shaderProgramObject, numAttachedShaders, &numAttachedShaders, shaderObjects);
			for (GLsizei i = 0; i < numAttachedShaders; i++)
			{
				glDetachShader(shaderProgramObject, shaderObjects[i]);
				glDeleteShader(shaderObjects[i]);
				shaderObjects[i] = 0;
			}

			free(shaderObjects);
			shaderObjects = NULL;
			glUseProgram(0);
			glDeleteProgram(shaderProgramObject);
			shaderProgramObject = 0;
		}
}

void Shader::createAndCompileShader(const GLchar* shaderString, GLenum shaderType) {
            GLint status;
			GLint infoLogLength;
			char* _log = NULL;
			GLuint shaderObject = glCreateShader(shaderType);
			if (shaderObject ==0)
			{
                
				logger.debug("Error creating shader type", shaderType);
				exit(0);
			}
			glShaderSource(shaderObject, 1, (const GLchar**)&shaderString, NULL);
			glCompileShader(shaderObject);
			glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &status);
			if (status == GL_FALSE)
			{
				glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);
				if (infoLogLength > 0)
				{
					_log = (char*)malloc(infoLogLength);
					if (_log != NULL)
					{
						GLsizei written;
						glGetShaderInfoLog(shaderObject, infoLogLength, &written, _log);
						logger.debug(  "shader type:",shaderType);
						logger.debug(  "Compilation log:", _log);
						free(_log);
						unitializeShader();
					}
				}
			}
			glAttachShader(shaderProgramObject, shaderObject);
}

void Shader::shaderObjectErrorChecking() {
    // Error checking for shader program
    	GLint status;
		GLint infoLogLength;
		char* log = NULL;


		glGetProgramiv(shaderProgramObject, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			glGetProgramiv(shaderProgramObject, GL_INFO_LOG_LENGTH, &infoLogLength);
			if (infoLogLength > 0)
			{
				log = (char*)malloc(infoLogLength);
				if (log != NULL)
				{
					GLsizei written;
					glGetProgramInfoLog(shaderProgramObject, infoLogLength, &written, log);
					logger.debug("Shader Program Link log: ", log);
					free(log);
					unitializeShader();

				}
			}
		}
}

void Shader::getAllUniformLocations(const std::string& filename) {
    // Code to get uniform locations and write to file
		std::ofstream outputFile("Uniform.log");

		if (!outputFile.is_open()) {

			return;
		}
		GLint numUniforms = 0;
		glGetProgramiv(shaderProgramObject, GL_ACTIVE_UNIFORMS, &numUniforms);

		std::vector<GLchar> nameData(256);
		GLsizei length = 0;
		GLint size = 0;
		GLenum type = 0;

		for (int i = 0; i < numUniforms; ++i) {
			glGetActiveUniform(shaderProgramObject, i, nameData.size(), &length, &size, &type, &nameData[0]);
			std::string name((char*)&nameData[0], length);

			GLint location = glGetUniformLocation(shaderProgramObject, name.c_str());
			outputFile << "Uniform: " << name << ", Location: " << location << std::endl;
		}

		outputFile.close();
	}

