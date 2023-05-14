#include "mainwindow.h"
#include "dialogdifficulty.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionCustomize_C_triggered()
{
    DialogDifficulty* pDifficultyCfg = new DialogDifficulty(this);
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
