/* Author: Cole Barbes
 * Creation data: 11/3/23
 * Last Edited: 11/13/23
 * Purpose: To implement a hill climbing decryption program
 */
#include <iostream>
#include <fstream>

#include "map.h"
#include "tinyfiledialogs.h"
#include <algorithm>
#include <cmath>
#include <stack>
#include <string>
#include <exception>

using namespace std;

const string Replacer = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
const int NUMALPHA = 26;
const int UPPERBOUND = 100;


void freqAnalysis(string, vector<pair<char, int>>&); // frequency analyze individual characters in a file
void replaceByFreq(vector<pair<char, int>>, vector<char>&); // go through a key and replace each char with its paired frequency char
double fitMeasureCalc(string, map<string, double>&, int, double); // calculate the fitness of the text
void decryptCipherString(string&, vector<char>); // decrypt the text
void transpose(vector<char>&, int, int); // transpose 2 chars
void HillClimb(map<string, double>, vector<char>&, string, double&, int, double); // hill climbing analysis step

bool comperator(pair<char, int> x, pair<char, int> y){
    return x.second > y.second;
}


void apply1(string &key, double &value, double applyAgent)
{
    value = value/applyAgent;
}

void apply2(string &key, double &value, double applyAgent)
{
    value = log10(value);
}

int main()
{
    
    map<string, double> NGramMap;

    vector<char> key;
    vector<pair<char, int>> Freqs;

    double fitMeasure = 0;
    double pfitMeasure = 0;
    double numEngChars = 0;
    int ngram = 3;
    string cipherText = "";
    string previousText = "";
    string newText = "";
    
    // create the key vector as just normally A-Z
    for(int i = 0; i<NUMALPHA; i++)
        key.push_back(('A'+i));

    // create the frequency vector
    for(int i = 0; i<NUMALPHA; i++){
        Freqs.push_back(make_pair(('A'+i), 0));
    }

    // get a file to use in n gram key calculation
    char const *lFilterPatterns[2] = { "*.txt", "*"};
    char const *filename1 = tinyfd_openFileDialog("Open N-Gram File", NULL, 1, lFilterPatterns, "N-Gram File", 0);
    cout<<"Opening "<<filename1<<endl;
    ifstream InFile1(filename1);// open the file for input
    if(InFile1){
        string word = "";
        double freq = 0;
        // load the information into the map then proceed
        while(InFile1){

            InFile1>>word>>freq;
            InFile1.ignore(256, '\n');
            numEngChars+=freq;
            NGramMap.set(word, freq);
        }
        ngram = word.size();
        
        NGramMap.InOrderAct(apply1, numEngChars);
        NGramMap.InOrderAct(apply2, 0);
    }else{
        cerr<<"N-Gram file is needed to proceed, exiting\n";
    }
    cout<<"N-Gram File Loaded"<<endl;
    //

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
    //


    // Hill Climbing algorithm Begins

    // Step 1: use the obtained frequencies and make replacements in the key
    cout<<"Single Character Frequencies"<<endl;
    for(unsigned int i = 0; i<Freqs.size(); i++)
        cout<<Freqs[i].first<<" "<<Freqs[i].second<<endl;
    
    // make the replacements
    replaceByFreq(Freqs, key);

    // print the key from the frequency substitution
    cout<<"Key from single character frequency analysis:"<<endl;
    for(int i = 0; i<NUMALPHA; i++){
        cout<<static_cast<char>('A'+i);
    }
    cout<<endl;
    for(int i = 0; i<NUMALPHA; i++){
        cout<<key[i];
    }
    cout<<endl;
    // after printing the key
    string strtmp = cipherText;
    newText = cipherText;
    // decrypt the text once before the iterative steps begin
    decryptCipherString(newText, key);

    // obtain the fitness measure of the first decryption
    fitMeasure = fitMeasureCalc(newText, NGramMap, ngram, numEngChars);
    // print the measure
    cout<<fitMeasure<<endl;
    
    pfitMeasure = fitMeasure -1;
    int i = 0;
    for(i = 0; i<UPPERBOUND && fitMeasure > pfitMeasure; i++){

        pfitMeasure = fitMeasure;
        HillClimb(NGramMap, key, cipherText, fitMeasure, ngram, numEngChars);
        // print the key from the frequency substitution
        cout<<"Key after "<<(i+1)<<" iterations of the kill climb algorithm:"<<endl;
        for(int n = 0; n<NUMALPHA; n++)
            cout<<static_cast<char>('A'+n);
        cout<<endl;
        // key after we replace them by frequency
        for(unsigned int n = 0; n<key.size(); n++)
            cout<<key[n];
        cout<<endl;
    }
    
    // print the key from the frequency substitution
    cout<<"Key after "<<(i+1)<<" iterations of the kill climb algorithm:"<<endl;
    for(int n = 0; n<NUMALPHA; n++)
        cout<<static_cast<char>('A'+n);
    cout<<endl;
    // key after we replace them by frequency
    for(unsigned int n = 0; n<key.size(); n++)
        cout<<key[n];
    cout<<endl;
    // after printing the key
    decryptCipherString(cipherText, key);
    cout<<cipherText<<endl;

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


double fitMeasureCalc(string cipherText, map<string, double> &Ngram, int n, double numChars)
{
    double fitMeasure = 0;
    string ngram = "";
    double relFrequency = 0;
    for(unsigned int i = 0; i<cipherText.size(); i++){
        ngram = cipherText.substr(i, (i+n-1));
        try{
            relFrequency = Ngram.get(ngram);
        }catch(const exception &e){
            relFrequency = log10((1.00/100.0)/numChars);
        }
        fitMeasure += relFrequency;
    }
    return fitMeasure;
}


void decryptCipherString(string &cipher, vector<char> key)
{
    for(unsigned int i = 0; i<cipher.length(); i++){
        int index = static_cast<int>(distance(key.begin(), find(key.begin(), key.end(), cipher[i])));
        cipher[i] ='A'+index;
    }
}


void transpose(vector<char> &key, int first, int second)
{
    char temp = key[first];
    key[first] = key[second];
    key[second] = temp;
}

void HillClimb(map<string, double> NGramMap, vector<char> &key, string cipherText, double &fitMeasure, int ngram, double numChars)
{
    string newText = "";

    double newfitMeasure = 0;
    //double tmpFit = fitMeasure;
    vector<char> testKey = key;
    //stack<pair<int, int>> saveIndex;
    // step 1: make a transposition in the key
    for(int j = 0; j<NUMALPHA; j++){
        for(int k = j+1; k<NUMALPHA; k++){
            // get the new key
            transpose(key, j, k);
             // get the previous text
            newText = cipherText;

            // decrypt the string given the new key
            decryptCipherString(newText, testKey);
            newfitMeasure = fitMeasureCalc(newText, NGramMap, ngram, numChars);
            if(newfitMeasure > fitMeasure){ // if the fitness increases then keep the key
                key = testKey;
                fitMeasure = newfitMeasure;
            }
        }

    }

}
