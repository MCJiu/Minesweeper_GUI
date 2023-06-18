#include <emojiitem.h>
#include <emojiscene.h>

EmojiScene::EmojiScene(QObject *parent) : QGraphicsScene{parent}
{
    clear();
    QRectF rect(-SIDE_LENTH / 2, -SIDE_LENTH / 2, SIDE_LENTH, SIDE_LENTH);
    setSceneRect(rect);
    emoji = new EmojiItem(CLASSIC);
    emoji->setPos(QPointF(-SIDE_LENTH / 2, -SIDE_LENTH / 2));
    emoji->updateEmoji();
    addItem(emoji);
}
