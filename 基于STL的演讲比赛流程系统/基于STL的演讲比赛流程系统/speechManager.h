#pragma once
#include "speaker.h"
#include<iostream>
#include<vector>
#include<map>

using namespace std;
class SpeechManager
{
public:
	vector<int>v1;  //�����һ�ֱ���ѡ�ֵı��
	vector<int>v2;	//����ڶ��ֱ���ѡ�ֵı��
	vector<int>v3;	//����ǰ����ѡ�ֱ������
	map<int, Speaker>m_Speaker;
	int m_Index;	//����������
	SpeechManager();
	~SpeechManager();
	void initSpeech();	//��ʼ������������
	void createSpeaker();

	void show_Menu();		//��ʾ�˵�
	void exitSystem();		//�˳�����
	void startSpeech();		//��ʼ����
	void speechDraw();		//��ǩ
	void speechContest();	//����
	void showScore();		//��ʾ�÷�
	void saveRecord();		//�����¼
	void loadRecord();		//��ȡ��¼
	bool fileIsEmpty;		//�ж��ļ��Ƿ�Ϊ��
	map<int, vector<string>>m_Record;	//��������¼������
	void showRecord();		//��ʾ��¼
	void clearRecord();		//����ļ�
};
