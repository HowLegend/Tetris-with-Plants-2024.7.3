#include "InterfaceBook.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <conio.h>
using namespace std;

InterfaceBook::InterfaceBook(int width, int height)
    : width(width), height(height), currentIndex(-1), player("unknown")
{
}

InterfaceBook::~InterfaceBook()
{
    int pageSize = pages.size();
    for (int i = 0; i < pageSize; i++)
    {
        delete pages[i];
    }

    int size_page = page_buttons.size();
    for (int i = 0; i < size_page; i++)
    {
        int size_page_button = page_buttons[i].size();
        for (int j = 0; j < size_page_button; j++)
        {
            delete page_buttons[i][j];
        }
    }
}

void InterfaceBook::init()
{
    // ��ʼ����Ϸ�ٶ�ѡ��
    enum gameSpeed
    {
        NORMAL,
        FASTER,
        FASTEST
    };

    // ��ʼ��Ĭ����Ϸ����
    mode = 'A';         // ��ʼ��Ϸģʽ
    speed = NORMAL;     // ��ʼ��Ϸ�ٶ�
    plantMode = false;  // ��ʼ��ֲ���淨ģʽ

    // ��ʼ��Ĭ�ϰ�������
    useDirectionKeys = true;
    keyArray_ASCII[0] = 'w';
    keyArray_ASCII[1] = 's';
    keyArray_ASCII[2] = 'a';
    keyArray_ASCII[3] = 'd';
    keyArray_ASCII[4] = 'p';
    keyArray_ASCII[5] = ' ';
    keyArray_ASCII[6] = 'z';
    keyArray_ASCII[7] = 'x';

    // ��ʼ����Ϸ��������
    bg = "bg1";
    // ��ʼ��������ʽ����
    bk = "bk1";
    // ��ʼ�����ֲ���
    music = "music1";

    // ��ǰ���� ���� С�����ͼ���ز�
    Block::loadSubBlockImg(bk);

    // ��ʼ��needDraw
    notNeedWait = true;
    // ��ʼ��exit
    exit = false;
    // ��ʼ���浵��������
    recordIndex = "0";

    // ��������
    initgraph(width, height);



    // ������Ч
    IMAGE k[102] = { 0 };//����IMAGE����
    char adr[200];
    for (int i = 0; i < 102; i++) {
        sprintf_s(adr, "./materials/start/Image%d.jpg", i + 1);
        loadimage(&k[i], adr, 1112, 610);//����ͼƬ
    }
    IMAGE* pageStart = new IMAGE;
    loadimage(pageStart, "./materials/home.png");
    putimage(0, 0, pageStart);
    mciSendString("play ./materials/open.mp3", 0, 0, 0);
    for (int j = 0; j < 102; j++) {
        putimage(264 , 143 , &k[j]);
        Sleep(50);//��ʱ0.05����һ��ͼƬ
    }




    //-----------------------------------------------------------------------------------[0]��Ϸ��ҳ����

    // ������Ϸ��ҳ
    IMAGE* pageHome = new IMAGE;
    loadimage(pageHome, "./materials/home.png"); // ����home��ҳ��ͼƬ
    addPage(pageHome);                           // ��� [0]home��ҳ

    // ��� home��ҳ �İ�ť
    // ��ť"��ʼ��Ϸ"
    const char* str = "��ʼ��Ϸ";
    Button* buttonPlay = new Button(723, 328, 180, 60, str, [&]()
        {
            // �����Ի�������������ƣ�
            if (!InputBox(player, 15, "����Ҵ��ڣ�����ȡ��һ��δ��ɵ���Ϸ�浵�����򣬴�������Ϸ��", "�����������", "unknown", 0, 0, false))
            { // ���û�����룬�����ȡ����
                return;
            }
            getButton(1, 0)->changeName(player);
            setCurrentIndex(1); // ��� ��ť"��ʼ��Ϸ" ʱ���л��� ��Ϸҳ��
        });
    addButton(0, buttonPlay); // �� ��ť"��ʼ��Ϸ" ��ӵ� home��ҳ

    // ��ť"�淨�л�"
    str = "�淨�л�";
    Button* buttonSwitch = new Button(723, 408, 180, 60, str, [&]()
        {
            setCurrentIndex(2); // ��� ��ť"�淨�л�" ʱ���л��� ѡ���淨ҳ
        });
    addButton(0, buttonSwitch); // �� ��ť"�淨�л�" ��ӵ� home��ҳ

    // ��ť"���а�"
    str = "���а�";
    Button* buttonRankList = new Button(723, 488, 180, 60, str, [&]()
        {
            setCurrentIndex(3); // ��� ��ť"���а�" ʱ���л��� ���а�ҳ
        });
    addButton(0, buttonRankList); // �� ��ť"���а�" ��ӵ� home��ҳ

    // ��ť"����"
    str = "����";
    Button* buttonSetting = new Button(723, 568, 180, 60, str, [&]()
        {
            setCurrentIndex(4); // ��� ��ť"����" ʱ���л��� ����ѡ��ҳ��
        });
    addButton(0, buttonSetting); // �� ��ť"����" ��ӵ� home��ҳ

    // ��ť"����"
    str = "����";
    Button* buttonIntroduction = new Button(723, 648, 180, 60, str, [&]()
        {
            setCurrentIndex(7); // ��� ��ť"����" ʱ���л��� ��Ϸҳ��
        });
    addButton(0, buttonIntroduction); // �� ��ť"����" ��ӵ� home��ҳ

    // ��ť"�˳�"
    str = "�˳�";
    Button* buttonExit = new Button(320, 638, 60, 60, str, [&]()
        {
            exit = true; // ��� ��ť"�˳�" ʱ���˳���Ϸflag��Ϊtrue
        });
    addButton(0, buttonExit); // �� ��ť"�˳�" ��ӵ� home��ҳ

    //-----------------------------------------------------------------------------------[1]�浵ѡ�����

    // �����浵ѡ�����
    IMAGE* pageSelectRecord = new IMAGE;
    loadimage(pageSelectRecord, "./materials/recordSelecting.png"); // ����浵ѡ�����ͼƬ
    addPage(pageSelectRecord);                           // ��� [1]�浵ѡ�����

    // ��ť"�������"
    str = player;
    Button* buttonName = new Button(476, 189, 247, 38, str, [&]()
        {
            // �����Ի�������������ƣ�
            if (!InputBox(player, 15, "��������Ҫ�л�������˺�����", "�л��˺�", player, 0, 0, false))
            { // ���û�����룬�����ȡ����
                return;
            }
            getButton(1, 0)->changeName(player);
        });
    addButton(1, buttonName); // �� ��ť"������ҳ" ��ӵ� �浵ѡ�����

    // ��ť"������ҳ"
    str = "������ҳ";
    Button* buttonBack1 = new Button(298, 639, 120, 60, str, [&]()
        {
            setCurrentIndex(0); // ��� ��ť"������ҳ" ʱ���л��� home��ҳ
        });
    addButton(1, buttonBack1); // �� ��ť"������ҳ" ��ӵ� �浵ѡ�����

    // ��ť"�浵һ"
    str = "�浵һ";
    Button* buttonRecord1 = new Button(880, 309, 180, 60, str, [&]()
        {
            recordIndex = "1";
            // ���´浵
            hasRecord = getLastInfo(mode);
            setCurrentIndex(8); // ��� ��ť"�浵һ" ʱ���浵��ʶ����Ϊ��1��
        });
    addButton(1, buttonRecord1); // �� ��ť"�浵һ" ��ӵ� �浵ѡ�����

    // ��ť"�浵��"
    str = "�浵��";
    Button* buttonRecord2 = new Button(820, 399, 180, 60, str, [&]()
        {
            recordIndex = "2";
            // ���´浵
            hasRecord = getLastInfo(mode);
            setCurrentIndex(8); // ��� ��ť"�浵һ" ʱ���浵��ʶ����Ϊ��2��
        });
    addButton(1, buttonRecord2); // �� ��ť"�浵һ" ��ӵ� �浵ѡ�����

    // ��ť"�浵��"
    str = "�浵��";
    Button* buttonRecord3 = new Button(880, 489, 180, 60, str, [&]()
        {
            recordIndex = "3";
            // ���´浵
            hasRecord = getLastInfo(mode);
            setCurrentIndex(8); // ��� ��ť"�浵һ" ʱ���浵��ʶ����Ϊ��3��
        });
    addButton(1, buttonRecord3); // �� ��ť"�浵һ" ��ӵ� �浵ѡ�����

    // ��ť"�浵��"
    str = "�浵��";
    Button* buttonRecord4 = new Button(820, 579, 180, 60, str, [&]()
        {
            recordIndex = "4";
            // ���´浵
            hasRecord = getLastInfo(mode);
            setCurrentIndex(8); // ��� ��ť"�浵��" ʱ���浵��ʶ����Ϊ��4��
        });
    addButton(1, buttonRecord4); // �� ��ť"�浵��" ��ӵ� �浵ѡ�����

    // ��ť"�浵��"
    str = "�浵��";
    Button* buttonRecord5 = new Button(880, 669, 180, 60, str, [&]()
        {
            recordIndex = "5";
            // ���´浵
            hasRecord = getLastInfo(mode);
            setCurrentIndex(8); // ��� ��ť"�浵��" ʱ���浵��ʶ����Ϊ��5��
        });
    addButton(1, buttonRecord5); // �� ��ť"�浵��" ��ӵ� �浵ѡ�����

    //-----------------------------------------------------------------------------------[2]�淨�л�����

    // �����淨�л�����
    IMAGE* pageSwitch = new IMAGE;
    loadimage(pageSwitch, "./materials/select.png"); // �����淨�л�����ͼƬ
    addPage(pageSwitch);                             // ��� [2]�淨�л�����

    // ��ť"������ҳ"
    str = "������ҳ";
    Button* buttonBack2 = new Button(298, 639, 120, 60, str, [&]()
        {
            setCurrentIndex(0); // ��� ��ť"������ҳ" ʱ���л��� home��ҳ
        });
    addButton(2, buttonBack2); // �� ��ť"������ҳ" ��ӵ� �淨�л�����

    // ��ť"20 �� 10"
    str = "*";
    Button* button20_10 = new Button(745, 390, 30, 30, str, [&]()
        {
            mode = 'A';// ��� ��ť"20 �� 10" ʱ��mode �л�ΪA

            // �޸ı�������str,��ѡ����Ϊ��*��
            getButton(2, 1)->changeKey('*');
            getButton(2, 2)->changeKey(' ');

            // ������Ϸ�����Ԥ�����̴�С
            updateBackground(mode, bg); });
    addButton(2, button20_10); // �� ��ť"20 �� 10" ��ӵ� �淨�л�����

    // ��ť"20 �� 20"
    str = " ";
    Button* button20_20 = new Button(745, 470, 30, 30, str, [&]()
        {
            mode = 'B';// ��� ��ť"20 �� 20" ʱ��mode �л�ΪB

            // �޸ı�������str,��ѡ����Ϊ��*��
            getButton(2, 1)->changeKey(' ');
            getButton(2, 2)->changeKey('*');

            // ������Ϸ�����Ԥ�����̴�С
            updateBackground(mode, bg); });
    addButton(2, button20_20); // �� ��ť"20 �� 20" ��ӵ� �淨�л�����

    // ��ť"����"
    str = "*";
    Button* buttonNormal = new Button(1105, 395, 30, 30, str, [&]()
        {
            speed = NORMAL;// ��� ��ť"����" ʱ��speed �л��� NORMAL

            // �޸ı�������str,��ѡ����Ϊ��*��
            getButton(2, 3)->changeKey('*');
            getButton(2, 4)->changeKey(' ');
            getButton(2, 5)->changeKey(' '); });
    addButton(2, buttonNormal); // �� ��ť"����" ��ӵ� �淨�л�����

    // ��ť"����"
    str = " ";
    Button* buttonFaster = new Button(1105, 470, 30, 30, str, [&]()
        {
            speed = FASTER;// ��� ��ť"����" ʱ��speed �л��� FASTER

            // �޸ı�������str,��ѡ����Ϊ��*��
            getButton(2, 3)->changeKey(' ');
            getButton(2, 4)->changeKey('*');
            getButton(2, 5)->changeKey(' '); });
    addButton(2, buttonFaster); // �� ��ť"����" ��ӵ� �淨�л�����

    // ��ť"����"
    str = " ";
    Button* buttonFastest = new Button(1105, 545, 30, 30, str, [&]()
        {
            speed = FASTEST;// ��� ��ť"����" ʱ��speed �л��� FASTEST

            // �޸ı�������str,��ѡ����Ϊ��*��
            getButton(2, 3)->changeKey(' ');
            getButton(2, 4)->changeKey(' ');
            getButton(2, 5)->changeKey('*'); });
    addButton(2, buttonFastest); // �� ��ť"����" ��ӵ� �淨�л�����

    // ��ť"ֲ��ģʽ"
    str = " ";
    Button* buttonPlant = new Button(965, 650, 30, 30, str, [&]()
        {
            plantMode = true;// ��� ��ť"ֲ��ģʽ" ʱ��������ɫģʽ
          
            // �޸ı�������str,��ѡ����Ϊ��*��
            getButton(2, 6)->changeKey('*');
            getButton(2, 7)->changeKey(' ');
        });
    addButton(2, buttonPlant); // �� ��ť"ֲ��ģʽ" ��ӵ� �淨�л�����

    // ��ť"����ģʽ"
    str = "*";
    Button* buttonClassic = new Button(1170, 650, 30, 30, str, [&]()
        {
            plantMode = false;// ��� ��ť"����ģʽ" 

            // �޸ı�������str,��ѡ����Ϊ��*��
            getButton(2, 6)->changeKey(' ');
            getButton(2, 7)->changeKey('*');
        });
    addButton(2, buttonClassic); // �� ��ť"����ģʽ" ��ӵ� �淨�л�����

    //-----------------------------------------------------------------------------------[3]���а����

    // �������а����
    IMAGE* pageRankList = new IMAGE;
    loadimage(pageRankList, "./materials/rankList.png"); // �������а����ͼƬ
    addPage(pageRankList);                               // ��� [3]���а����

    // ��ť"������ҳ"
    str = "������ҳ";
    Button* buttonBack3 = new Button(298, 639, 120, 60, str, [&]()
        {
            setCurrentIndex(0); // ��� ��ť"������ҳ" ʱ���л��� home��ҳ
        });
    addButton(3, buttonBack3); // �� ��ť"������ҳ" ��ӵ� ���а����

    // ��ť"20 �� 10 ����"
    str = "20 �� 10����";
    Button* buttonRankList20_10 = new Button(1150, 560, 190, 60, str, [&]()
        {
            // ��� ��ť"20 �� 10" ʱ��չʾmodeA�����а�
            //��������
            LOGFONT f;//�������
            gettextstyle(&f);//��ȡ��ǰ����
            f.lfHeight = 30;//����߶�
            f.lfWidth = 15;//������
            f.lfQuality = ANTIALIASED_QUALITY;//���忹���
            setbkmode(TRANSPARENT);//���屳����Ϊ͸��
            strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("����"));
            settextstyle(&f);
            settextcolor(RGB(0, 0, 0));

            // �������а�����
            RankList ranklist('A');
            vector<Record> list = ranklist.getRankList();

            stringstream stream;

            for (int i = 0; i < 10 && i < list.size(); i++)
            {
                // �������û�з�������ң�ֹͣ����ȥ
                if (!list[i].score)
                    break;

                stream.clear();
                stream << setw(15) << left << list[i].player << setw(5) << right << list[i].score;
                string line;// ��һ�м�¼
                getline(stream, line);

                // stringתchar[]
                char cline[50];
                strcpy_s(cline, line.data());

                outtextxy(740, 235 + i * 50, cline);
            }



            //�������ϸ�������ҳ��
            notNeedWait = false; });
    addButton(3, buttonRankList20_10); // �� ��ť"20 �� 10" ��ӵ� ���а����

    // ��ť"20 �� 20 ����"
    str = "20 �� 20����";
    Button* buttonRankList20_20 = new Button(1150, 640, 190, 60, str, [&]()
        {
            // ��� ��ť"20 �� 20" ʱ��չʾmodeB�����а�
            //��������
            LOGFONT f;//�������
            gettextstyle(&f);//��ȡ��ǰ����
            f.lfHeight = 30;//����߶�
            f.lfWidth = 15;//������
            f.lfQuality = ANTIALIASED_QUALITY;//���忹���
            setbkmode(TRANSPARENT);//���屳����Ϊ͸��
            strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("����"));
            settextstyle(&f);
            settextcolor(RGB(0, 0, 0));

            // �������а�����
            RankList ranklist('B');
            vector<Record> list = ranklist.getRankList();

            stringstream stream;

            for (int i = 0; i < 10 && i < list.size(); i++)
            {
                // �������û�з�������ң�ֹͣ����ȥ
                if (!list[i].score)
                    break;

                stream.clear();
                stream << setw(15) << left << list[i].player << setw(5) << right << list[i].score;
                string line;// ��һ�м�¼
                getline(stream, line);

                // stringתchar[]
                char cline[50];
                strcpy_s(cline, line.data());

                outtextxy(740, 235 + i * 50, cline);
            }

            //�������ϸ�������ҳ��
            notNeedWait = false;

            //�������ϸ�������ҳ��
            notNeedWait = false; });
    addButton(3, buttonRankList20_20); // �� ��ť"20 �� 20" ��ӵ� ���а����

    //-----------------------------------------------------------------------------------[4]���ý���

    // �������ý���
    IMAGE* pageSetting = new IMAGE;
    loadimage(pageSetting, "./materials/setting.png"); // �������ý���ͼƬ
    addPage(pageSetting);                              // ��� [4]���ý���

    // ��ť"������ҳ"
    str = "������ҳ";
    Button* buttonBack4 = new Button(298, 639, 120, 60, str, [&]()
        {
            setCurrentIndex(0); // ��� ��ť"������ҳ" ʱ���л��� home��ҳ
        });
    addButton(4, buttonBack4); // �� ��ť"������ҳ" ��ӵ� ���а����

    // ��� ���ý��� �İ�ť
    // ��ť"�����޸�"
    str = "�����޸�";
    Button* buttonControl = new Button(723, 328, 180, 60, str, [&]()
        {
            setCurrentIndex(5); // ��� ��ť"�����޸�" ʱ���л��� �����޸�ҳ
        });
    addButton(4, buttonControl); // �� ��ť"�����޸�" ��ӵ� ���ý���

    // ��ť"��ۡ�����"
    str = "��ۡ�����";
    Button* buttonArt = new Button(723, 408, 180, 60, str, [&]()
        {
            setCurrentIndex(6); // ��� ��ť"��ۡ�����" ʱ���л��� ��ۡ������л�ҳ
        });
    addButton(4, buttonArt); // �� ��ť"��ۡ�����" ��ӵ� ���ý���

    //-----------------------------------------------------------------------------------[5]�����޸Ľ���

    // ���������޸Ľ���
    IMAGE* pageControl = new IMAGE;
    loadimage(pageControl, "./materials/control.png"); // ���밴���޸Ľ���ͼƬ
    addPage(pageControl);                              // ��� [5]�����޸Ľ���

    // ��ť"���ز˵�"
    str = "���ز˵�";
    Button* buttonBack5 = new Button(298, 639, 120, 60, str, [&]()
        {
            setCurrentIndex(4); // ��� ��ť"���ز˵�" ʱ���л��� ��һҳ����ѡ��
        });
    addButton(5, buttonBack5); // �� ��ť"���ز˵�" ��ӵ� �����޸Ľ���

    // ��ť"�ָ�Ĭ��"
    str = "�ָ�Ĭ��";
    Button* buttonDefault = new Button(298, 559, 120, 60, str, [&]()
        {
            // �ָ�Ĭ������
            useDirectionKeys = true;
            keyArray_ASCII[0] = 'w';
            keyArray_ASCII[1] = 's';
            keyArray_ASCII[2] = 'a';
            keyArray_ASCII[3] = 'd';
            keyArray_ASCII[4] = 'p';
            keyArray_ASCII[5] = ' ';
            keyArray_ASCII[6] = 'z';
            keyArray_ASCII[7] = 'x';

            // ����Ĭ�ϰ�����ʾ�ڶ�Ӧ����չʾ��
            getButton(5, 2)->changeKey('*');
            getButton(5, 3)->changeKey(' ');
            getButton(5, 4)->changeKey('w');
            getButton(5, 5)->changeKey('s');
            getButton(5, 6)->changeKey('a');
            getButton(5, 7)->changeKey('d');
            getButton(5, 8)->changeKey('p');
            getButton(5, 9)->changeKey('_');
            getButton(5, 10)->changeKey('z'); 
            getButton(5, 11)->changeKey('x'); });
    addButton(5, buttonDefault); // �� ��ť"�ָ�Ĭ��" ��ӵ� �����޸Ľ���

    // ��ť"�����Ԥ��"
    str = "*";
    Button* buttonDirectionKey = new Button(800, 220, 30, 30, str, [&]()
        {
            // ʹ�÷������flag
            useDirectionKeys = true;

            // �޸ı�������str,��ѡ����Ϊ��*��
            getButton(5, 2)->changeKey('*');
            getButton(5, 3)->changeKey(' '); });
    addButton(5, buttonDirectionKey);

    // ��ť"�ַ��Զ������"
    str = " ";
    Button* buttonASCIIKey = new Button(1025, 220, 30, 30, str, [&]()
        {
            // ʹ�÷������flag
            useDirectionKeys = false;

            // �޸ı�������str,��ѡ����Ϊ��*��
            getButton(5, 2)->changeKey(' ');
            getButton(5, 3)->changeKey('*'); });
    addButton(5, buttonASCIIKey);

    // ��ť"Up"
    str = "w";
    Button* buttonUp = new Button(1110, 295, 50, 50, str, [&]()
        {
            // �ȴ�����
            char ch;
            while (true)
            {
                if (_kbhit()) {//����Ƿ��а������룬��ֹ������ȴ��������ס
                    ch = _getch();//������ֱ�����룬��س�
                    break;
                }
            }

            // ���İ�����Up��
            keyArray_ASCII[0] = ch;

            // �޸ı�������strΪ����ֵ, �жϣ�����ǿո񣬾͸�ֵΪ��__��������Ϊ����
            if (ch == ' ')
                ch = '_';
            getButton(5, 4)->changeKey(ch); });
    addButton(5, buttonUp);

    // ��ť"Stop"
    str = "s";
    Button* buttonDown = new Button(1110, 367, 50, 50, str, [&]()
        {
            // �ȴ�����
            char ch;
            while (true)
            {
                if (_kbhit()) {//����Ƿ��а������룬��ֹ������ȴ��������ס
                    ch = _getch();//������ֱ�����룬��س�
                    break;
                }
            }

            // ���İ�����Stop��
            keyArray_ASCII[1] = ch;

            // �޸ı�������strΪ����ֵ, �жϣ�����ǿո񣬾͸�ֵΪ��__��������Ϊ����
            if (ch == ' ')
                ch = '_';
            getButton(5, 5)->changeKey(ch); });
    addButton(5, buttonDown);

    // ��ť"Left"
    str = "a";
    Button* buttonLeft = new Button(1110, 438, 50, 50, str, [&]()
        {
            // �ȴ�����
            char ch;
            while (true)
            {
                if (_kbhit()) {//����Ƿ��а������룬��ֹ������ȴ��������ס
                    ch = _getch();//������ֱ�����룬��س�
                    break;
                }
            }

            // ���İ�����Left��
            keyArray_ASCII[2] = ch;

            // �޸ı�������strΪ����ֵ, �жϣ�����ǿո񣬾͸�ֵΪ��__��������Ϊ����
            if (ch == ' ')
                ch = '_';
            getButton(5, 6)->changeKey(ch); });
    addButton(5, buttonLeft);

    // ��ť"Right"
    str = "d";
    Button* buttonRight = new Button(1110, 510, 50, 50, str, [&]()
        {
            // �ȴ�����
            char ch;
            while (true)
            {
                if (_kbhit()) {//����Ƿ��а������룬��ֹ������ȴ��������ס
                    ch = _getch();//������ֱ�����룬��س�
                    break;
                }
            }

            // ���İ�����Right��
            keyArray_ASCII[3] = ch;

            // �޸ı�������strΪ����ֵ, �жϣ�����ǿո񣬾͸�ֵΪ��__��������Ϊ����
            if (ch == ' ')
                ch = '_';
            getButton(5, 7)->changeKey(ch); });
    addButton(5, buttonRight);

    // ��ť"Pause"
    str = "p";
    Button* buttonPause = new Button(840, 605, 100, 50, str, [&]()
        {
            // �ȴ�����
            char ch;
            while (true)
            {
                if (_kbhit()) {//����Ƿ��а������룬��ֹ������ȴ��������ס
                    ch = _getch();//������ֱ�����룬��س�
                    break;
                }
            }

            // ���İ�����Pause��
            keyArray_ASCII[4] = ch;

            // �޸ı�������strΪ����ֵ, �жϣ�����ǿո񣬾͸�ֵΪ��__��������Ϊ����
            if (ch == ' ')
                ch = '_';
            getButton(5, 8)->changeKey(ch); });
    addButton(5, buttonPause);

    // ��ť"Drop"
    str = "_";
    Button* buttonDrop = new Button(840, 675, 100, 50, str, [&]()
        {
            // �ȴ�����
            char ch;
            while (true)
            {
                if (_kbhit()) {//����Ƿ��а������룬��ֹ������ȴ��������ס
                    ch = _getch();//������ֱ�����룬��س�
                    break;
                }
            }

            // ���İ�����Drop��
            keyArray_ASCII[5] = ch;

            // �޸ı�������strΪ����ֵ, �жϣ�����ǿո񣬾͸�ֵΪ��__��������Ϊ����
            if (ch == ' ')
                ch = '_';
            getButton(5, 9)->changeKey(ch); });
    addButton(5, buttonDrop);

    // ��ť"Ice"
    str = "z";
    Button* buttonIce = new Button(1160, 605, 50, 50, str, [&]()
        {
            // �ȴ�����
            char ch;
            while (true)
            {
                if (_kbhit()) {//����Ƿ��а������룬��ֹ������ȴ��������ס
                    ch = _getch();//������ֱ�����룬��س�
                    break;
                }
            }

            // ���İ�����Drop��
            keyArray_ASCII[6] = ch;

            // �޸ı�������strΪ����ֵ, �жϣ�����ǿո񣬾͸�ֵΪ��__��������Ϊ����
            if (ch == ' ')
                ch = '_';
            getButton(5, 10)->changeKey(ch); });
    addButton(5, buttonIce);

    // ��ť"Boom"
    str = "x";
    Button* buttonBoom = new Button(1160, 675, 50, 50, str, [&]()
        {
            // �ȴ�����
            char ch;
            while (true)
            {
                if (_kbhit()) {//����Ƿ��а������룬��ֹ������ȴ��������ס
                    ch = _getch();//������ֱ�����룬��س�
                    break;
                }
            }

            // ���İ�����Drop��
            keyArray_ASCII[7] = ch;

            // �޸ı�������strΪ����ֵ, �жϣ�����ǿո񣬾͸�ֵΪ��__��������Ϊ����
            if (ch == ' ')
                ch = '_';
            getButton(5, 11)->changeKey(ch); });
    addButton(5, buttonBoom);

    //-----------------------------------------------------------------------------------[6]��ۡ������л�����

    // ������ۡ������л�����
    IMAGE* pageArt = new IMAGE;
    loadimage(pageArt, "./materials/art.png"); // ������ۡ������л�����ͼƬ
    addPage(pageArt);                          // ��� [6]��ۡ������л�����

    // ��ť"���ز˵�"
    str = "���ز˵�";
    Button* buttonBack6 = new Button(298, 639, 120, 60, str, [&]()
        {
            setCurrentIndex(4); // ��� ��ť"���ز˵�" ʱ���л��� ��һҳ����ѡ��
        });
    addButton(6, buttonBack6); // �� ��ť"���ز˵�" ��ӵ� ��ۡ������л�����

    // ��ť"BG1"
    str = "*";
    Button* buttonBG1 = new Button(750, 275, 30, 30, str, [&]()
        {
            // ʹ�ñ���bg1
            bg = "bg1";

            // �޸ı�������strΪ����ֵ, �жϣ�����ǿո񣬾͸�ֵΪ��__��������Ϊ����
            getButton(6, 1)->changeKey('*');
            getButton(6, 2)->changeKey(' ');

            // ������Ϸ�����Ԥ�����̴�С
            updateBackground(mode, bg); });
    addButton(6, buttonBG1);

    // ��ť"BG2"
    str = " ";
    Button* buttonBG2 = new Button(1075, 275, 30, 30, str, [&]()
        {
            // ʹ�ñ���
            bg = "bg2";

            // �޸ı�������strΪ����ֵ, �жϣ�����ǿո񣬾͸�ֵΪ��__��������Ϊ����
            getButton(6, 1)->changeKey(' ');
            getButton(6, 2)->changeKey('*');

            // ������Ϸ�����Ԥ�����̴�С
            updateBackground(mode, bg); });
    addButton(6, buttonBG2);

    // ��ť"BlockType1"
    str = "*";
    Button* buttonBlockType1 = new Button(750, 455, 30, 30, str, [&]()
        {
            // ѡ�񷽿���ʽ1��Flag
            bk = "bk1";
            //���� ���� С�����ͼ���ز�
            Block::loadSubBlockImg(bk);

            // �޸ı�������strΪ����ֵ, �жϣ�����ǿո񣬾͸�ֵΪ��__��������Ϊ����
            getButton(6, 3)->changeKey('*');
            getButton(6, 4)->changeKey(' '); });
    addButton(6, buttonBlockType1);

    // ��ť"BlockType2"
    str = " ";
    Button* buttonBlockType2 = new Button(1075, 455, 30, 30, str, [&]()
        {
            // ѡ�񷽿���ʽ2
            bk = "bk2";
            //���� ���� С�����ͼ���ز�
            Block::loadSubBlockImg(bk);

            // �޸ı�������strΪ����ֵ, �жϣ�����ǿո񣬾͸�ֵΪ��__��������Ϊ����
            getButton(6, 3)->changeKey(' ');
            getButton(6, 4)->changeKey('*'); });
    addButton(6, buttonBlockType2);

    // ��ť"Music1"
    str = "*";
    Button* buttonMusic1 = new Button(750, 620, 30, 30, str, [&]()
        {
            // ѡ������1
            music = "music1";

            // �޸ı�������strΪ����ֵ, �жϣ�����ǿո񣬾͸�ֵΪ��__��������Ϊ����
            getButton(6, 5)->changeKey('*');
            getButton(6, 6)->changeKey(' '); });
    addButton(6, buttonMusic1);

    // ��ť"Music2"
    str = " ";
    Button* buttonMusic2 = new Button(1075, 620, 30, 30, str, [&]()
        {
            // ѡ������2
            music = "music2";

            // �޸ı�������strΪ����ֵ, �жϣ�����ǿո񣬾͸�ֵΪ��__��������Ϊ����
            getButton(6, 5)->changeKey(' ');
            getButton(6, 6)->changeKey('*'); });
    addButton(6, buttonMusic2);

    //-----------------------------------------------------------------------------------[7]���ܽ���

    // ���ܽ���
    IMAGE* pageDetail = new IMAGE;
    loadimage(pageDetail, "./materials/detail.png"); // ������ܽ���ͼƬ
    addPage(pageDetail);                             // ��� [7]���ܽ���

    // ��ť"������ҳ"
    str = "������ҳ";
    Button* buttonBack7 = new Button(298, 639, 120, 60, str, [&]()
        {
            setCurrentIndex(0); // ��� ��ť"������ҳ" ʱ���л��� home��ҳ
        });
    addButton(7, buttonBack7); // �� ��ť"������ҳ" ��ӵ� ���ܽ���

    //-----------------------------------------------------------------------------------[8]��Ϸ����

    // ������Ϸ����
    IMAGE* pagePlay = new IMAGE;
    loadimage(pagePlay, "./materials/play_bg1_A.png"); // ������Ϸ����ͼƬ
    addPage(pagePlay);                                 // ��� [1]��Ϸ����

    // ��ť"���ش浵ѡ��ҳ��"
    str = "����ѡ��";
    Button* buttonBack8 = new Button(298, 639, 120, 60, str, [&]()
        {
            setCurrentIndex(1); // ��� ��ť "���ش浵ѡ��ҳ��" ʱ���л��� �浵ѡ��
        });
    addButton(8, buttonBack8); // �� ��ť"���ش浵ѡ��ҳ��" ��ӵ� ��Ϸ����

    // ��ť"��ʼ��Ϸ"
    str = "��ʼ��Ϸ";
    Button* buttonStart = new Button(298, 479, 120, 60, str, [&]()
        {
            if (hasRecord) // �д浵
            {
                //��ȡ ����Ϸ������
                //��ȡ ģʽ
                int rows = 0;
                int cols = 0;
                if (mode == 'A')
                {
                    rows = 20;
                    cols = 10;
                }
                else if (mode == 'B')
                {
                    rows = 20;
                    cols = 20;
                }
                //��ȡ �ٶȵ��и�
                int speedNormal = 0;
                int speedQuick = 0;
                if (speed == NORMAL)
                {
                    speedNormal = 500;
                    speedQuick = 50;
                }
                else if (speed == FASTER)
                {
                    speedNormal = 200;
                    speedQuick = 20;
                }
                else if (speed == FASTEST)
                {
                    speedNormal = 70;
                    speedQuick = 10;
                }
                //������Ϸ
                Game game(rows, cols, 491, 723 - 20 * 27, 27,
                    lastScore, lastMap, lastNextBlockInfo, lastCurBlockInfo, player, recordIndex,
                    mode, speedNormal, speedQuick, plantMode,
                    useDirectionKeys, keyArray_ASCII,
                    bg, music);
                game.play();
            }
            else
            {
                //��ȡ ����Ϸ������
                //��ȡ ģʽ
                int rows = 0;
                int cols = 0;
                if (mode == 'A')
                {
                    rows = 20;
                    cols = 10;
                }
                else if (mode == 'B')
                {
                    rows = 20;
                    cols = 20;
                }
                //��ȡ �ٶȵ��и�
                int speedNormal = 0;
                int speedQuick = 0;
                if (speed == NORMAL)
                {
                    speedNormal = 500;
                    speedQuick = 50;
                }
                else if (speed == FASTER)
                {
                    speedNormal = 200;
                    speedQuick = 20;
                }
                else if (speed == FASTEST)
                {
                    speedNormal = 70;
                    speedQuick = 10;
                }
                //��ʼ�µ���Ϸ
                Game game(rows, cols, 491, 723 - 20 * 27, 27,
                    player, recordIndex,
                    mode, speedNormal, speedQuick, plantMode,
                    useDirectionKeys, keyArray_ASCII,
                    bg, music);
                game.play();
            } 
            // ���´浵
            hasRecord = getLastInfo(mode);
        
        });
    addButton(8, buttonStart); // �� ��ť"������Ϸ" ��ӵ� ��Ϸ����

    // ��ť"ɾ���浵"
    str = "ɾ���浵";
    Button* buttonDelete = new Button(298, 559, 120, 60, str, [&]()
        {
            // ȷ�ϵ���
            if (MessageBox(NULL, ("ȷ��Ҫɾ���ô浵��"), ("��ʾ"), MB_YESNO | MB_ICONQUESTION) == IDYES)
            {
                // ��֯ �浵����txt�ĵ�ַ
                string address1 = "./data/player/mode";
                string address2(1, mode);
                string address3 = "/";
                string address4 = player;
                string address5 = recordIndex;
                string address6 = ".txt";
                string address = address1 + address2 + address3 + address4 + address5 + address6;

                // ɾ���浵
                const char* file_path = address.data(); // ָ���ļ�·��
                if (remove(file_path) != 0) { // ����ɾ���ļ�
                    MessageBox(NULL, ("ɾ��ʧ��"), ("��ʾ"), MB_OK | MB_ICONERROR);
                }
                else {
                    MessageBox(NULL, ("ɾ���ɹ�"), ("��ʾ"), MB_OK | MB_ICONINFORMATION);
                    setCurrentIndex(1);
                }
            }

        });
    addButton(8, buttonDelete); // �� ��ť"����Ϸ" ��ӵ� ��Ϸ����

    setCurrentIndex(0); // ���ó�ʼ��ʾҳ��Ϊ home��ҳ
}

