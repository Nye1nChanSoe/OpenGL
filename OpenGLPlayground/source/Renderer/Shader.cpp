#pragma warning(push)
#pragma warning(disable: 4806)

#include "Shader.h"

#include <fstream>
#include <filesystem>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "Core.h"


static GLenum ShaderTypeFromString(const std::string& type)
{
	if (type == "vertex")
		return GL_VERTEX_SHADER;
	if (type == "fragment" || type == "pixel")
		return GL_FRAGMENT_SHADER;

	// TODO: Support more shader types in the future!
	glAssert(false, "Unknown shader type!");
	return NULL;
}

Shader::Shader(const std::string& filepath)
	: m_RendererID(0)
{
	std::string source = ReadFile(filepath);
	std::unordered_map<GLenum, std::string> shaderType = PreProcess(source);
	Compile(shaderType);

	// assets/shaders/textures.glsl
	std::filesystem::path name = filepath;
	m_Name = name.stem().string();
}

Shader::Shader(const std::string& name, const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
	: m_RendererID(0), m_Name(name)
{
	std::unordered_map<GLenum, std::string> shaderSource;
	shaderSource[GL_VERTEX_SHADER] = vertexShaderSource;
	shaderSource[GL_FRAGMENT_SHADER] = fragmentShaderSource;
	Compile(shaderSource);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::UseProgram() const
{
	glUseProgram(m_RendererID);
}


void Shader::UnBind() const
{
	glUseProgram(0);
}

void Shader::DeleteProgram() const
{
	glUseProgram(0);
}

std::string Shader::ReadFile(const std::string& filepath)
{
	std::ifstream stream(filepath, std::ios::in | std::ios::binary);
	std::string result;

	if (stream.good())
	{
		stream.seekg(0, std::ios::end);  // set the postiion of the pointer at the eof
		result.resize(stream.tellg());   // get the size of the string by getting the pointer at the eof
		stream.seekg(0, std::ios::beg);	 // set the position of the pointer at the beginning 
		stream.read(&result[0], result.size());

		stream.close();
	}
	else
	{
		ERROR("Failed to open the file '%s'", filepath.c_str());
	}
	return result;
}

std::unordered_map<GLenum, std::string> Shader::PreProcess(const std::string& source)
{
	std::unordered_map<GLenum, std::string> shaderSource;

	const char* typeToken = "#type";
	size_t typeTokenLength = strlen(typeToken);
	size_t pos = source.find(typeToken, 0);

	while (pos != std::string::npos)
	{
		size_t eol = source.find_first_of("\r\n", pos);
		size_t begin = pos + typeTokenLength + 1;
		std::string type = source.substr(begin, eol - begin);

		size_t nextLine = source.find_first_not_of("\r\n", eol);
		pos = source.find(typeToken, nextLine);
		shaderSource[ShaderTypeFromString(type)] = source.substr(nextLine, pos - nextLine);
	}
	return shaderSource;
}

void Shader::Compile(const std::unordered_map<GLenum, std::string>& sources)
{
	GLuint program = glCreateProgram();

	std::vector<GLuint> shaderIDs;
	shaderIDs.reserve(sources.size());

	// Shader Compilation
	for (auto& kv : sources)
	{
		GLenum type = kv.first;
		const std::string& source_code = kv.second;

		GLuint shaderID = glCreateShader(type);
		const char* sourceCString = source_code.c_str();
		glShaderSource(shaderID, 1, &sourceCString, NULL);
		glCompileShader(shaderID);

		GLint success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLint length;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

			std::vector<GLchar> infoLog(length);
			glGetShaderInfoLog(shaderID, length, &length, &infoLog[0]);

			glDeleteShader(shaderID);
			ERROR("Failed to compile shader! %s", infoLog.data());
			return;
		}

		glAttachShader(program, shaderID);
		shaderIDs.push_back(shaderID);
	}

	// Linking
	glLinkProgram(program);
	
	GLint link_status;
	glGetProgramiv(program, GL_LINK_STATUS, &link_status);
	if (!link_status)
	{
		GLint length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

		std::vector<GLchar> infoLog(length);
		glGetProgramInfoLog(program, length, &length, infoLog.data());
		glDeleteProgram(program);

		for (auto& id : shaderIDs)
			glDeleteShader(id);

		ERROR("Failed to link! %s", infoLog.data());
		return;
	}

	for (auto& id : shaderIDs)
		glDetachShader(program, id);

	m_RendererID = program;
}

void Shader::UploadUniform1f(const std::string& name, const float& val)
{
	glUniform1f(GetUniformLocation(name), val);
}

void Shader::UploadUniform2f(const std::string& name, const glm::vec2& val)
{
	glUniform2f(GetUniformLocation(name), val.x, val.y);
}

void Shader::UploadUniform3f(const std::string& name, const glm::vec3& val)
{
	glUniform3f(GetUniformLocation(name), val.x, val.y, val.z);
}

void Shader::UploadUniform4f(const std::string& name, const glm::vec4& val)
{
	glUniform4f(GetUniformLocation(name), val.x, val.y, val.z, val.w);
}

void Shader::UploadUniform1i(const std::string& name, const int& val)
{
	glUniform1i(GetUniformLocation(name), val);
}

void Shader::UploadTextureUniform1i(const std::string& name, const int& slot)
{
	glUniform1i(GetUniformLocation(name), slot);
}

void Shader::UploadUniform2i(const std::string& name, const glm::ivec2& val)
{
	glUniform2i(GetUniformLocation(name), val.x, val.y);
}

void Shader::UploadUniform3i(const std::string& name, const glm::ivec3& val)
{
	glUniform3i(GetUniformLocation(name), val.x, val.y, val.z);
}

void Shader::UploadUniform4i(const std::string& name, const glm::ivec4& val)
{
	glUniform4i(GetUniformLocation(name), val.x, val.y, val.z, val.w);
}

void Shader::UploadUniformMat2(const std::string& name, const glm::mat2& val)
{
	glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(val));
}

void Shader::UploadUniformMat3(const std::string& name, const glm::mat3& val)
{
	glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(val));
}

void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& val)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(val));
}

int Shader::GetUniformLocation(const std::string& uniformName)
{
	if (m_UniformLocationCache.find(uniformName) != m_UniformLocationCache.end())
		return m_UniformLocationCache[uniformName];

	int location = glGetUniformLocation(m_RendererID, uniformName.c_str());
	if (location == -1)
		WARN("Uniform '%s' not found!", uniformName.c_str());
	m_UniformLocationCache[uniformName] = location;

	return location;
}

std::shared_ptr<Shader> Shader::Create(const std::string& filepath)
{
	return std::make_shared<Shader>(filepath);
}

#pragma warning(pop)

