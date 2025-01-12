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
    // 构造函数
    RankList();
    RankList(char mode_temp);
    // 析构函数
    ~RankList();
    // 对外的 保存数据 接口
    void saveRecord(Record rc);
    // 对外的 获取排行榜 接口
    vector<Record> getRankList();
    // 对外的 获取指定玩家 的最高分
    int getPlayerHighScore(string name);

private:
    // 写入数据
    void writeRecord();
    // 读取数据
    void readRecord();

private:
    vector<Record> list; // 记录数组
    char mode;           // 游戏模式标记
};