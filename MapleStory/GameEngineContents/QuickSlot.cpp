#include "PreCompile.h"
#include "QuickSlot.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineFontRenderer.h>
#include "Player.h"

QuickSlot::QuickSlot() 
	: mpUIRenderer(nullptr)
{
	mfWidth = 151.f;
	mfHeight = 80.f;
}

QuickSlot::~QuickSlot() 
{
}

void QuickSlot::Start()
{
	mpUIRenderer = CreateComponent<GameEngineUIRenderer>();
	mpUIRenderer->SetTexture("QuickSlot.png");
	mpUIRenderer->GetTransform().SetLocalScale(float4{ mfWidth, mfHeight, 1.f, 1.f });
	
}

void QuickSlot::Update(float _DeltaTime)
{
	Player* pPlayer = Player::GetPlayer();
	// 플레이어의 인벤토리 멤버에서 개수를 얻어옴.
}

