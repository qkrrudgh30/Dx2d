// IntroLevel.cpp

#include "IntroLevel.h"
#include "TitleLogo.h"
#include "Enums.h"

IntroLevel::IntroLevel() 
{
}

IntroLevel::~IntroLevel() 
{
}

void IntroLevel::Start()
{
	CreateActor<TitleLogo>(GameObjectGroup::UI);
}

void IntroLevel::Update(float _DeltaTime)
{
	
}

void IntroLevel::End()
{
}
