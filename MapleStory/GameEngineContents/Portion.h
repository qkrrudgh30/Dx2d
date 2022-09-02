#pragma once
#include "Item.h"

// Ό³Έν :
class Portion : public Item
{
public:
	// constrcuter destructer
	Portion();
	~Portion();

	// delete Function
	Portion(const Portion& _Other) = delete;
	Portion(Portion&& _Other) noexcept = delete;
	Portion& operator=(const Portion& _Other) = delete;
	Portion& operator=(Portion&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update(float _fDeltaTime) override;
	virtual void End() override;

private:

};

