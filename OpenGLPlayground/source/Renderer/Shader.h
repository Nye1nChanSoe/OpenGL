#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

#include <memory>

using GLenum = unsigned int;

class Shader
{
public:
	Shader(const std::string& filepath);
	Shader(const std::string& name, const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

	~Shader();

	void Bind() const;
	void UseProgram() const;
	void UnBind() const;
	void DeleteProgram() const;

	inline const std::string& GetName() const { return m_Name; }

	// Uniforms
	void UploadUniform1f(const std::string& name, const float& val);
	void UploadUniform2f(const std::string& name, const glm::vec2& val);
	void UploadUniform3f(const std::string& name, const glm::vec3& val);
	void UploadUniform4f(const std::string& name, const glm::vec4& val);

	void UploadUniform1i(const std::string& name, const int& val);
	void UploadTextureUniform1i(const std::string& name, const int& slot);
	void UploadUniform2i(const std::string& name, const glm::ivec2& val);
	void UploadUniform3i(const std::string& name, const glm::ivec3& val);
	void UploadUniform4i(const std::string& name, const glm::ivec4& val);

	void UploadUniformMat2(const std::string& name, const glm::mat2& val);
	void UploadUniformMat3(const std::string& name, const glm::mat3& val);
	void UploadUniformMat4(const std::string& name, const glm::mat4& val);

	static std::shared_ptr<Shader> Create(const std::string& filepath);
private:
	std::string ReadFile(const std::string& filepath);
	std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
	void Compile(const std::unordered_map<GLenum, std::string>& sources);

	int GetUniformLocation(const std::string& uniformName);

private:
	std::unordered_map<std::string, int> m_UniformLocationCache;
	unsigned int m_RendererID;
	std::string m_Name;
};

class ShaderLibrary
{
public:
	

private:

};