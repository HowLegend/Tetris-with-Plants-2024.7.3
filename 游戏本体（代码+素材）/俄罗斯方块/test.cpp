#include<stdio.h>
#include<graphics.h>
#include<Windows.h>

int test()
{
    // ҳ����ת��Ч
    IMAGE k[88] = { 0 };//����IMAGE����
    char adr[200];
    for (int i = 0; i < 88; i++) {
        sprintf_s(adr, "./materials/loading/Image%d.jpg", i + 1);
        loadimage(&k[i], adr, getwidth(), getheight());//����ͼƬ
    }
    for (int j = 0; j < 88; j++) {
        putimage(265, 152, &k[j]);
        Sleep(50);//��ʱ0.05����һ��ͼƬ
    }
    return 0;
}

void main01()
{
    initgraph(1640, 912);
    test();

}