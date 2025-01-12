#pragma once
#include <easyx.h>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

class Point
{
public:
    int row;
    int col;
};

class Block
{
public:
    // ���캯��
    Block();
    // ��������
    ~Block();

    // ������subBlock��ͼƬ���þ�̬�������ؾ�̬��������Ϊ������չ���������ܡ�ʱ���ֻ�δ����block����Ҫ���ⲿ����ͼ��
    static void loadSubBlockImg(string bk);
    // ���ƺ���
    virtual void draw(int leftMargin, int topMargin) = 0;
    // �����һ���ӿ� ���ڻ�÷�������
    virtual int getBlockType() = 0;
    // �½�
    void drop();
    // �����ƶ�
    void moveLeft();
    void moveRight();
    // ��ת
    void rotate();
    // �жϷ����Ƿ�Ϸ� ������硢��͸��������
    bool isInMapLegally(const vector<vector<int>>& map) const;
    // ���齫������Ϣ�洢����Ϸ����map�У�ʵ�̶ֹ�
    void solidify(vector<vector<int>>& map) const;
    // �����ṩsubBlock����λ�õĽӿ�
    Point* getSubBlockLocationArray();
    // ���ⲿ�ṩ ��� subBlock ͼ��ָ������� �ӿ�
    static IMAGE** getSubBlockImages();


protected:
    static IMAGE* imgs[7]; // ����������ɫ���͵� subBlock

    int blockType;      // ��������: 1~7������
    Point subBlocks[4]; // ��¼ ����һ������˹�����4��С�����λ��

    static int subBlockSize; // ͳһ�涨 subBlock �Ĵ�С��������Ϊ27���ص�������
};
