#pragma once
#include<iostream>
#include<vector>
#include<time.h>

using namespace std;

class InitPattern
{
public:
	const vector<string> patternNames;
public:
	InitPattern();
	void setCustomPattern(vector<vector<bool>> pattern);
	vector<vector<bool>> getPattern(int mode);
private:
	vector<vector<bool>> CustomPattern;
	vector<vector<bool>> Pattern1();
	vector<vector<bool>> Pattern2();
	vector<vector<bool>> Pattern3();
	vector<vector<bool>> Pattern4();
	vector<vector<bool>> Pattern5();
};

