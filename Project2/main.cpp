#include <iostream>
#include <fstream>

#include "map.h"
#include "tinyfiledialogs.h"
#include <algorithm>
#include <cmath>
#include <string>

using namespace std;

const string Replacer = "ETAOINSHRDLCUMWFGYPBVKJQXZ";

void incrementFrequency(char&, int&);
void freqAnalysis(string, vector<pair<char, int>>&);
void replaceByFreq(vector<pair<char, int>>, vector<char>&);
double fitMeasureCalc(string, map<string, double>&, int n);
void decryptCipherString(string, vector<char>);

int main()
{
    map<string, double> NGramMap;
    map<char, int> FreqMap;
    vector<char> key;
    vector<pair<char, int>> Freqs;
    double fitMeasure = 0;
    int ngram = 3;
    string cipherText = "";
    
    for(int i = 0; i<26; i++){
        Freqs[i].first = ('A' + i);
        Freqs[i].second = 0;
    }

    // get a file to use in n gram key calculation
    char const *lFilterPatterns[2] = { "*.txt", "*"};
    char const *filename1 = tinyfd_openFileDialog("Open N-Gram File", NULL, 1, lFilterPatterns, "N-Gram File", 0);
    cout<<"Opening "<<filename1<<endl;
    ifstream InFile1(filename1);// open the file for input

    if(InFile1){
        string word = "";
        // load the information into the map then proceed
        while(InFile1){
            double freq = 0;
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

    for(int i = 0; i<26; i++)
        key[i] = ('A'+i);
    
    //replaceByFreq(Freqs, key);

    //fitMeasure = fitMeasureCalc(cipherText, NGramMap, ngram);
    //cout<<fitMeasure<<endl;

    InFile1.close();
    InFile2.close();
    return 0;

}

void incrementFrequency(string &key, int &freq)
{
    freq++;
}

void freqAnalysis(string cipher, vector<pair<char, int>> &output)
{
    if(infile){
        char temp;
        while(infile>>temp){
            output[(temp - 'A')].second++;
        }
        infile.seekg(0, std::ios::beg);
    }else{
        cerr<<"Input File Error"<<endl;
    }
}

void replaceByFreq(vector<pair<char, int>> Freq, vector<char> &key)
{
    int spos = 0;
    for(unsigned int i = 0; i<Freq.size(); i++){
        int pos = (Freq[i].first - 'A');
        key[pos] = Replacer[spos++];
    }
}

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
