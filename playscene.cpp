#include "playscene.h"

PlayScene::PlayScene(QObject* parent)
    : QGraphicsScene { parent }
{
    setMap(9, 9, 10);
    m_remainMine = m_mineNum;
    m_steps = 0;
}

void PlayScene::setMap(int row, int column, int mine)
{
    m_row = row;
    m_column = column;
    m_mineNum = mine;
}
