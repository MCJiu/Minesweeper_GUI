#include "playscene.h"
#include <stdlib.h>
#include <time.h>

const int SIDE_LENTH = 20;

PlayScene::PlayScene(QObject *parent)
    : QGraphicsScene{parent}
{
    setMap(9, 9, 10);
    m_remainMine = m_mineNum;
    m_steps = 0;
}

void PlayScene::initialize()
{
    int left = -(SIDE_LENTH * m_row / 2);
    int top = -(SIDE_LENTH * m_column / 2);
    for (int i = 0; i < m_row; i++)
    {
        for (int j = 0; j < m_column; j++)
        {
            board[i][j] = new LatticeItem();
            board[i][j]->setRow(i);
            board[i][j]->setColumn(j);
            board[i][j]->setPos(QPointF(left + SIDE_LENTH * j, top + SIDE_LENTH * i));
            board[i][j]->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
            connect(board[i][j], SIGNAL(leftClickSignal()), this, SLOT(r_leftClick()));
            connect(board[i][j], SIGNAL(rightClickSignal()), this, SLOT(r_rightClick()));
            connect(board[i][j], SIGNAL(doubleClickSignal()), this, SLOT(r_doubleClick()));
            addItem(board[i][j]);
        }
    }
}

void PlayScene::setMap(int row, int column, int mine)
{
    m_row = row;
    m_column = column;
    m_mineNum = mine;
}

void PlayScene::r_leftClick()
{
}

void PlayScene::setRandMine()
{
    srand(time(nullptr));
    int minePlaced = 0;
    int x, y;
    while (minePlaced < m_mineNum)
    {
        x = rand() % m_row;
        y = rand() % m_column;
        if (!board[x][y]->isMine())
        {
            board[x][y]->setMine(true);
            minePlaced++;
        }
    }
}
