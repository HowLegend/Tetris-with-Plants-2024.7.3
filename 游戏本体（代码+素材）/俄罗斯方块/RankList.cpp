#include "RankList.h"

bool cmpRule(Record a, Record b)
{
    return a.score > b.score;
}

RankList::RankList()
{
    mode = 'A';

    // 清空
    if (!list.empty())
    {
        list.clear();
    }
}

RankList::RankList(char mode_temp)
    : mode(mode_temp)
{
    // 清空
    if (!list.empty())
    {
        list.clear();
    }
    // 读取记录
    readRecord();
}

RankList::~RankList()
{
}

void RankList::saveRecord(Record rc)
{
    // 将rc记录加入到list里面
    bool hasRecord = false; // 该玩家有无记录的标识
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i].player == rc.player)
        {
            list[i].score = rc.score;
            hasRecord = true; // 该玩家有记录，直接改后面的分数
            break;
        }
    }
    if (!hasRecord) // 该玩家无记录
    {
        list.push_back(rc);
    }

    // 将list成员变量整理好
    // 对list排序
    sort(list.begin(), list.end(), cmpRule);

    writeRecord();
}

vector<Record> RankList::getRankList()
{
    return list;
}

int RankList::getPlayerHighScore(string name)
{
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i].player == name)
        {
            return list[i].score;
        }
    }
    return 0;
}

void RankList::writeRecord()
{
    // 根据mode组织对应的txt文件地址
    string address1 = "./data/rankList/mode";
    string address2(1, mode);
    string address3 = ".txt";
    string address = address1 + address2 + address3;

    ofstream ofs;
    ofs.open(address); // 每次都覆盖重写一遍
    if (!ofs)
        return;

    for (int i = 0; i < list.size(); i++)
    {
        ofs << list[i].player << " " << list[i].score << endl;
    }

    ofs.close();
}

void RankList::readRecord()
{
    // 根据mode组织对应的txt文件地址
    string address1 = "./data/rankList/mode";
    string address2(1, mode);
    string address3 = ".txt";
    string address = address1 + address2 + address3;

    ifstream ifs;
    ifs.open(address);
    if (!ifs) // 文件不存在
    {
        ofstream ofs(address);
        ofs.close(); // 没有就创建一个
        return;
    }

    string line;
    stringstream stream;
    Record rc;

    while (getline(ifs, line))
    {
        stream.clear();
        stream.str(line);

        // 读取数据
        stream >> rc.player >> rc.score;

        // 加到list中
        list.push_back(rc);
    }
    // 对list排序
    sort(list.begin(), list.end(), cmpRule);

    ifs.close();
}
