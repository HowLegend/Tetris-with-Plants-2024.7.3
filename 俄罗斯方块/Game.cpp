#include "Game.h"
#include "Block.h"
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <mmsystem.h>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
using namespace std;
#pragma comment(lib, "winmm.lib")

Game::Game(int rows, int cols, int leftMargin, int topMargin, int blockSize, // 基础参数
    char* player, string recordIndex_temp,                                   // 玩家信息
    char mode, int speedNormal, int speedQuick, bool plantMode,              // 玩法参数
    bool useDirectionKeys_temp, char keyArray_ASCII[],                       // 按键参数
    string bg_temp, string music_temp)                                       // 图片、音乐参数

    // 初始化列表
    : rows_m(rows), cols_m(cols), leftMargin_m(leftMargin),
    topMargin_m(topMargin), blockSize_m(blockSize),
    hasUseRecordInfo_before(false), recordIndex(recordIndex_temp), lastCurBlock(NULL), lastNextBlock(NULL),
    mode(mode), SPEED_NORMAL(speedNormal), SPEED_QUICK(speedQuick), isPlantMode(plantMode),
    useDirectionKeys(useDirectionKeys_temp),
    bg(bg_temp), music(music_temp),
    // 一下为初始化参数
    randNum(0),// 初始化随机数
    player(player),// 这场游戏的玩家名字
    delay(SPEED_NORMAL),// 初始化速度
    SPEED_SUDDEN(1),SPEED_ICE(1000),// 初始化瞬间下落的速度、冻结时的速度
    update(false),gameIsStop(false),gameExit(false),isIce(false),becomeBoom(false),// 初始化标识
    curBlock(NULL),nextBlock(NULL),lastBlock(NULL),shadowBlock(NULL),lastShadow(NULL), ranklistPtr(NULL), pageStop(NULL),// 初始化指针
    playerHighestScore(0),// 初始化用户最高分（临时）
    score(0),// 初始化分数
    gameOver(false)// 初始化结束标识
{
    // 初始化 map 数组
    for (int i = 0; i < rows; i++)
    {
        vector<int> mapRow;
        for (int j = 0; j < cols; j++)
        {
            mapRow.push_back(0);
        }
        map.push_back(mapRow);
    }
    
    // 初始化按键数组
    for (int i = 0; i < 8; i++)
    {
        keyArray[i] = keyArray_ASCII[i];
    }

    // 配置随机种子
    srand((unsigned)time(0));
}

Game::Game(int rows, int cols, int leftMargin, int topMargin, int blockSize,                      // 基础参数
    int lastScore, vector<vector<int>> lastMap, int* lastNextBlockInfo, int* lastCurBlockInfo,    // 存档信息
    char* player, string recordIndex_temp,                                                        // 玩家信息
    char mode, int speedNormal, int speedQuick, bool plantMode,                                   // 玩法参数
    bool useDirectionKeys_temp, char keyArray_ASCII[],                                            // 按键参数
    string bg_temp, string music_temp)                                                            // 图片、音乐参数

    // 初始化列表
    : rows_m(rows), cols_m(cols), leftMargin_m(leftMargin),
    topMargin_m(topMargin), blockSize_m(blockSize),
    hasUseRecordInfo_before(true), recordIndex(recordIndex_temp), lastCurBlock(NULL), lastNextBlock(NULL),
    mode(mode), SPEED_NORMAL(speedNormal), SPEED_QUICK(speedQuick), isPlantMode(plantMode),
    useDirectionKeys(useDirectionKeys_temp),
    bg(bg_temp), music(music_temp),
    // 一下为初始化参数
    randNum(0),// 初始化随机数
    player(player),// 这场游戏的玩家名字
    delay(SPEED_NORMAL),// 初始化速度
    SPEED_SUDDEN(1), SPEED_ICE(1000),// 初始化瞬间下落的速度、冻结时的速度
    update(false), gameIsStop(false), gameExit(false), isIce(false), becomeBoom(false),// 初始化标识
    curBlock(NULL), nextBlock(NULL), lastBlock(NULL), shadowBlock(NULL), lastShadow(NULL), ranklistPtr(NULL), pageStop(NULL),// 初始化指针
    playerHighestScore(0),// 初始化用户最高分（临时）
    score(lastScore),// 初始化分数
    gameOver(false)// 初始化结束标识
{
    
    // 初始化 map 数组
    for (int i = 0; i < rows; i++)
    {
        vector<int> mapRow = lastMap[i];
        map.push_back(mapRow);
    }

    // 利用存档信息来初始化 预告方块和游戏方块指针
    nextBlock = producer.createBlock(lastNextBlockInfo[0]);
    curBlock = new GameBlock(lastCurBlockInfo);

    // 初始化按键数组
    for (int i = 0; i < 8; i++)
    {
        keyArray[i] = keyArray_ASCII[i];
    }

    // 配置随机种子
    srand((unsigned)time(0));

    // 初始化暂停界面的按钮
    initButtonFromStop();
}

