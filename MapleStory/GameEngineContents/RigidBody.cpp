#include "PreCompile.h"
#include "RigidBody.h"
#include "ContentsActor.h"

RigidBody::RigidBody() 
	: mfGravity(100.0f)
	, mpParent(nullptr)
{
}

RigidBody::~RigidBody() 
{
}

void RigidBody::Start()
{
	mpParent = dynamic_cast<ContentsActor*>(GetParent());
}

void RigidBody::Update(float _DeltaTime)
{
	if (nullptr == mpParent) { return; }
	if (false == mpParent->IsOnGround() && false == mpParent->IsOnLadder())
	{ 
		mpParent->GetTransform().SetWorldMove(float4{ 0.f, -mfGravity * _DeltaTime, 0.f, 0.f });
		// mpParent->mf4MoveAmount += float4{ 0.f, -mfGravity * _DeltaTime, 0.f, 0.f };
	}
}

void RigidBody::End()
{
}
