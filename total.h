#ifndef TOTAL_H
#define TOTAL_H
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
using namespace std;

extern clock_t starttime,endtime;
extern float runtime;
extern int countword;//单词总数
extern int countnumber;//数字总数
extern int countmark;//符号总数
extern QString filename;
extern QString outfilepath;
extern QString outfile;
extern int n;



// 词频顺序存储结构
struct Word{
    string word;	//单词
    int frequency;	//频率
    int key;
    int type;
};

typedef Word datatype;

#endif // TOTAL_H
