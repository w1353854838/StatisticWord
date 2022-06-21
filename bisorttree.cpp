#include "bisorttree.h"

using namespace std;



int BiSortTree::StatisticalWord(string word)	//统计文章词频(去掉重复单词)
{
    BiNode* temp=SearchBST(root,word);
    if(temp!=NULL)
    {
        temp->data.frequency++;
        return 0;
    }
    int type;
    if((word[0] >= 'a' && word[0] <= 'z') || (word[0] >= 'A' && word[0] <= 'Z')){
        type = 1;
    }else if(word[0]>=48 && word[0]<=57){
        type = 2;
    }else{
        type = 3;
    }
    datatype node;
    node.word=word;
    node.type=type;
    node.frequency=1;
    BiNode* tree = root;

    root=InsertBST(tree,node);

    return 1;
}

string BiSortTree::WordTransition(string word)	//大写英语单词转化成小写
{
    for (int i = 0; i < int(word.size()); i++) {	//获取字符串长度，使用length()也可以
        if (word[i] >= 'A' && word[i] <= 'Z')	//判断字符是否是大写字母
            word[i] = word[i] + 32;	//ASCII码表中十进制 A==65  a==97  中间相差32，后面的也是如此
    }	//for
    return word;	//返回小写单词
}


int BiSortTree::WordJudge(string word)//判断单词中是否有大写字母
{
    for (int i = 0; i < int(word.size()); i++) {
        if (word[i] >= 'A' && word[i] <= 'Z')	//判断单词中是否有大写字母
            return 1;	//如果有，返回1
    }	//for
    return 0;	//没有返回0
}

