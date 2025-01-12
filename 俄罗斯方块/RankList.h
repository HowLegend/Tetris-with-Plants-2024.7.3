#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

struct Record
{
    string player;
    int score;
};

class RankList
{
public:
    // ���캯��
    RankList();
    RankList(char mode_temp);
    // ��������
    ~RankList();
    // ����� �������� �ӿ�
    void saveRecord(Record rc);
    // ����� ��ȡ���а� �ӿ�
    vector<Record> getRankList();
    // ����� ��ȡָ����� ����߷�
    int getPlayerHighScore(string name);

private:
    // д������
    void writeRecord();
    // ��ȡ����
    void readRecord();

private:
    vector<Record> list; // ��¼����
    char mode;           // ��Ϸģʽ���
};