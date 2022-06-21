#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include "hashmap.h"
#include "linklist.h"
#include "total.h"



Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


QString Dialog::query(QString wordname){
    MainWindow main;
    string word = wordname.toStdString();
    if(n == 0){
        LinkList *l = main.getlist();
        if(l->Locate(word)==NULL){
            return NULL;
        }
        return QString::number(l->Locate(word)->data.frequency);
    }else if(n == 1){
        HashMap *hash = main.gethash();
        if(hash->query(word)<=0){
            return NULL;
        }
        return QString::number(hash->query(word));
    }else if(n == 2){
        BiSortTree *b = main.gettree();
        if(b->SearchBST(b->root,word)==NULL){
            return NULL;
        }
        return QString::number(b->SearchBST(b->root,word)->data.frequency);
    }
}

void Dialog::on_pushButton_clicked()
{
    QString wordname = ui->wordname->toPlainText();
    QString frequency = query(wordname);
    if(frequency==NULL){
        ui->frequency->setText("单词不存在");
    }else{
        string q = frequency.toStdString();
        cout << q << endl;
        ui->frequency->setText(frequency);
    }

}


