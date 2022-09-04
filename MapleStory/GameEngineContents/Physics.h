#pragma once

// 설명 :
class Physics
{
public:
	// constrcuter destructer
	Physics();
	~Physics();

	// delete Function
	Physics(const Physics& _Other) = delete;
	Physics(Physics&& _Other) noexcept = delete;
	Physics& operator=(const Physics& _Other) = delete;
	Physics& operator=(Physics&& _Other) noexcept = delete;

protected:

private:

};

// 이동 속도