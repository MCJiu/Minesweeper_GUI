#include <QDebug>
#include <include/latticeitem.h>

void LatticeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) //左键单击
    {
        qDebug() << "左键按下 " << m_row << ", " << m_column;
        emit leftClickSignal(m_row, m_column);
    }
    if (event->button() == Qt::RightButton)
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

LatticeItem::LatticeItem(int theme, QObject *parent)
    : QObject{parent}
{
    m_row = 0;
    m_column = 0;
    m_isMine = false;
    m_mineAround = 0;
    m_status = CLOSED;
    m_theme = theme;
    setFlag(GraphicsItemFlag::ItemIsSelectable);
    setAcceptedMouseButtons(Qt::AllButtons);

    updateLattice();
}

void LatticeItem::updateLattice()
{
    switch (m_theme)
    {
    case CLASSIC:
        if (m_status == CLOSED) //格子未打开
        {
            setPixmap(QPixmap(":/classic/pic/classicTheme/unopensqure.png"));
        }
        else if (m_status == FLAG)
        {
            setPixmap(QPixmap(":/classic/pic/classicTheme/flg.png"));
        }
        else if (m_status == QUESTION)
        {
            setPixmap(QPixmap(":/classic/pic/classicTheme/quest.png"));
        }
        else if (m_status == MINE_GAMEOVER)
        {
            setPixmap(QPixmap(":/classic/pic/classicTheme/goodboom.png"));
        }
        else if (m_status == OPENED)
        {
            if (isMine())
            {
                setPixmap(QPixmap(":/classic/pic/classicTheme/boom.png"));
            }
            else
            {
                switch (m_mineAround)
                {
                case 0:
                    setPixmap(QPixmap(":/classic/pic/classicTheme/opensqure.png"));
                    break;
                case 1:
                    setPixmap(QPixmap(":/classic/pic/classicTheme/1.png"));
                    break;
                case 2:
                    setPixmap(QPixmap(":/classic/pic/classicTheme/2.png"));
                    break;
                case 3:
                    setPixmap(QPixmap(":/classic/pic/classicTheme/3.png"));
                    break;
                case 4:
                    setPixmap(QPixmap(":/classic/pic/classicTheme/4.png"));
                    break;
                case 5:
                    setPixmap(QPixmap(":/classic/pic/classicTheme/5.png"));
                    break;
                case 6:
                    setPixmap(QPixmap(":/classic/pic/classicTheme/6.png"));
                    break;
                case 7:
                    setPixmap(QPixmap(":/classic/pic/classicTheme/7.png"));
                    break;
                case 8:
                    setPixmap(QPixmap(":/classic/pic/classicTheme/8.png"));
                    break;
                default:
                    break;
                }
            }
        }
        break;
    case DOG:
        if (m_status == CLOSED) //格子未打开
        {
            setPixmap(QPixmap(":/dog/pic/dogTheme/unopen.png"));
        }
        else if (m_status == FLAG)
        {
            setPixmap(QPixmap(":/dog/pic/dogTheme/flaghouse.png"));
        }
        else if (m_status == QUESTION)
        {
            setPixmap(QPixmap(":/dog/pic/dogTheme/questes.png"));
        }
        else if (m_status == MINE_GAMEOVER)
        {
            setPixmap(QPixmap(":/dog/pic/dogTheme/nice.png"));
        }
        else if (m_status == OPENED)
        {
            if (isMine())
            {
                setPixmap(QPixmap(":/dog/pic/dogTheme/boomboom.png"));
            }
            else
            {
                switch (m_mineAround)
                {
                case 0:
                    setPixmap(QPixmap(":/dog/pic/dogTheme/open.png"));
                    break;
                case 1:
                    setPixmap(QPixmap(":/dog/pic/dogTheme/one.png"));
                    break;
                case 2:
                    setPixmap(QPixmap(":/dog/pic/dogTheme/two.png"));
                    break;
                case 3:
                    setPixmap(QPixmap(":/dog/pic/dogTheme/three.png"));
                    break;
                case 4:
                    setPixmap(QPixmap(":/dog/pic/dogTheme/four.png"));
                    break;
                case 5:
                    setPixmap(QPixmap(":/dog/pic/dogTheme/five.png"));
                    break;
                case 6:
                    setPixmap(QPixmap(":/dog/pic/dogTheme/six.png"));
                    break;
                case 7:
                    setPixmap(QPixmap(":/dog/pic/dogTheme/seven.png"));
                    break;
                case 8:
                    setPixmap(QPixmap(":/dog/pic/dogTheme/eight.png"));
                    break;
                default:
                    break;
                }
            }
        }
        break;
    case PVZ:
        if (m_status == CLOSED) //格子未打开
        {
            setPixmap(QPixmap(":/pvz/pic/pvzTheme/block5.png"));
        }
        else if (m_status == FLAG)
        {
            setPixmap(QPixmap(":/pvz/pic/pvzTheme/flag.png"));
        }
        else if (m_status == QUESTION)
        {
            setPixmap(QPixmap(":/pvz/pic/pvzTheme/block1.png"));
        }
        else if (m_status == MINE_GAMEOVER)
        {
            setPixmap(QPixmap(":/pvz/pic/pvzTheme/mine2.png"));
        }
        else if (m_status == OPENED)
        {
            if (isMine())
            {
                setPixmap(QPixmap(":/pvz/pic/pvzTheme/mine3.png"));
            }
            else
            {
                switch (m_mineAround)
                {
                case 0:
                    setPixmap(QPixmap(":/pvz/pic/pvzTheme/block4.png"));
                    break;
                case 1:
                    setPixmap(QPixmap(":/pvz/pic/pvzTheme/1.png"));
                    break;
                case 2:
                    setPixmap(QPixmap(":/pvz/pic/pvzTheme/2.png"));
                    break;
                case 3:
                    setPixmap(QPixmap(":/pvz/pic/pvzTheme/3.png"));
                    break;
                case 4:
                    setPixmap(QPixmap(":/pvz/pic/pvzTheme/4.png"));
                    break;
                case 5:
                    setPixmap(QPixmap(":/pvz/pic/pvzTheme/5.png"));
                    break;
                case 6:
                    setPixmap(QPixmap(":/pvz/pic/pvzTheme/6.png"));
                    break;
                case 7:
                    setPixmap(QPixmap(":/pvz/pic/pvzTheme/7.png"));
                    break;
                case 8:
                    setPixmap(QPixmap(":/pvz/pic/pvzTheme/8.png"));
                    break;
                default:
                    break;
                }
            }
        }
        break;
    default:
        break;
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
