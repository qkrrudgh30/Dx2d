#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class Merchandiser : public GameEngineActor
{
public:
	// constrcuter destructer
	Merchandiser();
	~Merchandiser();

	// delete Function
	Merchandiser(const Merchandiser& _Other) = delete;
	Merchandiser(Merchandiser&& _Other) noexcept = delete;
	Merchandiser& operator=(const Merchandiser& _Other) = delete;
	Merchandiser& operator=(Merchandiser&& _Other) noexcept = delete;

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

