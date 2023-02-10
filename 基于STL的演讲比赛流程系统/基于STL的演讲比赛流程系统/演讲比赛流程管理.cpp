#include<iostream>
#include<map>
using namespace std;
#include "speechManager.h"
int main()
{
	SpeechManager sm;

	int choice = -1;
	while (true)
	{
		sm.show_Menu();
		cout << "请输入您的选择" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1://开始比赛
			sm.startSpeech();
			break;
		case 2://查看往届比赛
			sm.showRecord();
			break;
		case 3://清空比赛
			sm.clearRecord();
			break;
		case 0://退出系统
			sm.exitSystem();		
			break;
		default:
			break;

		}
	}
		
	return 0;
}