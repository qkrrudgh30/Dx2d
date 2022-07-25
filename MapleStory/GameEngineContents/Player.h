#pragma once
#include <GameEngineCore/CoreMinimal.h>

// ���� :
class GameEngineTextureRenderer;
class Player : public GameEngineActor
{
	friend class ContentsLevel;

private:
	GameEngineTextureRenderer* mpRenderer;
	float                      Speed;

public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	GameEngineTextureRenderer* GetRenderer() { return mpRenderer; }

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

};

