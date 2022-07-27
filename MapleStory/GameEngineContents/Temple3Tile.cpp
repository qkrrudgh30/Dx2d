#include "PreCompile.h"
#include "Temple3Tile.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

Temple3Tile::Temple3Tile()
	: mpRenderer(nullptr)
	, mfWidth(0)
	, mfHeight(0)
	, mfPositionX(0)
	, mfPositionY(0)
{
}

Temple3Tile::~Temple3Tile()
{
}

void Temple3Tile::Start()
{
	mfWidth = 2327.f;
	mfHeight = 935.f;
	mpRenderer = CreateComponent<GameEngineTextureRenderer>();
	// mpRenderer->GetTransform().SetWorldScale({ mfWidth, mfHeight, 1 });
	mpRenderer->GetTransform().SetWorldPosition(float4{ 0.f, 0.f, OBJECTORDER::UI, 1.f });
	mpRenderer->SetTexture("Temple3Tile.png", 0);
	mpRenderer->ScaleToTexture();
}

void Temple3Tile::Update(float _DeltaTime)
{
}

void Temple3Tile::End()
{
}
