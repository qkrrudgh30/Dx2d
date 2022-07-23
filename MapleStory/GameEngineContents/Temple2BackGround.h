#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class Temple2BackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	Temple2BackGround();
	~Temple2BackGround();

	// delete Function
	Temple2BackGround(const Temple2BackGround& _Other) = delete;
	Temple2BackGround(Temple2BackGround&& _Other) noexcept = delete;
	Temple2BackGround& operator=(const Temple2BackGround& _Other) = delete;
	Temple2BackGround& operator=(Temple2BackGround&& _Other) noexcept = delete;

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

