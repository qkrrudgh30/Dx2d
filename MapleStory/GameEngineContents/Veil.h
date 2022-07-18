#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class Veil : public GameEngineActor
{
public:
	// constrcuter destructer
	Veil();
	~Veil();

	// delete Function
	Veil(const Veil& _Other) = delete;
	Veil(Veil&& _Other) noexcept = delete;
	Veil& operator=(const Veil& _Other) = delete;
	Veil& operator=(Veil&& _Other) noexcept = delete;

	void SetColor(float4 _fColor) { mf4Color = _fColor; }
	float4 GetColor() { return mf4Color; }

	void FadeIn(float _fSecond);
	void FadeOut(float _fSecond);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* mpRenderer;
	float4                     mf4Size;
	float4                     mf4Color;

};