void InterfaceBook::run()
{
    ExMessage msg;

    while (true)
    {
        BeginBatchDraw();      // ��ʼ��������----����������棬��Ȼ��̫�淶�����ǿ��Խ����һ����Ϸ��������������
        if (peekmessage(&msg)) // ����Ƿ�����Ϣ
        {
            int mouseX = msg.x; // ��ȡ���x����
            int mouseY = msg.y; // ��ȡ���y����

            switch (msg.message)
            {
            case WM_LBUTTONDOWN:            // �����������¼�
                mouseClick(mouseX, mouseY); // ����������¼�
                break;
            case WM_MOUSEMOVE:             // ����ƶ��¼�
                mouseMove(mouseX, mouseY); // ��������ƶ��¼�
                break;
            }
        }

        draw(); // ���Ƶ�ǰҳ������

        Sleep(10);

        FlushBatchDraw(); // ��������������ʾ����Ļ��

        if (!notNeedWait)
        {
            // ֻ�иոյ���Ǹ���ť���ø��»��棬���滹û���İ�ťĬ����Ҫdraw�����Ի�ԭneedDraw
            notNeedWait = true;
            Sleep(2000);
        }

        if (exit)
            break;
    }

    EndBatchDraw(); // ������������
}

void InterfaceBook::addPage(IMAGE* page)
{
    pages.push_back(page);
    page_buttons.push_back({});
}

