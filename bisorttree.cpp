#include "bisorttree.h"

using namespace std;



int BiSortTree::StatisticalWord(string word)	//ͳ�����´�Ƶ(ȥ���ظ�����)
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

string BiSortTree::WordTransition(string word)	//��дӢ�ﵥ��ת����Сд
{
    for (int i = 0; i < int(word.size()); i++) {	//��ȡ�ַ������ȣ�ʹ��length()Ҳ����
        if (word[i] >= 'A' && word[i] <= 'Z')	//�ж��ַ��Ƿ��Ǵ�д��ĸ
            word[i] = word[i] + 32;	//ASCII�����ʮ���� A==65  a==97  �м����32�������Ҳ�����
    }	//for
    return word;	//����Сд����
}


int BiSortTree::WordJudge(string word)//�жϵ������Ƿ��д�д��ĸ
{
    for (int i = 0; i < int(word.size()); i++) {
        if (word[i] >= 'A' && word[i] <= 'Z')	//�жϵ������Ƿ��д�д��ĸ
            return 1;	//����У�����1
    }	//for
    return 0;	//û�з���0
}

void BiSortTree::StatisticsData()	//����ͳ��
{
    QFile fin(filename);
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        cout << "Open file failed.";
        return;
    }
    char ch;	//���ڻ�ȡ�ַ�
    string word;	//���ڴ�ŵ���
    string number;
    string mark;
    countword=0;//��������
    countnumber=0;//��������
    countmark=0;//��������
    //int min;	//min���ڱ����С�ĵ���
    for (int i = 0; fin.getChar(&ch); i++) {	//��ȡ�ļ����ݣ���ȥ������
        if (isalpha(ch)) {
            if (word == "\0")	//wordΪ�գ������һ����ĸ
                word = ch;
            else
                word += ch;	//word��Ϊ�գ�ƴ����ĸ��ɵ���
        }	//if
        else {
            if (word != "\0") {	//�ж�֮ǰ��word�����Ƿ��е���
                countword++;
                StatisticalWord(word);	//��ŵ��ṹ����������
            }	//if
            word = "\0";	//����word�����ڴ���µ���
        }	//else
        if(ch>=48 && ch<=57){//ͳ������
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

        if((ch>=33 && ch<=47) || (ch>=58 && ch<=64)){//ͳ�Ʒ���
            mark = ch;
            countmark++;
            StatisticalWord(mark);
        }

    }
    //for
    fin.close();	//�ر��ļ�
}

int  BiSortTree::WordTransitionKey(string word)	//������ת��ΪΨһ�ؼ���
{
    int a[21] = { 0,2,3,5,7,11,13,17,19,23,27,29,31,37,41,47,51,67,87,101,111 };	//�ʶ��20����ĸ�ĵĵ���
    int sumkey = 0;
    for (int i = 0; i < int(word.size()); i++) {
        sumkey += int(word[i]);	//ÿ���ַ���ASCLLֵ���
    }
    sumkey += int('h') * a[int(word.size())];
    return sumkey;
}

//�������
void  BiSortTree::InOrder(BiNode* bt) {	//�ݹ��������������
    ofstream fout;	//�ļ�д���� �ڴ�д��洢�豸
    fout.open(outfilepath.toStdString()+"/outfile3.txt", ios_base::out | ios_base::app);	//���ļ���������׷�ӵ��ļ�β
    if (bt == NULL)	//�ݹ���õĽ�������,��ָ��Ϊ��
        return;	//�˳�����
    else {
        InOrder(bt->lchild);	//����ݹ����bt��������
        cout << bt->data.frequency << "\t" << bt->data.word << endl;	//���ʸ����bt���������������Ļ
        fout << bt->data.frequency << "\t" << bt->data.word << endl; //���ʸ����bt��������������ļ�
        fout.close();	//�ر��ļ�
        InOrder(bt->rchild);	//����ݹ����bt��������
    }	//else
}

//�����������������Ļ��outfile3.txt
void BiSortTree::printf() {
    traversal(root);
    ofstream fout;	//�ļ�д���� �ڴ�д��洢�豸
    string out = outfilepath.toStdString()+"/outfile3.txt";
    fout.open(out);//���ļ�
    fout <<"��������ͳ�ƽ��:" << endl;
    fout <<"����������" << countword << endl;
    fout <<"����������" << countnumber << endl;
    fout <<"����������" << countmark << endl;
    fout << "��Ƶ" << "\t" << "����" << endl;
    InOrder(sort);	//�������
    return;	//�˳�����
}

