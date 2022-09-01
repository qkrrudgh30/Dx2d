#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class GameEngineUIRenderer;
class ETCMenuButton : public GameEngineActor
{
public:
	GameEngineUIRenderer* mpRenderer;
	float                      mfWidth;
	float                      mfHeight;
	POINT                      mptMousePos;
	float4                     mf4MousePos;
	float4                     mf4ButtonPos;
	bool                       mbToggle;

public:
	// constrcuter destructer
	ETCMenuButton();
	~ETCMenuButton();

	// delete Function
	ETCMenuButton(const ETCMenuButton& _Other) = delete;
	ETCMenuButton(ETCMenuButton&& _Other) noexcept = delete;
	ETCMenuButton& operator=(const ETCMenuButton& _Other) = delete;
	ETCMenuButton& operator=(ETCMenuButton&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:

};
