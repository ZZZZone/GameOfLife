#pragma once
#include<iostream>
#include <windows.h>
#include"Evolution.h"
#include"InitPattern.h"
#include"Draw.h"
#include<conio.h>
#include<string>

using namespace std;

class Game
{
private:
	const int MapLength = 600;
	int evolutionSpeed;
	int patternMode;
	InitPattern initPattern;
public:
	Game() :evolutionSpeed(200), patternMode(1), initPattern(){}
	void StartGame();

private:
	void StartEvolution();
	void SetPatternMode();
	void SetEvolutionSpeed();
	void IntroduceGame();
	void PrintPattern(vector<vector<bool>> &pattern);
	vector<vector<bool>> CustomPattern();
};

