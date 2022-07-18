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
	mpRenderer->GetTransform().SetLocalScale({ mfWidth, mfHeight, 1 });

	mpRenderer->SetTexture("Temple1Tile.png", 0);
}

void Temple1Tile::Update(float _DeltaTime)
{
}

void Temple1Tile::End()
{
}
