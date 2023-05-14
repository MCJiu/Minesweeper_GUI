#ifndef LATTICEITEM_H
#define LATTICEITEM_H

#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QObject>

class LatticeItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

private:
    int m_row;
    int m_column;
    bool m_isMine;
    int m_mineAround;
    int m_status; // 0-未被打开，1-已被打开，2-插旗，3-问号

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event);

public:
    explicit LatticeItem(QObject* parent = nullptr);
    ~LatticeItem() { }
    bool isMine() { return m_isMine; }
    int mineAround() { return m_mineAround; }
    int status() { return m_status; }
    void updateLattice();
    int r_leftClick();
    int openLattice();

signals:
    void leftClick(int row, int column);
    void rightClick(int row, int column);
    void doubleClick(int row, int column);
};

#endif // LATTICEITEM_H
