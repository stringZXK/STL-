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
		cout << "����������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1://��ʼ����
			sm.startSpeech();
			break;
		case 2://�鿴�������
			sm.showRecord();
			break;
		case 3://��ձ���
			sm.clearRecord();
			break;
		case 0://�˳�ϵͳ
			sm.exitSystem();		
			break;
		default:
			break;

		}
	}
		
	return 0;
}