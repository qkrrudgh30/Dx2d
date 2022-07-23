#include "PreCompile.h"
#include "Temple1Tile.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

Temple1Tile::Temple1Tile()
	: mpRenderer(nullptr)
	, mfWidth(0)
	, mfHeight(0)
	, mfPositionX(0)
	, mfPositionY(0)
{
}

Temple1Tile::~Temple1Tile()
{
}

void Temple1Tile::Start()
{
	mfWidth = 2327.f;
	mfHeight = 935.f;
	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	// mpRenderer->GetTransform().SetWorldScale({ mfWidth, mfHeight, 1 });
	mpRenderer->GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::Tile, 1.f });
	mpRenderer->SetTexture("Temple1Tile.png", 0);
	mpRenderer->ScaleToTexture();
}

void Temple1Tile::Update(float _DeltaTime)
{
}

void Temple1Tile::End()
{
}