Game::~Game()
{
    delete curBlock;
    curBlock = NULL;
    delete nextBlock;
    nextBlock = NULL;
    delete lastBlock;
    lastBlock = NULL;
    delete shadowBlock;
    shadowBlock = NULL;
    delete lastBlock;
    lastBlock = NULL;

    for (int i = 0; i < buttonsFromStop.size(); i++)
    {
        delete buttonsFromStop[i];
        buttonsFromStop[i] = NULL;
    }

    delete pageStop;
    pageStop = NULL;
    delete lastNextBlock;
    lastNextBlock = NULL;
    delete lastCurBlock;
    lastCurBlock = NULL;

    delete ranklistPtr;
    ranklistPtr = NULL;
}

void Game::init()
{
    // 播放游戏背景音乐
    if (music == "music1")
    {
        mciSendString("play ./materials/bg1.mp3 repeat", 0, 0, 0);
    }
    else if (music == "music2")
    {
        mciSendString("play ./materials/bg2.mp3 repeat", 0, 0, 0);
    }

    // 初始化速度
    delay = SPEED_NORMAL;

    //// 初始化排行榜 or 更新排行榜
    if (ranklistPtr)
    {
        delete ranklistPtr;
    }
    ranklistPtr = new RankList(mode);


    if (mode == 'A' && bg == "bg1")
    {
        loadimage(&backGroundImg, "./materials/play_bg1_A.png");
    }
    else if (mode == 'B' && bg == "bg1")
    {
        loadimage(&backGroundImg, "./materials/play_bg1_B.png");
    }
    else if (mode == 'A' && bg == "bg2")
    {
        loadimage(&backGroundImg, "./materials/play_bg2_A.png");
    }
    else if (mode == 'B' && bg == "bg2")
    {
        loadimage(&backGroundImg, "./materials/play_bg2_B.png");
    }

    loadimage(&overImg, "./materials/over.jpg");

    

    // 初始化游戏状态
    isIce = false;
    becomeBoom = false;

    // 初始化最高分 读取对应用户名的文件中的数据 ----------还要分别考虑模式A和模式B
    playerHighestScore = ranklistPtr->getPlayerHighScore(player);

    gameOver = false;

    // 初始化暂停界面的按钮
    initButtonFromStop();
    // 载入暂停界面图片
    pageStop = new IMAGE;
    loadimage(pageStop, "./materials/stop.png");
}