void InterfaceBook::addButton(int index, Button* button)
{
    if (index >= 0 && index < page_buttons.size())
    {
        page_buttons[index].push_back(button);
    }
}

void InterfaceBook::setCurrentIndex(int index)
{
    if (index >= 0 && index < pages.size())
    {
        currentIndex = index;
    }
}

Button* InterfaceBook::getButton(int i, int j)
{
    return this->page_buttons[i][j];
}

void InterfaceBook::mouseClick(int mouseX, int mouseY)
{
    if (currentIndex >= 0 && currentIndex < page_buttons.size())
    {
        for (Button* button : page_buttons[currentIndex])
        {
            if (button->checkClick(mouseX, mouseY))
            {
                break;
            }
        }
    }
}

void InterfaceBook::mouseMove(int mouseX, int mouseY)
{
    if (currentIndex >= 0 && currentIndex < page_buttons.size())
    {
        for (Button* button : page_buttons[currentIndex])
        {
            button->checkMouseOver(mouseX, mouseY);
        }
    }
}

void InterfaceBook::draw()
{

    if (notNeedWait)
    {
        if (currentIndex >= 0 && currentIndex < pages.size())
        {
            putimage(0, 0, pages[currentIndex]); // �ڴ����л��Ƶ�ǰҳ���ͼƬ

            if (currentIndex >= 0 && currentIndex < page_buttons.size())
            {
                for (Button* button : page_buttons[currentIndex])
                {
                    button->draw(); // ���Ƶ�ǰҳ���ϵ����а�ť
                }
            }
        }
        if (hasRecord && currentIndex == 8)
        {
            // ��ʾ�浵�еķ���
            drawLastMap_NextBlock_CurBlock();
            // ��ʾ�浵�еķ���
            drawLastScoreAndKeyInfo();
        }
    }
}

