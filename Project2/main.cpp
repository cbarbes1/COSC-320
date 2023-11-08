#include <iostream>
#include <fstream>

#include "map.h"
#include "tinyfiledialogs.h"
#include <algorithm>
#include <cmath>
#include <string>
#include <exception>

using namespace std;

const string Replacer = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
void RelativeFreqCalc(string &key, int &value);
void freqAnalysis(string, vector<pair<char, int>>&);
void replaceByFreq(vector<pair<char, int>>, vector<char>&);
double fitMeasureCalc(string, map<string, int>&, int n);
string decryptCipherString(string, vector<char>&);
vector<char> transpose(vector<char>, int, int);

bool comperator(pair<char, int> x, pair<char, int> y){
    return x.second > y.second;
}

int main()
{
    const int NUMALPHA = 26;
    const int UPPERBOUND = 100;
    map<string, int> NGramMap;
    map<char, int> FreqMap;
    vector<char> key;
    vector<pair<char, int>> Freqs;

    double fitMeasure = 0;
    double pfitMeasure = 0;
    int ngram = 3;
    string cipherText = "";
    string previousText = "";
    
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
    for(int i = 0; i<NUMALPHA; i++)
        cout<<static_cast<char>('A'+i);
    cout<<endl;
    // key after we replace them by frequency
    for(unsigned int i = 0; i<key.size(); i++)
        cout<<key[i];
    cout<<endl;
    // after printing the key

    // decrypt the text once before the iterative steps begin
    cipherText = decryptCipherString(cipherText, key);

    // obtain the fitness measure of the first decryption
    fitMeasure = fitMeasureCalc(cipherText, NGramMap, ngram);
    // print the measure
    cout<<fitMeasure<<endl;

    // create vars for this segment
    pfitMeasure = fitMeasure -1;
    for(int i = 0; i<UPPERBOUND && fitMeasure != pfitMeasure; i++){
        pfitMeasure = fitMeasure;
        cout<<pfitMeasure<<endl;

        // step 1: make a transposition in the key
        double previousMeasure = fitMeasure;
        for(int j = 0; j<NUMALPHA; j++){
            for(int k = i+1; k<NUMALPHA; k++){
                vector<char> testVector;
                // get the new key
                testVector = transpose(key, j, k);
                // get the previous tex
                previousText = cipherText;
                // decrypt the string given the new key
                cipherText = decryptCipherString(cipherText, testVector);
                // calculate the fitness measure of the possible key
                previousMeasure = fitMeasure;
                fitMeasure = fitMeasureCalc(cipherText, NGramMap, ngram);
                if(fitMeasure > previousMeasure){ // if the fitness increases then keep the key
                    cout<<"success in transpose"<<endl;
                    key = testVector;
                }else{ // if not set the text back to original and continue
                    cipherText = previousText;
                    fitMeasure = previousMeasure;
                }
            }
        }

        if(i == 4){
            // print the key from the frequency substitution
            cout<<"Key after 4 iterations of the kill climb algorithm:"<<endl;
            for(int i = 0; i<NUMALPHA; i++)
                cout<<static_cast<char>('A'+i);
            cout<<endl;
            // key after we replace them by frequency
            for(unsigned int i = 0; i<key.size(); i++)
                cout<<key[i];
            cout<<endl;
            // after printing the key
        }
        fitMeasure = fitMeasureCalc(cipherText, NGramMap, ngram);
        cout<<fitMeasure<<endl;
    }

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


double fitMeasureCalc(string cipherText, map<string, int> &Ngram, int n)
{
    double fitMeasure = 0;
    string ngram = "";
    int frequency = 0;
    double relFrequency = 0;
    int sizeOfMap = Ngram.size();
    for(unsigned int i = 0; i<cipherText.size(); i++){
        ngram = cipherText.substr(i, (i+n));
        try{
            frequency = Ngram.get(ngram);
            relFrequency = static_cast<double>(frequency)/sizeOfMap;
        }catch(const exception &e){
            relFrequency = 1.00/100.00;
        }
        fitMeasure += log10(relFrequency);
    }
            
    return fitMeasure;
}


string decryptCipherString(string cipherText, vector<char> &list)
{
    for(unsigned int i = 0; i<cipherText.size(); i++){
        cipherText[i] = list[ (cipherText[i] - 'A')];
    }
    return cipherText;
}


vector<char> transpose(vector<char> key, int first, int second)
{
    vector<char> vect = key;
    char temp = vect[first];
    vect[first] = vect[second];
    vect[second] = temp;

    return vect;
}

