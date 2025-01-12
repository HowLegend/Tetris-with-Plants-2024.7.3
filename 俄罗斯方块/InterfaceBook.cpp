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
    // 初始化游戏速度选项
    enum gameSpeed
    {
        NORMAL,
        FASTER,
        FASTEST
    };

    // 初始化默认游戏参数
    mode = 'A';         // 初始游戏模式
    speed = NORMAL;     // 初始游戏速度
    plantMode = false;  // 初始化植物玩法模式

    // 初始化默认按键设置
    useDirectionKeys = true;
    keyArray_ASCII[0] = 'w';
    keyArray_ASCII[1] = 's';
    keyArray_ASCII[2] = 'a';
    keyArray_ASCII[3] = 'd';
    keyArray_ASCII[4] = 'p';
    keyArray_ASCII[5] = ' ';
    keyArray_ASCII[6] = 'z';
    keyArray_ASCII[7] = 'x';

    // 初始化游戏背景参数
    bg = "bg1";
    // 初始化方块样式参数
    bk = "bk1";
    // 初始化音乐参数
    music = "music1";

    // 提前调用 载入 小方块的图像素材
    Block::loadSubBlockImg(bk);

    // 初始化needDraw
    notNeedWait = true;
    // 初始化exit
    exit = false;
    // 初始化存档索引代号
    recordIndex = "0";

    // 创建窗口
    initgraph(width, height);



    // 开场特效
    IMAGE k[102] = { 0 };//定义IMAGE数组
    char adr[200];
    for (int i = 0; i < 102; i++) {
        sprintf_s(adr, "./materials/start/Image%d.jpg", i + 1);
        loadimage(&k[i], adr, 1112, 610);//加载图片
    }
    IMAGE* pageStart = new IMAGE;
    loadimage(pageStart, "./materials/home.png");
    putimage(0, 0, pageStart);
    mciSendString("play ./materials/open.mp3", 0, 0, 0);
    for (int j = 0; j < 102; j++) {
        putimage(264 , 143 , &k[j]);
        Sleep(50);//延时0.05秒贴一张图片
    }




    //-----------------------------------------------------------------------------------[0]游戏主页界面

    // 创建游戏主页
    IMAGE* pageHome = new IMAGE;
    loadimage(pageHome, "./materials/home.png"); // 载入home主页面图片
    addPage(pageHome);                           // 添加 [0]home主页

    // 添加 home主页 的按钮
    // 按钮"开始游戏"
    const char* str = "开始游戏";
    Button* buttonPlay = new Button(723, 328, 180, 60, str, [&]()
        {
            // 弹出对话框，输入玩家名称：
            if (!InputBox(player, 15, "若玩家存在，则会读取上一次未完成的游戏存档，否则，创建新游戏。", "输入玩家名称", "unknown", 0, 0, false))
            { // 如果没有输入，点击“取消”
                return;
            }
            getButton(1, 0)->changeName(player);
            setCurrentIndex(1); // 点击 按钮"开始游戏" 时，切换到 游戏页面
        });
    addButton(0, buttonPlay); // 将 按钮"开始游戏" 添加到 home主页

    // 按钮"玩法切换"
    str = "玩法切换";
    Button* buttonSwitch = new Button(723, 408, 180, 60, str, [&]()
        {
            setCurrentIndex(2); // 点击 按钮"玩法切换" 时，切换到 选择玩法页
        });
    addButton(0, buttonSwitch); // 将 按钮"玩法切换" 添加到 home主页

    // 按钮"排行榜"
    str = "排行榜";
    Button* buttonRankList = new Button(723, 488, 180, 60, str, [&]()
        {
            setCurrentIndex(3); // 点击 按钮"排行榜" 时，切换到 排行榜页
        });
    addButton(0, buttonRankList); // 将 按钮"排行榜" 添加到 home主页

    // 按钮"设置"
    str = "设置";
    Button* buttonSetting = new Button(723, 568, 180, 60, str, [&]()
        {
            setCurrentIndex(4); // 点击 按钮"设置" 时，切换到 设置选择页面
        });
    addButton(0, buttonSetting); // 将 按钮"设置" 添加到 home主页

    // 按钮"介绍"
    str = "介绍";
    Button* buttonIntroduction = new Button(723, 648, 180, 60, str, [&]()
        {
            setCurrentIndex(7); // 点击 按钮"介绍" 时，切换到 游戏页面
        });
    addButton(0, buttonIntroduction); // 将 按钮"介绍" 添加到 home主页

    // 按钮"退出"
    str = "退出";
    Button* buttonExit = new Button(320, 638, 60, 60, str, [&]()
        {
            exit = true; // 点击 按钮"退出" 时，退出游戏flag设为true
        });
    addButton(0, buttonExit); // 将 按钮"退出" 添加到 home主页

    //-----------------------------------------------------------------------------------[1]存档选择界面

    // 创建存档选择界面
    IMAGE* pageSelectRecord = new IMAGE;
    loadimage(pageSelectRecord, "./materials/recordSelecting.png"); // 载入存档选择界面图片
    addPage(pageSelectRecord);                           // 添加 [1]存档选择界面

    // 按钮"玩家名称"
    str = player;
    Button* buttonName = new Button(476, 189, 247, 38, str, [&]()
        {
            // 弹出对话框，输入玩家名称：
            if (!InputBox(player, 15, "请输入你要切换的玩家账号名称", "切换账号", player, 0, 0, false))
            { // 如果没有输入，点击“取消”
                return;
            }
            getButton(1, 0)->changeName(player);
        });
    addButton(1, buttonName); // 将 按钮"返回主页" 添加到 存档选择界面

    // 按钮"返回主页"
    str = "返回主页";
    Button* buttonBack1 = new Button(298, 639, 120, 60, str, [&]()
        {
            setCurrentIndex(0); // 点击 按钮"返回主页" 时，切换到 home主页
        });
    addButton(1, buttonBack1); // 将 按钮"返回主页" 添加到 存档选择界面

    // 按钮"存档一"
    str = "存档一";
    Button* buttonRecord1 = new Button(880, 309, 180, 60, str, [&]()
        {
            recordIndex = "1";
            // 更新存档
            hasRecord = getLastInfo(mode);
            setCurrentIndex(8); // 点击 按钮"存档一" 时，存档标识设置为“1”
        });
    addButton(1, buttonRecord1); // 将 按钮"存档一" 添加到 存档选择界面

    // 按钮"存档二"
    str = "存档二";
    Button* buttonRecord2 = new Button(820, 399, 180, 60, str, [&]()
        {
            recordIndex = "2";
            // 更新存档
            hasRecord = getLastInfo(mode);
            setCurrentIndex(8); // 点击 按钮"存档一" 时，存档标识设置为“2”
        });
    addButton(1, buttonRecord2); // 将 按钮"存档一" 添加到 存档选择界面

    // 按钮"存档三"
    str = "存档三";
    Button* buttonRecord3 = new Button(880, 489, 180, 60, str, [&]()
        {
            recordIndex = "3";
            // 更新存档
            hasRecord = getLastInfo(mode);
            setCurrentIndex(8); // 点击 按钮"存档一" 时，存档标识设置为“3”
        });
    addButton(1, buttonRecord3); // 将 按钮"存档一" 添加到 存档选择界面

    // 按钮"存档四"
    str = "存档四";
    Button* buttonRecord4 = new Button(820, 579, 180, 60, str, [&]()
        {
            recordIndex = "4";
            // 更新存档
            hasRecord = getLastInfo(mode);
            setCurrentIndex(8); // 点击 按钮"存档四" 时，存档标识设置为“4”
        });
    addButton(1, buttonRecord4); // 将 按钮"存档四" 添加到 存档选择界面

    // 按钮"存档五"
    str = "存档五";
    Button* buttonRecord5 = new Button(880, 669, 180, 60, str, [&]()
        {
            recordIndex = "5";
            // 更新存档
            hasRecord = getLastInfo(mode);
            setCurrentIndex(8); // 点击 按钮"存档五" 时，存档标识设置为“5”
        });
    addButton(1, buttonRecord5); // 将 按钮"存档五" 添加到 存档选择界面

    //-----------------------------------------------------------------------------------[2]玩法切换界面

    // 创建玩法切换界面
    IMAGE* pageSwitch = new IMAGE;
    loadimage(pageSwitch, "./materials/select.png"); // 载入玩法切换界面图片
    addPage(pageSwitch);                             // 添加 [2]玩法切换界面

    // 按钮"返回主页"
    str = "返回主页";
    Button* buttonBack2 = new Button(298, 639, 120, 60, str, [&]()
        {
            setCurrentIndex(0); // 点击 按钮"返回主页" 时，切换到 home主页
        });
    addButton(2, buttonBack2); // 将 按钮"返回主页" 添加到 玩法切换界面

    // 按钮"20 × 10"
    str = "*";
    Button* button20_10 = new Button(745, 390, 30, 30, str, [&]()
        {
            mode = 'A';// 点击 按钮"20 × 10" 时，mode 切换为A

            // 修改本按键的str,被选择标记为“*”
            getButton(2, 1)->changeKey('*');
            getButton(2, 2)->changeKey(' ');

            // 更新游戏界面的预览棋盘大小
            updateBackground(mode, bg); });
    addButton(2, button20_10); // 将 按钮"20 × 10" 添加到 玩法切换界面

    // 按钮"20 × 20"
    str = " ";
    Button* button20_20 = new Button(745, 470, 30, 30, str, [&]()
        {
            mode = 'B';// 点击 按钮"20 × 20" 时，mode 切换为B

            // 修改本按键的str,被选择标记为“*”
            getButton(2, 1)->changeKey(' ');
            getButton(2, 2)->changeKey('*');

            // 更新游戏界面的预览棋盘大小
            updateBackground(mode, bg); });
    addButton(2, button20_20); // 将 按钮"20 × 20" 添加到 玩法切换界面

    // 按钮"正常"
    str = "*";
    Button* buttonNormal = new Button(1105, 395, 30, 30, str, [&]()
        {
            speed = NORMAL;// 点击 按钮"正常" 时，speed 切换到 NORMAL

            // 修改本按键的str,被选择标记为“*”
            getButton(2, 3)->changeKey('*');
            getButton(2, 4)->changeKey(' ');
            getButton(2, 5)->changeKey(' '); });
    addButton(2, buttonNormal); // 将 按钮"正常" 添加到 玩法切换界面

    // 按钮"加速"
    str = " ";
    Button* buttonFaster = new Button(1105, 470, 30, 30, str, [&]()
        {
            speed = FASTER;// 点击 按钮"加速" 时，speed 切换到 FASTER

            // 修改本按键的str,被选择标记为“*”
            getButton(2, 3)->changeKey(' ');
            getButton(2, 4)->changeKey('*');
            getButton(2, 5)->changeKey(' '); });
    addButton(2, buttonFaster); // 将 按钮"加速" 添加到 玩法切换界面

    // 按钮"极速"
    str = " ";
    Button* buttonFastest = new Button(1105, 545, 30, 30, str, [&]()
        {
            speed = FASTEST;// 点击 按钮"极速" 时，speed 切换到 FASTEST

            // 修改本按键的str,被选择标记为“*”
            getButton(2, 3)->changeKey(' ');
            getButton(2, 4)->changeKey(' ');
            getButton(2, 5)->changeKey('*'); });
    addButton(2, buttonFastest); // 将 按钮"极速" 添加到 玩法切换界面

    // 按钮"植物模式"
    str = " ";
    Button* buttonPlant = new Button(965, 650, 30, 30, str, [&]()
        {
            plantMode = true;// 点击 按钮"植物模式" 时，开启特色模式
          
            // 修改本按键的str,被选择标记为“*”
            getButton(2, 6)->changeKey('*');
            getButton(2, 7)->changeKey(' ');
        });
    addButton(2, buttonPlant); // 将 按钮"植物模式" 添加到 玩法切换界面

    // 按钮"经典模式"
    str = "*";
    Button* buttonClassic = new Button(1170, 650, 30, 30, str, [&]()
        {
            plantMode = false;// 点击 按钮"经典模式" 

            // 修改本按键的str,被选择标记为“*”
            getButton(2, 6)->changeKey(' ');
            getButton(2, 7)->changeKey('*');
        });
    addButton(2, buttonClassic); // 将 按钮"经典模式" 添加到 玩法切换界面

    //-----------------------------------------------------------------------------------[3]排行榜界面

    // 创建排行榜界面
    IMAGE* pageRankList = new IMAGE;
    loadimage(pageRankList, "./materials/rankList.png"); // 载入排行榜界面图片
    addPage(pageRankList);                               // 添加 [3]排行榜界面

    // 按钮"返回主页"
    str = "返回主页";
    Button* buttonBack3 = new Button(298, 639, 120, 60, str, [&]()
        {
            setCurrentIndex(0); // 点击 按钮"返回主页" 时，切换到 home主页
        });
    addButton(3, buttonBack3); // 将 按钮"返回主页" 添加到 排行榜界面

    // 按钮"20 × 10 排行"
    str = "20 × 10排行";
    Button* buttonRankList20_10 = new Button(1150, 560, 190, 60, str, [&]()
        {
            // 点击 按钮"20 × 10" 时，展示modeA的排行榜
            //设置字体
            LOGFONT f;//字体变量
            gettextstyle(&f);//获取当前字体
            f.lfHeight = 30;//字体高度
            f.lfWidth = 15;//字体宽度
            f.lfQuality = ANTIALIASED_QUALITY;//字体抗锯齿
            setbkmode(TRANSPARENT);//字体背景设为透明
            strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("楷体"));
            settextstyle(&f);
            settextcolor(RGB(0, 0, 0));

            // 导入排行榜数据
            RankList ranklist('A');
            vector<Record> list = ranklist.getRankList();

            stringstream stream;

            for (int i = 0; i < 10 && i < list.size(); i++)
            {
                // 如果读到没有分数的玩家，停止读下去
                if (!list[i].score)
                    break;

                stream.clear();
                stream << setw(15) << left << list[i].player << setw(5) << right << list[i].score;
                string line;// 存一行记录
                getline(stream, line);

                // string转char[]
                char cline[50];
                strcpy_s(cline, line.data());

                outtextxy(740, 235 + i * 50, cline);
            }



            //不用马上更新整个页面
            notNeedWait = false; });
    addButton(3, buttonRankList20_10); // 将 按钮"20 × 10" 添加到 排行榜界面

    // 按钮"20 × 20 排行"
    str = "20 × 20排行";
    Button* buttonRankList20_20 = new Button(1150, 640, 190, 60, str, [&]()
        {
            // 点击 按钮"20 × 20" 时，展示modeB的排行榜
            //设置字体
            LOGFONT f;//字体变量
            gettextstyle(&f);//获取当前字体
            f.lfHeight = 30;//字体高度
            f.lfWidth = 15;//字体宽度
            f.lfQuality = ANTIALIASED_QUALITY;//字体抗锯齿
            setbkmode(TRANSPARENT);//字体背景设为透明
            strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("楷体"));
            settextstyle(&f);
            settextcolor(RGB(0, 0, 0));

            // 导入排行榜数据
            RankList ranklist('B');
            vector<Record> list = ranklist.getRankList();

            stringstream stream;

            for (int i = 0; i < 10 && i < list.size(); i++)
            {
                // 如果读到没有分数的玩家，停止读下去
                if (!list[i].score)
                    break;

                stream.clear();
                stream << setw(15) << left << list[i].player << setw(5) << right << list[i].score;
                string line;// 存一行记录
                getline(stream, line);

                // string转char[]
                char cline[50];
                strcpy_s(cline, line.data());

                outtextxy(740, 235 + i * 50, cline);
            }

            //不用马上更新整个页面
            notNeedWait = false;

            //不用马上更新整个页面
            notNeedWait = false; });
    addButton(3, buttonRankList20_20); // 将 按钮"20 × 20" 添加到 排行榜界面

    //-----------------------------------------------------------------------------------[4]设置界面

    // 创建设置界面
    IMAGE* pageSetting = new IMAGE;
    loadimage(pageSetting, "./materials/setting.png"); // 载入设置界面图片
    addPage(pageSetting);                              // 添加 [4]设置界面

    // 按钮"返回主页"
    str = "返回主页";
    Button* buttonBack4 = new Button(298, 639, 120, 60, str, [&]()
        {
            setCurrentIndex(0); // 点击 按钮"返回主页" 时，切换到 home主页
        });
    addButton(4, buttonBack4); // 将 按钮"返回主页" 添加到 排行榜界面

    // 添加 设置界面 的按钮
    // 按钮"按键修改"
    str = "按键修改";
    Button* buttonControl = new Button(723, 328, 180, 60, str, [&]()
        {
            setCurrentIndex(5); // 点击 按钮"按键修改" 时，切换到 按键修改页
        });
    addButton(4, buttonControl); // 将 按钮"按键修改" 添加到 设置界面

    // 按钮"外观、音乐"
    str = "外观、音乐";
    Button* buttonArt = new Button(723, 408, 180, 60, str, [&]()
        {
            setCurrentIndex(6); // 点击 按钮"外观、音乐" 时，切换到 外观、音乐切换页
        });
    addButton(4, buttonArt); // 将 按钮"外观、音乐" 添加到 设置界面

    //-----------------------------------------------------------------------------------[5]按键修改界面

    // 创建按键修改界面
    IMAGE* pageControl = new IMAGE;
    loadimage(pageControl, "./materials/control.png"); // 载入按键修改界面图片
    addPage(pageControl);                              // 添加 [5]按键修改界面

    // 按钮"返回菜单"
    str = "返回菜单";
    Button* buttonBack5 = new Button(298, 639, 120, 60, str, [&]()
        {
            setCurrentIndex(4); // 点击 按钮"返回菜单" 时，切换到 上一页设置选项
        });
    addButton(5, buttonBack5); // 将 按钮"返回菜单" 添加到 按键修改界面

    // 按钮"恢复默认"
    str = "恢复默认";
    Button* buttonDefault = new Button(298, 559, 120, 60, str, [&]()
        {
            // 恢复默认设置
            useDirectionKeys = true;
            keyArray_ASCII[0] = 'w';
            keyArray_ASCII[1] = 's';
            keyArray_ASCII[2] = 'a';
            keyArray_ASCII[3] = 'd';
            keyArray_ASCII[4] = 'p';
            keyArray_ASCII[5] = ' ';
            keyArray_ASCII[6] = 'z';
            keyArray_ASCII[7] = 'x';

            // 换回默认按键显示在对应按键展示上
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
    addButton(5, buttonDefault); // 将 按钮"恢复默认" 添加到 按键修改界面

    // 按钮"方向键预设"
    str = "*";
    Button* buttonDirectionKey = new Button(800, 220, 30, 30, str, [&]()
        {
            // 使用方向键的flag
            useDirectionKeys = true;

            // 修改本按键的str,被选择标记为“*”
            getButton(5, 2)->changeKey('*');
            getButton(5, 3)->changeKey(' '); });
    addButton(5, buttonDirectionKey);

    // 按钮"字符自定义组合"
    str = " ";
    Button* buttonASCIIKey = new Button(1025, 220, 30, 30, str, [&]()
        {
            // 使用方向键的flag
            useDirectionKeys = false;

            // 修改本按键的str,被选择标记为“*”
            getButton(5, 2)->changeKey(' ');
            getButton(5, 3)->changeKey('*'); });
    addButton(5, buttonASCIIKey);

    // 按钮"Up"
    str = "w";
    Button* buttonUp = new Button(1110, 295, 50, 50, str, [&]()
        {
            // 等待输入
            char ch;
            while (true)
            {
                if (_kbhit()) {//检测是否有按键输入，防止程序因等待输入而卡住
                    ch = _getch();//按按键直接输入，免回车
                    break;
                }
            }

            // 更改按键“Up”
            keyArray_ASCII[0] = ch;

            // 修改本按键的str为输入值, 判断，如果是空格，就赋值为“__”，否则为其他
            if (ch == ' ')
                ch = '_';
            getButton(5, 4)->changeKey(ch); });
    addButton(5, buttonUp);

    // 按钮"Stop"
    str = "s";
    Button* buttonDown = new Button(1110, 367, 50, 50, str, [&]()
        {
            // 等待输入
            char ch;
            while (true)
            {
                if (_kbhit()) {//检测是否有按键输入，防止程序因等待输入而卡住
                    ch = _getch();//按按键直接输入，免回车
                    break;
                }
            }

            // 更改按键“Stop”
            keyArray_ASCII[1] = ch;

            // 修改本按键的str为输入值, 判断，如果是空格，就赋值为“__”，否则为其他
            if (ch == ' ')
                ch = '_';
            getButton(5, 5)->changeKey(ch); });
    addButton(5, buttonDown);

    // 按钮"Left"
    str = "a";
    Button* buttonLeft = new Button(1110, 438, 50, 50, str, [&]()
        {
            // 等待输入
            char ch;
            while (true)
            {
                if (_kbhit()) {//检测是否有按键输入，防止程序因等待输入而卡住
                    ch = _getch();//按按键直接输入，免回车
                    break;
                }
            }

            // 更改按键“Left”
            keyArray_ASCII[2] = ch;

            // 修改本按键的str为输入值, 判断，如果是空格，就赋值为“__”，否则为其他
            if (ch == ' ')
                ch = '_';
            getButton(5, 6)->changeKey(ch); });
    addButton(5, buttonLeft);

    // 按钮"Right"
    str = "d";
    Button* buttonRight = new Button(1110, 510, 50, 50, str, [&]()
        {
            // 等待输入
            char ch;
            while (true)
            {
                if (_kbhit()) {//检测是否有按键输入，防止程序因等待输入而卡住
                    ch = _getch();//按按键直接输入，免回车
                    break;
                }
            }

            // 更改按键“Right”
            keyArray_ASCII[3] = ch;

            // 修改本按键的str为输入值, 判断，如果是空格，就赋值为“__”，否则为其他
            if (ch == ' ')
                ch = '_';
            getButton(5, 7)->changeKey(ch); });
    addButton(5, buttonRight);

    // 按钮"Pause"
    str = "p";
    Button* buttonPause = new Button(840, 605, 100, 50, str, [&]()
        {
            // 等待输入
            char ch;
            while (true)
            {
                if (_kbhit()) {//检测是否有按键输入，防止程序因等待输入而卡住
                    ch = _getch();//按按键直接输入，免回车
                    break;
                }
            }

            // 更改按键“Pause”
            keyArray_ASCII[4] = ch;

            // 修改本按键的str为输入值, 判断，如果是空格，就赋值为“__”，否则为其他
            if (ch == ' ')
                ch = '_';
            getButton(5, 8)->changeKey(ch); });
    addButton(5, buttonPause);

    // 按钮"Drop"
    str = "_";
    Button* buttonDrop = new Button(840, 675, 100, 50, str, [&]()
        {
            // 等待输入
            char ch;
            while (true)
            {
                if (_kbhit()) {//检测是否有按键输入，防止程序因等待输入而卡住
                    ch = _getch();//按按键直接输入，免回车
                    break;
                }
            }

            // 更改按键“Drop”
            keyArray_ASCII[5] = ch;

            // 修改本按键的str为输入值, 判断，如果是空格，就赋值为“__”，否则为其他
            if (ch == ' ')
                ch = '_';
            getButton(5, 9)->changeKey(ch); });
    addButton(5, buttonDrop);

    // 按钮"Ice"
    str = "z";
    Button* buttonIce = new Button(1160, 605, 50, 50, str, [&]()
        {
            // 等待输入
            char ch;
            while (true)
            {
                if (_kbhit()) {//检测是否有按键输入，防止程序因等待输入而卡住
                    ch = _getch();//按按键直接输入，免回车
                    break;
                }
            }

            // 更改按键“Drop”
            keyArray_ASCII[6] = ch;

            // 修改本按键的str为输入值, 判断，如果是空格，就赋值为“__”，否则为其他
            if (ch == ' ')
                ch = '_';
            getButton(5, 10)->changeKey(ch); });
    addButton(5, buttonIce);

    // 按钮"Boom"
    str = "x";
    Button* buttonBoom = new Button(1160, 675, 50, 50, str, [&]()
        {
            // 等待输入
            char ch;
            while (true)
            {
                if (_kbhit()) {//检测是否有按键输入，防止程序因等待输入而卡住
                    ch = _getch();//按按键直接输入，免回车
                    break;
                }
            }

            // 更改按键“Drop”
            keyArray_ASCII[7] = ch;

            // 修改本按键的str为输入值, 判断，如果是空格，就赋值为“__”，否则为其他
            if (ch == ' ')
                ch = '_';
            getButton(5, 11)->changeKey(ch); });
    addButton(5, buttonBoom);

    //-----------------------------------------------------------------------------------[6]外观、音乐切换界面

    // 创建外观、音乐切换界面
    IMAGE* pageArt = new IMAGE;
    loadimage(pageArt, "./materials/art.png"); // 载入外观、音乐切换界面图片
    addPage(pageArt);                          // 添加 [6]外观、音乐切换界面

    // 按钮"返回菜单"
    str = "返回菜单";
    Button* buttonBack6 = new Button(298, 639, 120, 60, str, [&]()
        {
            setCurrentIndex(4); // 点击 按钮"返回菜单" 时，切换到 上一页设置选项
        });
    addButton(6, buttonBack6); // 将 按钮"返回菜单" 添加到 外观、音乐切换界面

    // 按钮"BG1"
    str = "*";
    Button* buttonBG1 = new Button(750, 275, 30, 30, str, [&]()
        {
            // 使用背景bg1
            bg = "bg1";

            // 修改本按键的str为输入值, 判断，如果是空格，就赋值为“__”，否则为其他
            getButton(6, 1)->changeKey('*');
            getButton(6, 2)->changeKey(' ');

            // 更新游戏界面的预览棋盘大小
            updateBackground(mode, bg); });
    addButton(6, buttonBG1);

    // 按钮"BG2"
    str = " ";
    Button* buttonBG2 = new Button(1075, 275, 30, 30, str, [&]()
        {
            // 使用背景
            bg = "bg2";

            // 修改本按键的str为输入值, 判断，如果是空格，就赋值为“__”，否则为其他
            getButton(6, 1)->changeKey(' ');
            getButton(6, 2)->changeKey('*');

            // 更新游戏界面的预览棋盘大小
            updateBackground(mode, bg); });
    addButton(6, buttonBG2);

    // 按钮"BlockType1"
    str = "*";
    Button* buttonBlockType1 = new Button(750, 455, 30, 30, str, [&]()
        {
            // 选择方块样式1的Flag
            bk = "bk1";
            //重新 载入 小方块的图像素材
            Block::loadSubBlockImg(bk);

            // 修改本按键的str为输入值, 判断，如果是空格，就赋值为“__”，否则为其他
            getButton(6, 3)->changeKey('*');
            getButton(6, 4)->changeKey(' '); });
    addButton(6, buttonBlockType1);

    // 按钮"BlockType2"
    str = " ";
    Button* buttonBlockType2 = new Button(1075, 455, 30, 30, str, [&]()
        {
            // 选择方块样式2
            bk = "bk2";
            //重新 载入 小方块的图像素材
            Block::loadSubBlockImg(bk);

            // 修改本按键的str为输入值, 判断，如果是空格，就赋值为“__”，否则为其他
            getButton(6, 3)->changeKey(' ');
            getButton(6, 4)->changeKey('*'); });
    addButton(6, buttonBlockType2);

    // 按钮"Music1"
    str = "*";
    Button* buttonMusic1 = new Button(750, 620, 30, 30, str, [&]()
        {
            // 选择音乐1
            music = "music1";

            // 修改本按键的str为输入值, 判断，如果是空格，就赋值为“__”，否则为其他
            getButton(6, 5)->changeKey('*');
            getButton(6, 6)->changeKey(' '); });
    addButton(6, buttonMusic1);

    // 按钮"Music2"
    str = " ";
    Button* buttonMusic2 = new Button(1075, 620, 30, 30, str, [&]()
        {
            // 选择音乐2
            music = "music2";

            // 修改本按键的str为输入值, 判断，如果是空格，就赋值为“__”，否则为其他
            getButton(6, 5)->changeKey(' ');
            getButton(6, 6)->changeKey('*'); });
    addButton(6, buttonMusic2);

    //-----------------------------------------------------------------------------------[7]介绍界面

    // 介绍界面
    IMAGE* pageDetail = new IMAGE;
    loadimage(pageDetail, "./materials/detail.png"); // 载入介绍界面图片
    addPage(pageDetail);                             // 添加 [7]介绍界面

    // 按钮"返回主页"
    str = "返回主页";
    Button* buttonBack7 = new Button(298, 639, 120, 60, str, [&]()
        {
            setCurrentIndex(0); // 点击 按钮"返回主页" 时，切换到 home主页
        });
    addButton(7, buttonBack7); // 将 按钮"返回主页" 添加到 介绍界面

    //-----------------------------------------------------------------------------------[8]游戏界面

    // 创建游戏界面
    IMAGE* pagePlay = new IMAGE;
    loadimage(pagePlay, "./materials/play_bg1_A.png"); // 载入游戏界面图片
    addPage(pagePlay);                                 // 添加 [1]游戏界面

    // 按钮"返回存档选择页面"
    str = "返回选择";
    Button* buttonBack8 = new Button(298, 639, 120, 60, str, [&]()
        {
            setCurrentIndex(1); // 点击 按钮 "返回存档选择页面" 时，切换到 存档选择
        });
    addButton(8, buttonBack8); // 将 按钮"返回存档选择页面" 添加到 游戏界面

    // 按钮"开始游戏"
    str = "开始游戏";
    Button* buttonStart = new Button(298, 479, 120, 60, str, [&]()
        {
            if (hasRecord) // 有存档
            {
                //读取 对游戏的设置
                //读取 模式
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
                //读取 速度低中高
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
                //继续游戏
                Game game(rows, cols, 491, 723 - 20 * 27, 27,
                    lastScore, lastMap, lastNextBlockInfo, lastCurBlockInfo, player, recordIndex,
                    mode, speedNormal, speedQuick, plantMode,
                    useDirectionKeys, keyArray_ASCII,
                    bg, music);
                game.play();
            }
            else
            {
                //读取 对游戏的设置
                //读取 模式
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
                //读取 速度低中高
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
                //开始新的游戏
                Game game(rows, cols, 491, 723 - 20 * 27, 27,
                    player, recordIndex,
                    mode, speedNormal, speedQuick, plantMode,
                    useDirectionKeys, keyArray_ASCII,
                    bg, music);
                game.play();
            } 
            // 更新存档
            hasRecord = getLastInfo(mode);
        
        });
    addButton(8, buttonStart); // 将 按钮"继续游戏" 添加到 游戏界面

    // 按钮"删除存档"
    str = "删除存档";
    Button* buttonDelete = new Button(298, 559, 120, 60, str, [&]()
        {
            // 确认弹窗
            if (MessageBox(NULL, ("确定要删除该存档吗？"), ("提示"), MB_YESNO | MB_ICONQUESTION) == IDYES)
            {
                // 组织 存档内容txt的地址
                string address1 = "./data/player/mode";
                string address2(1, mode);
                string address3 = "/";
                string address4 = player;
                string address5 = recordIndex;
                string address6 = ".txt";
                string address = address1 + address2 + address3 + address4 + address5 + address6;

                // 删除存档
                const char* file_path = address.data(); // 指定文件路径
                if (remove(file_path) != 0) { // 尝试删除文件
                    MessageBox(NULL, ("删除失败"), ("提示"), MB_OK | MB_ICONERROR);
                }
                else {
                    MessageBox(NULL, ("删除成功"), ("提示"), MB_OK | MB_ICONINFORMATION);
                    setCurrentIndex(1);
                }
            }

        });
    addButton(8, buttonDelete); // 将 按钮"新游戏" 添加到 游戏界面

    setCurrentIndex(0); // 设置初始显示页面为 home主页
}

void InterfaceBook::run()
{
    ExMessage msg;

    while (true)
    {
        BeginBatchDraw();      // 开始批量绘制----放这里，放里面，虽然不太规范，但是可以解决“一次游戏后屏闪”的问题
        if (peekmessage(&msg)) // 检查是否有消息
        {
            int mouseX = msg.x; // 获取鼠标x坐标
            int mouseY = msg.y; // 获取鼠标y坐标

            switch (msg.message)
            {
            case WM_LBUTTONDOWN:            // 鼠标左键按下事件
                mouseClick(mouseX, mouseY); // 处理鼠标点击事件
                break;
            case WM_MOUSEMOVE:             // 鼠标移动事件
                mouseMove(mouseX, mouseY); // 处理鼠标移动事件
                break;
            }
        }

        draw(); // 绘制当前页面内容

        Sleep(10);

        FlushBatchDraw(); // 将缓冲区内容显示在屏幕上

        if (!notNeedWait)
        {
            // 只有刚刚点的那个按钮不用更新画面，后面还没按的按钮默认需要draw，所以还原needDraw
            notNeedWait = true;
            Sleep(2000);
        }

        if (exit)
            break;
    }

    EndBatchDraw(); // 结束批量绘制
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
            putimage(0, 0, pages[currentIndex]); // 在窗口中绘制当前页面的图片

            if (currentIndex >= 0 && currentIndex < page_buttons.size())
            {
                for (Button* button : page_buttons[currentIndex])
                {
                    button->draw(); // 绘制当前页面上的所有按钮
                }
            }
        }
        if (hasRecord && currentIndex == 8)
        {
            // 显示存档中的方块
            drawLastMap_NextBlock_CurBlock();
            // 显示存档中的分数
            drawLastScoreAndKeyInfo();
        }
    }
}

