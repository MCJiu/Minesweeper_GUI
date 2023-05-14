#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QGraphicsScene>
#include <QList>
#include <latticeitem.h>

class PlayScene : public QGraphicsScene {
    Q_OBJECT
private:
    int m_row;
    int m_column;
    int m_mineNum;
    int m_remainMine;
    int m_steps;

public:
    explicit PlayScene(QObject* parent = nullptr);
    ~PlayScene() { }
    void setMap(int row, int column, int mine);
    int remainMine() { return m_remainMine; }
    int steps() { return m_steps; }
    QList<int> difficulty()
    {
        QList<int> difficulty;
        difficulty << m_row << m_column << m_mineNum;
        return difficulty;
    }
public slots:

};

#endif // PLAYSCENE_H