void Game::play()
{
    // 初始化
    init();

    // 创建方块
    if (hasUseRecordInfo_before)
    {
        hasUseRecordInfo_before = false;
    }
    else
    {
        randNum = rand() % 7 + 1;
        nextBlock = producer.createBlock(randNum);
        curBlock = new GameBlock(nextBlock);
        /*delete nextBlock;*/
        randNum = rand() % 7 + 1;
        nextBlock = producer.createBlock(randNum);
    }

    // 创建curBlock影子
    if (shadowBlock)
        delete shadowBlock;
    shadowBlock = new BlockShadow(curBlock);
    // 初始化两个备份成员
    lastBlock = new GameBlock;
    lastShadow = new BlockShadow;

    // 寻找并确认shadowBlock的位置坐标
    updateShadowBlock();

    int timer = 0;
    while (true)
    {
        bool hasKey;
        // 接受玩家键盘按键输入
        hasKey = dealWithKeyInformation(); // PS：实际运行是需要点击“黑框框”，否则请在本地电脑中设置：“设置”->“系统”->“开发者选项”->“终端”->“Windows控制台主机”
        if (hasKey)
        {
            /*if (shadowBlock)
                delete shadowBlock;*/
            shadowBlock = new BlockShadow(curBlock);
            // 寻找并确认shadowBlock的位置坐标
            updateShadowBlock();
        }

        timer += timeCounter();
        if (timer > delay)
        {
            timer = 0;
            gameBlockDrop();
            update = true; // 可以渲染了
        }


        if (update)
        {
            // 渲染游戏画面
            drawGame();
            // 若不是暂停状态，则重置update
            if(!gameIsStop)
            {
                update = false;
            }
            // 检查清行，有的话就消掉
            checkAndClearLine();
        }

        // 游戏结束的处理
        if (gameOver)
        {
            // 保存分数
            saveHighestScore();

            // 弹出恭喜窗口
            displayOverPicture();
            // 删除存档文件
            // 组织 存档内容txt的地址
            string address1 = "./data/player/mode";
            string address2(1, mode);
            string address3 = "/";
            string address4 = player;
            string address5 = recordIndex;
            string address6 = ".txt";
            string address = address1 + address2 + address3 + address4 + address5 + address6;

            // char[]才能用remove()函数
            char adr[40];
            int i;
            for (i = 0; i < address.length(); i++)
                adr[i] = address[i];
            adr[i] = '\0';

            remove(adr);

            // 按任意键回到开始界面
            system("pause");
            break;
        }

        // 处理中断退出
        if (gameExit)
        {
            break;
        }
    }
}

void Game::initButtonFromStop()
{
    // 按钮"继续游戏"
    const char* str = "继续游戏";
    Button* buttonContinue = new Button(723, 328, 180, 60, str, [&]()
        {
            gameIsStop = false;

            // 重新播放游戏音乐
            if (music == "music1")
            {
                mciSendString("play ./materials/bg1.mp3 repeat", 0, 0, 0);
            }
            else if (music == "music2")
            {
                mciSendString("play ./materials/bg2.mp3 repeat", 0, 0, 0);
            }
        });
    buttonsFromStop.push_back(buttonContinue);

    // 按钮"重新游戏"
    str = "重新游戏";
    Button* buttonReplay = new Button(723, 408, 180, 60, str, [&]()
        {
            gameIsStop = false;

            // 重开
            init();

            // 初始化分数
            score = 0;
            // 初始化游戏区域 map
            for (int i = 0; i < rows_m; i++)
            {
                for (int j = 0; j < cols_m; j++)
                {
                    map[i][j] = 0;
                }
            }


            delete curBlock;
            delete nextBlock;
            delete shadowBlock;

            // 创建方块
            //nextBlock = new AdvanceBlock;
            randNum = rand() % 7 + 1;
            nextBlock = producer.createBlock(randNum);
            curBlock = new GameBlock(nextBlock);
            delete nextBlock;
            //nextBlock = new AdvanceBlock;
            randNum = rand() % 7 + 1;
            nextBlock = producer.createBlock(randNum);

            // 创建curBlock影子
            shadowBlock = new BlockShadow(curBlock);
            // 寻找并确认shadowBlock的位置坐标
            updateShadowBlock();
        });
    buttonsFromStop.push_back(buttonReplay);

    // 按钮"存档退出"
    str = "存档退出";
    Button* buttonKeepFileAndExit = new Button(723, 488, 180, 60, str, [&]()
        {
            gameIsStop = false;

            // 存档
            saveGameInfo();

            // 启用直接退出标识符
            gameExit = true;
        });
    buttonsFromStop.push_back(buttonKeepFileAndExit);

    // 按钮"直接退出"
    str = "直接退出";
    Button* buttonExit = new Button(723, 568, 180, 60, str, [&]()
        {
            gameIsStop = false;

            // 启用直接退出标识符
            gameExit = true;
        });
    buttonsFromStop.push_back(buttonExit);

}

