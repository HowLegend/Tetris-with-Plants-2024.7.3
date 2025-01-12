#pragma once
#include <easyx.h>
#include <vector>
#include "Block.h"
#include "GameBlock.h"
#include "AdvanceBlock.h"
#include "BlockShadow.h"
#include "InterfaceBook.h"
#include "RankList.h"
#include "BlockProducer.h"
#include "PlantsPower.h"

using namespace std;

class Game
{
public:
    // ���캯��,rows��cols��ʾ��������ж����У�left��top��ʾ��Ϸ����blockSize��ʾ�����С
    Game(int rows, int cols, int leftMargin, int topMargin, int blockSize, // ��������
        char* player, string recordIndex_temp,                             // �����Ϣ
        char mode, int speedNormal, int speedQuick, bool plantMode,       // �淨����
        bool useDirectionKeys_temp, char keyArray_ASCII[],                // ��������
        string bg_temp, string music_temp);                               // ͼƬ�����ֲ���
    // ���д浵�Ĺ��캯��
    Game(int rows, int cols, int leftMargin, int topMargin, int blockSize,                            // ��������
        int lastScore, vector<vector<int>> lastMap, int* lastNextBlockInfo, int* lastCurBlockInfo,    // �浵��Ϣ
        char* player, string recordIndex_temp,                                                        // �����Ϣ
        char mode, int speedNormal, int speedQuick, bool plantMode,                                   // �淨����
        bool useDirectionKeys_temp, char keyArray_ASCII[],                                            // ��������
        string bg_temp, string music_temp);                                                           // ͼƬ�����ֲ���
    // ��������
    ~Game();
    // ��ʼ��
    void init();
    // ��ʼ��Ϸ
    void play();

    // ���ڲ�ʹ�ã�������Ϊ˽��
private:
    // ��ʼ��stop����İ�ť
    void initButtonFromStop();
    // ����stop����İ�ť
    void drawButtonsFromStop();
    // �������䷽���Ӱ�ӷ����λ��
    void updateShadowBlock();
    // ����������뺯��
    bool dealWithKeyInformation(); // PS��ʵ����������Ҫ������ڿ�򡱣��������ڱ��ص��������ã������á�->��ϵͳ��->��������ѡ�->���նˡ�->��Windows����̨������
    // ���ƻ���
    void drawGame();
    // ���ؾ�����һ�ε��øú���������˶���ʱ�䣨ms������һ�ε��øú���������0
    int timeCounter();
    // ÿһ��ʱ��ͻ������Ϸ������½�
    void gameBlockDrop();
    // ������У���һ�о�����
    void checkAndClearLine();
    // ��ͣ����
    void gameStop();
    // ˲������
    void dropSuddenly();
    // ��ת
    void blockRotate();
    // �����ƶ�
    void blockMoveLeft();
    void blockMoveRight();
    // ��ʾ��ǰ��Ϣ
    void showInfo();
    // ����һ�ξͼ���һ�㣬�����Ѷȣ���˹���һ�ζ��������������ޣ���ֹ�治��ȥ
    void speedUp();
    // �����Ϸ�Ƿ����
    void checkGameOver();
    // ������ϲ����,�ṩ����ҳ�����ؿ�������ѡ��
    void displayOverPicture();
    // �����player��߷��������а��ļ���
    void saveHighestScore();
    // �浵map��score
    void saveGameInfo();

    // Ϊ�˸���ͣ״̬ʵ��������
    // �����
    void mouseClick(int mouseX, int mouseY);
    // ����ƶ�����ť�Ϸ�
    void mouseMove(int mouseX, int mouseY);

private:
    bool update; // �Ƿ�Ҫ��Ⱦ�ı�־
    int delay;   // ʱ���ӳ���

    IMAGE backGroundImg; // ����ͼƬ
    IMAGE overImg;       // ����ͼƬ

    vector<vector<int>> map; // ��Ϸ���� �߽��ڵķ���ͼ ��ά����   0��ʾ�գ�i��ʾ��i�����͵ķ��飨0~6���ͣ�
    int leftMargin_m;        // ����ͼ��߽磨�������ò�ͬ��������Ϸ�߽磩
    int topMargin_m;         // ����ͼ�ұ߽�
    int rows_m;              // ����ͼ���������������ò�ͬ��С����ͼ����Ϸģʽ��
    int cols_m;              // ����ͼ������
    int blockSize_m;         // �����С

    BlockProducer producer; // ����BlockProducer
    int randNum; // �����
    Block* curBlock;    // ��Ϸ���� ��ǰ����ķ���
    Block* nextBlock;   // Ԥ�淽��
    Block* lastBlock;   // ���÷��飬����������һ���Ϸ�λ�õ� curBlock
    Block* shadowBlock; // ��ǰ���䷽���Ӱ�ӷ���
    Block* lastShadow;  // ���÷��飬����������һ���Ϸ�λ�õ� shadowBlock

    bool gameOver;  // ��Ϸ�����ı�ʶ
    bool gameIsStop;  // ��Ϸ��ͣ�ı�ʶ
    bool gameExit; // ��Ϸ�ж��˳���ʶ
    vector<Button*> buttonsFromStop; // ��ͣҳ��İ�ť
    IMAGE* pageStop;    // ��ͣҳ���ͼƬ

    // �����Ϣ
    char* player;                     // �������
    string recordIndex;               // �浵�������
    bool hasUseRecordInfo_before;     // ʹ�ô浵�ı�ʶ
    AdvanceBlock* lastNextBlock;      // �浵��Ԥ�淽��
    GameBlock* lastCurBlock;          // �浵����Ϸ����
    int score;                        // ������Ϸ�ۼƷ���
    int playerHighestScore;           // ��߷�
    RankList* ranklistPtr;            // �������а񣬱��ڶ�ȡ��߷ֺʹ洢�ɼ�

    // �淨�Ĳ���
    char mode;        // ��Ϸģʽ��A/B
    int SPEED_SUDDEN; // ��Ϸ�ٶ�
    int SPEED_NORMAL;
    int SPEED_QUICK;

    // ���õĲ���
    bool useDirectionKeys; // �Ƿ�ʹ�÷����Ԥ��
    char keyArray[8];      // 0~3�洢����Զ�����������Ұ�����4��5�洢�ˡ���ͣ�˵�������˲�����䡱�İ���
    string bg;             // ��������
    string music;          // ���ֲ���

    // ֲ�＼��ģʽ
    bool isPlantMode;       // �Ƿ�����ֲ���淨
    PlantsPower plantBox;   // ֲ��ϵͳ
    bool isIce;             // ��Ϸ������
    int SPEED_ICE;    // ����ʱ�ķ��������ٶ�
    bool becomeBoom;  // ���ը�����䲢��ը
};
