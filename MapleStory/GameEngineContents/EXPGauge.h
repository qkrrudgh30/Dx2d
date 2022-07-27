#pragma once

// Ό³Έν :
class GameEngineUIRenderer;
class EXPGauge : public GameEngineActor
{
private:
	GameEngineUIRenderer* mpUIRenderer;
	float                      mfWidth;
	float                      mfHeight;

public:
	// constrcuter destructer
	EXPGauge();
	~EXPGauge();

	// delete Function
	EXPGauge(const EXPGauge& _Other) = delete;
	EXPGauge(EXPGauge&& _Other) noexcept = delete;
	EXPGauge& operator=(const EXPGauge& _Other) = delete;
	EXPGauge& operator=(EXPGauge&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}

private:

};