void Game::drawButtonsFromStop()
{
    // 绘制暂停按钮
    if (gameIsStop)
    {
        for (Button* button : buttonsFromStop)
        {
            button->draw(); // 绘制当前页面上的所有按钮
        }
    }
}

void Game::updateShadowBlock()
{
    while (1)
    {
        // 备份
        *lastBlock = *shadowBlock;
        // lastShadow->copy(shadowBlock);

        shadowBlock->drop();
        if (!shadowBlock->isInMapLegally(map))
        {
            // 位置不合法后，将shadowBlock的位置还原为 备份的位置lastBlock
            *shadowBlock = *lastBlock;
            break;
        }
    }
}

bool Game::dealWithKeyInformation() // PS：实际运行是需要点击“黑框框”，否则请在本地电脑中设置：“设置”->“系统”->“开发者选项”->“终端”->“Windows控制台主机”
{
    unsigned char ch; // char(-128,127)  unsigned char(0,255)
    bool rotateFlag = false;
    bool leftFlag = false;
    bool rightFlag = false;

    if (_kbhit())
    {                  // 检测是否有按键输入，防止程序因等待输入而卡住
        ch = _getch(); // 按按键直接输入，免回车

        if (useDirectionKeys) // 使用了方向键预设
        {
            if (ch == 224) // 方向键有两个返回值构成，第一个均为224
            {
                ch = _getch();
                switch (ch)
                {
                case 72: // 上
                    rotateFlag = true;
                    break;
                case 80: // 下
                {
                    delay = SPEED_QUICK;
                    isIce = false;
                }
                    break;
                case 75: // 左
                    leftFlag = true;
                    break;
                case 77: // 右
                    rightFlag = true;
                    break;
                default:
                    break;
                }
            }
        }
        else // 使用了字符组合
        {
            if (ch == keyArray[0]) // 上
                rotateFlag = true;
            else if (ch == keyArray[1]) // 下
            {
                delay = SPEED_QUICK;
                isIce = false;
            }
            else if (ch == keyArray[2]) // 左
                leftFlag = true;
            else if (ch == keyArray[3]) // 右
                rightFlag = true;
        }

        if (ch == keyArray[4]) // 暂停
        {
            // 停止播放游戏音乐
            if (music == "music1")
            {
                mciSendString("stop ./materials/bg1.mp3", 0, 0, 0);
            }
            else if (music == "music2")
            {
                mciSendString("stop ./materials/bg2.mp3", 0, 0, 0);
            }
            // 暂停按键
            gameStop();
        }
        else if (ch == keyArray[5]) // 瞬间下落
        {
            dropSuddenly();
        }
        else if (ch == keyArray[6] && isPlantMode)
        {
            if (score >= 20)
            {
                isIce = true;
                delay = SPEED_ICE;
                update = true;

                // 消耗分数
                score -= 10;
            }
        }
        else if (ch == keyArray[7] && isPlantMode)
        {
            if(score >= 100)
            {
                dropSuddenly();
                becomeBoom = true;

                // 消耗分数
                score -= 100;
            }
        }

        // 根据Flag进行处理
        if (rotateFlag) // 旋转
        {
            blockRotate();
            update = true; // 按下按键后立刻刷新画面
        }
        else if (leftFlag)
        {
            blockMoveLeft();
            update = true; // 按下按键后立刻刷新画面
        }
        else if (rightFlag)
        {
            blockMoveRight();
            update = true; // 按下按键后立刻刷新画面
        }

        // 有按键输入
        return true;
    }

    // 没有按键输入
    return false;
}

