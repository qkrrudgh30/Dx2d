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
	ItemType = 6,
	
	MesoItem = 7,
	Meso1 = 8,
	Meso2 = 9,
	Meso3 = 10,
	Etc1 = 11,
	Etc2 = 12,
	Etc3 = 13,
	Portion1 = 14,
	Portion2 = 15,
	Portion3 = 16,
	
	UI = 17,
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

