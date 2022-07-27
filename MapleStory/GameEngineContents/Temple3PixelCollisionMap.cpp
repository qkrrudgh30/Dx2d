#include "PreCompile.h"
#include "Temple3PixelCollisionMap.h"

Temple3PixelCollisionMap::Temple3PixelCollisionMap() 
{
}

Temple3PixelCollisionMap::~Temple3PixelCollisionMap() 
{
}

void Temple3PixelCollisionMap::Start()
{
	GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::UI, 1.f });

	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpRenderer->GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::UI, 1.f });
	mpRenderer->SetTexture("Temple3TileP.png", 0);
	mpRenderer->ScaleToTexture();
}

void Temple3PixelCollisionMap::Update(float _DeltaTime)
{
}

void Temple3PixelCollisionMap::End()
{
}
