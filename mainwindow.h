#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"hashmap.h"
#include"linklist.h"
#include"bisorttree.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    HashMap* gethash();
    LinkList* getlist();
    BiSortTree* gettree();

private slots:
    void on_openfile_clicked();

    void on_outfile_clicked();

    void on_pushButton_clicked();

    void on_find_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
