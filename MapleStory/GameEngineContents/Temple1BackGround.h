#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class Temple1BackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	Temple1BackGround();
	~Temple1BackGround();

	// delete Function
	Temple1BackGround(const Temple1BackGround& _Other) = delete;
	Temple1BackGround(Temple1BackGround&& _Other) noexcept = delete;
	Temple1BackGround& operator=(const Temple1BackGround& _Other) = delete;
	Temple1BackGround& operator=(Temple1BackGround&& _Other) noexcept = delete;

	GameEngineTextureRenderer* GetRenderer() { return mpRenderer; }

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* mpRenderer;
	float                      mfWidth;
	float                      mfHeight;
	float                      mfPositionX;
	float                      mfPositionY;

};

