#pragma once
#include<DirectXMath.h>
#include"SpriteCommon.h"
#include<cassert>

class Sprite
{
public:
	//������
	void Initialize(SpriteCommon*_spriteCommon);

	//�`��
	void Draw();
private:
	//�X�v���C�g���ʕ���
	SpriteCommon* spriteCommon = nullptr;
	//���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource>vertBuff;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};

};

