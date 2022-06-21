#include"hashmap.h"

int HashMap::query(string wordname){
    it = hashMap.find(wordname);
    int f;
    if(it == hashMap.end()){
        return -1;
    }
    f = it->second;
    cout << "f:" << f <<endl;
    return f;
}

void HashMap::showInfo(){
    for(pair<string,int> kv : hashMap){
        cout<<kv.first<<"\t"<<kv.second<<endl;
    }
}

int HashMap::readIn(){
    QFile fin(filename);
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        cout << "Open file failed.";
        return -1;
    }
    char ch;
    string word,number,mark;
    countword=0;//��������
    countnumber=0;//��������
    countmark=0;//��������
    for (int i = 0; fin.getChar(&ch); i++){
        if (ch>='a' && ch<='z' || ch>='A' && ch<='Z'){//ͳ�Ƶ���
            word += ch;
        }
        else{
            if(word!="\0"){
                countword++;
                Insert(word);
            }
            word = "\0";
        }

        if(ch>=48 && ch<=57){//ͳ������
            if(number == "\0")
                number = ch;
            else
                number += ch;
        }else{
            if(number != "\0"){
                countnumber++;
                Insert(number);
            }
            number="\0";
        }

        if((ch>=33 && ch<=47) || (ch>=58 && ch<=64)){//ͳ�Ʒ���
            mark = ch;
            countmark++;
            Insert(mark);
        }

    }
    fin.close();
    return 0;
}

void HashMap::Insert(string data){
    pair<string,int> temp ={data,1};
    if(!data.empty()){
        if(hashMap.size()!=0){
            it=hashMap.find(data);
            if(it!=hashMap.end()){
                it->second++;
            }
            else{
                hashMap.insert(temp);
            }
        }
        else{
                hashMap.insert(temp);
        }
    }
}

void HashMap::Print(){
    string out = outfilepath.toStdString()+"/outfile2.txt";
    ofstream fout;
    fout.open(out);
    fout <<"��ϣ��ͳ�ƽ��:" << endl;
    fout <<"����������" << countword << endl;
    fout <<"����������" << countnumber << endl;
    fout <<"����������" << countmark << endl;
    fout << "��Ƶ" << "\t" << "����" << endl;
    for(pair<string,int> kv : hashMap){
        fout << kv.second << "\t" << kv.first<<endl;
    }
}

void HashMap::Release(){
    hashMap.clear();
}

int HashMap::isEmpty(){
    if(hashMap.empty()){
        return 1;
    }
    return 0;
}
