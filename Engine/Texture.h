#pragma once
#include "DirectX3DManager.h"
#include <string>
#include <wincodec.h>
#include <vector>
#include "BaseData.h"

/// <summary>
/// 画像を表示するクラス
/// </summary>
class Texture : public BaseData {
protected:
	UINT width_, height_;
	std::string path_;

	ID3D11SamplerState* samplerState_ = nullptr;
	ID3D11ShaderResourceView* shaderResourceView_ = nullptr;
	ID3D11Buffer* constantBuffer_ = nullptr;
	ID3D11Buffer* vertexBuffer_ = nullptr;
	IWICImagingFactory* pFactory = nullptr;
	IWICBitmapDecoder* pDecoder = nullptr;
	IWICBitmapFrameDecode* pFrame = nullptr;
	IWICFormatConverter* pConverter = nullptr;
	Vertex vertices_[6];
	bool isGray_;
public:
	Texture(const std::string& path, const float leftX, const float leftY);
	~Texture() {};
	void Init() override;
	void Release() override;

	UINT GetWidth() { return width_; }
	UINT GetHeight() { return height_; }
	std::string GetFilePath() { return path_; }
	ID3D11SamplerState* GetSampleState() { return samplerState_; }
	ID3D11ShaderResourceView* GetShaderReasourceView() { return shaderResourceView_; }
	ID3D11Buffer* GetConstantBuffer() { return constantBuffer_; }
	ID3D11Buffer* GetVertexBuffer() { return vertexBuffer_; }
	IWICImagingFactory* GetFactory() { return pFactory; }
	IWICBitmapFrameDecode* GetFrameDecode() { return pFrame; }
	IWICFormatConverter* GetConverter() { return pConverter; }
	Vertex* GetVertex() { return vertices_; }
	bool IsGray() const { return isGray_; }
	void SetGray(bool flag) { isGray_ = flag; }
};
