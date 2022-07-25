#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class GameEngineTextureRenderer;
class Guardian : public GameEngineActor
{
public:
	// constrcuter destructer
	Guardian();
	~Guardian();

	// delete Function
	Guardian(const Guardian& _Other) = delete;
	Guardian(Guardian&& _Other) noexcept = delete;
	Guardian& operator=(const Guardian& _Other) = delete;
	Guardian& operator=(Guardian&& _Other) noexcept = delete;

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