bool InterfaceBook::getLastInfo(char mode)
{
    // ��֯ �浵����txt�ĵ�ַ
    string address1 = "./data/player/mode";
    string address2(1, mode);
    string address3 = "/";
    string address4 = player;
    string address5 = recordIndex;
    string address6 = ".txt";
    string address = address1 + address2 + address3 + address4 + address5 + address6;

    ifstream ifs(address);
    if (!ifs.is_open())
    {
        return false; // ����false�Ա���������ж�
    }
    else
    {
        int cols_temp = 0; // ��ͬģʽ�µ�����
        if (mode == 'A')
        {
            cols_temp = 10;
        }
        else if (mode == 'B')
        {
            cols_temp = 20;
        }
        ifs >> lastScore; // �浵����
        if (lastMap.size() != 0)
        {
            // ���ԭ����map
            for (int i = 0; i < 20; i++)
            {
                lastMap.pop_back();
            }
        }
        for (int i = 0; i < 20; i++)
        {
            vector<int> tempRow;
            int data;
            for (int j = 0; j < cols_temp; j++) // �浵map
            {
                ifs >> data;
                tempRow.push_back(data);
            }
            lastMap.push_back(tempRow);
        }
        // �浵��Ϸ���� ���ͱ��+8��λ�ò���
        for (int i = 0; i < 9; i++)
        {
            ifs >> lastNextBlockInfo[i];
        }
        // �浵��Ϸ���� ���ͱ��+8��λ�ò���
        for (int i = 0; i < 9; i++)
        {
            ifs >> lastCurBlockInfo[i];
        }


        ifs.close(); // �ر��ļ�
        return true;
    }
}

