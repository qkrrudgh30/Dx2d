#pragma once
#include "Player.h"
#include "Monster.h"

enum OBJECTORDER
{
	Alpha = 1,
	UI = 2,
	Character = 3,
	Mob = 4,
	Cloud = 5,
	Tile = 6,
	BackGround = 7,
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
		static Monster* TestMonster;

	private:
		Actors() {		}
		~Actors() {		}
	};

private:
	GlobalContentsValue()	{	}

	~GlobalContentsValue()	{	}
};

