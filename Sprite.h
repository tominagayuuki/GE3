#pragma once
#include<DirectXMath.h>
#include"SpriteCommon.h"
#include<cassert>

class Sprite
{
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