void InterfaceBook::drawLastMap_NextBlock_CurBlock()
{
    // ��lastMapͼ
    IMAGE** imgs = GameBlock::getSubBlockImages(); // ͨ���������þ�̬��������ȡС����ͼ������
    for (int i = 0; i < lastMap.size(); i++)
    {
        for (int j = 0; j < lastMap[0].size(); j++)
        {
            if (lastMap[i][j] != 0)
            {
                int x = 491 + j * 27;
                int y = (723 - 20 * 27) + i * 27;
                putimage(x, y, imgs[lastMap[i][j] - 1]);
            }
        }
    }

    // ��lastNextBlock
    for (int i = 0; i < 4; i++)
    {
        int x = 491 + 27 * (lastNextBlockInfo[2 * i + 2] - 9 );	   // ���x����
        int y = (723 - 20 * 27) + 27 * (lastNextBlockInfo[2 * i + 1] + 4 );      // ���y����
        putimage(x, y, imgs[lastNextBlockInfo[0]-1]);
    }

    // ��lastCurBlock
    for (int i = 0; i < 4; i++)
    {
        if (lastCurBlockInfo[2 * i + 1] >= 0)
        {
            int x = 491 + 27 * lastCurBlockInfo[2 * i + 2];	   // ���x����
            int y = (723 - 20 * 27) + 27 * lastCurBlockInfo[2 * i + 1];      // ���y����

            putimage(x, y, imgs[lastCurBlockInfo[0] - 1]);
        }
        
    }

}

