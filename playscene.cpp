#include "playscene.h"
#include <mainwindow.h>
#include <stdlib.h>
#include <time.h>

PlayScene::PlayScene(QObject *parent)
    : QGraphicsScene{parent}
{
    setMap(9, 9, 10);
    m_theme = CLASSIC;
}

void PlayScene::initialize()
{
    clear();
    m_remainMine = m_mineNum;
    m_steps = 0;
    // 设置 scene 的直角坐标位置参数
    int left = -(SIDE_LENTH * column() / 2);
    int top = -(SIDE_LENTH * row() / 2);
    int width = SIDE_LENTH * column();
    int height = SIDE_LENTH * row();

    // 设置 scene 并将scene与gameView关联
    QRectF rect(left, top, width, height);
    setSceneRect(rect);

    for (int i = 0; i < m_row; i++)
    {
        for (int j = 0; j < m_column; j++)
        {
            board[i][j] = new LatticeItem(m_theme);
            board[i][j]->setRow(i);
            board[i][j]->setColumn(j);
            board[i][j]->setPos(QPointF(left + SIDE_LENTH * j, top + SIDE_LENTH * i));
            board[i][j]->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
            connect(board[i][j], &LatticeItem::leftClickSignal, this, &PlayScene::r_leftClick);
            connect(board[i][j], &LatticeItem::rightClickSignal, this, &PlayScene::r_rightClick);
            connect(board[i][j], &LatticeItem::doubleClickSignal, this, &PlayScene::r_doubleClick);
        }
    }

    setRandMine();   // 随机布雷
    setMineAround(); // 设置格子周围雷数

    for (int i = 0; i < m_row; i++)
    {
        for (int j = 0; j < m_column; j++)
        {
            addItem(board[i][j]);
        }
    }
    emit flagNumChangeSignal();
    emit timerStartSignal();
}

void PlayScene::setMap(int row, int column, int mine)
{
    m_row = row;
    m_column = column;
    m_mineNum = mine;
}

void PlayScene::r_leftClick(int x, int y)
{
    openLattice(x, y);
    emit gameStatusChangeSignal();
}

void PlayScene::r_rightClick(int x, int y)
{
    if (board[x][y]->status() == CLOSED)
    {
        board[x][y]->setStatus(FLAG);
    }
    else if (board[x][y]->status() == FLAG)
    {
        board[x][y]->setStatus(QUESTION);
    }
    else if (board[x][y]->status() == QUESTION)
    {
        board[x][y]->setStatus(CLOSED);
    }
    board[x][y]->updateLattice();
    emit flagNumChangeSignal();
}

void PlayScene::r_doubleClick(int x, int y)
{
    int countFlag = 0, countQuestion = 0;
    if (board[x][y]->status() == OPENED && board[x][y]->isMine() == false)
    {
        //统计周围插旗格子数和问号格子数
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (x + i >= 0 && x + i < m_row && y + j >= 0 && y + j < m_column) //避免越界
                {
                    if (board[x + i][y + j]->status() == FLAG)
                    {
                        countFlag++;
                    }
                    else if (board[x + i][y + j]->status() == QUESTION)
                    {
                        countQuestion++;
                    }
                }
            }
        }
        if (countFlag == board[x][y]->mineAround() && countQuestion == 0)
        {
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    if (x + i >= 0 && x + i < m_row && y + j >= 0 && y + j < m_column) //避免越界
                    {
                        openLattice(x + i, y + j);
                    }
                }
            }
        }
        emit gameStatusChangeSignal();
    }
}

void PlayScene::openLattice(int x, int y)
{
    if (board[x][y]->status() == CLOSED)
    {
        board[x][y]->setStatus(OPENED);
        board[x][y]->updateLattice();
        if (board[x][y]->mineAround() == 0 && board[x][y]->isMine() == false) // 如果被打开的格子是0，则要递归打开周围的格子
        {
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    if (x + i >= 0 && x + i < m_row && y + j >= 0 && y + j < m_column) // 在未越界的情况下
                    {
                        openLattice(x + i, y + j);
                    }
                }
            }
        }
    }
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

void PlayScene::setMineAround()
{
    int mineAround = 0;
    for (int i = 0; i < m_row; i++)
    {
        for (int j = 0; j < m_column; j++)
        {
            if (!board[i][j]->isMine())
            { // 如果当前格子不是雷，就要统计这个格子周围的地雷数
                for (int k = -1; k <= 1; k++)
                {
                    for (int m = -1; m <= 1; m++)
                    {
                        if (i + k >= 0 && i + k < m_row && j + m >= 0 && j + m < m_column) // 如果搜寻的区域没有越界
                        {
                            if (board[i + k][j + m]->isMine())
                            {
                                mineAround++;
                            }
                        }
                    }
                }
                board[i][j]->setMineAround(mineAround);
                mineAround = 0;
            }
        }
    }
}

void PlayScene::on_gameStatusChange()
{
    int countStepOnMine = 0, countOpenedLattice = 0;
    for (int i = 0; i < m_row; i++)
    {
        for (int j = 0; j < m_column; j++)
        {
            if (board[i][j]->status() == OPENED && board[i][j]->isMine() == true)
            {
                countStepOnMine++;
            }
            if (board[i][j]->status() == OPENED && board[i][j]->isMine() == false)
            {
                countOpenedLattice++;
            }
        }
    }
    if (countStepOnMine != 0) //踩到雷了
    {
        emit gameOver(LOSE);
    }
    else if (countOpenedLattice == m_row * m_column - m_mineNum)
    {
        emit gameOver(WIN);
    }
}

void PlayScene::on_flagNumChange()
{
    int countFlag = 0;
    for (int i = 0; i < m_row; i++)
    {
        for (int j = 0; j < m_column; j++)
        {
            if (board[i][j]->status() == FLAG)
            {
                countFlag++;
            }
        }
    }
    m_remainMine = m_mineNum - countFlag;
    emit changeLCD_remainMineSignal(m_remainMine);
}

void PlayScene::showAllMine(int result)
{
    for (int i = 0; i < m_row; i++)
    {
        for (int j = 0; j < m_column; j++)
        {
            if (board[i][j]->isMine() == true && board[i][j]->status() != OPENED)
            {
                if (board[i][j]->status() == FLAG)
                {
                    board[i][j]->setStatus(MINE_GAMEOVER); // 已标记的地雷用“绿色地雷”显示
                }
                else if (result == LOSE)
                {
                    board[i][j]->setStatus(OPENED); // 若游戏失败，则未标记的地雷用“红色地雷”表示
                }
                else
                {
                    board[i][j]->setStatus(MINE_GAMEOVER); //若游戏胜利，则未标记的地雷也用“绿色地雷”表示
                }
                board[i][j]->updateLattice();
            }
        }
    }
}

void PlayScene::changeLatticeTheme()
{
    for (int i = 0; i < m_row; i++)
    {
        for (int j = 0; j < m_column; j++)
        {
            board[i][j]->setTheme(m_theme);
            board[i][j]->updateLattice();
        }
    }
}
