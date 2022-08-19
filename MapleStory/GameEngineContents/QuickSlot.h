#pragma once

// Ό³Έν :
class GameEngineUIRenderer;
class QuickSlot : public GameEngineActor
{
private:
	GameEngineUIRenderer* mpUIRenderer;
	float                 mfWidth;
	float                 mfHeight;

public:
	// constrcuter destructer
	QuickSlot();
	~QuickSlot();

	// delete Function
	QuickSlot(const QuickSlot& _Other) = delete;
	QuickSlot(QuickSlot&& _Other) noexcept = delete;
	QuickSlot& operator=(const QuickSlot& _Other) = delete;
	QuickSlot& operator=(QuickSlot&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}

private:

};

