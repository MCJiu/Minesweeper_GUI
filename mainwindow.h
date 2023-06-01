#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <emojiscene.h>
#include <globalconst.h>
#include <playscene.h>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void on_gameOver(int result);
    void on_flagNumChange();
    void on_changeRemainMineLCD(int remain_mine);
    void on_timerStart();
    void on_timerStop();
    void on_timer_timeout();

  private slots:
    void on_actionCustomize_C_triggered();

    void on_actionPrimary_P_triggered();

    void on_actionIntermediate_M_triggered();

    void on_actionAdvanced_A_triggered();

    void on_actionNewGame_N_triggered();

    void on_actionClassic_C_triggered();

    void on_actionDog_D_triggered();

    void on_actionPvZ_P_triggered();

    void on_actionAbout_A_triggered();

  private:
    Ui::MainWindow *ui;
    PlayScene *scene;
    EmojiScene *emoScene;
    QTimer *fTimer;
    int timer_time; // 计时器应显示的值
  signals:
    void timerStopSignal();
};
#endif // MAINWINDOW_H
