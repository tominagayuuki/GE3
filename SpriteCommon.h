#pragma once
#include<DirectXMath.h>
#include<d3d12.h>
#include<wrl.h>

#include"DirectXCommon.h"

class SpriteCommon
{

public:
	//������
	void Initialize(DirectXCommon*_dxCommon);

	//�`��
	void PreDraw();

	//Getter
	DirectXCommon* GetDirectXCommon() { return dxCommon; }
	
private://�����o�ϐ�
	DirectXCommon* dxCommon;

	//�p�C�v���C���X�e�[�g
	Microsoft::WRL::ComPtr<ID3D12PipelineState>pipelineState;
	//���[�g�V�O�l�`��
	Microsoft::WRL::ComPtr <ID3D12RootSignature>rootSignature;
};

