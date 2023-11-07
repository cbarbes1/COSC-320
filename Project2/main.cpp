#include <iostream>
#include <fstream>

#include "map.h"
#include "tinyfiledialogs.h"
#include <algorithm>
#include <cmath>

using namespace std;

const string Replacer = "ETAOINSHRDLCUMWFGYPBVKJQXZ";

void incrementFrequency(char&, int&);
void freqAnalysis(ifstream&, map<string, int>&, int n);
void replaceByFreq(vector<pair<char, int>>, vector<char>&);

double fitMeasureCalc(vector<pair<string, int>>);

bool comparator(pair<char, int> left, pair<char, int> right){
    return left.second > right.second;
}

int main()
{
    map<string, int> NGramMap;
    map<char, int> FreqMap;
    vector<char> key;
    vector<pair<char, int>> Freqs;
    double fitMeasure = 0;

    // get a file to use in n gram key calculation
    char const *lFilterPatterns[2] = { "*.txt", "*"};
    char const *filename1 = tinyfd_openFileDialog("Open N-Gram File", NULL, 1, lFilterPatterns, "N-Gram File", 0);
    cout<<"Opening "<<filename1<<endl;
    ifstream InFile1(filename1);// open the file for input

    if(InFile1){
        // load the information into the map then proceed
        while(InFile1){
            string word = "";
            int freq = 0;
            InFile1>>word>>freq;
            InFile1.ignore(256, '\n');

            NGramMap.set(word, freq);
        }

    }else{
        cerr<<"N-Gram file is needed to proceed, exiting\n";
    }

    // get a file for the Cyphertext
    char const *filename2 = tinyfd_openFileDialog("Open Ciphertext File", NULL, 1, lFilterPatterns, "CipherText File", 0);
    cout<<"Opening "<<filename2<<endl;
    ifstream InFile2(filename2);// open the file for input
    if(InFile2){
        // load the information into the map then proceed
        freqAnalysis(InFile2, FreqMap);
    }else{
        cerr<<"N-Gram file is needed to proceed, exiting"<<endl;
    }

    cout<<FreqMap<<endl;
    for(unsigned int i = 0; i<26; i++){
        key.push_back(('A'+i));
    }
    FreqMap.toVector(Freqs);

    replaceByFreq(Freqs, key);

    /*
    for(unsigned int i = 0; i<key.size(); i++)
        cout<<static_cast<char>('A'+i)<<" "<<key[i]<<endl;
    */

    fitMeasure = fitMeasureCalc(Freqs);
    cout<<fitMeasure<<endl;

    InFile1.close();
    InFile2.close();
    return 0;

}

void incrementFrequency(string &key, int &freq)
{
    freq++;
}

void freqAnalysis(ifstream &infile, map<string, int> &output, int n)
{
    if(infile){
        char temp;
        string word = "";
        int i = 0;
        while(infile>>temp){
            i++;
            word += temp;
            if(i!=n){
                continue;
            }else{
                if(!output.InOrderAct(temp, incrementFrequency)){
                    output.set(word, 1);
                }
                i=0;
            }
        }
        infile.seekg(0, std::ios::beg);
    }else{
        cerr<<"Input File Error"<<endl;
    }
}

void replaceByFreq(vector<pair<string, int>> Freq, vector<string> &key)
{
    sort(Freq.begin(), Freq.end(), comparator);

    int spos = 0;
    for(unsigned int i = 0; i<Freq.size(); i++){
        int pos = (Freq[i].first[0] - 'A');
        key[pos] = Replacer[spos++];
    }
}

double fitMeasureCalc(vector<pair<string, int>> freqVect)
{
    double fitMeasure = 0;
    for(unsigned int i = 0; i<freqVect.size(); i++){
        fitMeasure += log10((static_cast<double>(freqVect[i].second)/static_cast<int>(freqVect.size())));
    }
    return fitMeasure;
}
