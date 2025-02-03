#ifndef APP_INCLUDE_SHADER_H_
#define APP_INCLUDE_SHADER_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

class Shader
{
public:
	Shader(const char* vName, const char* fName);
	virtual ~Shader();

	// シェーダのバインド
	void Bind() const { glUseProgram(m_programID); }
	
	// アンバインド
	void Unbind() const { glUseProgram(0); }

	// bool
	void Set(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(m_programID, name.c_str()), GLint(value));
	}
	// int
	void Set(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(m_programID, name.c_str()), value);
	}
	// uint
	void Set(const std::string& name, uint32_t value) const
	{
		glUniform1ui(glGetUniformLocation(m_programID, name.c_str()), value);
	}
	// float
	void Set(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(m_programID, name.c_str()), value);
	}
	// vector2
	void Set(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(m_programID, name.c_str()), x, y);
	}
	void Set(const std::string& name, const glm::vec2& vec) const
	{
		glUniform2fv(glGetUniformLocation(m_programID, name.c_str()), 1, &vec[0]);
	}
	void Set(const std::string& name, const glm::vec2* values, int count) const
	{
		glUniform2fv(glGetUniformLocation(m_programID, name.c_str()), count, glm::value_ptr(*values));
	}
	// vector3
	void Set(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(m_programID, name.c_str()), x, y, z);
	}
	void Set(const std::string& name, const glm::vec3& vec) const
	{
		glUniform3fv(glGetUniformLocation(m_programID, name.c_str()), 1, &vec[0]);
	}
	void Set(const std::string& name, const glm::vec3* values, int count) const
	{
		glUniform3fv(glGetUniformLocation(m_programID, name.c_str()), count, glm::value_ptr(*values));
	}
	// vector4
	void Set(const std::string& name, float x, float y, float z, float w) const
	{
		glUniform4f(glGetUniformLocation(m_programID, name.c_str()), x, y, z, w);
	}
	void Set(const std::string& name, const glm::vec4& vec) const
	{
		glUniform4fv(glGetUniformLocation(m_programID, name.c_str()), 1, &vec[0]);
	}
	void Set(const std::string& name, const glm::vec4* values, int count) const
	{
		glUniform4fv(glGetUniformLocation(m_programID, name.c_str()), count, glm::value_ptr(*values));
	}
	// mat2
	void Set(const std::string& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(m_programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	void Set(const std::string& name, const glm::mat2* mat, int count) const
	{
		glUniformMatrix2fv(glGetUniformLocation(m_programID, name.c_str()), count, GL_FALSE, glm::value_ptr(*mat));
	}
	// mat3
	void Set(const std::string& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(m_programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	void Set(const std::string& name, const glm::mat3* mat, int count) const
	{
		glUniformMatrix3fv(glGetUniformLocation(m_programID, name.c_str()), count, GL_FALSE, glm::value_ptr(*mat));
	}
	// mat4
	void Set(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	void Set(const std::string& name, const glm::mat4* mat, int count) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_programID, name.c_str()), count, GL_FALSE, glm::value_ptr(*mat));
	}

protected:
	// ファイルの読み込み
	static std::string loadFile(const char* fileName);

	// シェーダのコンパイル
	static GLuint compileShader(const char* code, GLenum glShaderType);

	// コンパイルエラーチェック
	static void checkCompileErrors(GLuint shader, std::string type);

protected:
	GLuint m_programID;
};

#endif