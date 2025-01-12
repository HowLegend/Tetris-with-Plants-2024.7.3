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

Game::Game(int rows, int cols, int leftMargin, int topMargin, int blockSize, // ��������
    char* player, string recordIndex_temp,                                   // �����Ϣ
    char mode, int speedNormal, int speedQuick, bool plantMode,              // �淨����
    bool useDirectionKeys_temp, char keyArray_ASCII[],                       // ��������
    string bg_temp, string music_temp)                                       // ͼƬ�����ֲ���

    // ��ʼ���б�
    : rows_m(rows), cols_m(cols), leftMargin_m(leftMargin),
    topMargin_m(topMargin), blockSize_m(blockSize),
    hasUseRecordInfo_before(false), recordIndex(recordIndex_temp), lastCurBlock(NULL), lastNextBlock(NULL),
    mode(mode), SPEED_NORMAL(speedNormal), SPEED_QUICK(speedQuick), isPlantMode(plantMode),
    useDirectionKeys(useDirectionKeys_temp),
    bg(bg_temp), music(music_temp),
    // һ��Ϊ��ʼ������
    randNum(0),// ��ʼ�������
    player(player),// �ⳡ��Ϸ���������
    delay(SPEED_NORMAL),// ��ʼ���ٶ�
    SPEED_SUDDEN(1),SPEED_ICE(1000),// ��ʼ��˲��������ٶȡ�����ʱ���ٶ�
    update(false),gameIsStop(false),gameExit(false),isIce(false),becomeBoom(false),// ��ʼ����ʶ
    curBlock(NULL),nextBlock(NULL),lastBlock(NULL),shadowBlock(NULL),lastShadow(NULL), ranklistPtr(NULL), pageStop(NULL),// ��ʼ��ָ��
    playerHighestScore(0),// ��ʼ���û���߷֣���ʱ��
    score(0),// ��ʼ������
    gameOver(false)// ��ʼ��������ʶ
{
    // ��ʼ�� map ����
    for (int i = 0; i < rows; i++)
    {
        vector<int> mapRow;
        for (int j = 0; j < cols; j++)
        {
            mapRow.push_back(0);
        }
        map.push_back(mapRow);
    }
    
    // ��ʼ����������
    for (int i = 0; i < 8; i++)
    {
        keyArray[i] = keyArray_ASCII[i];
    }

    // �����������
    srand((unsigned)time(0));
}

