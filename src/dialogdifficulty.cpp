#include "ui_dialogdifficulty.h"
#include <include/dialogdifficulty.h>

DialogDifficulty::DialogDifficulty(QWidget *parent)
    : QDialog(parent), ui(new Ui::DialogDifficulty)
{
    ui->setupUi(this);
}

DialogDifficulty::~DialogDifficulty() { delete ui; }

int DialogDifficulty::rowCount() { return ui->spinBoxRow->value(); }

int DialogDifficulty::columnCount() { return ui->spinBoxColumn->value(); }

int DialogDifficulty::mineCount() { return ui->spinBoxMine->value(); }

void DialogDifficulty::iniDialogDifficulty(int row, int column, int mine)
{
    ui->spinBoxRow->setValue(row);
    ui->spinBoxColumn->setValue(column);
    ui->spinBoxMine->setValue(mine);
}

// 在行数设置发生变化时改变雷数设置的最大值
void DialogDifficulty::on_spinBoxRow_valueChanged(int rowValue)
{
    int colunmValue = ui->spinBoxColumn->value();
    ui->spinBoxMine->setMinimum(int(rowValue * colunmValue * 0.1)); //设置雷数最小值为格子总数的0.1倍
    ui->spinBoxMine->setMaximum(int(rowValue * colunmValue * 0.7)); // 设置雷数最大值为格子总数的0.7倍
}
// 在列数设置发生变化时改变雷数设置的最大值
void DialogDifficulty::on_spinBoxColumn_valueChanged(int colunmValue)
{
    int rowValue = ui->spinBoxRow->value();
    ui->spinBoxMine->setMinimum(int(rowValue * colunmValue * 0.1)); //设置雷数最小值为格子总数的0.1倍
    ui->spinBoxMine->setMaximum(int(rowValue * colunmValue * 0.7)); // 设置雷数最大值为格子总数的0.7倍
}