void Game::gameStop()
{
    gameIsStop = true; // 停止标识符启用，为后面绘制页面使用，让他把按钮也绘制上
    update = true;
    
    while (gameIsStop)
    {
        drawGame();
    }
    
}

void Game::dropSuddenly()
{
    delay = SPEED_SUDDEN;
    isIce = false;
}

void Game::drawGame()
{
    // 绘制背景图片
    putimage(0, 0, &backGroundImg);

    // 打包渲染过程，先全部处理完再一次性绘制，防止闪屏 --开启
    BeginBatchDraw();

    // 渲染植物卡组
    if (isPlantMode)
        plantBox.showPlantCards();

    // 渲染预告方块
    nextBlock->draw(245, 220);
    // 渲染下落方块的影子方块
    shadowBlock->draw(leftMargin_m, topMargin_m);
    // 渲染下落的方块
    curBlock->draw(leftMargin_m, topMargin_m);

    // 展示冻结效果
    if (isIce)
    {
        plantBox.draw_Ice(leftMargin_m, topMargin_m, blockSize_m, curBlock);
    }


    // 渲染底部方块
    IMAGE** imgs = Block::getSubBlockImages(); // 通过类名调用静态函数，获取小方块图像数组
    for (int i = 0; i < rows_m; i++)
    {
        for (int j = 0; j < cols_m; j++)
        {
            if (map[i][j] != 0)
            {
                int x = leftMargin_m + j * blockSize_m;
                int y = topMargin_m + i * blockSize_m;
                putimage(x, y, imgs[map[i][j] - 1]);
            }
        }
    }

    // 显示当前得分
    showInfo();

    if (gameIsStop)
    {
        ExMessage msg;
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

        putimage(688, 211, pageStop);
        drawButtonsFromStop(); // 绘制当前页面内容

        Sleep(10);
    }


    // 完成渲染打包 --关闭
    EndBatchDraw();
    


    
    
}

int Game::timeCounter()
{
    static unsigned long long lastTime = 0;
    unsigned long long currentTime = GetTickCount(); // 返回与开机有关的时间

    if (lastTime == 0)
    {
        lastTime = currentTime;
        return 0;
    }
    else
    {
        int temp = currentTime - lastTime;
        lastTime = currentTime;
        return temp;
    }
}

void Game::gameBlockDrop()
{
    // 备份
    *lastBlock = *curBlock;

    // 调用Block的drop，让它下落
    curBlock->drop();

    if (!curBlock->isInMapLegally(map))
    {
        // 播放落地音乐
        mciSendString("play ./materials/dropped.mp3", 0, 0, 0);
        // 删除非法的curBlock
        delete curBlock;
        // 固定方块，因为curBlock已经下落到非法位置，所以固定的是lastBlock
        lastBlock->solidify(map);
        // 若刚刚使用了“瞬间下落”将delay设置成了SPEED_SUDDEN,则这里落地后要重置速度
        if (delay == SPEED_SUDDEN)
        {
            delay = SPEED_NORMAL;
            if(becomeBoom)
            {
                plantBox.draw_Boom(leftMargin_m, topMargin_m, blockSize_m, lastBlock, map);
                becomeBoom = false;
            }
        }
        // 若该方块时冻结的，就还原正常速度
        else if (delay == SPEED_ICE)
        {
            delay = SPEED_NORMAL;
            isIce = false;
        }

        // 将预告方块放入当前方块，开始新的循环
        // 创建方块
        curBlock = new GameBlock(nextBlock);
        delete nextBlock;
        //nextBlock = new AdvanceBlock;
        randNum = rand() % 7 + 1;
        nextBlock = producer.createBlock(randNum);

        // 创建curBlock影子
        if (shadowBlock)
            delete shadowBlock;
        shadowBlock = new BlockShadow(curBlock);
        // 寻找并确认shadowBlock的位置坐标
        updateShadowBlock();

        // 检查游戏是否结束
        checkGameOver();
    }

    if (delay == SPEED_QUICK)
    {
        // 若之前右按下“↓”键时的加速，这里给它初始化速度
        delay = delay = SPEED_NORMAL;
    }
}

