#include <iostream>
#include <fstream>

#include "map.h"
#include "tinyfiledialogs.h"
#include <algorithm>
#include <cmath>
#include <string>

using namespace std;

const string Replacer = "ETAOINSHRDLCUMWFGYPBVKJQXZ";

void freqAnalysis(string, vector<pair<char, int>>&);
void replaceByFreq(vector<pair<char, int>>, vector<char>&);
//double fitMeasureCalc(string, map<string, double>&, int n);
void decryptCipherString(string, vector<char>);

bool comperator(pair<char, int> x, pair<char, int> y){
    return x.second > y.second;
}

int main()
{
    map<string, int> NGramMap;
    map<char, int> FreqMap;
    vector<char> key;
    vector<pair<char, int>> Freqs;
    double fitMeasure = 0;
    int ngram = 3;
    string cipherText = "";
    
    // create the key vector as just normally A-Z
    for(int i = 0; i<26; i++)
        key.push_back(('A'+i));

    // create the frequency vector
    for(int i = 0; i<26; i++){
        Freqs.push_back(make_pair(('A'+i), 0));
    }
    // get a file to use in n gram key calculation
    char const *lFilterPatterns[2] = { "*.txt", "*"};
    char const *filename1 = tinyfd_openFileDialog("Open N-Gram File", NULL, 1, lFilterPatterns, "N-Gram File", 0);
    cout<<"Opening "<<filename1<<endl;
    ifstream InFile1(filename1);// open the file for input

    if(InFile1){
        string word = "";
        int freq = 0;
        // load the information into the map then proceed
        while(InFile1){

            InFile1>>word>>freq;
            InFile1.ignore(256, '\n');

            NGramMap.set(word, freq);
        }
        ngram = word.size();
    }else{
        cerr<<"N-Gram file is needed to proceed, exiting\n";
    }
    cout<<"N-Gram File Loaded"<<endl;
    // get a file for the Cyphertext
    char const *filename2 = tinyfd_openFileDialog("Open Ciphertext File", NULL, 1, lFilterPatterns, "CipherText File", 0);
    cout<<"Opening "<<filename2<<endl;
    ifstream InFile2(filename2);// open the file for input
    if(InFile2){
        // load the information into the map then proceed
        char buf;
        while(InFile2>>buf){
            if(buf != '\n')
                cipherText += buf;
        }

        freqAnalysis(cipherText, Freqs);
    }else{
        cerr<<"cipher text file is needed to proceed, exiting"<<endl;
    }
    cout<<"Cipher Text File Loaded"<<endl;




    for(unsigned int i = 0; i<Freqs.size(); i++)
        cout<<Freqs[i].first<<" "<<Freqs[i].second<<endl;
    
    replaceByFreq(Freqs, key);

    for(unsigned int i = 0; i<key.size(); i++)
        cout<<key[i]<<" ";
    cout<<endl;

    //fitMeasure = fitMeasureCalc(cipherText, NGramMap, ngram);
    //cout<<fitMeasure<<endl;

    InFile1.close();
    InFile2.close();
    return 0;

}

void freqAnalysis(string cipher, vector<pair<char, int>> &output)
{
    for(unsigned int i = 0; i<cipher.size(); i++){
        output[(cipher[i] - 'A')].second++;
    }
}

void replaceByFreq(vector<pair<char, int>> Freq, vector<char> &key)
{
    sort(Freq.begin(), Freq.end(), comperator);
    int spos = 0;
    for(unsigned int i = 0; i<Freq.size(); i++){
        int pos = (Freq[i].first - 'A');
        key[pos] = Replacer[spos++];
    }
}

/*
double fitMeasureCalc(string cipherText, map<string, double> &ngram, int n)
{
    double fitMeasure = 0;
    string ngram = "";
    char temp;
    for(int i = 0; i<cipherText.size(); i++){
        fitMeasure += log10(ngram.get(cipherText.substr(i, (i+n))/ngram.size());
    }
            
    return fitMeasure;
}


string decryptCipherString(string cipherText, vector<char> list)
{
    for(int i = 0; i<cipherText.size(); i++){
        cipherText[i] = list[ (cipherText[i] - 'A')];
    }
    return cipherText;
}

*/
