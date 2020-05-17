#pragma once
#ifndef CHARSRAIN
#define CHARSRAIN

#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#define High 800  // 游戏画面尺寸
#define Width 1000
#define CharSize 25 // 每个字符显示的大小

void charsrain(void* drawbale)
{
    int highNum = High / CharSize;
    int widthNum = Width / CharSize;

    int CharRain[Width / CharSize][High / CharSize];
    int CNum[Width / CharSize]; // 每一列的有效字符个数
    int ColorG[Width / CharSize]; // 每一列字符的颜色
    int i, j, x, y;
    srand((unsigned)time(NULL));
    for (i = 0; i < widthNum; i++)
    {
        CNum[i] = (rand() % (highNum * 9 / 10)) + highNum / 10;
        ColorG[i] = 255;
        for (j = 0; j < CNum[i]; j++)
            CharRain[j][i] = (rand() % 26) + 65;
    }
    initgraph(Width, High);
    BeginBatchDraw();

    while (1)
    {
        for (i = 0; i < widthNum; i++)
        {
            if (CNum[i] < highNum - 1)
            {
                for (j = CNum[i] - 1; j >= 0; j--)  //如果从零开始递加，会覆盖掉后面的字符，所以用递减的方法
                    CharRain[j + 1][i] = CharRain[j][i];
                CharRain[0][i] = (rand() % 26) + 65;
                CNum[i] = CNum[i] + 1;
            }
            else
            {
                if (ColorG[i] > 40)
                    ColorG[i] = ColorG[i] - 20; // 让满的这一列逐渐变暗
                else
                {
                    CNum[i] = (rand() % (highNum / 3)) + highNum / 10;
                    ColorG[i] = (rand() % 75) + 180;
                    for (j = 0; j < CNum[i]; j++)
                        CharRain[j][i] = (rand() % 26) + 65;
                }
            }
        }

        for (i = 0; i < widthNum; i++)
        {
            x = i * CharSize;
            for (j = 0; j < CNum[i]; j++)
            {
                y = j * CharSize;
                setcolor(RGB(0, ColorG[i], 0));
                outtextxy(x, y, CharRain[j][i]);
            }
        }
        FlushBatchDraw();
        Sleep(30);
        clearrectangle(0, 0, Width - 1, High - 1);  // 清空画面全部矩形区域
    }

    EndBatchDraw();
    _getch();
    closegraph();
}
#endif