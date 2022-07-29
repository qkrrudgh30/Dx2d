#include "PreCompile.h"
#include "Temple0PixelCollisionMap.h"

Temple0PixelCollisionMap::Temple0PixelCollisionMap() 
{
}

Temple0PixelCollisionMap::~Temple0PixelCollisionMap() 
{
}

void Temple0PixelCollisionMap::Start()
{
	GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::UI, 1.f });

	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpRenderer->GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::UI, 1.f });
	mpRenderer->SetTexture("Temple0TileP.png", 0);
	mpRenderer->ScaleToTexture();
}

void Temple0PixelCollisionMap::Update(float _DeltaTime)
{
}

void Temple0PixelCollisionMap::End()
{
}
