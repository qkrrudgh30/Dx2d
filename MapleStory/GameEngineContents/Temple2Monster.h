#pragma once

#include "Monster.h"

// ���� :
class Temple2Monster : public Monster
{
public:
	// constrcuter destructer
	Temple2Monster();
	~Temple2Monster();

	// delete Function
	Temple2Monster(const Temple2Monster& _Other) = delete;
	Temple2Monster(Temple2Monster&& _Other) noexcept = delete;
	Temple2Monster& operator=(const Temple2Monster& _Other) = delete;
	Temple2Monster& operator=(Temple2Monster&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

