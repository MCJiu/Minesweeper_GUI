#include <QObject>
#include <include/emojiitem.h>

EmojiItem::EmojiItem(int theme, QObject *parent) : QObject{parent}
{
    m_theme = theme;
    m_status = SMILE;
    setFlag(GraphicsItemFlag::ItemIsSelectable);
    setAcceptedMouseButtons(Qt::AllButtons);
}

void EmojiItem::updateEmoji()
{
    switch (m_theme)
    {
    case PVZ:
    case CLASSIC:
        if (m_status == SMILE)
        {
            setPixmap(QPixmap(":/classic/pic/classicTheme/smile.png"));
        }
        else
        {
            setPixmap(QPixmap(":/classic/pic/classicTheme/cryface.png"));
        }
        break;
    case DOG:
        if (m_status == SMILE)
        {
            setPixmap(QPixmap(":/dog/pic/dogTheme/haha.png"));
        }
        else
        {
            setPixmap(QPixmap(":/dog/pic/dogTheme/cry.png"));
        }
        break;
    default:
        break;
    }
}
