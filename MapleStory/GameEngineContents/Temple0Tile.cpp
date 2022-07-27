#include "PreCompile.h"
#include "Temple0Tile.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

Temple0Tile::Temple0Tile()
	: mpRenderer(nullptr)
	, mfWidth(0)
	, mfHeight(0)
	, mfPositionX(0)
	, mfPositionY(0)
{
}

Temple0Tile::~Temple0Tile() 
{
}

void Temple0Tile::Start()
{
	GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::UI, 1.f });

	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpRenderer->GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::UI, 1.f });
	mpRenderer->SetTexture("Temple0Tile.png", 0);
	mpRenderer->ScaleToTexture();
}

void Temple0Tile::Update(float _DeltaTime)
{
}

void Temple0Tile::End()
{
}
