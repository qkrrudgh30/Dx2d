#include "PreCompile.h"
#include "Temple2PixelCollisionMap.h"

Temple2PixelCollisionMap::Temple2PixelCollisionMap() 
{
}

Temple2PixelCollisionMap::~Temple2PixelCollisionMap() 
{
}

void Temple2PixelCollisionMap::Start()
{
	GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::UI, 1.f });

	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpRenderer->GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::UI, 1.f });
	mpRenderer->SetTexture("Temple2TileP.png", 0);
	mpRenderer->ScaleToTexture();
}

void Temple2PixelCollisionMap::Update(float _DeltaTime)
{
}

void Temple2PixelCollisionMap::End()
{
}
