#include "latticeitem.h"
#include <QDebug>

void LatticeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) //左键单击
    {
        qDebug() << "左键按下 " << m_row << ", " << m_column;
        emit leftClickSignal(m_row, m_column);
    }
    else if (event->button() == Qt::RightButton)
    {
        qDebug() << "右键按下 " << m_row << ", " << m_column;
        emit rightClickSignal(m_row, m_column);
    }
}

void LatticeItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) // 左键双击
    {
        qDebug() << "双击 " << m_row << ", " << m_column;
        emit doubleClickSignal(m_row, m_column);
    }
}

LatticeItem::LatticeItem(QObject *parent)
    : QObject{parent}
{
    m_row = 0;
    m_column = 0;
    m_isMine = false;
    m_mineAround = 0;
    m_status = CLOSED;
    setFlag(GraphicsItemFlag::ItemIsSelectable);
    setAcceptedMouseButtons(Qt::AllButtons);

    updateLattice();
}

void LatticeItem::updateLattice()
{
    if (m_status == CLOSED) //格子未打开
    {
        setPixmap(QPixmap(":/mine/pic/notSweep.jpg"));
    }
    else if (m_status == FLAG)
    {
        setPixmap(QPixmap(":/mine/pic/flag.jpg"));
    }
    else if (m_status == MINE_GAMEOVER)
    {
        setPixmap(QPixmap(":/mine/pic/mine.jpg"));
    }
    else if (m_status == OPENED)
    {
        if (isMine())
        {
            setPixmap(QPixmap(":/mine/pic/mine_step.jpg"));
        }
        else
        {
            switch (m_mineAround)
            {
            case 0:
                setPixmap(QPixmap(":/mine/pic/mine0.jpg"));
                break;
            case 1:
                setPixmap(QPixmap(":/mine/pic/mine1.jpg"));
                break;
            case 2:
                setPixmap(QPixmap(":/mine/pic/mine2.jpg"));
                break;
            case 3:
                setPixmap(QPixmap(":/mine/pic/mine3.jpg"));
                break;
            case 4:
                setPixmap(QPixmap(":/mine/pic/mine4.jpg"));
                break;
            case 5:
                setPixmap(QPixmap(":/mine/pic/mine5.jpg"));
                break;
            case 6:
                setPixmap(QPixmap(":/mine/pic/mine6.jpg"));
                break;
            case 7:
                setPixmap(QPixmap(":/mine/pic/mine7.jpg"));
                break;
            case 8:
                setPixmap(QPixmap(":/mine/pic/mine8.jpg"));
                break;
            default:
                break;
            }
        }
    }
}

/*
int LatticeItem::r_leftClick()
{
    if (m_status == CLOSED) {

    }
}

int LatticeItem::openLattice()
{
    if (m_status == 0) {
        m_status = 1;
        updateLattice();
        if (m_mineAround == 0) {
        }
    }
}
*/
