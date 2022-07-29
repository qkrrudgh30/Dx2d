#pragma once

// Ό³Έν :
class GameEngineUIRenderer;
class MPGauge : public GameEngineActor
{
private:
	GameEngineUIRenderer* mpUIRenderer;
	float                      mfWidth;
	float                      mfHeight;

public:
	// constrcuter destructer
	MPGauge();
	~MPGauge();

	// delete Function
	MPGauge(const MPGauge& _Other) = delete;
	MPGauge(MPGauge&& _Other) noexcept = delete;
	MPGauge& operator=(const MPGauge& _Other) = delete;
	MPGauge& operator=(MPGauge&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}

private:

};

