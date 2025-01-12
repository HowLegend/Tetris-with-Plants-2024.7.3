#pragma once
#include <easyx.h>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

class Point
{
public:
    int row;
    int col;
};

class Block
{
public:
    // 构造函数
    Block();
    // 析构函数
    ~Block();

    // 加载入subBlock的图片，用静态函数加载静态变量，因为后来扩展“读档功能”时发现还未创建block就需要让外部调用图像
    static void loadSubBlockImg(string bk);
    // 绘制函数
    virtual void draw(int leftMargin, int topMargin) = 0;
    // 对外的一个接口 用于获得方块类型
    virtual int getBlockType() = 0;
    // 下降
    void drop();
    // 左右移动
    void moveLeft();
    void moveRight();
    // 旋转
    void rotate();
    // 判断方块是否合法 避免出界、穿透其他方块
    bool isInMapLegally(const vector<vector<int>>& map) const;
    // 方块将自身信息存储在游戏区域map中，实现固定
    void solidify(vector<vector<int>>& map) const;
    // 对外提供subBlock坐标位置的接口
    Point* getSubBlockLocationArray();
    // 给外部提供 获得 subBlock 图像指针数组的 接口
    static IMAGE** getSubBlockImages();


protected:
    static IMAGE* imgs[7]; // 存下七种颜色类型的 subBlock

    int blockType;      // 方块类型: 1~7种类型
    Point subBlocks[4]; // 记录 构成一个俄罗斯方块的4个小方块的位置

    static int subBlockSize; // 统一规定 subBlock 的大小，经测量为27像素的正方形
};
