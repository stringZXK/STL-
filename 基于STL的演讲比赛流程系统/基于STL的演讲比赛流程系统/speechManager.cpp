#pragma once
#include "speechManager.h"
#include "speaker.h"
#include<deque>
#include<algorithm>
#include<functional>
#include<numeric>
#include<fstream>
SpeechManager::SpeechManager() 
{ 
	this->initSpeech();		//初始化属性
	this->createSpeaker();	//创建12名选手
	loadRecord();			//加载往届比赛
}
SpeechManager::~SpeechManager(){}
void SpeechManager::show_Menu()			//显示菜单
{
	cout << "*******" << endl;
	cout << "欢迎参加演讲比赛" << endl;
	cout << "1.开始" << endl;
	cout << "2.查看往届记录" << endl;
	cout << "3.清空演讲比赛" << endl;
	cout << "0.退出比赛程序" << endl;
	cout << "*******" << endl;
	cout << endl;
}
void SpeechManager::exitSystem()	//退出程序
{
	cout << "欢迎下次使用" << endl;
	exit(0);
}
void SpeechManager:: initSpeech()	//初始化容器和属性
{
	this->v1.clear();
	this->v2.clear();
	this->v3.clear();
	this->m_Speaker.clear();
	this->m_Index = 1;
	this->m_Record.clear();
}
void SpeechManager::createSpeaker()	//创建12名选手
{
	//创建选手
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0;i < nameSeed.size();i++)
	{

		string name = "选手";
		name += nameSeed[i];
		Speaker	sp;
		sp.m_Name = name;
		for (int j = 0;j < 2;j++)
		{
			sp.m_Score[j] = 0;
		}
		//创建选手的编号
		this->v1.push_back(10001 + i);

		//选手编号以及对应选手，放入到map容器中
		this->m_Speaker.insert(make_pair(10001 + i, sp));
	}


}
void SpeechManager::startSpeech()		//开始比赛
{
	//第一轮开始比赛
	//1.抽签
	speechDraw();
	//2.比赛
	speechContest();
	//3.显示晋级结果
	showScore();
	
	//第二轮比赛
	m_Index = 2;
	//1.抽签
	speechDraw();
	//2.比赛
	speechContest();
	//3.显示最终结果
	showScore();
	//4.保存分数到文件中
	saveRecord();
	cout << "本届比赛完毕！！！" << endl;
	system("pause");
	system("cls");
}
void SpeechManager::speechDraw()		//抽签
{
	cout << "第" << m_Index << "轮的选手正在抽签" << endl;
	cout << "-----------------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;

	srand(time(0));
	if (m_Index == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		for (auto x : v1)
		{
			cout << x << endl;
		}
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());

	}
	cout << "----------------------------" << endl;
	system("pause");
}
void SpeechManager::speechContest()		//比赛
{
	cout << "第" << m_Index << "轮比赛正式开始!" << endl;

	multimap<double, int, greater<double>>groupScore;	//准备临时容器，存放小组成绩
	int num = 0;		//记录人员个数，6人一组

	vector<int>v_Src;	//比赛选手的容器
	srand(time(0));
	if (m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	for (auto x : v_Src)
	{
		num++;
		deque<double>d;
		for (int i = 0;i < 10;i++)
		{
			double score = (rand() % 401 + 600) / 10.0;
			//cout << score << " ";
			d.push_back(score);
		}
		//cout << endl;
		sort(d.begin(), d.end(), greater<double>());	//排序
		d.pop_front();	//去除最高分
		d.pop_back();	//去除最低分
		double sum = accumulate(d.begin(), d.end(), 0.0);	//总分
		double avg = sum / (double)d.size();		//平均分
		//cout << "编号：" << x << "  姓名 :" << m_Speaker[x].m_Name << "  平均分：" << avg<< endl;

		m_Speaker[x].m_Score[m_Index-1] = avg;			//map 容器的按key？？？
		groupScore.insert(make_pair(avg, x));	//key是得分，value是具体选手的编号
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次" << endl;
			for (const auto &x : groupScore)
			{
				cout << "编号" << x.second <<"姓名"<<m_Speaker[x.second].m_Name<<"成绩"<<x.first<<endl;
			}
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin();it != groupScore.end() && count < 3;it++, count++)
			{
				if (m_Index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					v3.push_back((*it).second);
				}
			}
			cout << endl;
			groupScore.clear();
		}
	}
	cout <<"--------------------------"<< endl;
	cout << "第" << m_Index << "轮比赛完毕！" << endl << endl;
	system("pause");
}
void SpeechManager:: showScore()		//显示得分
{
	cout << "-----------------第" << m_Index << "轮晋级选手信息如下：-------------" << endl;
	vector<int>v;
	if (m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = v3;
	}
	for (auto x : v)
	{
		cout << "  选手编号： " << x << "  姓名： " << m_Speaker[x].m_Name << "  选手得分: "<< m_Speaker[x].m_Score[m_Index-1]<<endl;
	}
	system("pause");
	system("cls");
	show_Menu();
}
void SpeechManager::saveRecord()		//保存记录
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	if (!ofs.is_open()) { cout << "打开文件失败";return ; }
	for (auto x : v3)
	{
		ofs << x << "," << m_Speaker[x].m_Score[m_Index - 1] << ",";
	}
	cout << endl;
	ofs.close();
	cout << "记录已经成功保存" << endl;
	fileIsEmpty = false;
}
void SpeechManager::loadRecord()		//读取记录
{
	ifstream ifs;
	ifs.open("speech.csv", ios::in);
	if (!ifs.is_open()) { cout << "打开文件失败";fileIsEmpty = true; ifs.close();return; }
	//文件清空的情况？
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空" << endl;
		fileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件不为空
	fileIsEmpty = false;
	ifs.putback(ch);	//将上面读取的单个字符放回来 ？

	vector<string>v;	//存放6个字符串
	string data;
	int index = 0;		//第几届
	while (ifs >> data)
	{
		//cout << data << endl;
		int pos = -1;
		int start = 0;
		string temp;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1) break;
			temp = data.substr(start, pos - start);
			//cout << temp << endl;
			v.push_back(temp);
			start = pos + 1;
		}
		m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}
void SpeechManager::showRecord()		//显示记录
{
	if (fileIsEmpty) { cout << "文件为空或者不存在" << endl; }
	for (int i = 0;i < m_Record.size();i++)
	{
		cout << "第" << i + 1 << "届" << " 冠军编号：" << m_Record[i][0]
			<< " 得分：" << m_Record[i][1]
			<< "  亚军编号：" << m_Record[i][2]
			<< "  得分：" << m_Record[i][3]
			<< " 季军编号：" << m_Record[i][4]
			<< "  得分：" << m_Record[i][5] << endl;
	}
	system("pause");
	system("cls");
}
void SpeechManager::clearRecord()		//清空文件
{
	cout << "是否确定清空文件" << endl;
	cout << "1.是" << endl;
	cout << "2.否" << endl;
	//确认清空
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		initSpeech();		//初始化容器和属性
		createSpeaker();	//创建12名选手
		loadRecord();		//加载往届记录
		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");
}