void InterfaceBook::drawLastScoreAndKeyInfo()
{
    char Text[32]; // �ı����� �ı�����

    if (mode == 'A')
    {
        // ��ӡ��ǰ��õķ���
        sprintf_s(Text, sizeof(Text), "��ǰ�÷֣�%d", lastScore);
        outtextxy(860, 620, Text);

        // ��ӡ��ǰ�Ĳ�������
        if (useDirectionKeys)
        {
            sprintf_s(Text, sizeof(Text), "��ת����");
            outtextxy(860, 170, Text);
            sprintf_s(Text, sizeof(Text), "���٣���");
            outtextxy(860, 220, Text);
            sprintf_s(Text, sizeof(Text), "���󣺡�");
            outtextxy(860, 270, Text);
            sprintf_s(Text, sizeof(Text), "���ң���");
            outtextxy(860, 320, Text);
            sprintf_s(Text, sizeof(Text), "��ͣ�˵���%c", keyArray_ASCII[4] == ' ' ? '_' : keyArray_ASCII[4]);
            outtextxy(860, 370, Text);
            sprintf_s(Text, sizeof(Text), "˲�����䣺%c", keyArray_ASCII[5] == ' ' ? '_' : keyArray_ASCII[5]);
            outtextxy(860, 420, Text);
        }
        else
        {
            sprintf_s(Text, sizeof(Text), "��ת��%c", keyArray_ASCII[0] == ' ' ? '_' : keyArray_ASCII[0]);
            outtextxy(860, 170, Text);
            sprintf_s(Text, sizeof(Text), "���٣�%c", keyArray_ASCII[1] == ' ' ? '_' : keyArray_ASCII[1]);
            outtextxy(860, 220, Text);
            sprintf_s(Text, sizeof(Text), "����%c", keyArray_ASCII[2] == ' ' ? '_' : keyArray_ASCII[2]);
            outtextxy(860, 270, Text);
            sprintf_s(Text, sizeof(Text), "���ң�%c", keyArray_ASCII[3] == ' ' ? '_' : keyArray_ASCII[3]);
            outtextxy(860, 320, Text);
            sprintf_s(Text, sizeof(Text), "��ͣ�˵���%c", keyArray_ASCII[4] == ' ' ? '_' : keyArray_ASCII[4]);
            outtextxy(860, 370, Text);
            sprintf_s(Text, sizeof(Text), "˲�����䣺%c", keyArray_ASCII[5] == ' ' ? '_' : keyArray_ASCII[5]);
            outtextxy(860, 420, Text);
        }
    }
    else if (mode == 'B')
    {
        // ��ӡ��ǰ��õķ���
        sprintf_s(Text, sizeof(Text), "��ǰ�÷֣�%d", lastScore);
        outtextxy(1100, 620, Text);

        // ��ӡ��ǰ�Ĳ�������
        if (useDirectionKeys)
        {
            sprintf_s(Text, sizeof(Text), "��ת����");
            outtextxy(1100, 170, Text);
            sprintf_s(Text, sizeof(Text), "���٣���");
            outtextxy(1100, 220, Text);
            sprintf_s(Text, sizeof(Text), "���󣺡�");
            outtextxy(1100, 270, Text);
            sprintf_s(Text, sizeof(Text), "���ң���");
            outtextxy(1100, 320, Text);
            sprintf_s(Text, sizeof(Text), "��ͣ�˵���%c", keyArray_ASCII[4] == ' ' ? '_' : keyArray_ASCII[4]);
            outtextxy(1100, 370, Text);
            sprintf_s(Text, sizeof(Text), "˲�����䣺%c", keyArray_ASCII[5] == ' ' ? '_' : keyArray_ASCII[5]);
            outtextxy(1100, 420, Text);
        }
        else
        {
            sprintf_s(Text, sizeof(Text), "��ת��%c", keyArray_ASCII[0] == ' ' ? '_' : keyArray_ASCII[0]);
            outtextxy(1100, 170, Text);
            sprintf_s(Text, sizeof(Text), "���٣�%c", keyArray_ASCII[1] == ' ' ? '_' : keyArray_ASCII[1]);
            outtextxy(1100, 220, Text);
            sprintf_s(Text, sizeof(Text), "����%c", keyArray_ASCII[2] == ' ' ? '_' : keyArray_ASCII[2]);
            outtextxy(1100, 270, Text);
            sprintf_s(Text, sizeof(Text), "���ң�%c", keyArray_ASCII[3] == ' ' ? '_' : keyArray_ASCII[3]);
            outtextxy(1100, 320, Text);
            sprintf_s(Text, sizeof(Text), "��ͣ�˵���%c", keyArray_ASCII[4] == ' ' ? '_' : keyArray_ASCII[4]);
            outtextxy(1100, 370, Text);
            sprintf_s(Text, sizeof(Text), "˲�����䣺%c", keyArray_ASCII[5] == ' ' ? '_' : keyArray_ASCII[5]);
            outtextxy(1100, 420, Text);
        }
    }
}

void InterfaceBook::updateBackground(char mode, string bg)
{
    if (mode == 'A' && bg == "bg1")
    {
        loadimage(pages[8], "./materials/play_bg1_A.png");
    }
    else if (mode == 'B' && bg == "bg1")
    {
        loadimage(pages[8], "./materials/play_bg1_B.png");
    }
    else if (mode == 'A' && bg == "bg2")
    {
        loadimage(pages[8], "./materials/play_bg2_A.png");
    }
    else if (mode == 'B' && bg == "bg2")
    {
        loadimage(pages[8], "./materials/play_bg2_B.png");
    }
}
