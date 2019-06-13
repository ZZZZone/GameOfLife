#include "Game.h"

void Game::StartGame()
{
	while (true) {
		printf("*****������Ϸ*****\n\n");
		printf("1.��ʼ�ݱ�\n\n");
		printf("2.����ģʽ\n\n");
		printf("3.�����ٶ�\n\n");
		printf("4.��Ϸ����\n\n");
		printf("5.�˳���Ϸ\n\n");
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
	cout << "�����ǳ�ʼ\"ϸ���Զ���\"ѡ�\n" << endl;
	const vector<string> patternNames = initPattern.patternNames;
	for (int i = 0; i < (int)patternNames.size(); ++i) {
		cout << i + 1 << "." << patternNames[i].c_str() <<"\n"<< endl;
	}
	cout << to_string(patternNames.size() + 1)<<".�Զ���ģʽ\n\n";
	cout << "ѡ��";

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
	cout << "������󳤶ȣ�С��" << MapLength << ");";
	int inputSize;
	cin >> inputSize;
	if (inputSize < 3) inputSize = 3;
	if (inputSize > MapLength) inputSize = MapLength;
	vector<vector<bool> > pattern(inputSize, vector<bool>(inputSize, false));
	while (true) {
		cout << "����������X" << endl;
		int x, y;
		cin >> x;
		cout << "����������Y" << endl;
		cin >> y;
		if(!(x<0||y<0||x>=inputSize||y>=inputSize)) pattern[x][y] = true;
		cout << "��������������룬 q����������" << endl;
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
	cout << "����ϸ���ݻ������ڣ���λ�����룩��" ;
	int getTime = 500;
	cin >> getTime;

	if (getTime <= 0) getTime = 10;
	evolutionSpeed = getTime;
}

void Game::IntroduceGame() {
	system("cls");
	printf("������Ϸ��John Conway ���ֵ�һ����Ϸ,��Ϸ������������ʿ��ϲ����\n\n");
	printf("��Ϸ�������£�\n\n");
	printf("1.���һ��ϸ����Χ��3��ϸ��Ϊ����һ��ϸ����Χ����8��ϸ���������ϸ��Ϊ����\n\n");
	printf("2.���һ��ϸ����Χ��2��ϸ��Ϊ�������ϸ��������״̬���ֲ��䣻\n\n");
	printf("3.����������£���ϸ��Ϊ����\n\n");
	printf("����汾��1.01��UI��\n\n");
	printf("������ߣ���������������\n\n");
	printf("���س��˳�\n");

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
			if (pattern[i][j]) printf("��");
			else printf("..");
		}
		cout << "\n";
	}
	cout << "\n";
	cout << "\n���س����ص�������" << endl;
}
