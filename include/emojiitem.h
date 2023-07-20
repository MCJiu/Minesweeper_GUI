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
    int m_theme;  // emoji的主题
    int m_status; // emoji的状态（笑脸或哭脸）

  public:
    EmojiItem(int theme = CLASSIC, QObject *parent = nullptr);
    int theme() { return m_theme; }
    int status() { return m_status; }
    void setTheme(int theme) { m_theme = theme; }
    void setStatus(int status) { m_status = status; }
    void updateEmoji(); //更新emoji的贴图
};

#endif // EMOJIITEM_H
