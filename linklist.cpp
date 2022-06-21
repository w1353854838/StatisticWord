
#include<linklist.h>
using namespace std;


void my_swap(Node* p, Node* q) {
    // 自写交换函数
    // 只交换值，不更改链表指针，减少执行时间
    // 这里如果想交换指针，就需要增加前驱，麻烦点而已
    datatype tmp = p->data;
    p->data = q->data;
    q->data = tmp;

}
void LinkList::Quick_Sort(Node* head,Node* tail)
{
    if (head == tail || head == NULL || head == tail->next)
    {
        return;
    }// 递归出口
    Node* p, * q, * pre;
    p = q = pre = head;
    while (q != tail) {
        q = q->next; // 对于一个链表只遍历一遍
        if (q->data.frequency>head->data.frequency) {
                // 如果q的值大于base则放在p左边
            pre = p;
            p = p->next;
            my_swap(p, q);
        }
    }// 执行while完毕后的情况：
        // base在head,[head->next,p]小于base,[p->next,tail]大于base
    my_swap(head, p); // 将base放在最终位置
    Quick_Sort(head, pre);
    Quick_Sort(p->next, tail);

}

// 读取TXT内容并整理
//统计文章词频(去掉重复单词)
int LinkList::StatisticalWord(string word) {
    int type;
    if((word[0] >= 'a' && word[0] <= 'z') || (word[0] >= 'A' && word[0] <= 'Z')){
        type = 1;
    }else if(word[0]>=48 && word[0]<=57){
        type = 2;
    }else{
        type = 3;
    }
    Insert(word,type);
}

//大写英语单词转化成小写
string LinkList::WordTransition(string word) {
    for (int i = 0; i < int(word.size()); i++) {	//获取字符串长度，使用length()也可以
        if (word[i] >= 'A' && word[i] <= 'Z')	//判断字符是否是大写字母
            word[i] = word[i] + 32;	//ASCII码表中十进制 A==65  a==97  中间相差32，后面的也是如此
    }	//for
    return word;	//返回小写单词
}

//判断单词中是否有大写字母
int LinkList::WordJudge(string word) {
    for (int i = 0; i < int(word.size()); i++) {
        if (word[i] >= 'A' && word[i] <= 'Z')	//判断单词中是否有大写字母
            return 1;	//如果有，返回1
    }	//for
    return 0;	//没有返回0
}

//词频统计
void LinkList::StatisticsData() {
    QFile fin(filename);
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        cout << "Open file failed.";
        return;
    }
    char ch;	//用于获取字符
    string word;	//用于存放单词
    string number;
    string mark;
    countword=0;//单词总数
    countnumber=0;//数字总数
    countmark=0;//符号总数
    //int min;	//min用于标记最小的单词
    for (int i = 0; fin.getChar(&ch); i++) {	//读取文件内容，并去除符号
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            if (word == "\0")	//word为空，放入第一个字母
                word = ch;
            else
                word += ch;	//word不为空，拼接字母组成单词
        }	//if
        else {
            if (word != "\0") {	//判断之前的word里面是否有单词
                countword++;
                StatisticalWord(word);	//存放到结构体数组里面
            }	//if
            word = "\0";	//重置word，用于存放新单词
        }	//else
        if(ch>=48 && ch<=57){
            if(number == "\0")
                number = ch;
            else
                number += ch;
        }else{
            if(number != "\0"){
                countnumber++;
                StatisticalWord(number);
            }
            number="\0";
        }

        if((ch>=33 && ch<=47) || (ch>=58 && ch<=64)){
            mark = ch;
            countmark++;
            StatisticalWord(mark);
        }

    }
    //for
    fin.close();	//关闭文件
}

//将单词转换为唯一关键码
int LinkList::WordTransitionKey(string word) {
    int a[21] = { 0,2,3,5,7,11,13,17,19,23,27,29,31,37,41,47,51,67,87,101,111 };	//最长识别20个字母的的单词
    int sumkey = 0;
    for (int i = 0; i < int(word.size()); i++) {
        sumkey += int(word[i]);	//每个字符的ASCLL值相加
    }
    sumkey += int('h') * a[int(word.size())];
    return sumkey;
}


void LinkList::Insert(string word,int type){
    Node* p = NULL;
    if(Locate(word)!=NULL){
        p = Locate(word);
        p->data.frequency++;
    }else{
        p = new Node;
        p->data.word = word;
        p->data.key = WordTransitionKey(word);
        p->data.frequency = 1;
        p->data.type = type;
        p->pre = tail;
        p->next = tail->next;
        tail->next = p;
        tail = p;
    }
}

//返回数据域
datatype LinkList::getdata(int n) {
    Node* t = Head->next;	//指针初始化
    for (int i = 1; i < n; i++)
        t = t->next;
    return t->data;

}

//判空
int LinkList::isEmpty() {
    if (Head->next)
        return 0;	//链表非空，返回0
    return 1;	//链表为空，返回1
}

//输出单链表
void LinkList::PrintList() {
    Node* p = Head->next;//工作指针p初始化
    ofstream fout;	//文件写操作 内存写入存储设备
    string out = outfilepath.toStdString()+"/outfile1.txt";
    fout.open(out);	//打开文件
    fout <<"双链表法统计结果:" << endl;
    fout <<"单词总数：" << countword << endl;
    fout <<"数字总数：" << countnumber << endl;
    fout <<"符号总数：" << countmark << endl;
    fout << "词频" << "\t" << "单词" << endl;
    while (p != NULL) {
        fout << p->data.frequency << "\t" << p->data.word << endl;
        p = p->next;	//指针p后移
    }	//while
    fout.close();	//关闭文件

    cout <<"单词总数：" << countword << endl;
    cout <<"数字总数：" << countnumber << endl;
    cout <<"符号总数：" << countmark << endl;
    cout << "词频" << "\t" << "单词" << endl;
    Node* p1 = Head->next;//工作指针p初始化
    while (p1) {	//p <--> p != NULL
        cout << p1->data.frequency << "\t" << p1->data.word << endl;
        p1 = p1->next;                 //工作指针p后移，注意不能写作p++
    }	//while
    cout << "单词以及词频已经保存到文件outfile1.txt文件中" << endl;
}

//按值查找，返回结点指针
Node* LinkList::Locate(string word) {
    Node* p = Head->next;   //指针p初始化
    while (p != NULL) {
        if (p->data.word.compare(word)==0)
            return p;     //查找成功，结束函数并返回下标
        p = p->next;	//p指针后移
    }	//while
    return NULL;	//退出循环表明查找失败
}

void LinkList::Release(){
    while (Head != NULL) {	//释放单链表的每一个结点的存储空间
        Node* temp = Head;	//暂存被释放结点
        Head = Head->next;	// Head指向被释放结点的下一个结点
        delete temp;
    }	//while
}
