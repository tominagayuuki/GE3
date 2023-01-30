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
		DirectX::XMFLOAT2 uv;
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
	void Initialize(SpriteCommon*_spriteCommon,uint32_t textureIndex = UINT32_MAX);

	//�X�V
	void Update();

	//�`��
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
	//�e�N�X�`���T�C�Y���C���[�W�ɍ��킹��
	void AdjustTextureSize();
private:
	//�X�v���C�g���ʕ���
	SpriteCommon* spriteCommon = nullptr;

	//�e�N�X�`���ԍ�
	uint32_t textureIndex = 0;

	DirectX::XMFLOAT4 color = { 1,1,1,1 };
	//�X�v���C�g���
	float rotationZ=0.f;
	DirectX::XMFLOAT2 position={100.f,100.f};
	DirectX::XMFLOAT2 size = { 100.f,100.f };
	DirectX::XMFLOAT2 anchorPoint = { 0.f,0.f };

	//�e�N�X�`�����
	DirectX::XMFLOAT2 textureLeftTop = { 0.f,0.f };
	DirectX::XMFLOAT2 textureSize = { 100.f,100.f };

	bool IsFlipX = false;
	bool IsFlipY = false;

	bool IsInvisible = false;
	
	//���_�f�[�^
	Vertex vertices[4];
	//���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource>vertBuff;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	//�萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> constBufferMaterial;
	ConstBufferDataMaterial* constMapMaterial = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Resource> constBufferTransform;
	ConstBufferDataTransform* constMapTransform = nullptr;
};

