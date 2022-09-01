#pragma once

#include "Item.h"

// Ό³Έν :
class Meso : public Item
{
private:

public:
	// constrcuter destructer
	Meso();
	~Meso();

	// delete Function
	Meso(const Meso& _Other) = delete;
	Meso(Meso&& _Other) noexcept = delete;
	Meso& operator=(const Meso& _Other) = delete;
	Meso& operator=(Meso&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update(float _fDeltaTime) override;
	virtual void End() override;

private:

};

