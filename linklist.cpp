
#include<linklist.h>
using namespace std;


void my_swap(Node* p, Node* q) {
    // ��д��������
    // ֻ����ֵ������������ָ�룬����ִ��ʱ��
    // ��������뽻��ָ�룬����Ҫ����ǰ�����鷳�����
    datatype tmp = p->data;
    p->data = q->data;
    q->data = tmp;

}
void LinkList::Quick_Sort(Node* head,Node* tail)
{
    if (head == tail || head == NULL || head == tail->next)
    {
        return;
    }// �ݹ����
    Node* p, * q, * pre;
    p = q = pre = head;
    while (q != tail) {
        q = q->next; // ����һ������ֻ����һ��
        if (q->data.frequency>head->data.frequency) {
                // ���q��ֵ����base�����p���
            pre = p;
            p = p->next;
            my_swap(p, q);
        }
    }// ִ��while��Ϻ�������
        // base��head,[head->next,p]С��base,[p->next,tail]����base
    my_swap(head, p); // ��base��������λ��
    Quick_Sort(head, pre);
    Quick_Sort(p->next, tail);

}

// ��ȡTXT���ݲ�����
//ͳ�����´�Ƶ(ȥ���ظ�����)
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

//��дӢ�ﵥ��ת����Сд
string LinkList::WordTransition(string word) {
    for (int i = 0; i < int(word.size()); i++) {	//��ȡ�ַ������ȣ�ʹ��length()Ҳ����
        if (word[i] >= 'A' && word[i] <= 'Z')	//�ж��ַ��Ƿ��Ǵ�д��ĸ
            word[i] = word[i] + 32;	//ASCII�����ʮ���� A==65  a==97  �м����32�������Ҳ�����
    }	//for
    return word;	//����Сд����
}

//�жϵ������Ƿ��д�д��ĸ
int LinkList::WordJudge(string word) {
    for (int i = 0; i < int(word.size()); i++) {
        if (word[i] >= 'A' && word[i] <= 'Z')	//�жϵ������Ƿ��д�д��ĸ
            return 1;	//����У�����1
    }	//for
    return 0;	//û�з���0
}

//��Ƶͳ��
void LinkList::StatisticsData() {
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
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
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
    fin.close();	//�ر��ļ�
}

//������ת��ΪΨһ�ؼ���
int LinkList::WordTransitionKey(string word) {
    int a[21] = { 0,2,3,5,7,11,13,17,19,23,27,29,31,37,41,47,51,67,87,101,111 };	//�ʶ��20����ĸ�ĵĵ���
    int sumkey = 0;
    for (int i = 0; i < int(word.size()); i++) {
        sumkey += int(word[i]);	//ÿ���ַ���ASCLLֵ���
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

//����������
datatype LinkList::getdata(int n) {
    Node* t = Head->next;	//ָ���ʼ��
    for (int i = 1; i < n; i++)
        t = t->next;
    return t->data;

}

//�п�
int LinkList::isEmpty() {
    if (Head->next)
        return 0;	//����ǿգ�����0
    return 1;	//����Ϊ�գ�����1
}

//���������
void LinkList::PrintList() {
    Node* p = Head->next;//����ָ��p��ʼ��
    ofstream fout;	//�ļ�д���� �ڴ�д��洢�豸
    string out = outfilepath.toStdString()+"/outfile1.txt";
    fout.open(out);	//���ļ�
    fout <<"˫����ͳ�ƽ��:" << endl;
    fout <<"����������" << countword << endl;
    fout <<"����������" << countnumber << endl;
    fout <<"����������" << countmark << endl;
    fout << "��Ƶ" << "\t" << "����" << endl;
    while (p != NULL) {
        fout << p->data.frequency << "\t" << p->data.word << endl;
        p = p->next;	//ָ��p����
    }	//while
    fout.close();	//�ر��ļ�

    cout <<"����������" << countword << endl;
    cout <<"����������" << countnumber << endl;
    cout <<"����������" << countmark << endl;
    cout << "��Ƶ" << "\t" << "����" << endl;
    Node* p1 = Head->next;//����ָ��p��ʼ��
    while (p1) {	//p <--> p != NULL
        cout << p1->data.frequency << "\t" << p1->data.word << endl;
        p1 = p1->next;                 //����ָ��p���ƣ�ע�ⲻ��д��p++
    }	//while
    cout << "�����Լ���Ƶ�Ѿ����浽�ļ�outfile1.txt�ļ���" << endl;
}

//��ֵ���ң����ؽ��ָ��
Node* LinkList::Locate(string word) {
    Node* p = Head->next;   //ָ��p��ʼ��
    while (p != NULL) {
        if (p->data.word.compare(word)==0)
            return p;     //���ҳɹ������������������±�
        p = p->next;	//pָ�����
    }	//while
    return NULL;	//�˳�ѭ����������ʧ��
}

void LinkList::Release(){
    while (Head != NULL) {	//�ͷŵ������ÿһ�����Ĵ洢�ռ�
        Node* temp = Head;	//�ݴ汻�ͷŽ��
        Head = Head->next;	// Headָ���ͷŽ�����һ�����
        delete temp;
    }	//while
}
