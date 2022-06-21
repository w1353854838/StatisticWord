#ifndef HASHMAP_H
#define HASHMAP_H

#include <QMainWindow>
#include "total.h"
#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<algorithm>
#include<list>
#include<functional>
#include <unordered_map>
using namespace std;

class HashMap{
private:
    unordered_map<string,int> hashMap;
    unordered_map<string,int>::iterator it;
    int sum;
public:
    int query(string wordname);
    void showInfo();
    int readIn();
    void Insert(string data);
    void Print();
    void Release();
    int isEmpty();
};
#endif // HASHMAP_H
