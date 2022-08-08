#pragma once
#include "Player.h"

enum OBJECTORDER
{
	UIGauge = -350,
	UIGaugeBG = -300,
	UIBackBoard = -200,
	UIBackGround = -150,
	Alpha = 1,
	Mob = 2,
	Character = 3,
	CharacterAttack = 4,
	BackGround = 5,
	UI = 6,
};

enum MOVINGSTATE
{
	MOVELEFT = -1,
	STAND = 0,
	MOVERIGHT = 1
};

// Ό³Έν :
class GlobalContentsValue
{
public:
	class Enums 
	{
	};

	class Actors 
	{
	public:
		// static Monster* TestMonster;

	private:
		Actors() {		}
		~Actors() {		}
	};

private:
	GlobalContentsValue()	{	}

	~GlobalContentsValue()	{	}
};

