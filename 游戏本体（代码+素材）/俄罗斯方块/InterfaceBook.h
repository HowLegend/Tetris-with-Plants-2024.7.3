#pragma once
#include <graphics.h>
#include <functional>
#include <string>
#include <vector>
#include <iostream>
#include "Button.h"
#include "Game.h"
#include <conio.h>
#include <mmsystem.h>
#include <Windows.h>
#include <cstdio>

using namespace std;

// ҳ����ϵͳ��
class InterfaceBook
{
public:
    // ���캯��
    InterfaceBook(int width, int height);
    // ��������
    ~InterfaceBook();
    // ��ʼ��ϵͳ�߼���ϵ������ͼ�δ��ڣ�����ҳ��Ͱ�ť
    void init();
    // ���У�������Ϣѭ��
    void run();

private:
    // ���һ��ҳ��
    void addPage(IMAGE* page);
    // ��ָ��ҳ�������һ����ť
    void addButton(int index, Button* button);
    // �����
    void mouseClick(int mouseX, int mouseY);
    // ����ƶ�����ť�Ϸ�
    void mouseMove(int mouseX, int mouseY);
    // ���Ƶ�ǰҳ�������
    void draw();
    // ���õ�ǰ��ʾ��ҳ������һҳ
    void setCurrentIndex(int index);
    // �ṩ��iҳ��j����ť�Ľӿ�
    Button* getButton(int i, int j);

    // ��ȡplayer�Ĵ浵lastMap,����ֵ��ʾ��player�Ƿ��д浵
    bool getLastInfo(char mode);
    // �����浵lastMap��ͼ��Ԥ�淽�����Ϸ����
    void drawLastMap_NextBlock_CurBlock();
    // �����浵�еķ����Ͱ�����Ϣ
    void drawLastScoreAndKeyInfo();
    // ������Ҹ�����Ϸ�����Ԥ�����������̴�С
    void updateBackground(char mode, string bg);

private:
    int width;                              // ���
    int height;                             // �߶�
    int currentIndex;                       // ��ǰҳ����������
    vector<IMAGE*> pages;                   // �洢����ҳ���ͼƬָ��
    vector<vector<Button*>> page_buttons;   // �洢ÿ��ҳ���ϵİ�ť
    bool exit;                              // �˳������Flag

    bool notNeedWait;   // һ�㰴ť����Ҫ����ͣ�ͣ����еİ�ť����ˢ��ҳ�棬��Ҫ����ͣ�ͼ���
    string recordIndex; // �浵���
    bool hasRecord;     // ��ʾ������д浵

    char player[15];             // �������
    int lastScore;               // ��Ҵ浵����score
    vector<vector<int>> lastMap; // ��Ҵ浵map
    int lastNextBlockInfo[9];    // ��Ҵ浵�е�Ԥ�淽�� ���ͱ��+8��λ�ò���
    int lastCurBlockInfo[9];     // ��Ҵ浵����Ϸ���� ���ͱ��+8��λ�ò���

    // ��Ҷ�ģʽ������
    char mode;      // ��Ϸ���̴�С����ΪA��B
    int speed;      // ��Ϸ�ٶ�
    bool plantMode; // ֲ�� ��Ϸ�淨

    // ��Ҷ԰���������
    bool useDirectionKeys;  // �Ƿ�ʹ�÷����Ԥ��
    char keyArray_ASCII[8]; // 0~3�洢����Զ�����������Ұ�����4��5�洢�ˡ���ͣ�˵�������˲�����䡱�İ���, 6��7�洢������������ը����

    // ��ҶԱ�����ѡ��
    string bg;
    // ��ҶԷ�����ʽ��ѡ��
    string bk;
    // ��Ҷ���Ϸ���ֵ�ѡ��
    string music;
};
