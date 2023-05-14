#include "dialogdifficulty.h"

#include "ui_dialogdifficulty.h"

DialogDifficulty::DialogDifficulty(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::DialogDifficulty)
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
    ui->spinBoxMine->setMaximum(rowValue * colunmValue);
}
// 在列数设置发生变化时改变雷数设置的最大值
void DialogDifficulty::on_spinBoxColumn_valueChanged(int colunmValue)
{
    int rowValue = ui->spinBoxRow->value();
    ui->spinBoxMine->setMaximum(int(rowValue * colunmValue * 0.9));
}