Game::Game(int rows, int cols, int leftMargin, int topMargin, int blockSize,                      // ��������
    int lastScore, vector<vector<int>> lastMap, int* lastNextBlockInfo, int* lastCurBlockInfo,    // �浵��Ϣ
    char* player, string recordIndex_temp,                                                        // �����Ϣ
    char mode, int speedNormal, int speedQuick, bool plantMode,                                   // �淨����
    bool useDirectionKeys_temp, char keyArray_ASCII[],                                            // ��������
    string bg_temp, string music_temp)                                                            // ͼƬ�����ֲ���

    // ��ʼ���б�
    : rows_m(rows), cols_m(cols), leftMargin_m(leftMargin),
    topMargin_m(topMargin), blockSize_m(blockSize),
    hasUseRecordInfo_before(true), recordIndex(recordIndex_temp), lastCurBlock(NULL), lastNextBlock(NULL),
    mode(mode), SPEED_NORMAL(speedNormal), SPEED_QUICK(speedQuick), isPlantMode(plantMode),
    useDirectionKeys(useDirectionKeys_temp),
    bg(bg_temp), music(music_temp),
    // һ��Ϊ��ʼ������
    randNum(0),// ��ʼ�������
    player(player),// �ⳡ��Ϸ���������
    delay(SPEED_NORMAL),// ��ʼ���ٶ�
    SPEED_SUDDEN(1), SPEED_ICE(1000),// ��ʼ��˲��������ٶȡ�����ʱ���ٶ�
    update(false), gameIsStop(false), gameExit(false), isIce(false), becomeBoom(false),// ��ʼ����ʶ
    curBlock(NULL), nextBlock(NULL), lastBlock(NULL), shadowBlock(NULL), lastShadow(NULL), ranklistPtr(NULL), pageStop(NULL),// ��ʼ��ָ��
    playerHighestScore(0),// ��ʼ���û���߷֣���ʱ��
    score(lastScore),// ��ʼ������
    gameOver(false)// ��ʼ��������ʶ
{
    
    // ��ʼ�� map ����
    for (int i = 0; i < rows; i++)
    {
        vector<int> mapRow = lastMap[i];
        map.push_back(mapRow);
    }

    // ���ô浵��Ϣ����ʼ�� Ԥ�淽�����Ϸ����ָ��
    nextBlock = producer.createBlock(lastNextBlockInfo[0]);
    curBlock = new GameBlock(lastCurBlockInfo);

    // ��ʼ����������
    for (int i = 0; i < 8; i++)
    {
        keyArray[i] = keyArray_ASCII[i];
    }

    // �����������
    srand((unsigned)time(0));

    // ��ʼ����ͣ����İ�ť
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
    // ������Ϸ��������
    if (music == "music1")
    {
        mciSendString("play ./materials/bg1.mp3 repeat", 0, 0, 0);
    }
    else if (music == "music2")
    {
        mciSendString("play ./materials/bg2.mp3 repeat", 0, 0, 0);
    }

    // ��ʼ���ٶ�
    delay = SPEED_NORMAL;

    //// ��ʼ�����а� or �������а�
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

    

    // ��ʼ����Ϸ״̬
    isIce = false;
    becomeBoom = false;

    // ��ʼ����߷� ��ȡ��Ӧ�û������ļ��е����� ----------��Ҫ�ֱ���ģʽA��ģʽB
    playerHighestScore = ranklistPtr->getPlayerHighScore(player);

    gameOver = false;

    // ��ʼ����ͣ����İ�ť
    initButtonFromStop();
    // ������ͣ����ͼƬ
    pageStop = new IMAGE;
    loadimage(pageStop, "./materials/stop.png");
}

void Game::play()
{
    // ��ʼ��
    init();

    // ��������
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

    // ����curBlockӰ��
    if (shadowBlock)
        delete shadowBlock;
    shadowBlock = new BlockShadow(curBlock);
    // ��ʼ���������ݳ�Ա
    lastBlock = new GameBlock;
    lastShadow = new BlockShadow;

    // Ѱ�Ҳ�ȷ��shadowBlock��λ������
    updateShadowBlock();

    int timer = 0;
    while (true)
    {
        bool hasKey;
        // ������Ҽ��̰�������
        hasKey = dealWithKeyInformation(); // PS��ʵ����������Ҫ������ڿ�򡱣��������ڱ��ص��������ã������á�->��ϵͳ��->��������ѡ�->���նˡ�->��Windows����̨������
        if (hasKey)
        {
            /*if (shadowBlock)
                delete shadowBlock;*/
            shadowBlock = new BlockShadow(curBlock);
            // Ѱ�Ҳ�ȷ��shadowBlock��λ������
            updateShadowBlock();
        }

        timer += timeCounter();
        if (timer > delay)
        {
            timer = 0;
            gameBlockDrop();
            update = true; // ������Ⱦ��
        }


        if (update)
        {
            // ��Ⱦ��Ϸ����
            drawGame();
            // ��������ͣ״̬��������update
            if(!gameIsStop)
            {
                update = false;
            }
            // ������У��еĻ�������
            checkAndClearLine();
        }

        // ��Ϸ�����Ĵ���
        if (gameOver)
        {
            // �������
            saveHighestScore();

            // ������ϲ����
            displayOverPicture();
            // ɾ���浵�ļ�
            // ��֯ �浵����txt�ĵ�ַ
            string address1 = "./data/player/mode";
            string address2(1, mode);
            string address3 = "/";
            string address4 = player;
            string address5 = recordIndex;
            string address6 = ".txt";
            string address = address1 + address2 + address3 + address4 + address5 + address6;

            // char[]������remove()����
            char adr[40];
            int i;
            for (i = 0; i < address.length(); i++)
                adr[i] = address[i];
            adr[i] = '\0';

            remove(adr);

            // ��������ص���ʼ����
            system("pause");
            break;
        }

        // �����ж��˳�
        if (gameExit)
        {
            break;
        }
    }
}

