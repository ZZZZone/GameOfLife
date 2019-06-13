#include "InitPattern.h"

static const float PI = 3.1415926;

InitPattern::InitPattern() :patternNames({ "脉冲星","法式长棍","广播体操","十字架","随机" }) {}

vector<vector<bool>> InitPattern::getPattern(int mode) {
	switch (mode) {
	case 1:
		return Pattern1();
	case 2:
		return Pattern2();
	case 3:
		return Pattern3();
	case 4:
		return Pattern4();
	case 5:
		return Pattern5();
	default:
		break;
	}
	return vector<vector<bool>>();
}

vector<vector<bool>> InitPattern::Pattern1() {
	const int size = 17;
	vector<vector<bool>> pattern(size, vector<bool>(size, false));
	for (int j = 0; j < 3; ++j) {
		pattern[size / 2 - 4 + j][2] = true;
		pattern[size / 2 - 4 + j][size - 3] = true;
		pattern[size / 2 - 4 + j][size / 2 - 1] = true;
		pattern[size / 2 - 4 + j][size / 2 + 1] = true;

		pattern[size / 2 + 2 + j][2] = true;
		pattern[size / 2 + 2 + j][size - 3] = true;
		pattern[size / 2 + 2 + j][size / 2 - 1] = true;
		pattern[size / 2 + 2 + j][size / 2 + 1] = true;

		pattern[2][size / 2 - 4 + j] = true;
		pattern[size - 3][size / 2 - 4 + j] = true;
		pattern[size / 2 - 1][size / 2 - 4 + j] = true;
		pattern[size / 2 + 1][size / 2 - 4 + j] = true;

		pattern[2][size / 2 + 2 + j] = true;
		pattern[size - 3][size / 2 + 2 + j] = true;
		pattern[size / 2 - 1][size / 2 + 2 + j] = true;
		pattern[size / 2 + 1][size / 2 + 2 + j] = true;
	}
	return pattern;
}

vector<vector<bool>> InitPattern::Pattern2() {
	const int size = 33;
	vector<vector<bool>> pattern(size, vector<bool>(size, false));
	for (int i = 1; i<size - 1; ++i) {
		pattern[i][size / 2 - 1] = true;
		pattern[i][size / 2] = true;
		pattern[i][size / 2 + 1] = true;
	}
	return pattern;
}

vector<vector<bool>> InitPattern::Pattern3() {
	const int size = 30 + rand()%30;
	vector<vector<bool>> pattern(size, vector<bool>(size, false));

	for (int i = 2; i < size; i+=6) {
		for (int j = 1+(i/6)%2; j < size -2; j+=6) {
			pattern[i][j] = pattern[i][j + 1] = pattern[i][j + 2] = true;
		}
	}

	return pattern;
}

vector<vector<bool>> InitPattern::Pattern4() {
	const int size = 81;
	vector<vector<bool>> pattern(size, vector<bool>(size, false));

	for (int i = 5; i < size - 5; ++i) {
		pattern[size / 2][i] = true;
		pattern[i][size / 2] = true;
	}

	return pattern;
}

vector<vector<bool>> InitPattern::Pattern5() {
	srand((unsigned)time(0));
	const int size = 100;
	vector<vector<bool>> pattern(size, vector<bool>(size, false));

	for (int i = 0; i < size*5; ++i) {
		pattern[size/2 + (1-2*(rand()%2))*rand()%(size/3)][size / 2 + (1 - 2 * (rand() % 2))*rand() % (size / 3)] = true;
	}

	return pattern;
}
