// <hide/>

// Guardian.cpp

#include "PreCompile.h"
#include "Guardian.h"

Guardian::Guardian()
{
}

Guardian::~Guardian()
{
}

void Guardian::Start()
{
    mfWidth = 2327.f;
    mfHeight = 935.f;
    mpRenderer = CreateComponent<GameEngineTextureRenderer>();
    mpRenderer->GetTransform().SetWorldScale({ mfWidth, mfHeight, 1 });

    mpRenderer->SetTexture("Guardian2.png", 0);
}

void Guardian::Update(float _DeltaTime)
{
}

void Guardian::End()
{
}
