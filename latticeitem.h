#ifndef LATTICEITEM_H
#define LATTICEITEM_H

#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QObject>

enum
{
    CLOSED,
    OPENED,
    FLAG,
    QUESTION,
    MINE_GAMEOVER
};

enum
{
    CLASSIC,
    DOG,
    PVZ
};

class LatticeItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

  private:
    int m_row;
    int m_column;
    bool m_isMine;
    int m_mineAround;
    int m_status; // CLOSED, OPENED, FLAG, QUESTION
    int m_theme;

  protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

  public:
    explicit LatticeItem(int theme = CLASSIC, QObject *parent = nullptr);
    ~LatticeItem() {}
    bool isMine() { return m_isMine; }
    int mineAround() { return m_mineAround; }
    int status() { return m_status; }
    int theme() { return m_theme; }

    // 设置私有成员的方法
    void setRow(int row) { m_row = row; }
    void setColumn(int column) { m_column = column; }
    void setMine(bool isMine) { m_isMine = isMine; }
    void setMineAround(int mineAround) { m_mineAround = mineAround; }
    void setStatus(int status) { m_status = status; }
    void setTheme(int theme) { m_theme = theme; }

    void updateLattice();
    int r_leftClick();
    int openLattice();

  signals:
    void leftClickSignal(int row, int column);
    void rightClickSignal(int row, int column);
    void doubleClickSignal(int row, int column);
};

#endif // LATTICEITEM_H
