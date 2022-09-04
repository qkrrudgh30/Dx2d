#include "PreCompile.h"
#include "MouseSlot.h"


#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineFontRenderer.h>

MouseSlot* MouseSlot::spMouseSlot = nullptr;

MouseSlot::MouseSlot() 
	: mfWidth(32.f)
	, mfHeight(32.f)
	, mpRenderer(nullptr)
	, mpSelectedItemPointer()
{
	spMouseSlot = this;
}

MouseSlot::~MouseSlot() 
{
}

void MouseSlot::SetRenderer(const std::string& _Name)
{
	mpRenderer->SetTexture(_Name);
	// mpRenderer->GetColorData().PlusColor = float4{0.f, 0.f, 0.f, 0.4f};
}

void MouseSlot::SetSelectedItemPointer(const std::pair<GameEngineUIRenderer*, ItemInfo*>& _pSelectedItem)
{
	mpSelectedItemPointer = _pSelectedItem;
}

void MouseSlot::Start()
{
	mpRenderer = CreateComponent<GameEngineUIRenderer>();
	mpRenderer->GetTransform().SetLocalScale(float4{mfWidth, mfHeight, 1.f, 1.f});
	mpRenderer->SetTexture("Clear.png");
}

void MouseSlot::Update(float _DeltaTime)
{
	GetTransform().SetLocalPosition(GetLevel()->GetUICamera()->GetMouseWorldPosition());

	if (true == GameEngineInput::GetInst()->IsUp("MouseLButtonDown"))
	{
		mpRenderer->SetTexture("Clear.png");
	}
}

void MouseSlot::End()
{
}