void Game::initButtonFromStop()
{
    // ��ť"������Ϸ"
    const char* str = "������Ϸ";
    Button* buttonContinue = new Button(723, 328, 180, 60, str, [&]()
        {
            gameIsStop = false;

            // ���²�����Ϸ����
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

    // ��ť"������Ϸ"
    str = "������Ϸ";
    Button* buttonReplay = new Button(723, 408, 180, 60, str, [&]()
        {
            gameIsStop = false;

            // �ؿ�
            init();

            // ��ʼ������
            score = 0;
            // ��ʼ����Ϸ���� map
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

            // ��������
            //nextBlock = new AdvanceBlock;
            randNum = rand() % 7 + 1;
            nextBlock = producer.createBlock(randNum);
            curBlock = new GameBlock(nextBlock);
            delete nextBlock;
            //nextBlock = new AdvanceBlock;
            randNum = rand() % 7 + 1;
            nextBlock = producer.createBlock(randNum);

            // ����curBlockӰ��
            shadowBlock = new BlockShadow(curBlock);
            // Ѱ�Ҳ�ȷ��shadowBlock��λ������
            updateShadowBlock();
        });
    buttonsFromStop.push_back(buttonReplay);

    // ��ť"�浵�˳�"
    str = "�浵�˳�";
    Button* buttonKeepFileAndExit = new Button(723, 488, 180, 60, str, [&]()
        {
            gameIsStop = false;

            // �浵
            saveGameInfo();

            // ����ֱ���˳���ʶ��
            gameExit = true;
        });
    buttonsFromStop.push_back(buttonKeepFileAndExit);

    // ��ť"ֱ���˳�"
    str = "ֱ���˳�";
    Button* buttonExit = new Button(723, 568, 180, 60, str, [&]()
        {
            gameIsStop = false;

            // ����ֱ���˳���ʶ��
            gameExit = true;
        });
    buttonsFromStop.push_back(buttonExit);

}

void Game::drawButtonsFromStop()
{
    // ������ͣ��ť
    if (gameIsStop)
    {
        for (Button* button : buttonsFromStop)
        {
            button->draw(); // ���Ƶ�ǰҳ���ϵ����а�ť
        }
    }
}

void Game::updateShadowBlock()
{
    while (1)
    {
        // ����
        *lastBlock = *shadowBlock;
        // lastShadow->copy(shadowBlock);

        shadowBlock->drop();
        if (!shadowBlock->isInMapLegally(map))
        {
            // λ�ò��Ϸ��󣬽�shadowBlock��λ�û�ԭΪ ���ݵ�λ��lastBlock
            *shadowBlock = *lastBlock;
            break;
        }
    }
}

bool Game::dealWithKeyInformation() // PS��ʵ����������Ҫ������ڿ�򡱣��������ڱ��ص��������ã������á�->��ϵͳ��->��������ѡ�->���նˡ�->��Windows����̨������
{
    unsigned char ch; // char(-128,127)  unsigned char(0,255)
    bool rotateFlag = false;
    bool leftFlag = false;
    bool rightFlag = false;

    if (_kbhit())
    {                  // ����Ƿ��а������룬��ֹ������ȴ��������ס
        ch = _getch(); // ������ֱ�����룬��س�

        if (useDirectionKeys) // ʹ���˷����Ԥ��
        {
            if (ch == 224) // ���������������ֵ���ɣ���һ����Ϊ224
            {
                ch = _getch();
                switch (ch)
                {
                case 72: // ��
                    rotateFlag = true;
                    break;
                case 80: // ��
                {
                    delay = SPEED_QUICK;
                    isIce = false;
                }
                    break;
                case 75: // ��
                    leftFlag = true;
                    break;
                case 77: // ��
                    rightFlag = true;
                    break;
                default:
                    break;
                }
            }
        }
        else // ʹ�����ַ����
        {
            if (ch == keyArray[0]) // ��
                rotateFlag = true;
            else if (ch == keyArray[1]) // ��
            {
                delay = SPEED_QUICK;
                isIce = false;
            }
            else if (ch == keyArray[2]) // ��
                leftFlag = true;
            else if (ch == keyArray[3]) // ��
                rightFlag = true;
        }

        if (ch == keyArray[4]) // ��ͣ
        {
            // ֹͣ������Ϸ����
            if (music == "music1")
            {
                mciSendString("stop ./materials/bg1.mp3", 0, 0, 0);
            }
            else if (music == "music2")
            {
                mciSendString("stop ./materials/bg2.mp3", 0, 0, 0);
            }
            // ��ͣ����
            gameStop();
        }
        else if (ch == keyArray[5]) // ˲������
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

                // ���ķ���
                score -= 10;
            }
        }
        else if (ch == keyArray[7] && isPlantMode)
        {
            if(score >= 100)
            {
                dropSuddenly();
                becomeBoom = true;

                // ���ķ���
                score -= 100;
            }
        }

        // ����Flag���д���
        if (rotateFlag) // ��ת
        {
            blockRotate();
            update = true; // ���°���������ˢ�»���
        }
        else if (leftFlag)
        {
            blockMoveLeft();
            update = true; // ���°���������ˢ�»���
        }
        else if (rightFlag)
        {
            blockMoveRight();
            update = true; // ���°���������ˢ�»���
        }

        // �а�������
        return true;
    }

    // û�а�������
    return false;
}

