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
    countword=0;//单词总数
    countnumber=0;//数字总数
    countmark=0;//符号总数
    for (int i = 0; fin.getChar(&ch); i++){
        if (ch>='a' && ch<='z' || ch>='A' && ch<='Z'){//统计单词
            word += ch;
        }
        else{
            if(word!="\0"){
                countword++;
                Insert(word);
            }
            word = "\0";
        }

        if(ch>=48 && ch<=57){//统计数字
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

        if((ch>=33 && ch<=47) || (ch>=58 && ch<=64)){//统计符号
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
    fout <<"哈希表法统计结果:" << endl;
    fout <<"单词总数：" << countword << endl;
    fout <<"数字总数：" << countnumber << endl;
    fout <<"符号总数：" << countmark << endl;
    fout << "词频" << "\t" << "单词" << endl;
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
