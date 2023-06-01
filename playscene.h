#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QGraphicsScene>
#include <QList>
#include <globalconst.h>
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
    int m_theme;
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

    int theme() { return m_theme; }

    void setTheme(int theme) { m_theme = theme; }

    void r_leftClick(int x, int y);
    void r_rightClick(int x, int y);
    void r_doubleClick(int x, int y);
    void openLattice(int x, int y);
    void setRandMine();
    void setMineAround();
    void on_gameStatusChange();
    void on_flagNumChange();
    void showAllMine(int result);
    void changeLatticeTheme();

  signals:
    void gameStatusChangeSignal();
    void flagNumChangeSignal();
    void gameOver(int result);
    void changeLCD_remainMineSignal(int remain_mine);
    void timerStartSignal();
  public slots:
};

#endif // PLAYSCENE_H
