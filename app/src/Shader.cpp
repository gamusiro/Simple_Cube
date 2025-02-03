#include "Shader.h"

Shader::Shader(const char* vName, const char* fName)
{
	assert(vName || fName);

	// シェーダファイル読み込み
	std::string vsCode = this->loadFile(vName);
	std::string fsCode = this->loadFile(fName);

	// シェーダコンパイル
	GLuint vertex = this->compileShader(vsCode.c_str(), GL_VERTEX_SHADER);
	this->checkCompileErrors(vertex, "VERTEX");

	GLuint fragment = this->compileShader(fsCode.c_str(), GL_FRAGMENT_SHADER);
	this->checkCompileErrors(fragment, "FRAGMENT");

	// プログラムの設定
	m_programID = glCreateProgram();
	glAttachShader(m_programID, vertex);
	glAttachShader(m_programID, fragment);
	glLinkProgram(m_programID);
	this->checkCompileErrors(m_programID, "PROGRAM");

	// シェーダの破棄
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader()
{
	glDeleteProgram(m_programID);
}

std::string Shader::loadFile(const char* fileName)
{
	// ファイルを開く
	std::ifstream ifs(fileName);
	assert(ifs.is_open());

	// データ読み込み
	std::stringstream ss;
	ss << ifs.rdbuf();
	ifs.close();

	return ss.str();
}

GLuint Shader::compileShader(const char* code, GLenum glShaderType)
{
	GLuint shaderID = 0;
	shaderID = glCreateShader(glShaderType);
	glShaderSource(shaderID, 1, &code, nullptr);
	glCompileShader(shaderID);

	return shaderID;
}

void Shader::checkCompileErrors(GLuint shader, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}
