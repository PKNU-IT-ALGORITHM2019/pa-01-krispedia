#include<iostream>
#include<fstream>
#include<string>

using namespace std;

string dict[1000000];
string word[1000000];
int numIndex[1000000]={0};
int dictCount=0;
int wordCount=0;

string extractWord(string line){
    int index = line.find("(");
    
    return line.substr(0, index-1);
}
string lowerWord(string word){
    for(int i=0; i<word.size(); i++)
    word[i] = tolower(word[i]);
    
    return word;
}

int binarySerch(int start, int end, string keyword){
    int mid = (start+end)/2;
    if(start > end)
    return (-1)*mid;
    
    if(word[mid].compare(keyword) == 0)
    return mid;
    else if(word[mid].compare(keyword) > 0)
    return binarySerch(start, mid-1, keyword);
    else
    return binarySerch(mid+1, end, keyword);
}
void printNearWord(int index){
    string out1, out2;
    int divIndex;
    index = (-1)*index;
    
    int start = 0;
    for(int i=0; i<=index; i++)
    start += numIndex[i];
    start -= 1;
    
    out1 = dict[start];
    divIndex = out1.find(")");
    out1 = out1.substr(0, divIndex);
    out2 = dict[start+1];
    divIndex = out2.find(")");
    out2 = out2.substr(0, divIndex+1);
    
    cout<<out1<<endl;
    cout<<"---------"<<endl;
    cout<<out2<<endl;
}
void printWord(int index) {
    int start = 0;
    for(int i=0; i<index; i++)
    start += numIndex[i];
    
    for(int i=0; i<numIndex[index]; i++){
        //cout<<"start+i"<<start+i<<endl;
        cout<<dict[start+i]<<endl;
    }
}
void read(string fileName){
    string line, nword;
    
    fstream fin(fileName);
    
    if(!fin){
        cout<<"Can't Open File."<<endl;
        return;
    }
    
    while(!fin.eof()){
        getline(fin, line);
        if(line == "")
        continue;
        dict[dictCount++] = line;
        
        nword = extractWord(line);
        nword = lowerWord(nword);
        cout<<"nword: "<<nword<<endl;
        int i;
        for(i=0; i<wordCount; i++){
            if(nword.compare(word[i]) == 0){
                numIndex[i]++;
                break;
            }
        }
        if(i == wordCount){
            word[wordCount++] = nword;
            cout<<"new: "<<nword<<endl;
            numIndex[i]++;
        }
    }
    fin.close();
    cout<<"READING DONE!"<<endl;
    
    cout<<"DICT-------------------"<<endl;
    for(int i=0; i<dictCount; i++)
    cout<<dict[i]<<endl;
    cout<<"WORD-------------------"<<endl;
    for(int i=0; i<wordCount; i++)
    cout<<word[i]<<endl;
    cout<<"numIndex---------------"<<endl;
    for(int i=0; i<wordCount; i++)
    cout<<numIndex[i]<<endl;
    
}
void find(string argument) {
    argument = lowerWord(argument);
    int index = binarySerch(0, wordCount, argument);
    if(index<0){
        cout<<"Not Found."<<endl;
        printNearWord(index);
    }
    else{
        cout<<"Found "<<numIndex[index]<<" items"<<endl;
        printWord(index);
        //cout<<"index: "<<index<<endl;
    }
}
void commandLine(){
    string command, argument;
    string line;
    int index;
    
    ios_base::sync_with_stdio(false);
    while(1) {
        cin.clear();
        cin>>command;
        
        if(command == "read"){
            cin>>argument;
            read(argument);
        }
        else if(command == "size")
        cout<<dictCount<<endl;
        else if(command == "find"){
            cin>>argument;
            find(argument);
        }
        else if(command == "exit")
        return;
        else{
            cout<<"invalid command!"<<endl;
            continue;
        }
    }
}

int main(void){
    
    commandLine();
    return 0;
}
