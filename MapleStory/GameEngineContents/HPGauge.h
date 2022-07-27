#pragma once

// Ό³Έν :
class GameEngineUIRenderer;
class HPGauge : public GameEngineActor
{
private:
	GameEngineUIRenderer* mpUIRenderer;
	float                 mfWidth;
	float                 mfHeight;

public:
	// constrcuter destructer
	HPGauge();
	~HPGauge();

	// delete Function
	HPGauge(const HPGauge& _Other) = delete;
	HPGauge(HPGauge&& _Other) noexcept = delete;
	HPGauge& operator=(const HPGauge& _Other) = delete;
	HPGauge& operator=(HPGauge&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}

private:

};

