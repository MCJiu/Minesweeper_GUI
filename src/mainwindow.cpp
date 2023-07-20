#include "ui_mainwindow.h"
#include <QMessageBox>
#include <include/dialogdifficulty.h>
#include <include/latticeitem.h>
#include <include/mainwindow.h>
#include <include/playscene.h>

//LatticeItem **createBoard(int row, int column);
//void freeBoard(LatticeItem **board, int row);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new PlayScene();
    emoScene = new EmojiScene();

    /* 设置计时器 */
    fTimer = new QTimer(this);
    fTimer->stop();
    fTimer->setInterval(1000); //设置计时间隔为1000ms
    on_timerStop();

    connect(fTimer, &QTimer::timeout, this, &MainWindow::on_timer_timeout);
    connect(scene, &PlayScene::timerStartSignal, this, &MainWindow::on_timerStart);
    connect(this, &MainWindow::timerStopSignal, this, &MainWindow::on_timerStop);
    connect(scene, &PlayScene::gameOver, this, &MainWindow::on_gameOver);
    connect(scene, &PlayScene::gameStatusChangeSignal, scene, &PlayScene::on_gameStatusChange);
    connect(scene, &PlayScene::flagNumChangeSignal, scene, &PlayScene::on_flagNumChange);
    connect(scene, &PlayScene::changeLCD_remainMineSignal, this, &MainWindow::on_changeRemainMineLCD);
    scene->initialize();
    ui->gameView->setScene(scene);
    ui->gameView->setFixedHeight(SIDE_LENTH * scene->row() + 5); // +5是为了额外多出一些空间
    ui->gameView->setFixedWidth(SIDE_LENTH * scene->column() + 5);
    ui->emojiView->setFixedHeight(45);
    ui->emojiView->setFixedWidth(45);
    ui->lcd_remainMine->setFixedHeight(45);
    ui->lcd_remainMine->setFixedWidth(100);
    ui->lcd_timer->setFixedHeight(45);
    ui->lcd_timer->setFixedWidth(100);
    this->setFixedHeight(SIDE_LENTH * scene->row() + 100);
    this->setFixedWidth(SIDE_LENTH * scene->column() + 20);
    ui->emojiView->setScene(emoScene);

    // LatticeItem二维数组，用于存放游戏面板
    //    LatticeItem **board = createBoard(playSceneItem->row(), playSceneItem->column());

    // 设置flag和位置，并显示
    //    for (int i = 0; i < playSceneItem->row(); i++)
    //    {
    //        for (int j = 0; j < playSceneItem->column(); j++)
    //        {
    //            board[i][j].setPos(QPointF(left + SIDE_LENTH * j, top + SIDE_LENTH * i));
    //            board[i][j].setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    //            scene->addItem(&board[i][j]);
    //        }
    //    }
    //    freeBoard(board, playSceneItem->row());
    //    delete playSceneItem;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionCustomize_C_triggered()
{
    DialogDifficulty *pDifficultyCfg = new DialogDifficulty(this);
    Qt::WindowFlags flags = pDifficultyCfg->windowFlags();
    pDifficultyCfg->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    pDifficultyCfg->iniDialogDifficulty(scene->row(), scene->column(), scene->mineNum()); //后续记得修改参数
    pDifficultyCfg->setWindowTitle("自定义难度");
    int ret_val = pDifficultyCfg->exec();
    if (ret_val == QDialog::Accepted) // 如果玩家按下确定按钮
    {
        scene->setMap(pDifficultyCfg->rowCount(), pDifficultyCfg->columnCount(), pDifficultyCfg->mineCount());
        ui->gameView->setFixedHeight(SIDE_LENTH * scene->row() + 5); // +5是为了额外多出一些空间
        ui->gameView->setFixedWidth(SIDE_LENTH * scene->column() + 5);
        this->setFixedHeight(SIDE_LENTH * scene->row() + 100);
        this->setFixedWidth(SIDE_LENTH * scene->column() + 20);
        scene->initialize();
    }
    delete pDifficultyCfg;
}

