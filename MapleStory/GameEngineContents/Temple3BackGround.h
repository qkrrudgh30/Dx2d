#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class Temple3BackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	Temple3BackGround();
	~Temple3BackGround();

	// delete Function
	Temple3BackGround(const Temple3BackGround& _Other) = delete;
	Temple3BackGround(Temple3BackGround&& _Other) noexcept = delete;
	Temple3BackGround& operator=(const Temple3BackGround& _Other) = delete;
	Temple3BackGround& operator=(Temple3BackGround&& _Other) noexcept = delete;

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

