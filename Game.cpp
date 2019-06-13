#include "Game.h"

void Game::StartGame()
{
	while (true) {
		printf("*****生命游戏*****\n\n");
		printf("1.开始演变\n\n");
		printf("2.设置模式\n\n");
		printf("3.设置速度\n\n");
		printf("4.游戏介绍\n\n");
		printf("5.退出游戏\n\n");
		printf(">>");

		int choose = 0;
		cin >> choose;

		switch (choose)
		{
		case 1:
			StartEvolution();
			break;
		case 2:
			SetPatternMode();
			break;
		case 3:
			SetEvolutionSpeed();
			break;
		case 4:
			IntroduceGame();
			break;
		case 5:
			return;
		default:
			break;
		}

		system("cls");
	}
}

void Game::StartEvolution() {
	Evolution evolution(initPattern.getPattern(patternMode));
	vector<vector<bool>> pattern = evolution.pattern;
	Draw draw(MapLength);
	bool IfStable = false;
	while (true) {
		if (!IfStable) {
			draw.DrawPattern(pattern);
			pattern = evolution.getEvolutionResult(IfStable);
			if (pattern.size() > MapLength) return;
		}
		Sleep(evolutionSpeed);

		while (_kbhit()) {
			char hitChar = _getch();
			if (hitChar == 13) return;
			switch (hitChar) {
			case 'a':
				evolutionSpeed += 100;
				if (evolutionSpeed > 500) evolutionSpeed = 500;
				break;
			case 'd':
				if (evolutionSpeed > 100)evolutionSpeed -= 100;
				break;
			default:
				break;
			}
			cout <<hitChar<<","<< evolutionSpeed << endl;
		}
	}
}

void Game::SetPatternMode() {
	system("cls");
	cout << "以下是初始\"细胞自动机\"选项：\n" << endl;
	const vector<string> patternNames = initPattern.patternNames;
	for (int i = 0; i < (int)patternNames.size(); ++i) {
		cout << i + 1 << "." << patternNames[i].c_str() <<"\n"<< endl;
	}
	cout << to_string(patternNames.size() + 1)<<".自定义模式\n\n";
	cout << "选择：";

	int selectedMode = 0;
	cin>> selectedMode;
	if (selectedMode > 0 && selectedMode <= (int)patternNames.size()) {
		patternMode = selectedMode;
	}
	else if(selectedMode == patternNames.size() + 1){
		patternMode = selectedMode;
		initPattern.setCustomPattern(CustomPattern());
	}
}

vector<vector<bool>> Game::CustomPattern() {
	system("cls");
	cout << "输入矩阵长度（小于" << MapLength << ");";
	int inputSize;
	cin >> inputSize;
	if (inputSize < 3) inputSize = 3;
	if (inputSize > MapLength) inputSize = MapLength;
	vector<vector<bool> > pattern(inputSize, vector<bool>(inputSize, false));
	while (true) {
		cout << "请输入坐标X" << endl;
		int x, y;
		cin >> x;
		cout << "请输入坐标Y" << endl;
		cin >> y;
		if(!(x<0||y<0||x>=inputSize||y>=inputSize)) pattern[x][y] = true;
		cout << "按任意键继续输入， q键结束输入" << endl;
		while (!_kbhit()) {};
		char inputChar = _getch();
		if (inputChar == 'q') {
			cout << "\n";
			break;
		}
	}
	return pattern;
}

void Game::SetEvolutionSpeed() {
	system("cls");
	cout << "设置细胞演化的周期（单位：毫秒）：" ;
	int getTime = 500;
	cin >> getTime;

	if (getTime <= 0) getTime = 10;
	evolutionSpeed = getTime;
}

void Game::IntroduceGame() {
	system("cls");
	printf("生命游戏是John Conway 发现的一种游戏,游戏深受世界编程人士的喜爱。\n\n");
	printf("游戏规则如下：\n\n");
	printf("1.如果一个细胞周围有3个细胞为生（一个细胞周围共有8个细胞），则该细胞为生；\n\n");
	printf("2.如果一个细胞周围有2个细胞为生，则该细胞的生死状态保持不变；\n\n");
	printf("3.在其它情况下，该细胞为死。\n\n");
	printf("软件版本：1.01半UI版\n\n");
	printf("软件作者：俞世超，刘金宗\n\n");
	printf("按回车退出\n");

	while (true) {
		if (_kbhit()) {
			char hitChar = _getch();
			if (hitChar == 13) break;
		}
	}
}

void Game::PrintPattern(vector<vector<bool>> &pattern) {
	system("cls");
	for (int i = 0; i < (int)pattern.size(); ++i) {
		for (int j = 0; j < (int)pattern.size(); ++j) {
			if (pattern[i][j]) printf("国");
			else printf("..");
		}
		cout << "\n";
	}
	cout << "\n";
	cout << "\n按回车键回到主界面" << endl;
}
