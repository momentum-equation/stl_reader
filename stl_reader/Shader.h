#pragma once
#include <string>
#include <unordered_map>


struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader {
private:
	std::string FilePath_;
	unsigned int RendererID_;
	std::unordered_map<std::string, int> UniformLocationCache_;
	// caching

public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	unsigned int CompileShader(unsigned int type, const std::string& source);
	int GetUniformLocation(const std::string& name);
};