#include "Sprite.h"

using namespace DirectX;
using namespace Microsoft::WRL;

void Sprite::Initialize(SpriteCommon* _spriteCommon, uint32_t textureIndex)
{
	HRESULT result{};
	assert(_spriteCommon);
	spriteCommon = _spriteCommon;
	
	//テクスチャサイズをイメージに合わせる
	if (textureIndex != UINT32_MAX) {
		this->textureIndex = textureIndex;
		AdjustTextureSize();
		size = textureSize;
	}

	//uv
	{
		ID3D12Resource* textureBuffer = spriteCommon->GetTextureBuffer(textureIndex);

		if (textureBuffer) {
			//テクスチャ情報取得
			D3D12_RESOURCE_DESC resDesc = textureBuffer->GetDesc();

			float tex_left = textureLeftTop.x / resDesc.Width;
			float tex_right = (textureLeftTop.x + textureSize.x)/resDesc.Width;
			float tex_top = textureLeftTop.y / resDesc.Height;
			float tex_bottom = (textureLeftTop.y + textureSize.y) / resDesc.Height;

			vertices[LB].uv = { tex_left, tex_bottom };
			vertices[LT].uv = { tex_left, tex_top };
			vertices[RB].uv = { tex_right, tex_bottom };
			vertices[RT].uv = { tex_right, tex_top };
		}
	}


	//座標
	{
		float left = (0.0f - anchorPoint.x) * size.x;
		float right = (1.0f - anchorPoint.x) * size.x;
		float top = (0.0f - anchorPoint.y) * size.y;
		float bottom = (1.0f - anchorPoint.y) * size.y;

		if (IsFlipX) {
			left = -left;
			right = -right;
		}
		if (IsFlipY) {
			top = -top;
			bottom = -bottom;
		}

		//頂点データ
		vertices[LB].pos = {left, bottom,0.0f};
		vertices[LT].pos = {left,    top,0.0f};
		vertices[RB].pos = {right,bottom,0.0f};
		vertices[RT].pos = {right,   top,0.0f};
	}

	//頂点データ
	UINT sizeVB = static_cast<UINT>(sizeof(vertices[0]) * _countof(vertices));

	//頂点バッファの設定
	D3D12_HEAP_PROPERTIES heapProp{};//ヒープ設定
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
	//リソース設定
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB;
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	//生成
	result = spriteCommon->GetDirectXCommon()->GetDevice()->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff)
	);
	assert(SUCCEEDED(result));

	//転送
	Vertex* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));
	//全頂点に対して
	for (int i = 0; i < _countof(vertices); i++) {
		vertMap[i] = vertices[i];
	}
	vertBuff->Unmap(0, nullptr);


	//頂点バッファビュー
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeVB;
	vbView.StrideInBytes = sizeof(vertices[0]);

    //マテリアル
	{
		//設定
		D3D12_HEAP_PROPERTIES cbHeapProp{};
		cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
		D3D12_RESOURCE_DESC cbResourceDesc{};
		cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		cbResourceDesc.Width = (sizeof(ConstBufferDataMaterial) + 0xff) & ~0xff;
		cbResourceDesc.Height = 1;
		cbResourceDesc.DepthOrArraySize = 1;
		cbResourceDesc.MipLevels = 1;
		cbResourceDesc.SampleDesc.Count = 1;
		cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		//生成
		result = spriteCommon->GetDirectXCommon()->GetDevice()->CreateCommittedResource(
			&cbHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&cbResourceDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&constBufferMaterial)
		);
		assert(SUCCEEDED(result));

		//マッピング
		result = constBufferMaterial->Map(0, nullptr, (void**)&constMapMaterial);
		assert(SUCCEEDED(result));
		constMapMaterial->color = color;
	}
	//行列
	{
		//設定
		D3D12_HEAP_PROPERTIES cbHeapProp{};
		cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
		D3D12_RESOURCE_DESC cbResourceDesc{};
		cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		cbResourceDesc.Width = (sizeof(ConstBufferDataTransform) + 0xff) & ~0xff;
		cbResourceDesc.Height = 1;
		cbResourceDesc.DepthOrArraySize = 1;
		cbResourceDesc.MipLevels = 1;
		cbResourceDesc.SampleDesc.Count = 1;
		cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		//生成
		result = spriteCommon->GetDirectXCommon()->GetDevice()->CreateCommittedResource(
			&cbHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&cbResourceDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&constBufferTransform)
		);
		assert(SUCCEEDED(result));

		//マッピング
		result = constBufferTransform->Map(0, nullptr, (void**)&constMapTransform);
		assert(SUCCEEDED(result));

		//ワールド
		XMMATRIX matWorld;
		matWorld = XMMatrixIdentity();

		//回転
		XMMATRIX matRot;
		matRot = XMMatrixIdentity();
		matRot *= XMMatrixRotationZ(XMConvertToRadians(rotationZ));
		matWorld *= matRot;

		//平行移動
		XMMATRIX matTrans;
		matTrans = XMMatrixTranslation(position.x, position.y,0.f);
		matWorld *= matTrans;

		//射影行列
		XMMATRIX matProjection = XMMatrixOrthographicOffCenterLH(
			0.f, WinApp::window_width,
			WinApp::window_height, 0.f,
			0.0f, 1.0f
		);

		constMapTransform->mat = matWorld * matProjection;

	}
}

