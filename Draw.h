#pragma once
#include<iostream>
#include<vector>
#include<easyx.h>

using namespace std;

class Draw
{
private:
	const int MapLength;
public:
	Draw(int MapLength = 500);
	~Draw();
	void DrawPattern(vector<vector<bool>> &pattern);
};

