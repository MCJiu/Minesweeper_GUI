#ifndef EMOJIITEM_H
#define EMOJIITEM_H

#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QObject>
#include <globalconst.h>

class EmojiItem : public QObject,
                  public QGraphicsPixmapItem
{
    Q_OBJECT

  private:
    int m_theme;
    int m_status;

  public:
    EmojiItem(int theme = CLASSIC, QObject *parent = nullptr);
    int theme() { return m_theme; }
    int status() { return m_status; }
    void setTheme(int theme) { m_theme = theme; }
    void setStatus(int status) { m_status = status; }
    void updateEmoji();
};

#endif // EMOJIITEM_H