void Game::checkAndClearLine()
{
    // 统计本次累计消除的行数
    int rmLines = 0;

    // 类双指针法
    int i = rows_m - 1; // 第一个指针
    int k = rows_m - 1; // 第二个指针

    while (i)
    {
        // 看看第i行是否满行
        bool isFull = true; // 满行标识，假设满行
        for (int j = 0; j < cols_m; j++)
        {
            if (map[i][j] == 0) // 如果遇到一个是空
            {
                isFull = false;
            }
        }

        if (!isFull) // 若不满行
        {
            map[k] = map[i];
            k--;
            i--;
        }
        else
        {
            rmLines++; // 记录本次消除行数
            i--;
        }
    }
    while (k) // map上方还有些方块遗留，将i检查过但k没处理过的行数进行初始化
    {
        vector<int> NULLrow;

        for (int j = 0; j < cols_m; j++)
        {
            NULLrow.push_back(0);
        }

        map[k] = NULLrow;
        k--;
    }

    if (rmLines > 0)
    {
        // 播放消行音效
        mciSendString("play ./materials/delete1.mp3", 0, 0, 0);
        update = true; // 马上更新

        // 得分设计，一次性消得多，得分越多，上限一次5行
        vector<int> scoreTable;
        scoreTable.push_back(10);            // 一行
        scoreTable.push_back(30);            // 两行
        scoreTable.push_back(70);            // 三行
        scoreTable.push_back(130);           // 四行
        for (int i = 0; i < rows_m - 5; i++) // 大于等于5行
        {
            scoreTable.push_back(200);
        }

        // 计算得分
        score += scoreTable[rmLines - 1];

        // 消除一次加速一次，鼓励一次多消
        speedUp();
    }
}

void Game::blockRotate()
{
    // “7 田” 没必要旋转
    if (curBlock->getBlockType() == 7)
    {
        return;
    }

    // 备份
    *lastBlock = *curBlock;
    // 移动
    curBlock->rotate();
    // 判断移动后是否合法
    if (!curBlock->isInMapLegally(map)) // 如果非法
    {
        *curBlock = *lastBlock; // 还原回上一次的位置
    }
}

void Game::blockMoveLeft()
{
    // 备份
    *lastBlock = *curBlock;
    // 移动
    curBlock->moveLeft();
    // 判断移动后是否合法
    if (!curBlock->isInMapLegally(map)) // 如果非法
    {
        *curBlock = *lastBlock; // 还原回上一次的位置
    }
}

void Game::blockMoveRight()
{
    // 备份
    *lastBlock = *curBlock;
    // 移动
    curBlock->moveRight();
    // 判断移动后是否合法
    if (!curBlock->isInMapLegally(map)) // 如果非法
    {
        *curBlock = *lastBlock; // 还原回上一次的位置
    }
}

