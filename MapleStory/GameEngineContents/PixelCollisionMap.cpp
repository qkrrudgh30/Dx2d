#include "PreCompile.h"
#include "PixelCollisionMap.h"

PixelCollisionMap::PixelCollisionMap()
	: mpRenderer(nullptr)
{
}

PixelCollisionMap::~PixelCollisionMap()
{
}

void PixelCollisionMap::Start()
{
	
}

void PixelCollisionMap::Update(float _DeltaTime)
{
}

void PixelCollisionMap::End()
{
}

void PixelCollisionMap::SetInfo(const std::string& _strTextureName)
{
	GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::UI, 1.f });

	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpRenderer->GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::UI, 1.f });
	mpRenderer->SetTexture(_strTextureName, 0);
	mpRenderer->ScaleToTexture();
}
