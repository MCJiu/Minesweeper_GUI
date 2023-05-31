#include "ui_mainwindow.h"
#include <dialogdifficulty.h>
#include <latticeitem.h>
#include <mainwindow.h>
#include <playscene.h>

const int SIDE_LENTH = 20;

//LatticeItem **createBoard(int row, int column);
//void freeBoard(LatticeItem **board, int row);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new PlayScene();

    // 设置 scene 的直角坐标位置参数
    int left = -(SIDE_LENTH * scene->row() / 2);
    int top = -(SIDE_LENTH * scene->column() / 2);
    int width = SIDE_LENTH * scene->row();
    int height = SIDE_LENTH * scene->column();

    // 设置 scene 并将scene与gameView关联
    QRectF rect(left, top, width, height);
    scene->setSceneRect(rect);
    ui->gameView->setScene(scene);
    scene->initialize();
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
    pDifficultyCfg->iniDialogDifficulty(9, 9, 10); //后续记得修改参数
    pDifficultyCfg->setWindowTitle("自定义难度");
    int ret_val = pDifficultyCfg->exec();
    if (ret_val == QDialog::Accepted) // 如果玩家按下确定按钮
    {
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
