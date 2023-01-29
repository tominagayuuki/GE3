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
		DirectX::XMFLOAT3 pos;
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
	void Initialize(SpriteCommon*_spriteCommon);

	//描画
	void Draw();
private:
	//スプライト共通部分
	SpriteCommon* spriteCommon = nullptr;
	//頂点バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource>vertBuff;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};

};

