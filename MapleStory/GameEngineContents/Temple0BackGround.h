#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class Temple0BackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	Temple0BackGround();
	~Temple0BackGround();

	// delete Function
	Temple0BackGround(const Temple0BackGround& _Other) = delete;
	Temple0BackGround(Temple0BackGround&& _Other) noexcept = delete;
	Temple0BackGround& operator=(const Temple0BackGround& _Other) = delete;
	Temple0BackGround& operator=(Temple0BackGround&& _Other) noexcept = delete;

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