void Game::gameStop()
{
    gameIsStop = true; // ֹͣ��ʶ�����ã�Ϊ�������ҳ��ʹ�ã������Ѱ�ťҲ������
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
    // ���Ʊ���ͼƬ
    putimage(0, 0, &backGroundImg);

    // �����Ⱦ���̣���ȫ����������һ���Ի��ƣ���ֹ���� --����
    BeginBatchDraw();

    // ��Ⱦֲ�￨��
    if (isPlantMode)
        plantBox.showPlantCards();

    // ��ȾԤ�淽��
    nextBlock->draw(245, 220);
    // ��Ⱦ���䷽���Ӱ�ӷ���
    shadowBlock->draw(leftMargin_m, topMargin_m);
    // ��Ⱦ����ķ���
    curBlock->draw(leftMargin_m, topMargin_m);

    // չʾ����Ч��
    if (isIce)
    {
        plantBox.draw_Ice(leftMargin_m, topMargin_m, blockSize_m, curBlock);
    }


    // ��Ⱦ�ײ�����
    IMAGE** imgs = Block::getSubBlockImages(); // ͨ���������þ�̬��������ȡС����ͼ������
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

    // ��ʾ��ǰ�÷�
    showInfo();

    if (gameIsStop)
    {
        ExMessage msg;
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

        putimage(688, 211, pageStop);
        drawButtonsFromStop(); // ���Ƶ�ǰҳ������

        Sleep(10);
    }


    // �����Ⱦ��� --�ر�
    EndBatchDraw();
    


    
    
}

