#include "PreCompile.h"
#include "Physics.h"
#include "ContentsActor.h"

// 이동 속도
// F = M * A
// A = F / M
// V += A * dt
// x += v * dt

Physics::Physics() 
	: mpParent(nullptr)
	, mf4Force()
	, mf4Mass()
	, mf4Accelation()
	, mf4Velocity()
	, mf4Position()
	, mfGravity()
{
}

Physics::~Physics() 
{
}

void Physics::Start()
{
	mpParent = dynamic_cast<ContentsActor*>(GetParent());
}

void Physics::Update(float _fDeltaTime)
{
	// mfAccelation = mpParent->mfAccelation;
	// mfVelocity = mpParent->mfVelocity;
	// 
	// mpParent->GetTransform().SetWorldMove();
}

void Physics::End()
{
}
