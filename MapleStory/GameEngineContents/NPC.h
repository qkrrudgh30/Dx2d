#pragma once
#include "ContentsActor.h"

// Ό³Έν :
class Player;
class NPC : public ContentsActor
{
private:
	Player* mpPlayer;
	bool mbStoreOn;

public:
	// constrcuter destructer
	NPC();
	~NPC();

	// delete Function
	NPC(const NPC& _Other) = delete;
	NPC(NPC&& _Other) noexcept = delete;
	NPC& operator=(const NPC& _Other) = delete;
	NPC& operator=(NPC&& _Other) noexcept = delete;

	void SetStoreOn(bool _bool) { mbStoreOn = _bool; }

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	void EndStand(const FrameAnimation_DESC& _Info);
	void EndSay(const FrameAnimation_DESC& _Info);
	void EndEye(const FrameAnimation_DESC& _Info);

};