void Sprite::Update()
{
	//uv
	{
		ID3D12Resource* textureBuffer = spriteCommon->GetTextureBuffer(textureIndex);

		if (textureBuffer) {
			//テクスチャ情報取得
			D3D12_RESOURCE_DESC resDesc = textureBuffer->GetDesc();

			float tex_left = textureLeftTop.x / resDesc.Width;
			float tex_right = (textureLeftTop.x + textureSize.x) / resDesc.Width;
			float tex_top = textureLeftTop.y / resDesc.Height;
			float tex_bottom = (textureLeftTop.y + textureSize.y) / resDesc.Height;

			vertices[LB].uv = { tex_left, tex_bottom };
			vertices[LT].uv = { tex_left, tex_top };
			vertices[RB].uv = { tex_right, tex_bottom };
			vertices[RT].uv = { tex_right, tex_top };
		}
	}

	//座標
	{
		float left = (0.0f - anchorPoint.x) * size.x;
		float right = (1.0f - anchorPoint.x) * size.x;
		float top = (0.0f - anchorPoint.y) * size.y;
		float bottom = (1.0f - anchorPoint.y) * size.y;

		if (IsFlipX) {
			left = -left;
			right = -right;
		}
		if (IsFlipY) {
			top = -top;
			bottom = -bottom;
		}

		//頂点データ
		vertices[LB].pos = { left, bottom,0.0f };
		vertices[LT].pos = { left,    top,0.0f };
		vertices[RB].pos = { right,bottom,0.0f };
		vertices[RT].pos = { right,   top,0.0f };
	}
	//転送
	Vertex* vertMap = nullptr;
	HRESULT result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));
	//全頂点に対して
	for (int i = 0; i < _countof(vertices); i++) {
		vertMap[i] = vertices[i];
	}
	vertBuff->Unmap(0, nullptr);


	constMapMaterial->color = color;

	//ワールド
	XMMATRIX matWorld;
	matWorld = XMMatrixIdentity();

	//回転
	XMMATRIX matRot;
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(XMConvertToRadians(rotationZ));
	matWorld *= matRot;

	//平行移動
	XMMATRIX matTrans;
	matTrans = XMMatrixTranslation(position.x, position.y,0.f);
	matWorld *= matTrans;

	//射影行列
	XMMATRIX matProjection = XMMatrixOrthographicOffCenterLH(
		0.f, WinApp::window_width,
		WinApp::window_height, 0.f,
		0.0f, 1.0f
	);

	constMapTransform->mat = matWorld * matProjection;
}

void Sprite::Draw()
{
	if (IsInvisible) {
		return;
	}

	//テクスチャコマンド
	spriteCommon->SetTextureCommands(textureIndex);

	spriteCommon->GetDirectXCommon()->GetCommandList()->IASetVertexBuffers(0, 1, &vbView);

	spriteCommon->GetDirectXCommon()->GetCommandList()->SetGraphicsRootConstantBufferView(0, constBufferMaterial->GetGPUVirtualAddress());
	spriteCommon->GetDirectXCommon()->GetCommandList()->SetGraphicsRootConstantBufferView(2, constBufferTransform->GetGPUVirtualAddress());

	spriteCommon->GetDirectXCommon()->GetCommandList()->DrawInstanced(4, 1, 0, 0);
}

void Sprite::AdjustTextureSize()
{
	ID3D12Resource* textureBuffer = spriteCommon->GetTextureBuffer(textureIndex);
	assert(textureBuffer);

	//テクスチャ情報
	D3D12_RESOURCE_DESC resDesc = textureBuffer->GetDesc();

	textureSize.x = static_cast<float>(resDesc.Width);
	textureSize.y = static_cast<float>(resDesc.Height);
}
