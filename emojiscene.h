#ifndef EMOJISCENE_H
#define EMOJISCENE_H

#include <QGraphicsScene>
#include <emojiitem.h>
#include <globalconst.h>

class EmojiScene : public QGraphicsScene
{
    Q_OBJECT

  private:
    EmojiItem *emoji;

  public:
    explicit EmojiScene(QObject *parent = nullptr);
    void setEmojiTheme(int theme)
    {
        emoji->setTheme(theme);
        emoji->updateEmoji();
    }
    void setEmojiStatus(int status)
    {
        emoji->setStatus(status);
        emoji->updateEmoji();
    }
};

#endif // EMOJISCENE_H
