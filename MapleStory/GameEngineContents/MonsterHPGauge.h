#pragma once

// Ό³Έν :
class GameEngineTextureRenderer;
class ContentsActor;
class MonsterHPGauge : public GameEngineActor
{
private:
	GameEngineTextureRenderer* mpBackgroundRenderer;
	GameEngineTextureRenderer* mpGaugeRenderer;
	float                      mfWidth;
	float                      mfHeight;
	ContentsActor*             mpParentMonster;

public:
	// constrcuter destructer
	MonsterHPGauge();
	~MonsterHPGauge();

	// delete Function
	MonsterHPGauge(const MonsterHPGauge& _Other) = delete;
	MonsterHPGauge(MonsterHPGauge&& _Other) noexcept = delete;
	MonsterHPGauge& operator=(const MonsterHPGauge& _Other) = delete;
	MonsterHPGauge& operator=(MonsterHPGauge&& _Other) noexcept = delete;

	void SetParentMonster(ContentsActor* _pParent) { mpParentMonster = _pParent; }
	ContentsActor* GetParentMonster() { return mpParentMonster; }

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}

private:

};

