#pragma once
#include<iostream>
#include<vector>

using namespace std;

class Evolution
{
public:
	vector<vector<bool>> pattern;
	Evolution(vector<vector<bool>> pattern) :pattern(pattern) {};
	vector<vector<bool>> getEvolutionResult(bool &IfStable);
private:
	int getLiveCeilNum(int x, int y);
	void nextEvolution(bool &IfStable);
};

