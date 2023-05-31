#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QGraphicsScene>
#include <QList>
#include <latticeitem.h>

const int MAX_ROW = 24;
const int MAX_COLUMN = 30;

class PlayScene : public QGraphicsScene
{
    Q_OBJECT
  private:
    int m_row;        //行数
    int m_column;     //列数
    int m_mineNum;    //总雷数
    int m_remainMine; // 剩余雷数
    int m_steps;      // 已进行的操作数
    LatticeItem *board[MAX_ROW][MAX_COLUMN];

  public:
    explicit PlayScene(QObject *parent = nullptr);

    // 初始化游戏板
    void initialize();
    // 布置游戏面板
    void setMap(int row, int column, int mine);

    // 返回剩余雷数
    int remainMine() { return m_remainMine; }

    // 返回已进行的操作数
    int steps() { return m_steps; }

    int row() { return m_row; }

    int column() { return m_column; }

    int mineNum() { return m_mineNum; }

    QList<int> difficulty()
    {
        QList<int> difficulty;
        difficulty << m_row << m_column << m_mineNum;
        return difficulty;
    }
  public slots:
};

#endif // PLAYSCENE_H
