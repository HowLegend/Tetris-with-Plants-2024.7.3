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
    // 构造函数,rows和cols表示方块多少行多少列，left和top表示游戏区域，blockSize表示方块大小
    Game(int rows, int cols, int leftMargin, int topMargin, int blockSize, // 基础参数
        char* player, string recordIndex_temp,                             // 玩家信息
        char mode, int speedNormal, int speedQuick, bool plantMode,       // 玩法参数
        bool useDirectionKeys_temp, char keyArray_ASCII[],                // 按键参数
        string bg_temp, string music_temp);                               // 图片、音乐参数
    // 带有存档的构造函数
    Game(int rows, int cols, int leftMargin, int topMargin, int blockSize,                            // 基础参数
        int lastScore, vector<vector<int>> lastMap, int* lastNextBlockInfo, int* lastCurBlockInfo,    // 存档信息
        char* player, string recordIndex_temp,                                                        // 玩家信息
        char mode, int speedNormal, int speedQuick, bool plantMode,                                   // 玩法参数
        bool useDirectionKeys_temp, char keyArray_ASCII[],                                            // 按键参数
        string bg_temp, string music_temp);                                                           // 图片、音乐参数
    // 析构函数
    ~Game();
    // 初始化
    void init();
    // 开始游戏
    void play();

    // 供内部使用，所以设为私有
private:
    // 初始化stop界面的按钮
    void initButtonFromStop();
    // 绘制stop界面的按钮
    void drawButtonsFromStop();
    // 更新下落方块的影子方块的位置
    void updateShadowBlock();
    // 处理玩家输入函数
    bool dealWithKeyInformation(); // PS：实际运行是需要点击“黑框框”，否则请在本地电脑中设置：“设置”->“系统”->“开发者选项”->“终端”->“Windows控制台主机”
    // 绘制画面
    void drawGame();
    // 返回距离上一次调用该函数，间隔了多少时间（ms），第一次调用该函数，返回0
    int timeCounter();
    // 每一段时间就会让最上方方块下降
    void gameBlockDrop();
    // 检查清行，满一行就消掉
    void checkAndClearLine();
    // 暂停按键
    void gameStop();
    // 瞬间下落
    void dropSuddenly();
    // 旋转
    void blockRotate();
    // 左右移动
    void blockMoveLeft();
    void blockMoveRight();
    // 显示当前信息
    void showInfo();
    // 消除一次就加速一点，增加难度，因此鼓励一次多消，但是有上限，防止玩不下去
    void speedUp();
    // 检查游戏是否结束
    void checkGameOver();
    // 弹出恭喜窗口,提供“主页”“重开”两个选项
    void displayOverPicture();
    // 保存该player最高分数到排行榜文件中
    void saveHighestScore();
    // 存档map和score
    void saveGameInfo();

    // 为了给暂停状态实现鼠标操作
    // 鼠标点击
    void mouseClick(int mouseX, int mouseY);
    // 鼠标移动到按钮上方
    void mouseMove(int mouseX, int mouseY);

private:
    bool update; // 是否要渲染的标志
    int delay;   // 时间延迟量

    IMAGE backGroundImg; // 背景图片
    IMAGE overImg;       // 结束图片

    vector<vector<int>> map; // 游戏区域 边界内的方格图 二维数组   0表示空，i表示第i中类型的方块（0~6类型）
    int leftMargin_m;        // 方格图左边界（可以设置不同背景下游戏边界）
    int topMargin_m;         // 方格图右边界
    int rows_m;              // 方格图的行数（可以设置不同大小方格图的游戏模式）
    int cols_m;              // 方格图的列数
    int blockSize_m;         // 方块大小

    BlockProducer producer; // 创建BlockProducer
    int randNum; // 随机数
    Block* curBlock;    // 游戏方块 当前下落的方块
    Block* nextBlock;   // 预告方块
    Block* lastBlock;   // 备用方块，用来备份上一个合法位置的 curBlock
    Block* shadowBlock; // 当前下落方块的影子方块
    Block* lastShadow;  // 备用方块，用来备份上一个合法位置的 shadowBlock

    bool gameOver;  // 游戏结束的标识
    bool gameIsStop;  // 游戏暂停的标识
    bool gameExit; // 游戏中断退出标识
    vector<Button*> buttonsFromStop; // 暂停页面的按钮
    IMAGE* pageStop;    // 暂停页面的图片

    // 玩家信息
    char* player;                     // 玩家名称
    string recordIndex;               // 存档索引编号
    bool hasUseRecordInfo_before;     // 使用存档的标识
    AdvanceBlock* lastNextBlock;      // 存档的预告方块
    GameBlock* lastCurBlock;          // 存档的游戏方块
    int score;                        // 本次游戏累计分数
    int playerHighestScore;           // 最高分
    RankList* ranklistPtr;            // 导入排行榜，便于读取最高分和存储成绩

    // 玩法的参数
    char mode;        // 游戏模式：A/B
    int SPEED_SUDDEN; // 游戏速度
    int SPEED_NORMAL;
    int SPEED_QUICK;

    // 设置的参数
    bool useDirectionKeys; // 是否使用方向键预设
    char keyArray[8];      // 0~3存储玩家自定义的上下左右按键，4、5存储了“暂停菜单”、“瞬间下落”的按键
    string bg;             // 背景参数
    string music;          // 音乐参数

    // 植物技能模式
    bool isPlantMode;       // 是否开启了植物玩法
    PlantsPower plantBox;   // 植物系统
    bool isIce;             // 游戏被冻结
    int SPEED_ICE;    // 冻结时的方块下落速度
    bool becomeBoom;  // 变成炸弹掉落并爆炸
};
