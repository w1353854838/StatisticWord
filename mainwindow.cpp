#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include "dialog.h"
#include"hashmap.h"
#include"linklist.h"
#include"bisorttree.h"
#include"total.h"
using namespace std;

clock_t starttime,endtime;
float runtime;
int countword = 0;//单词总数
int countnumber = 0;//数字总数
int countmark = 0;//符号总数
QString filename;
QString outfilepath;
QString outfile;
int n;
LinkList l;
HashMap hashmap;
BiSortTree b;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openfile_clicked()
{
    QString curPath;
    curPath=QCoreApplication::applicationDirPath(); //获取应用程序的路径
   //调用打开文件对话框打开一个文件
    filename=QFileDialog::getOpenFileName(this,tr("打开一个文件"),curPath,"文本文件(*.txt);;C++程序文件(*.cpp);;H头文件(*.h);;所有文件(*.*)");
    ui->filepath->setText(filename);
}

void MainWindow::on_outfile_clicked()
{
    outfilepath=QFileDialog::getExistingDirectory(this, tr("选择文件保存路径"), "./", QFileDialog::ShowDirsOnly);
    ui->outfilepath->setText(outfilepath);//显示输出文件目录
}

void MainWindow::on_pushButton_clicked()
{
    n = ui->comboBox->currentIndex();
    ui->tip->setText(" ");
    if(filename==NULL||outfilepath==NULL){
        ui->tip->setText("请选择文件和输出路径");
        return;
    }

    hashmap.Release();


    if(n == 0){//双链表
        starttime = clock();
        LinkList *list = new LinkList();
        list->StatisticsData();
        list->Quick_Sort(l.Head,l.tail);
        list->PrintList();
        l=*list;
        endtime = clock();
        runtime = (float)(endtime - starttime)/CLOCKS_PER_SEC;
        QString time = QString("%1 秒").arg(runtime);
        ui->runtime->setText(time);
        outfile = outfilepath + "/outfile1.txt";
        QFile f1(outfile);
        ui->outfilepath_2->setText(outfile);
        if (f1.open(QFile::ReadOnly))
        {
            QTextStream q1(&f1);
            QString t1 = q1.readAll();
            ui->textBrowser->setText(t1);//预览结果
        }
        f1.close();
        if(!l.isEmpty()){
            ui->find->setEnabled(true);
        }else{
            ui->find->setEnabled(false);
        }
    }else if(n == 1){//哈希表
        starttime = clock();
        //HashMap hash;
        hashmap.readIn();
        hashmap.Print();//词频统计
        endtime = clock();
        runtime = (float)(endtime - starttime)/CLOCKS_PER_SEC;
        QString time = QString("%1 秒").arg(runtime);
        ui->runtime->setText(time);
        outfile = outfilepath + "/outfile2.txt";
        QFile f2(outfile);
        ui->outfilepath_2->setText(outfile);
        if (f2.open(QFile::ReadOnly))
        {
            QTextStream q2(&f2);
            QString t2 = q2.readAll();
            ui->textBrowser->setText(t2);//预览结果
        }
        f2.close();
        if(!hashmap.isEmpty()){
            ui->find->setEnabled(true);
        }else{
            ui->find->setEnabled(false);
        }
    }else if(n == 2){//二叉树
        starttime = clock();
        BiSortTree* bt = new BiSortTree();
        bt->StatisticsData();
        bt->printf();
        b=*bt;
        //b.readIn();
        //b.Print();//词频统计
        endtime = clock();
        runtime = (float)(endtime - starttime)/CLOCKS_PER_SEC;
        QString time = QString("%1 秒").arg(runtime);
        ui->runtime->setText(time);
        outfile = outfilepath + "/outfile3.txt";
        QFile f3(outfile);
        QString s3 = QDir::currentPath()+"outfile3.txt";
        if (f3.open(QFile::ReadOnly))
        {
            QTextStream in3(&f3);
            QString t3 = in3.readAll();
            ui->textBrowser->setText(t3);//预览结果
            ui->outfilepath->setText(s3);//显示输出文件目录
        }
        f3.close();
        if(!b.isEmpty()){
            ui->find->setEnabled(true);
        }else{
            ui->find->setEnabled(false);
        }
    }
}

void MainWindow::on_find_clicked()
{
    Dialog dialog;
    dialog.exec();
}

HashMap* MainWindow::gethash(){
    return &hashmap;
}

LinkList* MainWindow::getlist(){
    return &l;
}

BiSortTree* MainWindow::gettree(){
    return &b;
}


