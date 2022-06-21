#ifndef BISORTTREE_H
#define BISORTTREE_H
#include<total.h>
using namespace std;

//二叉排序树链式存储结构
typedef struct BiNode {
    datatype data;	//节点数据域
    BiNode* lchild, * rchild;	//左右孩子指针
}BiNode;

class BiSortTree
{
public:
    BiNode* root=NULL;
    BiNode* sort=NULL;

    BiSortTree(){
        root=new BiNode;
        root->data.word="";
        root->data.type=0;
        root->data.frequency=0;
    }

    ~BiSortTree(){
        Release(root);
        Release(sort);
    }

    BiNode* InsertBST(datatype data) {	//函数重载，插入数据域data
        return InsertBST(root, data);
    }

    BiNode* SearchBST(string word) {	//函数重载,查找值为word的结点
        return SearchBST(root, word);
    }
    void printf();	//输出函数
    int StatisticalWord(string word);	//统计文章词频(去掉重复单词)
    string WordTransition(string word);	//大写英语单词转化成小写
    int WordJudge(string word);	//判断单词中是否有大写字母
    void StatisticsData();	//数据统计
    int  WordTransitionKey(string word);	//将单词转换为唯一关键码
    void Release(BiNode* bt);	//释放空间
    BiNode* InsertBST(BiNode* bt, datatype data);	//插入数据域data
    BiNode* SearchBST(BiNode* bt, string word);	//查找值为word的结点
    void InOrder(BiNode* bt);	//中序遍历函数调用
    BiNode* Sort(BiNode* T,BiNode* p);
    BiNode* in_traversal(BiNode* T);
    BiNode* traversal(BiNode* T);
    int isEmpty();
};

#endif // BISORTTREE_H
