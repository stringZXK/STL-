#pragma once
#include "speaker.h"
#include<iostream>
#include<vector>
#include<map>

using namespace std;
class SpeechManager
{
public:
	vector<int>v1;  //保存第一轮比赛选手的编号
	vector<int>v2;	//保存第二轮比赛选手的编号
	vector<int>v3;	//保存前三名选手编号容器
	map<int, Speaker>m_Speaker;
	int m_Index;	//比赛的轮数
	SpeechManager();
	~SpeechManager();
	void initSpeech();	//初始化容器和属性
	void createSpeaker();

	void show_Menu();		//显示菜单
	void exitSystem();		//退出程序
	void startSpeech();		//开始比赛
	void speechDraw();		//抽签
	void speechContest();	//比赛
	void showScore();		//显示得分
	void saveRecord();		//保存记录
	void loadRecord();		//读取记录
	bool fileIsEmpty;		//判断文件是否为空
	map<int, vector<string>>m_Record;	//存放往届记录的容器
	void showRecord();		//显示记录
	void clearRecord();		//清空文件
};