int Game::timeCounter()
{
    static unsigned long long lastTime = 0;
    unsigned long long currentTime = GetTickCount(); // �����뿪���йص�ʱ��

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
    // ����
    *lastBlock = *curBlock;

    // ����Block��drop����������
    curBlock->drop();

    if (!curBlock->isInMapLegally(map))
    {
        // �����������
        mciSendString("play ./materials/dropped.mp3", 0, 0, 0);
        // ɾ���Ƿ���curBlock
        delete curBlock;
        // �̶����飬��ΪcurBlock�Ѿ����䵽�Ƿ�λ�ã����Թ̶�����lastBlock
        lastBlock->solidify(map);
        // ���ո�ʹ���ˡ�˲�����䡱��delay���ó���SPEED_SUDDEN,��������غ�Ҫ�����ٶ�
        if (delay == SPEED_SUDDEN)
        {
            delay = SPEED_NORMAL;
            if(becomeBoom)
            {
                plantBox.draw_Boom(leftMargin_m, topMargin_m, blockSize_m, lastBlock, map);
                becomeBoom = false;
            }
        }
        // ���÷���ʱ����ģ��ͻ�ԭ�����ٶ�
        else if (delay == SPEED_ICE)
        {
            delay = SPEED_NORMAL;
            isIce = false;
        }

        // ��Ԥ�淽����뵱ǰ���飬��ʼ�µ�ѭ��
        // ��������
        curBlock = new GameBlock(nextBlock);
        delete nextBlock;
        //nextBlock = new AdvanceBlock;
        randNum = rand() % 7 + 1;
        nextBlock = producer.createBlock(randNum);

        // ����curBlockӰ��
        if (shadowBlock)
            delete shadowBlock;
        shadowBlock = new BlockShadow(curBlock);
        // Ѱ�Ҳ�ȷ��shadowBlock��λ������
        updateShadowBlock();

        // �����Ϸ�Ƿ����
        checkGameOver();
    }

    if (delay == SPEED_QUICK)
    {
        // ��֮ǰ�Ұ��¡�������ʱ�ļ��٣����������ʼ���ٶ�
        delay = delay = SPEED_NORMAL;
    }
}

void Game::checkAndClearLine()
{
    // ͳ�Ʊ����ۼ�����������
    int rmLines = 0;

    // ��˫ָ�뷨
    int i = rows_m - 1; // ��һ��ָ��
    int k = rows_m - 1; // �ڶ���ָ��

    while (i)
    {
        // ������i���Ƿ�����
        bool isFull = true; // ���б�ʶ����������
        for (int j = 0; j < cols_m; j++)
        {
            if (map[i][j] == 0) // �������һ���ǿ�
            {
                isFull = false;
            }
        }

        if (!isFull) // ��������
        {
            map[k] = map[i];
            k--;
            i--;
        }
        else
        {
            rmLines++; // ��¼������������
            i--;
        }
    }
    while (k) // map�Ϸ�����Щ������������i������kû��������������г�ʼ��
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
        // ����������Ч
        mciSendString("play ./materials/delete1.mp3", 0, 0, 0);
        update = true; // ���ϸ���

        // �÷���ƣ�һ�������ö࣬�÷�Խ�࣬����һ��5��
        vector<int> scoreTable;
        scoreTable.push_back(10);            // һ��
        scoreTable.push_back(30);            // ����
        scoreTable.push_back(70);            // ����
        scoreTable.push_back(130);           // ����
        for (int i = 0; i < rows_m - 5; i++) // ���ڵ���5��
        {
            scoreTable.push_back(200);
        }

        // ����÷�
        score += scoreTable[rmLines - 1];

        // ����һ�μ���һ�Σ�����һ�ζ���
        speedUp();
    }
}

void Game::blockRotate()
{
    // ��7 � û��Ҫ��ת
    if (curBlock->getBlockType() == 7)
    {
        return;
    }

    // ����
    *lastBlock = *curBlock;
    // �ƶ�
    curBlock->rotate();
    // �ж��ƶ����Ƿ�Ϸ�
    if (!curBlock->isInMapLegally(map)) // ����Ƿ�
    {
        *curBlock = *lastBlock; // ��ԭ����һ�ε�λ��
    }
}