//LatticeItem** createBoard(int row, int column)
//{
//    LatticeItem** board = new LatticeItem*[row];
//    for (int i = 0; i < row; i++) {
//        board[i] = new LatticeItem[column];
//    }
//    return board;
//}

//void freeBoard(LatticeItem** board, int row)
//{
//    for (int i = 0; i < row; i++) {
//        delete[] board[i];
//    }
//    delete[] board;
//}

void MainWindow::on_gameOver(int result)
{
    scene->showAllMine(result);
    emit timerStopSignal();
    if (result == WIN)
    {
        QString dlgTitle = "游戏结束";
        QString dlgMsg = "您获胜了!";
        QMessageBox::information(this, dlgTitle, dlgMsg);
    }
    else // result==LOSE
    {
        emoScene->setEmojiStatus(CRY);
        QString dlgTitle = "游戏结束";
        QString dlgMsg = "很遗憾，扫雷失败!";
        QMessageBox::critical(this, dlgTitle, dlgMsg);
    }
    scene->initialize();
    emoScene->setEmojiStatus(SMILE);
}

void MainWindow::on_changeRemainMineLCD(int remain_mine)
{
    ui->lcd_remainMine->display(remain_mine);
}

void MainWindow::on_timerStart()
{
    timer_time = 0;
    fTimer->start();
    ui->lcd_timer->display(timer_time);
}

void MainWindow::on_timerStop()
{
    fTimer->stop();
    ui->lcd_timer->display(timer_time);
}

void MainWindow::on_timer_timeout()
{
    timer_time++;
    ui->lcd_timer->display(timer_time);
}

void MainWindow::on_actionPrimary_P_triggered()
{
    scene->setMap(9, 9, 10);
    ui->gameView->setFixedHeight(SIDE_LENTH * scene->row() + 5); // +5是为了额外多出一些空间
    ui->gameView->setFixedWidth(SIDE_LENTH * scene->column() + 5);
    this->setFixedHeight(SIDE_LENTH * scene->row() + 100);
    this->setFixedWidth(SIDE_LENTH * scene->column() + 20);
    scene->initialize();
}

void MainWindow::on_actionIntermediate_M_triggered()
{
    scene->setMap(16, 16, 40);
    ui->gameView->setFixedHeight(SIDE_LENTH * scene->row() + 5); // +5是为了额外多出一些空间
    ui->gameView->setFixedWidth(SIDE_LENTH * scene->column() + 5);
    this->setFixedHeight(SIDE_LENTH * scene->row() + 100);
    this->setFixedWidth(SIDE_LENTH * scene->column() + 20);
    scene->initialize();
}

void MainWindow::on_actionAdvanced_A_triggered()
{
    scene->setMap(16, 30, 99);
    ui->gameView->setFixedHeight(SIDE_LENTH * scene->row() + 5); // +5是为了额外多出一些空间
    ui->gameView->setFixedWidth(SIDE_LENTH * scene->column() + 5);
    this->setFixedHeight(SIDE_LENTH * scene->row() + 100);
    this->setFixedWidth(SIDE_LENTH * scene->column() + 20);
    scene->initialize();
}

void MainWindow::on_actionNewGame_N_triggered()
{
    scene->initialize();
}

void MainWindow::on_actionClassic_C_triggered()
{
    scene->setTheme(CLASSIC);
    scene->changeLatticeTheme();
    emoScene->setEmojiTheme(CLASSIC);
}

void MainWindow::on_actionDog_D_triggered()
{
    scene->setTheme(DOG);
    scene->changeLatticeTheme();
    emoScene->setEmojiTheme(DOG);
}

void MainWindow::on_actionPvZ_P_triggered()
{
    scene->setTheme(PVZ);
    scene->changeLatticeTheme();
    emoScene->setEmojiTheme(PVZ);
}

void MainWindow::on_actionAbout_A_triggered()
{
    QMessageBox::information(this, "关于", "本项目由北京邮电大学计算机学院 MCJiu, cby, Gcoin42 开发\n联系邮箱: mcjiu@bupt.edu.cn");
}
