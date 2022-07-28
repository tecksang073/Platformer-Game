/********************************************
Course : TGD2251 Game Physics
Session: Trimester 1, 2020/21
ID and Name #1 : 1161104534 Ho Teck Sang
Contacts #1 : 0126287073
********************************************/

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

#include "Level.h"

int main() {
	bool levelOne = true;
	bool restart = false;

	do
	{
		Level* levelPack = new Level();
		levelPack->createLevelOne();
		levelOne = levelPack->levelOneUpdate();

		if (levelOne == false)
		{
			restart = levelPack->levelOneLose();
			delete levelPack;
		}
		else
		{
			levelOne = true;
			restart = false;
			break;
		}

	} while (restart);

	return 0;
}