void Game::blockMoveLeft()
{
    // ����
    *lastBlock = *curBlock;
    // �ƶ�
    curBlock->moveLeft();
    // �ж��ƶ����Ƿ�Ϸ�
    if (!curBlock->isInMapLegally(map)) // ����Ƿ�
    {
        *curBlock = *lastBlock; // ��ԭ����һ�ε�λ��
    }
}

void Game::blockMoveRight()
{
    // ����
    *lastBlock = *curBlock;
    // �ƶ�
    curBlock->moveRight();
    // �ж��ƶ����Ƿ�Ϸ�
    if (!curBlock->isInMapLegally(map)) // ����Ƿ�
    {
        *curBlock = *lastBlock; // ��ԭ����һ�ε�λ��
    }
}

void Game::showInfo()
{
    // ��������
    LOGFONT f;                         // �������
    gettextstyle(&f);                  // ��ȡ��ǰ����
    f.lfHeight = 40;                   // ����߶�
    f.lfWidth = 15;                    // ������
    f.lfQuality = ANTIALIASED_QUALITY; // ���忹���
    setbkmode(TRANSPARENT);            // ���屳����Ϊ͸��
    strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("����"));
    settextstyle(&f);
    settextcolor(RGB(0, 0, 0));

    char Text[32]; // �ı����� �ı�����

    if (mode == 'A')
    {
        // ��ӡ��ǰ��õķ���
        sprintf_s(Text, sizeof(Text), "��ǰ�÷֣�%d", score);
        outtextxy(860, 620, Text);
        // ��ӡ�����ʷ��߷�
        sprintf_s(Text, sizeof(Text), "��ʷ��߷֣�%d", playerHighestScore);
        outtextxy(860, 670, Text);

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
            sprintf_s(Text, sizeof(Text), "��ͣ�˵���%c", keyArray[4] == ' ' ? '_' : keyArray[4]);
            outtextxy(860, 370, Text);
            sprintf_s(Text, sizeof(Text), "˲�����䣺%c", keyArray[5] == ' ' ? '_' : keyArray[5]);
            outtextxy(860, 420, Text);
        }
        else
        {
            sprintf_s(Text, sizeof(Text), "��ת��%c", keyArray[0] == ' ' ? '_' : keyArray[0]);
            outtextxy(860, 170, Text);
            sprintf_s(Text, sizeof(Text), "���٣�%c", keyArray[1] == ' ' ? '_' : keyArray[1]);
            outtextxy(860, 220, Text);
            sprintf_s(Text, sizeof(Text), "����%c", keyArray[2] == ' ' ? '_' : keyArray[2]);
            outtextxy(860, 270, Text);
            sprintf_s(Text, sizeof(Text), "���ң�%c", keyArray[3] == ' ' ? '_' : keyArray[3]);
            outtextxy(860, 320, Text);
            sprintf_s(Text, sizeof(Text), "��ͣ�˵���%c", keyArray[4] == ' ' ? '_' : keyArray[4]);
            outtextxy(860, 370, Text);
            sprintf_s(Text, sizeof(Text), "˲�����䣺%c", keyArray[5] == ' ' ? '_' : keyArray[5]);
            outtextxy(860, 420, Text);
        }
    }
    else if (mode == 'B')
    {
        // ��ӡ��ǰ��õķ���
        sprintf_s(Text, sizeof(Text), "��ǰ�÷֣�%d", score);
        outtextxy(1100, 620, Text);
        // ��ӡ�����ʷ��߷�
        sprintf_s(Text, sizeof(Text), "��ʷ��߷֣�%d", playerHighestScore);
        outtextxy(1100, 670, Text);

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
            sprintf_s(Text, sizeof(Text), "��ͣ�˵���%c", keyArray[4] == ' ' ? '_' : keyArray[4]);
            outtextxy(1100, 370, Text);
            sprintf_s(Text, sizeof(Text), "˲�����䣺%c", keyArray[5] == ' ' ? '_' : keyArray[5]);
            outtextxy(1100, 420, Text);
        }
        else
        {
            sprintf_s(Text, sizeof(Text), "��ת��%c", keyArray[0] == ' ' ? '_' : keyArray[0]);
            outtextxy(1100, 170, Text);
            sprintf_s(Text, sizeof(Text), "���٣�%c", keyArray[1] == ' ' ? '_' : keyArray[1]);
            outtextxy(1100, 220, Text);
            sprintf_s(Text, sizeof(Text), "����%c", keyArray[2] == ' ' ? '_' : keyArray[2]);
            outtextxy(1100, 270, Text);
            sprintf_s(Text, sizeof(Text), "���ң�%c", keyArray[3] == ' ' ? '_' : keyArray[3]);
            outtextxy(1100, 320, Text);
            sprintf_s(Text, sizeof(Text), "��ͣ�˵���%c", keyArray[4] == ' ' ? '_' : keyArray[4]);
            outtextxy(1100, 370, Text);
            sprintf_s(Text, sizeof(Text), "˲�����䣺%c", keyArray[5] == ' ' ? '_' : keyArray[5]);
            outtextxy(1100, 420, Text);
        }
    }
    
    if(isPlantMode)
    {
        char Text_plant[3]; // �ı����� �ı�����
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
    // ֹͣ������Ϸ����
    if (music == "music1")
    {
        mciSendString("stop ./materials/bg1.mp3", 0, 0, 0);
    }
    else if (music == "music2")
    {
        mciSendString("stop ./materials/bg2.mp3", 0, 0, 0);
    }

    // ��������
    IMAGE k[54] = { 0 };//����IMAGE����
    char adr[200];
    for (int i = 0; i < 54; i++) {
        sprintf_s(adr, "./materials/KO/Image%d.jpg", i + 1);
        loadimage(&k[i], adr, 1112, 610);//����ͼƬ
    }
    mciSendString("play ./materials/over.mp3", 0, 0, 0); // ��Ϸ��������
    for (int j = 0; j < 54; j++) {
        putimage(264, 143, &k[j]);
        Sleep(50);//��ʱ0.05����һ��ͼƬ
    }



    // ��������
    LOGFONT f;                         // �������
    gettextstyle(&f);                  // ��ȡ��ǰ����
    f.lfHeight = 40;                   // ����߶�
    f.lfWidth = 15;                    // ������
    f.lfQuality = ANTIALIASED_QUALITY; // ���忹���
    //setbkmode(TRANSPARENT);            // ���屳����Ϊ͸��
    strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("����"));
    settextstyle(&f);
    settextcolor(RGB(0, 0, 0));

    char Text[32]; // �ı����� �ı�����

    // ��ʾ�÷�
    sprintf_s(Text, sizeof(Text), "�÷֣�%d !!!", score);
    outtextxy(600, 610, Text);

    // ��ʾ�������
    outtextxy(910, 647, player);
}

void Game::saveGameInfo()
{
    // ��֯ �浵����txt�ĵ�ַ
    string address1 = "./data/player/mode";
    string address2(1, mode);
    string address3 = "/";
    string address4 = player;
    string address5 = recordIndex;
    string address6 = ".txt";
    string address = address1 + address2 + address3 + address4 + address5 + address6;
    // �����
    ofstream ofs(address);
    ofs << score << endl; // �洢��ǰ����
    // �洢map
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {
            ofs << map[i][j] << " ";
        }
        ofs << endl;
    }
    // ����Ԥ�淽��λ��������
    ofs << nextBlock->getBlockType() << endl;
    Point* nextLoc = nextBlock->getSubBlockLocationArray();
    for (int i = 0; i < 4; i++)
    {
        ofs << nextLoc[i].row << ' ' << nextLoc[i].col << endl;
    }
    // ������Ϸ����λ��������
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
