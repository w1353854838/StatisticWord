#ifndef LINKLIST_H
#define LINKLIST_H
#include<iostream>
#include<thread>
#include<fstream>
#include<string>
#include<ctime>
#include<cmath>
#include<Windows.h>
#include<QFileDialog>
#include<QIODevice>
#include<QApplication>
#include<total.h>
//词频链式存储结构
struct Node {
    datatype data;	//数据域
    Node* pre;
    Node* next;	//指针域
};

class LinkList {
public:
    LinkList() {
        Head = new Node;	//生成头结点
        tail = Head;
        tail->pre = NULL;
        tail->next = NULL;	//单链表建立完毕，将终端结点的指针域置空
    }

    ~LinkList() {	//析构函数
        Node* temp = NULL;	//定义临时节点
        while (Head != NULL) {	//释放单链表的每一个结点的存储空间
            temp = Head;	//暂存被释放结点
            Head = Head->next;	// Head指向被释放结点的下一个结点
            delete temp;
        }	//while
    }

    void Insert(string word,int type);
    int isEmpty();	//判断链表是否为空
    Node* Locate(string word);	//按值查找，返回下标
    void PrintList();	//遍历操作，按序号依次输出各元素
    datatype getdata(int n);
    int StatisticalWord(string word);	//统计文章词频(去掉重复单词)
    string WordTransition(string word);	//大写英语单词转化成小写
    int WordJudge(string word);	//判断单词中是否有大写字母
    void StatisticsData();	//数据统计
    int  WordTransitionKey(string word);	//将单词转换为唯一关键码
    void Quick_Sort(Node* Head,Node* tail);
    void Release();	//释放空间


    Node* Head;           //单链表的头指针
    Node* tail;
};
#endif // LINKLIST_H
