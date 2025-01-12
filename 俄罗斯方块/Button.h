#pragma once
#include <graphics.h>
#include <functional>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

// ��ť
class Button
{
public:
    // ���캯��
    Button(int x, int y, int width, int height, const char* str, const function<void()>& onClick);
    // ��������
    ~Button();
    // �������Ƿ��ڰ�ť�Ϸ�
    void checkMouseOver(int mouseX, int mouseY);
    // ������������ڰ�ť�ڣ�ִ�зº���
    bool checkClick(int mouseX, int mouseY);
    // ���ư�ť
    void draw();
    // ��������޸İ�ť���ƣ������ڰ����޸ĺ󣬰���ֱ��չʾ
    void changeKey(char ch);
    // ���İ�ť����
    void changeName(string name);
    // ��ȡ��ť״̬ (ֻȡ��һλ��ֻ�����ж��Ƿ� ʱ��ѡ��ť��*��)
    char getStatus() const;

private:
    int x;                    // ��ť���Ͻ�x����
    int y;                    // ��ť���Ͻ�y����
    int width;                // ��ť���
    int height;               // ��ť�߶�
    float scale;              // ���ű���������ʵ�������ͣЧ��
    bool isMouseOver;         // ��ʾ����Ƿ��ڰ�ť�Ϸ�
    char text[32];            // ��ť�ı�
    function<void()> onClick; // �����ť�����ĺ���
};