void Game::showInfo()
{
    // 设置字体
    LOGFONT f;                         // 字体变量
    gettextstyle(&f);                  // 获取当前字体
    f.lfHeight = 40;                   // 字体高度
    f.lfWidth = 15;                    // 字体宽度
    f.lfQuality = ANTIALIASED_QUALITY; // 字体抗锯齿
    setbkmode(TRANSPARENT);            // 字体背景设为透明
    strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("楷体"));
    settextstyle(&f);
    settextcolor(RGB(0, 0, 0));

    char Text[32]; // 文本共用 文本数组

    if (mode == 'A')
    {
        // 打印当前获得的分数
        sprintf_s(Text, sizeof(Text), "当前得分：%d", score);
        outtextxy(860, 620, Text);
        // 打印玩家历史最高分
        sprintf_s(Text, sizeof(Text), "历史最高分：%d", playerHighestScore);
        outtextxy(860, 670, Text);

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
            sprintf_s(Text, sizeof(Text), "暂停菜单：%c", keyArray[4] == ' ' ? '_' : keyArray[4]);
            outtextxy(860, 370, Text);
            sprintf_s(Text, sizeof(Text), "瞬间下落：%c", keyArray[5] == ' ' ? '_' : keyArray[5]);
            outtextxy(860, 420, Text);
        }
        else
        {
            sprintf_s(Text, sizeof(Text), "旋转：%c", keyArray[0] == ' ' ? '_' : keyArray[0]);
            outtextxy(860, 170, Text);
            sprintf_s(Text, sizeof(Text), "加速：%c", keyArray[1] == ' ' ? '_' : keyArray[1]);
            outtextxy(860, 220, Text);
            sprintf_s(Text, sizeof(Text), "向左：%c", keyArray[2] == ' ' ? '_' : keyArray[2]);
            outtextxy(860, 270, Text);
            sprintf_s(Text, sizeof(Text), "向右：%c", keyArray[3] == ' ' ? '_' : keyArray[3]);
            outtextxy(860, 320, Text);
            sprintf_s(Text, sizeof(Text), "暂停菜单：%c", keyArray[4] == ' ' ? '_' : keyArray[4]);
            outtextxy(860, 370, Text);
            sprintf_s(Text, sizeof(Text), "瞬间下落：%c", keyArray[5] == ' ' ? '_' : keyArray[5]);
            outtextxy(860, 420, Text);
        }
    }
    else if (mode == 'B')
    {
        // 打印当前获得的分数
        sprintf_s(Text, sizeof(Text), "当前得分：%d", score);
        outtextxy(1100, 620, Text);
        // 打印玩家历史最高分
        sprintf_s(Text, sizeof(Text), "历史最高分：%d", playerHighestScore);
        outtextxy(1100, 670, Text);

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
            sprintf_s(Text, sizeof(Text), "暂停菜单：%c", keyArray[4] == ' ' ? '_' : keyArray[4]);
            outtextxy(1100, 370, Text);
            sprintf_s(Text, sizeof(Text), "瞬间下落：%c", keyArray[5] == ' ' ? '_' : keyArray[5]);
            outtextxy(1100, 420, Text);
        }
        else
        {
            sprintf_s(Text, sizeof(Text), "旋转：%c", keyArray[0] == ' ' ? '_' : keyArray[0]);
            outtextxy(1100, 170, Text);
            sprintf_s(Text, sizeof(Text), "加速：%c", keyArray[1] == ' ' ? '_' : keyArray[1]);
            outtextxy(1100, 220, Text);
            sprintf_s(Text, sizeof(Text), "向左：%c", keyArray[2] == ' ' ? '_' : keyArray[2]);
            outtextxy(1100, 270, Text);
            sprintf_s(Text, sizeof(Text), "向右：%c", keyArray[3] == ' ' ? '_' : keyArray[3]);
            outtextxy(1100, 320, Text);
            sprintf_s(Text, sizeof(Text), "暂停菜单：%c", keyArray[4] == ' ' ? '_' : keyArray[4]);
            outtextxy(1100, 370, Text);
            sprintf_s(Text, sizeof(Text), "瞬间下落：%c", keyArray[5] == ' ' ? '_' : keyArray[5]);
            outtextxy(1100, 420, Text);
        }
    }
    
    if(isPlantMode)
    {
        char Text_plant[3]; // 文本共用 文本数组
        sprintf_s(Text_plant, sizeof(Text_plant), "%c:", keyArray[6] == ' ' ? '_' : keyArray[6]);
        outtextxy(310, 470, Text_plant);
        sprintf_s(Text_plant, sizeof(Text_plant), "%c:", keyArray[7] == ' ' ? '_' : keyArray[7]);
        outtextxy(310, 570, Text_plant);
    }
}

