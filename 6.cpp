// search for words in a file and count the number of times each word occurs using openmp
// read words from a file and count the number of times each word occurs using openmp
#include<bits/stdc++.h>
#include<omp.h>

using namespace std;

int main(){
    vector<string> words = {"the", "a", "there", "answer", "any", "by", "bye", "their"};
    vector<string> input;
    ifstream file("words.txt");
    string str;
    

    //read file into a string
    while(file>>str){
        //cout<<str<<endl;
        input.push_back(str);
    }

    //count the number of times each word occurs
    vector<int> count(words.size(), 0);
    #pragma omp parallel for 
    for(int i=0;i<words.size();i++){
        for(int j=0;j<input.size();j++){
            if(words[i]==input[j]){
                count[i]++;
            }
        }
    }
    
    //print the result
    for(int i=0;i<words.size();i++){
        cout<<words[i]<<" "<<count[i]<<endl;
    }

    return 0;
    
}