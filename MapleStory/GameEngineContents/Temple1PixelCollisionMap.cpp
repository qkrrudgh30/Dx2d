#include "PreCompile.h"
#include "Temple1PixelCollisionMap.h"

Temple1PixelCollisionMap::Temple1PixelCollisionMap() 
{
}

Temple1PixelCollisionMap::~Temple1PixelCollisionMap() 
{
}

void Temple1PixelCollisionMap::Start()
{
	GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::UI, 1.f });

	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpRenderer->GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::UI, 1.f });
	mpRenderer->SetTexture("Temple1TileP.png", 0);
	mpRenderer->ScaleToTexture();
}

void Temple1PixelCollisionMap::Update(float _DeltaTime)
{
}

void Temple1PixelCollisionMap::End()
{
}
