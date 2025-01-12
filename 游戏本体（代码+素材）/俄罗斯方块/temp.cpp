
//-----------------------------------------------------------------------------------[1]��Ϸ����

    // ������Ϸ����
IMAGE* pageSelectRecord = new IMAGE;
loadimage(pageSelectRecord, "./materials/play_bg1_A.png"); // ������Ϸ����ͼƬ
addPage(pageSelectRecord);                                 // ��� [1]��Ϸ����

// ��ť"�鿴�浵"
str = "�鿴�浵";
Button* buttonShowRecord = new Button(298, 399, 120, 60, str, [&]()
    {
        // ���´浵
        hasRecord = getLastInfo(mode);
        // �д浵
        if (hasRecord)
        {
            // ��ʾ�浵�еķ���
            drawLastMap_NextBlock_CurBlock();
            // ��ʾ�浵�еķ���
            drawLastScore();
            // ���ø�������ҳ��
            notNeedWait = false;
        }
        else
        {
            //��������
            LOGFONT f;//�������
            gettextstyle(&f);//��ȡ��ǰ����
            f.lfHeight = 50;//����߶�
            f.lfWidth = 25;//������
            f.lfQuality = ANTIALIASED_QUALITY;//���忹���
            setbkmode(OPAQUE);//���屳����Ϊ͸��
            strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("����"));
            settextstyle(&f);
            settextcolor(RED);

            char tipLine[100] = "����û�д浵������������Ϸ����ť��";

            outtextxy(450, 400, tipLine);

            //�������ϸ�������ҳ��
            notNeedWait = false;
        } });
addButton(1, buttonShowRecord); // �� ��ť"�鿴�浵" ��ӵ� ��Ϸ����

// ��ť"������Ϸ"
str = "������Ϸ";
Button* buttonContinue = new Button(298, 479, 120, 60, str, [&]()
    {
        // ���´浵
        hasRecord = getLastInfo(mode);
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
                lastScore, lastMap, lastNextBlockInfo, lastCurBlockInfo, player,
                mode, speedNormal, speedQuick, plantMode,
                useDirectionKeys, keyArray_ASCII,
                bg, music);
            game.play();
        }
        else
        {
            //��������
            LOGFONT f;//�������
            gettextstyle(&f);//��ȡ��ǰ����
            f.lfHeight = 50;//����߶�
            f.lfWidth = 25;//������
            f.lfQuality = ANTIALIASED_QUALITY;//���忹���
            setbkmode(OPAQUE);//���屳����Ϊ��͸��
            strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("����"));
            settextstyle(&f);
            settextcolor(RED);

            char tipLine[100] = "����û�д浵������������Ϸ����ť��";

            outtextxy(450, 400, tipLine);

            //�������ϸ�������ҳ��
            notNeedWait = false;
        } });
addButton(1, buttonContinue); // �� ��ť"������Ϸ" ��ӵ� ��Ϸ����

// ��ť"����Ϸ"
str = "����Ϸ";
Button* buttonNewGame = new Button(298, 559, 120, 60, str, [&]()
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
            player, mode, speedNormal, speedQuick, plantMode,
            useDirectionKeys, keyArray_ASCII,
            bg, music);
        game.play(); });
addButton(1, buttonNewGame); // �� ��ť"����Ϸ" ��ӵ� ��Ϸ����

// ��ť"������ҳ"
str = "������ҳ";
Button* buttonBack1 = new Button(298, 639, 120, 60, str, [&]()
    {
        setCurrentIndex(0); // ��� ��ť"������ҳ" ʱ���л��� home��ҳ
    });
addButton(1, buttonBack1); // �� ��ť"������ҳ" ��ӵ� ��Ϸ����