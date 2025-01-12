#include "Button.h"

Button::Button(int x, int y, int width, int height, const char* str, const function<void()>& onClick)
    : x(x), y(y), width(width), height(height), onClick(onClick), scale(1.0f), isMouseOver(false)
{
    strcpy_s(text, str);
}

Button::~Button()
{
}

void Button::checkMouseOver(int mouseX, int mouseY)
{
    isMouseOver = (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height);

    if (isMouseOver)
    {
        scale = 0.9f; // �����ͣʱ���Ű�ť
    }
    else
    {
        scale = 1.0f; // �ָ���ťԭʼ��С
    }
}

bool Button::checkClick(int mouseX, int mouseY)
{
    if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height)
    {
        onClick(); // ִ�а�ť���ʱ�ĺ���
        isMouseOver = false;
        scale = 1.0f;
        return true;
    }
    return false;
}

void Button::draw()
{
    int scaledWidth = width * scale;               // ���ź�İ�ť���
    int scaledHeight = height * scale;             // ���ź�İ�ť�߶�
    int scaledX = x + (width - scaledWidth) / 2;   // ���ź�İ�ťx����
    int scaledY = y + (height - scaledHeight) / 2; // ���ź�İ�ťy����

    if (isMouseOver)
    {
        setlinecolor(RGB(0, 120, 215));  // �����ͣʱ��ť�߿���ɫ  ԭɫ��RGB(0, 120, 215)
        setfillcolor(RGB(157, 196, 90)); // �����ͣʱ��ť�����ɫ  ԭɫ��RGB(229, 241, 251)
    }
    else
    {
        setlinecolor(RGB(55, 37, 97));  // ��ť�߿���ɫ  ԭɫ��RGB(173, 173, 173)
        setfillcolor(RGB(247, 145, 1)); // ��ť�����ɫ  ԭɫ��RGB(173, 173, 173)
    }

    // ���ÿ����
    LOGFONT f;                         // �������
    gettextstyle(&f);                  // ��ȡ��ǰ����
    f.lfQuality = ANTIALIASED_QUALITY; // ���忹���
    settextstyle(&f);

    fillrectangle(scaledX, scaledY, scaledX + scaledWidth, scaledY + scaledHeight); // ���ư�ť
    settextcolor(BLACK);                                                            // �����ı���ɫΪ��ɫ
    setbkmode(TRANSPARENT);                                                         // �����ı�����͸��
    settextstyle(30 * scale, 0, _T("����"));                                        // �����ı���С������
    // ������ʾ��ť�ı�
    int textX = scaledX + (scaledWidth - textwidth(text)) / 2;          // �����ı��ڰ�ť�����x����
    int textY = scaledY + (scaledHeight - textheight(_T("����"))) / 2;  // �����ı��ڰ�ť�����y����
    outtextxy(textX, textY, text);                                     // �ڰ�ť�ϻ����ı�
}

void Button::changeKey(char ch)
{
    sprintf_s(text, "%c", ch);
}

void Button::changeName(string name)
{
    strcpy_s(text, name.c_str());
}

char Button::getStatus() const
{
    return text[0];
}
