
//-----------------------------------------------------------------------------------[1]游戏界面

    // 创建游戏界面
IMAGE* pageSelectRecord = new IMAGE;
loadimage(pageSelectRecord, "./materials/play_bg1_A.png"); // 载入游戏界面图片
addPage(pageSelectRecord);                                 // 添加 [1]游戏界面

// 按钮"查看存档"
str = "查看存档";
Button* buttonShowRecord = new Button(298, 399, 120, 60, str, [&]()
    {
        // 更新存档
        hasRecord = getLastInfo(mode);
        // 有存档
        if (hasRecord)
        {
            // 显示存档中的方块
            drawLastMap_NextBlock_CurBlock();
            // 显示存档中的分数
            drawLastScore();
            // 不用更新整个页面
            notNeedWait = false;
        }
        else
        {
            //设置字体
            LOGFONT f;//字体变量
            gettextstyle(&f);//获取当前字体
            f.lfHeight = 50;//字体高度
            f.lfWidth = 25;//字体宽度
            f.lfQuality = ANTIALIASED_QUALITY;//字体抗锯齿
            setbkmode(OPAQUE);//字体背景设为透明
            strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("楷体"));
            settextstyle(&f);
            settextcolor(RED);

            char tipLine[100] = "您还没有存档！请点击“新游戏”按钮。";

            outtextxy(450, 400, tipLine);

            //不用马上更新整个页面
            notNeedWait = false;
        } });
addButton(1, buttonShowRecord); // 将 按钮"查看存档" 添加到 游戏界面

// 按钮"继续游戏"
str = "继续游戏";
Button* buttonContinue = new Button(298, 479, 120, 60, str, [&]()
    {
        // 更新存档
        hasRecord = getLastInfo(mode);
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
                lastScore, lastMap, lastNextBlockInfo, lastCurBlockInfo, player,
                mode, speedNormal, speedQuick, plantMode,
                useDirectionKeys, keyArray_ASCII,
                bg, music);
            game.play();
        }
        else
        {
            //设置字体
            LOGFONT f;//字体变量
            gettextstyle(&f);//获取当前字体
            f.lfHeight = 50;//字体高度
            f.lfWidth = 25;//字体宽度
            f.lfQuality = ANTIALIASED_QUALITY;//字体抗锯齿
            setbkmode(OPAQUE);//字体背景设为不透明
            strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("楷体"));
            settextstyle(&f);
            settextcolor(RED);

            char tipLine[100] = "您还没有存档！请点击“新游戏”按钮。";

            outtextxy(450, 400, tipLine);

            //不用马上更新整个页面
            notNeedWait = false;
        } });
addButton(1, buttonContinue); // 将 按钮"继续游戏" 添加到 游戏界面

// 按钮"新游戏"
str = "新游戏";
Button* buttonNewGame = new Button(298, 559, 120, 60, str, [&]()
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
            player, mode, speedNormal, speedQuick, plantMode,
            useDirectionKeys, keyArray_ASCII,
            bg, music);
        game.play(); });
addButton(1, buttonNewGame); // 将 按钮"新游戏" 添加到 游戏界面

// 按钮"返回主页"
str = "返回主页";
Button* buttonBack1 = new Button(298, 639, 120, 60, str, [&]()
    {
        setCurrentIndex(0); // 点击 按钮"返回主页" 时，切换到 home主页
    });
addButton(1, buttonBack1); // 将 按钮"返回主页" 添加到 游戏界面