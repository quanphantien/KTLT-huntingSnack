#include "GamePlay.h"
#include <iostream>
#include "Console.h"
#include "Graphic.h"

using namespace std;

int countScore()
{
    return 1;
}

void DrawFullScoreGraphic(int score)
{
    int temp = (score)%3;
    for (int i = 1; i <= temp; i++)
        DrawScoreGraphic(i);
}
void DrawScoreGraphic(int score)
{
    int height = 5;
    int s = (score - 1) % 3;
    switch (s)
    {
    case 0:
        setColorText(251);
        break;
    case 1:
        setColorText(250);
        break;
    case 2:
        setColorText(242);
        break;
    default:
        break;
    }
    int j = menuFrame_ymax - height * ((score-1)%3);
    for (int i = menuFrame_xmin + 1; i <= menuFrame_xmax - 1; i++)
    {
        j = menuFrame_ymax  - height * ((score-1)%3);
        for (int count = 0; count < 5; count++)
        {
            GotoXY(i, j);
            cout << "█";
            j--;
        }
    }
}