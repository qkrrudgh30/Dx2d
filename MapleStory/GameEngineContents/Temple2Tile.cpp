#include "PreCompile.h"
#include "Temple2Tile.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

Temple2Tile::Temple2Tile()
	: mpRenderer(nullptr)
	, mfWidth(0)
	, mfHeight(0)
	, mfPositionX(0)
	, mfPositionY(0)
{
}

Temple2Tile::~Temple2Tile()
{
}

void Temple2Tile::Start()
{
	mfWidth = 2327.f;
	mfHeight = 935.f;
	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	mpRenderer->GetTransform().SetLocalScale({ mfWidth, mfHeight, 1 });

	mpRenderer->SetTexture("Temple2Tile.png", 0);
}

void Temple2Tile::Update(float _DeltaTime)
{
}

void Temple2Tile::End()
{
}
