#pragma once
#include <fstream>
#include <filesystem>
#include <vector>
#include <wrl/client.h>
#include <d3d11.h>
template <class T>
class SHADER
{
	Microsoft::WRL::ComPtr<T> shader;
	std::vector<char> byteCode;
	std::size_t size;

private:
	void readShader(const std::string& fileName) {

		std::ifstream shaderFile;
		shaderFile.open(fileName, std::ios::binary | std::ios::in);

		shaderFile.read(byteCode.data(), size);
		shaderFile.close();
	};
	SHADER& operator=(const SHADER&) = delete;
	SHADER() = delete;
	SHADER(const SHADER&) = delete;

public:
	SHADER(const std::string& fileName) 
		:byteCode(size = std::filesystem::file_size(fileName))  //dang how cool is this
		{
			readShader(fileName);
		};

		void* data() 
		{
				return byteCode.data();
		};


		inline std::size_t& getSize() { return size; };

		Microsoft::WRL::Details::ComPtrRef<Microsoft::WRL::ComPtr<T>> operator&() { return &shader; };
		T* operator->() { return shader.operator->(); };
		T** GetAddressOf() { return shader.GetAddressOf(); };
		Microsoft::WRL::ComPtr<T>& getShader() { return shader; };

	};