void BiSortTree::StatisticsData()	//数据统计
{
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
        if (isalpha(ch)) {
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
        if(ch>=48 && ch<=57){//统计数字
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

        if((ch>=33 && ch<=47) || (ch>=58 && ch<=64)){//统计符号
            mark = ch;
            countmark++;
            StatisticalWord(mark);
        }

    }
    //for
    fin.close();	//关闭文件
}

int  BiSortTree::WordTransitionKey(string word)	//将单词转换为唯一关键码
{
    int a[21] = { 0,2,3,5,7,11,13,17,19,23,27,29,31,37,41,47,51,67,87,101,111 };	//最长识别20个字母的的单词
    int sumkey = 0;
    for (int i = 0; i < int(word.size()); i++) {
        sumkey += int(word[i]);	//每个字符的ASCLL值相加
    }
    sumkey += int('h') * a[int(word.size())];
    return sumkey;
}

//输出函数
void  BiSortTree::InOrder(BiNode* bt) {	//递归输出二叉排序树
    ofstream fout;	//文件写操作 内存写入存储设备
    fout.open(outfilepath.toStdString()+"/outfile3.txt", ios_base::out | ios_base::app);	//打开文件并将内容追加到文件尾
    if (bt == NULL)	//递归调用的结束条件,根指针为空
        return;	//退出函数
    else {
        InOrder(bt->lchild);	//中序递归遍历bt的左子树
        cout << bt->data.frequency << "\t" << bt->data.word << endl;	//访问根结点bt的数据域，输出到屏幕
        fout << bt->data.frequency << "\t" << bt->data.word << endl; //访问根结点bt的数据域，输出到文件
        fout.close();	//关闭文件
        InOrder(bt->rchild);	//中序递归遍历bt的右子树
    }	//else
}

//输出二叉排序树到屏幕和outfile3.txt
void BiSortTree::printf() {
    traversal(root);
    ofstream fout;	//文件写操作 内存写入存储设备
    string out = outfilepath.toStdString()+"/outfile3.txt";
    fout.open(out);//打开文件
    fout <<"二叉树法统计结果:" << endl;
    fout <<"单词总数：" << countword << endl;
    fout <<"数字总数：" << countnumber << endl;
    fout <<"符号总数：" << countmark << endl;
    fout << "词频" << "\t" << "单词" << endl;
    InOrder(sort);	//输出函数
    return;	//退出函数
}

//递归查找函数，返回指针
BiNode* BiSortTree::SearchBST(BiNode* bt, string word) {
    if (bt == NULL)
        return NULL;	//未找到，返回NULL
    if(bt->data.word=="")
    {
        return NULL;
    }
    if (bt->data.word == word)
        return bt;	//找到word，返回该指针
    else if (bt->data.word > word)	//数据大于word
        return SearchBST(bt->lchild, word);	//递归查找左子树
    else	//数据小于word
        return SearchBST(bt->rchild, word);	//递归查找右子树
}

//递归插入函数
BiNode* BiSortTree::InsertBST(BiNode* bt, datatype data) {

    if(bt == NULL||bt->data.word=="") {
        BiNode* s = new BiNode;	//生成一个新的储存空间
        s->data.word=data.word;	//为数据域赋值
        s->data.frequency=data.frequency;
        s->data.type=data.type;
        s->data.key=data.key;
        s->lchild = NULL;	//左孩子指针置空
        s->rchild = NULL;	//右孩子指针置空
        bt = s;	//根指针更新
        return bt;	//返回根指针
    }	//if
    if (bt->data.word.compare(data.word)>0) {	//根节点数据大于要插入的数据
        bt->lchild = InsertBST(bt->lchild, data);	//更新左孩子指针
        return bt;	//返回根指针
    }	//else if
    else {	//根节点数据小于要插入的数据
        bt->rchild = InsertBST(bt->rchild, data);	//更新有孩子指针
        return bt;	//返回根指针
    }	//else
    //BiNode* p=bt;
}

//中序递归遍历
BiNode* BiSortTree::in_traversal(BiNode *T)
{
    if (T == NULL)	//递归调用的结束条件,根指针为空
        return NULL;	//退出函数
    else {
        T->lchild=in_traversal(T->lchild);	//中序递归遍历bt的左子树
        cout << T->data.frequency << "\t" << T->data.word << endl;	//访问根结点bt的数据域，输出到屏幕
        T->rchild=in_traversal(T->rchild);	//中序递归遍历bt的右子树
        return T;
    }	//else
}

BiNode* BiSortTree::traversal(BiNode* T){
    if (T == NULL)	//递归调用的结束条件,根指针为空
        return NULL;	//退出函数
    else {
        BiNode* p = T;
        T->lchild=traversal(T->lchild);	//中序递归遍历bt的左子树
        sort = Sort(sort,p);
        T->rchild=traversal(T->rchild);	//中序递归遍历bt的右子树
        return T;
    }	//else
}
BiNode* BiSortTree::Sort(BiNode*T ,BiNode* p)
{

    if(T == NULL) {
        BiNode* s = new BiNode;	//生成一个新的储存空间
        s->data.word=p->data.word;	//为数据域赋值
        s->data.frequency=p->data.frequency;
        s->data.type=p->data.type;
        s->data.key=p->data.key;
        s->lchild = NULL;	//左孩子指针置空
        s->rchild = NULL;	//右孩子指针置空
        T = s;	//根指针更新
        return T;	//返回根指针
    }	//if
    if (T->data.frequency < p->data.frequency) {	//根节点数据小于要插入的数据
        T->lchild = Sort(T->lchild, p);	//更新左孩子指针
        return T;	//返回根指针
    }	//else if
    else {	//根节点数据小于要插入的数据
        T->rchild = Sort(T->rchild, p);	//更新有孩子指针
        return T;	//返回根指针
    }	//else
    //BiNode* p=bt;

}

//递归析构函数
void BiSortTree::Release(BiNode* bt) {
    if (bt == NULL)
        return;	//根指针为空直接退出
    else {
        Release(bt->lchild);	//释放左子树
        Release(bt->rchild);	//释放右子树
        delete bt;	//释放根结点
    }
}

//判空
int BiSortTree::isEmpty() {
    if (root!=NULL)
        return 0;	//链表非空，返回0
    return 1;	//链表为空，返回1
}
