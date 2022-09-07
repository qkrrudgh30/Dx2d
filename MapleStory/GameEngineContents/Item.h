#pragma once

#include "ContentsActor.h"

// Ό³Έν :
class GameEngineTextureRenderer;
class GameEngineCollision;
class Player;
class RigidBody;
class ContentsLevel;
class Item : public ContentsActor
{
public:
	GameEngineTextureRenderer* mpRenderer;
	GameEngineCollision* mpCollision;
	Player* mpPlayer;
	OBJECTORDER mnOrder;
	RigidBody* mpRigidBody;
	float4 mf4PixelData;
	ContentsLevel* mpParentLevel;
	bool mbOnCreate;
	float mfSpeed;
	float mfBeforeAccTimeForCreate;
	float mfAccTime;
	float mfWidth;
	float mfHeight;
	unsigned int muAmount;
	bool mbAcquired;

public:
	// constrcuter destructer
	Item();
	~Item();

	// delete Function
	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

	void SetCollision(GameEngineCollision* _pCollision) { mpCollision = _pCollision; }
	GameEngineCollision* GetCollision() { return mpCollision; }

	void SetParentLevel(GameEngineLevel* _pParentLevel)
	{
		mpParentLevel = dynamic_cast<ContentsLevel*>(_pParentLevel);
	}

	void SetCreatedAfterSecond()
	{
		if (-1.f != mfBeforeAccTimeForCreate && 0.5f <= mfAccTime - mfBeforeAccTimeForCreate)
		{
			mbOnCreate = false;
			mfBeforeAccTimeForCreate = -1.f;
		}
	}

	unsigned int GetMesoAmount() { return muAmount; }

	OBJECTORDER GetItemInfo() { return static_cast<OBJECTORDER>(mnOrder); }

	void SetAcquired(bool _bAcquired) { mbAcquired = _bAcquired; }

protected:
	virtual void Start() override;
	virtual void Update(float _fDeltaTime) override;
	virtual void End() override;

private:

};