void Game::speedUp()
{
    if (SPEED_NORMAL > 230)
    {
        SPEED_NORMAL -= 10;
    }
}

void Game::checkGameOver()
{
    if (curBlock->isInMapLegally(map))
    {
        gameOver = false;
    }
    else
    {
        gameOver = true;
    }
}

void Game::saveHighestScore()
{
    if (score > playerHighestScore)
    {
        playerHighestScore = score;

        Record rc;
        rc.player = player;
        rc.score = playerHighestScore;

        ranklistPtr->saveRecord(rc);
    }
}

void Game::displayOverPicture()
{
    // 停止播放游戏音乐
    if (music == "music1")
    {
        mciSendString("stop ./materials/bg1.mp3", 0, 0, 0);
    }
    else if (music == "music2")
    {
        mciSendString("stop ./materials/bg2.mp3", 0, 0, 0);
    }

    // 结束动画
    IMAGE k[54] = { 0 };//定义IMAGE数组
    char adr[200];
    for (int i = 0; i < 54; i++) {
        sprintf_s(adr, "./materials/KO/Image%d.jpg", i + 1);
        loadimage(&k[i], adr, 1112, 610);//加载图片
    }
    mciSendString("play ./materials/over.mp3", 0, 0, 0); // 游戏结束音乐
    for (int j = 0; j < 54; j++) {
        putimage(264, 143, &k[j]);
        Sleep(50);//延时0.05秒贴一张图片
    }



    // 设置字体
    LOGFONT f;                         // 字体变量
    gettextstyle(&f);                  // 获取当前字体
    f.lfHeight = 40;                   // 字体高度
    f.lfWidth = 15;                    // 字体宽度
    f.lfQuality = ANTIALIASED_QUALITY; // 字体抗锯齿
    //setbkmode(TRANSPARENT);            // 字体背景设为透明
    strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("楷体"));
    settextstyle(&f);
    settextcolor(RGB(0, 0, 0));

    char Text[32]; // 文本共用 文本数组

    // 显示得分
    sprintf_s(Text, sizeof(Text), "得分：%d !!!", score);
    outtextxy(600, 610, Text);

    // 显示玩家名称
    outtextxy(910, 647, player);
}

void Game::saveGameInfo()
{
    // 组织 存档内容txt的地址
    string address1 = "./data/player/mode";
    string address2(1, mode);
    string address3 = "/";
    string address4 = player;
    string address5 = recordIndex;
    string address6 = ".txt";
    string address = address1 + address2 + address3 + address4 + address5 + address6;
    // 输出流
    ofstream ofs(address);
    ofs << score << endl; // 存储当前分数
    // 存储map
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {
            ofs << map[i][j] << " ";
        }
        ofs << endl;
    }
    // 储存预告方块位置与类型
    ofs << nextBlock->getBlockType() << endl;
    Point* nextLoc = nextBlock->getSubBlockLocationArray();
    for (int i = 0; i < 4; i++)
    {
        ofs << nextLoc[i].row << ' ' << nextLoc[i].col << endl;
    }
    // 储存游戏方块位置与类型
    ofs << curBlock->getBlockType() << endl;
    Point* curLoc = curBlock->getSubBlockLocationArray();
    for (int i = 0; i < 4; i++)
    {
        ofs << curLoc[i].row << ' ' << curLoc[i].col << endl;
    }


    ofs.close();
}

void Game::mouseClick(int mouseX, int mouseY)
{
    for (Button* button : buttonsFromStop)
    {
        if (button->checkClick(mouseX, mouseY))
        {
            break;
        }
    }
}

void Game::mouseMove(int mouseX, int mouseY)
{
    for (Button* button : buttonsFromStop)
    {
        button->checkMouseOver(mouseX, mouseY);
    }
}
