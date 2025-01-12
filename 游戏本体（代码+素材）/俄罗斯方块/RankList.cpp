#include "RankList.h"

bool cmpRule(Record a, Record b)
{
    return a.score > b.score;
}

RankList::RankList()
{
    mode = 'A';

    // ���
    if (!list.empty())
    {
        list.clear();
    }
}

RankList::RankList(char mode_temp)
    : mode(mode_temp)
{
    // ���
    if (!list.empty())
    {
        list.clear();
    }
    // ��ȡ��¼
    readRecord();
}

RankList::~RankList()
{
}

void RankList::saveRecord(Record rc)
{
    // ��rc��¼���뵽list����
    bool hasRecord = false; // ��������޼�¼�ı�ʶ
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i].player == rc.player)
        {
            list[i].score = rc.score;
            hasRecord = true; // ������м�¼��ֱ�Ӹĺ���ķ���
            break;
        }
    }
    if (!hasRecord) // ������޼�¼
    {
        list.push_back(rc);
    }

    // ��list��Ա���������
    // ��list����
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
    // ����mode��֯��Ӧ��txt�ļ���ַ
    string address1 = "./data/rankList/mode";
    string address2(1, mode);
    string address3 = ".txt";
    string address = address1 + address2 + address3;

    ofstream ofs;
    ofs.open(address); // ÿ�ζ�������дһ��
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
    // ����mode��֯��Ӧ��txt�ļ���ַ
    string address1 = "./data/rankList/mode";
    string address2(1, mode);
    string address3 = ".txt";
    string address = address1 + address2 + address3;

    ifstream ifs;
    ifs.open(address);
    if (!ifs) // �ļ�������
    {
        ofstream ofs(address);
        ofs.close(); // û�оʹ���һ��
        return;
    }

    string line;
    stringstream stream;
    Record rc;

    while (getline(ifs, line))
    {
        stream.clear();
        stream.str(line);

        // ��ȡ����
        stream >> rc.player >> rc.score;

        // �ӵ�list��
        list.push_back(rc);
    }
    // ��list����
    sort(list.begin(), list.end(), cmpRule);

    ifs.close();
}
