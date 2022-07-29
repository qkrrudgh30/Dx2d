#include "PreCompile.h"
#include "RigidBody.h"
#include "ContentsActor.h"

RigidBody::RigidBody() 
	: mfGravity(400.0f)
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
	if (false == mpParent->IsOnGround()) 
	{ 
		mpParent->GetTransform().SetWorldMove(float4{ 0.f, -mfGravity * _DeltaTime, 0.f, 0.f });
	}
}

void RigidBody::End()
{
}