//�ݹ���Һ���������ָ��
BiNode* BiSortTree::SearchBST(BiNode* bt, string word) {
    if (bt == NULL)
        return NULL;	//δ�ҵ�������NULL
    if(bt->data.word=="")
    {
        return NULL;
    }
    if (bt->data.word == word)
        return bt;	//�ҵ�word�����ظ�ָ��
    else if (bt->data.word > word)	//���ݴ���word
        return SearchBST(bt->lchild, word);	//�ݹ����������
    else	//����С��word
        return SearchBST(bt->rchild, word);	//�ݹ����������
}

//�ݹ���뺯��
BiNode* BiSortTree::InsertBST(BiNode* bt, datatype data) {

    if(bt == NULL||bt->data.word=="") {
        BiNode* s = new BiNode;	//����һ���µĴ���ռ�
        s->data.word=data.word;	//Ϊ������ֵ
        s->data.frequency=data.frequency;
        s->data.type=data.type;
        s->data.key=data.key;
        s->lchild = NULL;	//����ָ���ÿ�
        s->rchild = NULL;	//�Һ���ָ���ÿ�
        bt = s;	//��ָ�����
        return bt;	//���ظ�ָ��
    }	//if
    if (bt->data.word.compare(data.word)>0) {	//���ڵ����ݴ���Ҫ���������
        bt->lchild = InsertBST(bt->lchild, data);	//��������ָ��
        return bt;	//���ظ�ָ��
    }	//else if
    else {	//���ڵ�����С��Ҫ���������
        bt->rchild = InsertBST(bt->rchild, data);	//�����к���ָ��
        return bt;	//���ظ�ָ��
    }	//else
    //BiNode* p=bt;
}

//����ݹ����
BiNode* BiSortTree::in_traversal(BiNode *T)
{
    if (T == NULL)	//�ݹ���õĽ�������,��ָ��Ϊ��
        return NULL;	//�˳�����
    else {
        T->lchild=in_traversal(T->lchild);	//����ݹ����bt��������
        cout << T->data.frequency << "\t" << T->data.word << endl;	//���ʸ����bt���������������Ļ
        T->rchild=in_traversal(T->rchild);	//����ݹ����bt��������
        return T;
    }	//else
}

BiNode* BiSortTree::traversal(BiNode* T){
    if (T == NULL)	//�ݹ���õĽ�������,��ָ��Ϊ��
        return NULL;	//�˳�����
    else {
        BiNode* p = T;
        T->lchild=traversal(T->lchild);	//����ݹ����bt��������
        sort = Sort(sort,p);
        T->rchild=traversal(T->rchild);	//����ݹ����bt��������
        return T;
    }	//else
}
BiNode* BiSortTree::Sort(BiNode*T ,BiNode* p)
{

    if(T == NULL) {
        BiNode* s = new BiNode;	//����һ���µĴ���ռ�
        s->data.word=p->data.word;	//Ϊ������ֵ
        s->data.frequency=p->data.frequency;
        s->data.type=p->data.type;
        s->data.key=p->data.key;
        s->lchild = NULL;	//����ָ���ÿ�
        s->rchild = NULL;	//�Һ���ָ���ÿ�
        T = s;	//��ָ�����
        return T;	//���ظ�ָ��
    }	//if
    if (T->data.frequency < p->data.frequency) {	//���ڵ�����С��Ҫ���������
        T->lchild = Sort(T->lchild, p);	//��������ָ��
        return T;	//���ظ�ָ��
    }	//else if
    else {	//���ڵ�����С��Ҫ���������
        T->rchild = Sort(T->rchild, p);	//�����к���ָ��
        return T;	//���ظ�ָ��
    }	//else
    //BiNode* p=bt;

}

//�ݹ���������
void BiSortTree::Release(BiNode* bt) {
    if (bt == NULL)
        return;	//��ָ��Ϊ��ֱ���˳�
    else {
        Release(bt->lchild);	//�ͷ�������
        Release(bt->rchild);	//�ͷ�������
        delete bt;	//�ͷŸ����
    }
}

//�п�
int BiSortTree::isEmpty() {
    if (root!=NULL)
        return 0;	//����ǿգ�����0
    return 1;	//����Ϊ�գ�����1
}
