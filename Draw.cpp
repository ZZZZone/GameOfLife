#include "Draw.h"

Draw::Draw(int MapLength):MapLength(MapLength)
{
	initgraph(MapLength, MapLength);
	setbkcolor(WHITE);
	cleardevice();
	setlinecolor(WHITE);
	settextcolor(RED);
}

Draw::~Draw()
{
	closegraph();
}

void Draw::DrawPattern(vector<vector<bool>> &pattern) {
	setfillcolor(WHITE);
	fillrectangle(0, 0, MapLength, MapLength);
	setfillcolor(BLACK);
	int sideLength = MapLength / pattern.size();
	for (int i = 0; i < pattern.size(); ++i) {
		for (int j = 0; j < pattern.size(); ++j) {
			if (pattern[i][j]) {
				fillrectangle(j*sideLength, i*sideLength, (j + 1)*sideLength, (i + 1)*sideLength);
			}
		}
	}
	
	outtextxy(MapLength / 20, MapLength - MapLength / 20 ,"按A键减速，按D键加速，按回车键返回主界面");
}
