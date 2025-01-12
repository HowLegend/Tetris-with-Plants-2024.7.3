#include<stdio.h>
#include<graphics.h>
#include<Windows.h>

int test()
{
    // 页面跳转特效
    IMAGE k[88] = { 0 };//定义IMAGE数组
    char adr[200];
    for (int i = 0; i < 88; i++) {
        sprintf_s(adr, "./materials/loading/Image%d.jpg", i + 1);
        loadimage(&k[i], adr, getwidth(), getheight());//加载图片
    }
    for (int j = 0; j < 88; j++) {
        putimage(265, 152, &k[j]);
        Sleep(50);//延时0.05秒贴一张图片
    }
    return 0;
}

void main01()
{
    initgraph(1640, 912);
    test();

}