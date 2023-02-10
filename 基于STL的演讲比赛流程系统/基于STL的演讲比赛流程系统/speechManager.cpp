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
	this->initSpeech();		//��ʼ������
	this->createSpeaker();	//����12��ѡ��
	loadRecord();			//�����������
}
SpeechManager::~SpeechManager(){}
void SpeechManager::show_Menu()			//��ʾ�˵�
{
	cout << "*******" << endl;
	cout << "��ӭ�μ��ݽ�����" << endl;
	cout << "1.��ʼ" << endl;
	cout << "2.�鿴�����¼" << endl;
	cout << "3.����ݽ�����" << endl;
	cout << "0.�˳���������" << endl;
	cout << "*******" << endl;
	cout << endl;
}
void SpeechManager::exitSystem()	//�˳�����
{
	cout << "��ӭ�´�ʹ��" << endl;
	exit(0);
}
void SpeechManager:: initSpeech()	//��ʼ������������
{
	this->v1.clear();
	this->v2.clear();
	this->v3.clear();
	this->m_Speaker.clear();
	this->m_Index = 1;
	this->m_Record.clear();
}
void SpeechManager::createSpeaker()	//����12��ѡ��
{
	//����ѡ��
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0;i < nameSeed.size();i++)
	{

		string name = "ѡ��";
		name += nameSeed[i];
		Speaker	sp;
		sp.m_Name = name;
		for (int j = 0;j < 2;j++)
		{
			sp.m_Score[j] = 0;
		}
		//����ѡ�ֵı��
		this->v1.push_back(10001 + i);

		//ѡ�ֱ���Լ���Ӧѡ�֣����뵽map������
		this->m_Speaker.insert(make_pair(10001 + i, sp));
	}


}
void SpeechManager::startSpeech()		//��ʼ����
{
	//��һ�ֿ�ʼ����
	//1.��ǩ
	speechDraw();
	//2.����
	speechContest();
	//3.��ʾ�������
	showScore();
	
	//�ڶ��ֱ���
	m_Index = 2;
	//1.��ǩ
	speechDraw();
	//2.����
	speechContest();
	//3.��ʾ���ս��
	showScore();
	//4.����������ļ���
	saveRecord();
	cout << "���������ϣ�����" << endl;
	system("pause");
	system("cls");
}
void SpeechManager::speechDraw()		//��ǩ
{
	cout << "��" << m_Index << "�ֵ�ѡ�����ڳ�ǩ" << endl;
	cout << "-----------------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;

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
void SpeechManager::speechContest()		//����
{
	cout << "��" << m_Index << "�ֱ�����ʽ��ʼ!" << endl;

	multimap<double, int, greater<double>>groupScore;	//׼����ʱ���������С��ɼ�
	int num = 0;		//��¼��Ա������6��һ��

	vector<int>v_Src;	//����ѡ�ֵ�����
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
		sort(d.begin(), d.end(), greater<double>());	//����
		d.pop_front();	//ȥ����߷�
		d.pop_back();	//ȥ����ͷ�
		double sum = accumulate(d.begin(), d.end(), 0.0);	//�ܷ�
		double avg = sum / (double)d.size();		//ƽ����
		//cout << "��ţ�" << x << "  ���� :" << m_Speaker[x].m_Name << "  ƽ���֣�" << avg<< endl;

		m_Speaker[x].m_Score[m_Index-1] = avg;			//map �����İ�key������
		groupScore.insert(make_pair(avg, x));	//key�ǵ÷֣�value�Ǿ���ѡ�ֵı��
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С���������" << endl;
			for (const auto &x : groupScore)
			{
				cout << "���" << x.second <<"����"<<m_Speaker[x.second].m_Name<<"�ɼ�"<<x.first<<endl;
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
	cout << "��" << m_Index << "�ֱ�����ϣ�" << endl << endl;
	system("pause");
}
void SpeechManager:: showScore()		//��ʾ�÷�
{
	cout << "-----------------��" << m_Index << "�ֽ���ѡ����Ϣ���£�-------------" << endl;
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
		cout << "  ѡ�ֱ�ţ� " << x << "  ������ " << m_Speaker[x].m_Name << "  ѡ�ֵ÷�: "<< m_Speaker[x].m_Score[m_Index-1]<<endl;
	}
	system("pause");
	system("cls");
	show_Menu();
}
void SpeechManager::saveRecord()		//�����¼
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	if (!ofs.is_open()) { cout << "���ļ�ʧ��";return ; }
	for (auto x : v3)
	{
		ofs << x << "," << m_Speaker[x].m_Score[m_Index - 1] << ",";
	}
	cout << endl;
	ofs.close();
	cout << "��¼�Ѿ��ɹ�����" << endl;
	fileIsEmpty = false;
}
void SpeechManager::loadRecord()		//��ȡ��¼
{
	ifstream ifs;
	ifs.open("speech.csv", ios::in);
	if (!ifs.is_open()) { cout << "���ļ�ʧ��";fileIsEmpty = true; ifs.close();return; }
	//�ļ���յ������
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��" << endl;
		fileIsEmpty = true;
		ifs.close();
		return;
	}
	//�ļ���Ϊ��
	fileIsEmpty = false;
	ifs.putback(ch);	//�������ȡ�ĵ����ַ��Ż��� ��

	vector<string>v;	//���6���ַ���
	string data;
	int index = 0;		//�ڼ���
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
void SpeechManager::showRecord()		//��ʾ��¼
{
	if (fileIsEmpty) { cout << "�ļ�Ϊ�ջ��߲�����" << endl; }
	for (int i = 0;i < m_Record.size();i++)
	{
		cout << "��" << i + 1 << "��" << " �ھ���ţ�" << m_Record[i][0]
			<< " �÷֣�" << m_Record[i][1]
			<< "  �Ǿ���ţ�" << m_Record[i][2]
			<< "  �÷֣�" << m_Record[i][3]
			<< " ������ţ�" << m_Record[i][4]
			<< "  �÷֣�" << m_Record[i][5] << endl;
	}
	system("pause");
	system("cls");
}
void SpeechManager::clearRecord()		//����ļ�
{
	cout << "�Ƿ�ȷ������ļ�" << endl;
	cout << "1.��" << endl;
	cout << "2.��" << endl;
	//ȷ�����
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		initSpeech();		//��ʼ������������
		createSpeaker();	//����12��ѡ��
		loadRecord();		//���������¼
		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}