bool InterfaceBook::getLastInfo(char mode)
{
    // 组织 存档内容txt的地址
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
        return false; // 返回false以便后续程序判断
    }
    else
    {
        int cols_temp = 0; // 不同模式下的列数
        if (mode == 'A')
        {
            cols_temp = 10;
        }
        else if (mode == 'B')
        {
            cols_temp = 20;
        }
        ifs >> lastScore; // 存档分数
        if (lastMap.size() != 0)
        {
            // 清空原来的map
            for (int i = 0; i < 20; i++)
            {
                lastMap.pop_back();
            }
        }
        for (int i = 0; i < 20; i++)
        {
            vector<int> tempRow;
            int data;
            for (int j = 0; j < cols_temp; j++) // 存档map
            {
                ifs >> data;
                tempRow.push_back(data);
            }
            lastMap.push_back(tempRow);
        }
        // 存档游戏方块 类型编号+8个位置参数
        for (int i = 0; i < 9; i++)
        {
            ifs >> lastNextBlockInfo[i];
        }
        // 存档游戏方块 类型编号+8个位置参数
        for (int i = 0; i < 9; i++)
        {
            ifs >> lastCurBlockInfo[i];
        }


        ifs.close(); // 关闭文件
        return true;
    }
}

void InterfaceBook::drawLastMap_NextBlock_CurBlock()
{
    // 画lastMap图
    IMAGE** imgs = GameBlock::getSubBlockImages(); // 通过类名调用静态函数，获取小方块图像数组
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

    // 画lastNextBlock
    for (int i = 0; i < 4; i++)
    {
        int x = 491 + 27 * (lastNextBlockInfo[2 * i + 2] - 9 );	   // 算出x坐标
        int y = (723 - 20 * 27) + 27 * (lastNextBlockInfo[2 * i + 1] + 4 );      // 算出y坐标
        putimage(x, y, imgs[lastNextBlockInfo[0]-1]);
    }

    // 画lastCurBlock
    for (int i = 0; i < 4; i++)
    {
        if (lastCurBlockInfo[2 * i + 1] >= 0)
        {
            int x = 491 + 27 * lastCurBlockInfo[2 * i + 2];	   // 算出x坐标
            int y = (723 - 20 * 27) + 27 * lastCurBlockInfo[2 * i + 1];      // 算出y坐标

            putimage(x, y, imgs[lastCurBlockInfo[0] - 1]);
        }
        
    }

}

