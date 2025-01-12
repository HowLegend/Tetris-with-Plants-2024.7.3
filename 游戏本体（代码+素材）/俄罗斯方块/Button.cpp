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
        scale = 0.9f; // 鼠标悬停时缩放按钮
    }
    else
    {
        scale = 1.0f; // 恢复按钮原始大小
    }
}

bool Button::checkClick(int mouseX, int mouseY)
{
    if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height)
    {
        onClick(); // 执行按钮点击时的函数
        isMouseOver = false;
        scale = 1.0f;
        return true;
    }
    return false;
}

void Button::draw()
{
    int scaledWidth = width * scale;               // 缩放后的按钮宽度
    int scaledHeight = height * scale;             // 缩放后的按钮高度
    int scaledX = x + (width - scaledWidth) / 2;   // 缩放后的按钮x坐标
    int scaledY = y + (height - scaledHeight) / 2; // 缩放后的按钮y坐标

    if (isMouseOver)
    {
        setlinecolor(RGB(0, 120, 215));  // 鼠标悬停时按钮边框颜色  原色：RGB(0, 120, 215)
        setfillcolor(RGB(157, 196, 90)); // 鼠标悬停时按钮填充颜色  原色：RGB(229, 241, 251)
    }
    else
    {
        setlinecolor(RGB(55, 37, 97));  // 按钮边框颜色  原色：RGB(173, 173, 173)
        setfillcolor(RGB(247, 145, 1)); // 按钮填充颜色  原色：RGB(173, 173, 173)
    }

    // 设置抗锯齿
    LOGFONT f;                         // 字体变量
    gettextstyle(&f);                  // 获取当前字体
    f.lfQuality = ANTIALIASED_QUALITY; // 字体抗锯齿
    settextstyle(&f);

    fillrectangle(scaledX, scaledY, scaledX + scaledWidth, scaledY + scaledHeight); // 绘制按钮
    settextcolor(BLACK);                                                            // 设置文本颜色为黑色
    setbkmode(TRANSPARENT);                                                         // 设置文本背景透明
    settextstyle(30 * scale, 0, _T("楷体"));                                        // 设置文本大小和字体
    // 居中显示按钮文本
    int textX = scaledX + (scaledWidth - textwidth(text)) / 2;          // 计算文本在按钮中央的x坐标
    int textY = scaledY + (scaledHeight - textheight(_T("楷体"))) / 2;  // 计算文本在按钮中央的y坐标
    outtextxy(textX, textY, text);                                     // 在按钮上绘制文本
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
