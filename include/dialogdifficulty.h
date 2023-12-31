#ifndef DIALOGDIFFICULTY_H
#define DIALOGDIFFICULTY_H

#include <QDialog>

namespace Ui
{
class DialogDifficulty;
}

class DialogDifficulty : public QDialog
{
    Q_OBJECT

  public:
    explicit DialogDifficulty(QWidget *parent = nullptr);
    ~DialogDifficulty();
    int rowCount();
    int columnCount();
    int mineCount();

    // 在打开自定义难度对话框时初始化对话框中三个spinbox的值
    void iniDialogDifficulty(int row, int column, int mine);

  private slots:
    // 在行数设置发生变化时改变雷数设置的最大值
    void on_spinBoxRow_valueChanged(int arg1);
    // 在列数设置发生变化时改变雷数设置的最大值
    void on_spinBoxColumn_valueChanged(int arg1);

  private:
    Ui::DialogDifficulty *ui;
};

#endif // DIALOGDIFFICULTY_H