void InterfaceBook::drawLastScoreAndKeyInfo()
{
    char Text[32]; // 文本共用 文本数组

    if (mode == 'A')
    {
        // 打印当前获得的分数
        sprintf_s(Text, sizeof(Text), "当前得分：%d", lastScore);
        outtextxy(860, 620, Text);

        // 打印当前的操作按键
        if (useDirectionKeys)
        {
            sprintf_s(Text, sizeof(Text), "旋转：↑");
            outtextxy(860, 170, Text);
            sprintf_s(Text, sizeof(Text), "加速：↓");
            outtextxy(860, 220, Text);
            sprintf_s(Text, sizeof(Text), "向左：←");
            outtextxy(860, 270, Text);
            sprintf_s(Text, sizeof(Text), "向右：→");
            outtextxy(860, 320, Text);
            sprintf_s(Text, sizeof(Text), "暂停菜单：%c", keyArray_ASCII[4] == ' ' ? '_' : keyArray_ASCII[4]);
            outtextxy(860, 370, Text);
            sprintf_s(Text, sizeof(Text), "瞬间下落：%c", keyArray_ASCII[5] == ' ' ? '_' : keyArray_ASCII[5]);
            outtextxy(860, 420, Text);
        }
        else
        {
            sprintf_s(Text, sizeof(Text), "旋转：%c", keyArray_ASCII[0] == ' ' ? '_' : keyArray_ASCII[0]);
            outtextxy(860, 170, Text);
            sprintf_s(Text, sizeof(Text), "加速：%c", keyArray_ASCII[1] == ' ' ? '_' : keyArray_ASCII[1]);
            outtextxy(860, 220, Text);
            sprintf_s(Text, sizeof(Text), "向左：%c", keyArray_ASCII[2] == ' ' ? '_' : keyArray_ASCII[2]);
            outtextxy(860, 270, Text);
            sprintf_s(Text, sizeof(Text), "向右：%c", keyArray_ASCII[3] == ' ' ? '_' : keyArray_ASCII[3]);
            outtextxy(860, 320, Text);
            sprintf_s(Text, sizeof(Text), "暂停菜单：%c", keyArray_ASCII[4] == ' ' ? '_' : keyArray_ASCII[4]);
            outtextxy(860, 370, Text);
            sprintf_s(Text, sizeof(Text), "瞬间下落：%c", keyArray_ASCII[5] == ' ' ? '_' : keyArray_ASCII[5]);
            outtextxy(860, 420, Text);
        }
    }
    else if (mode == 'B')
    {
        // 打印当前获得的分数
        sprintf_s(Text, sizeof(Text), "当前得分：%d", lastScore);
        outtextxy(1100, 620, Text);

        // 打印当前的操作按键
        if (useDirectionKeys)
        {
            sprintf_s(Text, sizeof(Text), "旋转：↑");
            outtextxy(1100, 170, Text);
            sprintf_s(Text, sizeof(Text), "加速：↓");
            outtextxy(1100, 220, Text);
            sprintf_s(Text, sizeof(Text), "向左：←");
            outtextxy(1100, 270, Text);
            sprintf_s(Text, sizeof(Text), "向右：→");
            outtextxy(1100, 320, Text);
            sprintf_s(Text, sizeof(Text), "暂停菜单：%c", keyArray_ASCII[4] == ' ' ? '_' : keyArray_ASCII[4]);
            outtextxy(1100, 370, Text);
            sprintf_s(Text, sizeof(Text), "瞬间下落：%c", keyArray_ASCII[5] == ' ' ? '_' : keyArray_ASCII[5]);
            outtextxy(1100, 420, Text);
        }
        else
        {
            sprintf_s(Text, sizeof(Text), "旋转：%c", keyArray_ASCII[0] == ' ' ? '_' : keyArray_ASCII[0]);
            outtextxy(1100, 170, Text);
            sprintf_s(Text, sizeof(Text), "加速：%c", keyArray_ASCII[1] == ' ' ? '_' : keyArray_ASCII[1]);
            outtextxy(1100, 220, Text);
            sprintf_s(Text, sizeof(Text), "向左：%c", keyArray_ASCII[2] == ' ' ? '_' : keyArray_ASCII[2]);
            outtextxy(1100, 270, Text);
            sprintf_s(Text, sizeof(Text), "向右：%c", keyArray_ASCII[3] == ' ' ? '_' : keyArray_ASCII[3]);
            outtextxy(1100, 320, Text);
            sprintf_s(Text, sizeof(Text), "暂停菜单：%c", keyArray_ASCII[4] == ' ' ? '_' : keyArray_ASCII[4]);
            outtextxy(1100, 370, Text);
            sprintf_s(Text, sizeof(Text), "瞬间下落：%c", keyArray_ASCII[5] == ' ' ? '_' : keyArray_ASCII[5]);
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
