#include "Evolution.h"

vector<vector<bool>> Evolution::getEvolutionResult(bool &IfStable) {
	nextEvolution(IfStable);
	return pattern;
}

int Evolution::getLiveCeilNum(int x, int y) {
	int liveCeilNum = 0;
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (i == 0 && j == 0) continue;
			int dx = x + i;
			int dy = y + j;
			if (dx < 0 || dx >= (int)pattern.size() || dy < 0 || dy >= (int)pattern.size()) continue;
			if (pattern[dx][dy]) ++liveCeilNum;
		}
	}
	return liveCeilNum;
}

void Evolution::nextEvolution(bool &IfStable) {
	vector<vector<bool>> nextPattern(pattern.size(), vector<bool>(pattern.size(), false));
	IfStable = true;
	bool IfExtend = false;
	for (int i = 0; i < pattern.size(); ++i) {
		for (int j = 0; j < pattern.size(); ++j) {
			int liveCeilNum = getLiveCeilNum(i, j);
			if (liveCeilNum == 3) nextPattern[i][j] = true;
			else if (liveCeilNum == 2) nextPattern[i][j] = pattern[i][j];
			else nextPattern[i][j] = false;

			if (!IfExtend) {
				IfExtend = nextPattern[i][j] && 
					(i == 0 || j == 0 || i == pattern.size() - 1 || j == pattern.size() - 1);
			}

			if (IfStable && nextPattern[i][j] != pattern[i][j]) IfStable = false;
		}
	}

	if (IfExtend) {
		vector<vector<bool>> ExtendPattern(pattern.size()*1.2, vector<bool>(pattern.size()*1.2, false));

		int delta= (ExtendPattern.size() - pattern.size()) / 2;
		for (int i = 0; i <  pattern.size(); ++i) {
			for (int j = 0; j < pattern.size(); ++j) {
				ExtendPattern[i + delta][j + delta] = nextPattern[i][j];
			}
		}
		nextPattern = ExtendPattern;
	}

	pattern = nextPattern;
}