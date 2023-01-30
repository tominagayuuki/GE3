#pragma once
#include<DirectXMath.h>
#include"SpriteCommon.h"
#include<cassert>

class Sprite
{
	//構造体
public:
	//頂点データ構造体
	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 uv;
	};
	//定数バッファ(マテリアル)
	struct ConstBufferDataMaterial 
	{
		DirectX::XMFLOAT4 color;
	};
	//定数バッファ(3D変換行列)
	struct ConstBufferDataTransform {
		DirectX::XMMATRIX mat;
	};

	enum VertexNumber {
		LB,
		LT,
		RB,
		RT,
	};

public:
	//初期化
	void Initialize(SpriteCommon*_spriteCommon,uint32_t textureIndex = UINT32_MAX);

	//更新
	void Update();

	//描画
	void Draw();

	//Getter
	const DirectX::XMFLOAT4 GetColor() const { return color; }

	const uint32_t GetTextureIndex()const { return textureIndex; }

	const DirectX::XMFLOAT2& GetPosition()const { return position; }
	const float& GetRotationZ()const { return rotationZ; }
	const DirectX::XMFLOAT2& GetSize()const { return size; }
	const DirectX::XMFLOAT2& GetAnchorPoint()const { return anchorPoint; }

	const DirectX::XMFLOAT2& GetTextureLeftTop()const { return textureLeftTop; }
	const DirectX::XMFLOAT2& GetTextureSizet()const { return textureSize; }

	const bool& GetIsFlipX() const { return IsFlipX; }
	const bool& GetIsFlipY() const { return IsFlipY; }

	const bool& GetIsInvisible() const { return IsInvisible; }

	//Setter
	void SetColor(const DirectX::XMFLOAT4 color) { this->color = color; }

	void SetTextureIndex(uint32_t index) { this->textureIndex = index; }

	void SetPosition(const DirectX::XMFLOAT2& position) { this->position = position; }
	void SetRotationZ(const float& rotationZ) { this->rotationZ = rotationZ; }
	void SetSize(DirectX::XMFLOAT2& size) { this->size = size; }
	void SetAnchorPoint(DirectX::XMFLOAT2& anchorPoint) { this->anchorPoint = anchorPoint; }

	void SetTextureLeftTop(DirectX::XMFLOAT2& leftTop) { this->textureLeftTop = leftTop; }
	void SetTextureSize(DirectX::XMFLOAT2& size) { this->textureSize = size; }

	void SetIsFlipX(const bool& isFlipX) { this->IsFlipX = isFlipX; }
	void SetIsFlipY(const bool& isFlipY) { this->IsFlipY = isFlipY; }

	void SetIsInvisible(const bool& IsInvisible) { this->IsInvisible = IsInvisible; }
private:
	//テクスチャサイズをイメージに合わせる
	void AdjustTextureSize();
private:
	//スプライト共通部分
	SpriteCommon* spriteCommon = nullptr;

	//テクスチャ番号
	uint32_t textureIndex = 0;

	DirectX::XMFLOAT4 color = { 1,1,1,1 };
	//スプライト情報
	float rotationZ=0.f;
	DirectX::XMFLOAT2 position={100.f,100.f};
	DirectX::XMFLOAT2 size = { 100.f,100.f };
	DirectX::XMFLOAT2 anchorPoint = { 0.f,0.f };

	//テクスチャ情報
	DirectX::XMFLOAT2 textureLeftTop = { 0.f,0.f };
	DirectX::XMFLOAT2 textureSize = { 100.f,100.f };

	bool IsFlipX = false;
	bool IsFlipY = false;

	bool IsInvisible = false;
	
	//頂点データ
	Vertex vertices[4];
	//頂点バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource>vertBuff;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	//定数バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> constBufferMaterial;
	ConstBufferDataMaterial* constMapMaterial = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Resource> constBufferTransform;
	ConstBufferDataTransform* constMapTransform = nullptr;
};

