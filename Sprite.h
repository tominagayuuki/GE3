#pragma once
#include<DirectXMath.h>
#include"SpriteCommon.h"
#include<cassert>

class Sprite
{
	//�\����
public:
	//���_�f�[�^�\����
	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 pos;
	};
	//�萔�o�b�t�@(�}�e���A��)
	struct ConstBufferDataMaterial 
	{
		DirectX::XMFLOAT4 color;
	};
	//�萔�o�b�t�@(3D�ϊ��s��)
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

