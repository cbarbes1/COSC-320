/* Author: Cole Barbes
 * Creation data: 11/3/23
 * Last Edited: 11/13/23
 * Purpose: To implement a hill climbing decryption program
 */
#include <iostream>
#include <fstream>

#include "Map.h"
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
double fitMeasureCalc(string, Map<string, double>&, int, double); // calculate the fitness of the text
void decryptCipherString(string&, vector<char>); // decrypt the text
void transpose(vector<char>&, int, int); // transpose 2 chars
bool HillClimb(Map<string, double>, vector<char>&, string, double&, int, double); // hill climbing analysis step

// make function to use as a comparator in the sort function
bool comperator(pair<char, int> x, pair<char, int> y){
    return x.second > y.second;
}

// create an apply function to find the relative frequency 
void apply1(string &key, double &value, double applyAgent)
{
    value = value/applyAgent;
}

// create an apply function for taking the log 
void apply2(string &key, double &value, double applyAgent)
{
    value = log10(value);
}

int main()
{
    // create storage container
    Map<string, double> NGramMap;
    vector<char> key;
    vector<pair<char, int>> Freqs;
    double fitMeasure = 0;
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
            InFile1>>word>>freq; // grab the line
            InFile1.ignore(256, '\n');
            numEngChars+=freq; // sum the frequency into the total
            NGramMap.set(word, freq); // set the key into the map
        }
        ngram = word.size(); // get the size
        
        NGramMap.InOrderAct(apply1, numEngChars); // divide each value by the number of chars
        NGramMap.InOrderAct(apply2, 0); // take the log of all the values
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
        while(InFile2>>buf){ // while the buffer gets value 
            if(buf != '\n') // if not an end line add to the string
                cipherText += buf;
        }

        freqAnalysis(cipherText, Freqs); // frequency analyze each char in the file
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
    
    int i = 0;
    bool checker = true;
    for(i = 0; i<UPPERBOUND && checker; i++){
        checker = false;
        checker = HillClimb(NGramMap, key, cipherText, fitMeasure, ngram, numEngChars);
    }
    
    // print the key from the frequency substitution
    cout<<"Key after "<<i<<" iterations of the Hill Climb algorithm:"<<endl;
    for(int n = 0; n<NUMALPHA; n++)
        cout<<static_cast<char>('A'+n);
    cout<<endl;
    // key after we replace them by frequency
    for(unsigned int n = 0; n<key.size(); n++)
        cout<<key[n];
    cout<<endl;
    // after printing the key
    
    decryptCipherString(cipherText, key); //decrypt the text
    cout<<cipherText<<endl; // print the text

    // close the file
    InFile1.close();
    InFile2.close();
    return 0;

}

/* Description: frequency analyze each char in the ciphertext
 * parameters: String for the cipher, vector with the frequencies of each char
 */
void freqAnalysis(string cipher, vector<pair<char, int>> &output)
{
    for(unsigned int i = 0; i<cipher.size(); i++){
        output[(cipher[i] - 'A')].second++;
    }
}

/* Description: Replace each key entry with its english language counter part
 * parameters: the frequency vector and the key
 */
void replaceByFreq(vector<pair<char, int>> Freq, vector<char> &key)
{
    // sort the vector in descending order
    sort(Freq.begin(), Freq.end(), comperator);
    int spos = 0;
    for(unsigned int i = 0; i<Freq.size(); i++){ 
        int pos = (Freq[i].first - 'A'); // get the position
        key[pos] = Replacer[spos++]; // get the char from the replacer
    }
}

/* Description:
 * parameters: the string, the map , the number, the number of chars in the trigram
 * return: the fitness measure
 */
double fitMeasureCalc(string cipherText, Map<string, double> &Ngram, int n, double numChars)
{
    double fitMeasure = 0;
    string ngram = "";
    double relFrequency = 0;
    for(unsigned int i = 0; i<cipherText.size()-n; i++){
        ngram = cipherText.substr(i, n);// get the piece of text to find
        if(Ngram.find(ngram)){// if the ngram is found then get the relative frequency 
            relFrequency = Ngram.get(ngram);
        }else{ // if not then place the constant in
            relFrequency = log10((1.00/100.0)/numChars);
        }
        fitMeasure += relFrequency; // add into the fitmeasure
    }
    return fitMeasure;
}

/* Description: decrypt the string
 * parameters: the string and the key vector
 */
void decryptCipherString(string &cipher, vector<char> key)
{
    bool found = false; // grab the test var
    for(unsigned int i = 0; i<cipher.length(); i++){
        found = false; //set to false
        for(int j = 0; j < NUMALPHA && !found; j++){
            if(cipher[i] == key[j]){ // check if the char is the char in the key
                found = true;
                cipher[i] = 'A' + j; // set the letter into it
            }
        }
    }
}

/* Description: transpose 2 vector entries
 */
void transpose(vector<char> &key, int first, int second)
{
    char temp = key[first];
    key[first] = key[second];
    key[second] = temp;
}

/* Description: transpose characters and test if that choise was valuable
 * parameters: the map, the key, the string, the fitmeasure, the number of grams, the number of chars
 * return true if something was changed and false if nothing changed
 */
bool HillClimb(Map<string, double> NGramMap, vector<char> &key, string cipherText, double &fitMeasure, int ngram, double numChars)
{
    string newText = "";
    bool checker = false;
    double newfitMeasure = 0;
    // step 1: make a transposition in the key
    for(int j = 0; j<NUMALPHA; j++){
        for(int k = j+1; k<NUMALPHA; k++){
            vector<char> testKey = key;
            // get the new key
            transpose(testKey, j, k);
             // get the previous text
            newText = cipherText;

            // decrypt the string given the new key
            decryptCipherString(newText, testKey);
            newfitMeasure = fitMeasureCalc(newText, NGramMap, ngram, numChars);
            if(newfitMeasure > fitMeasure){ // if the fitness increases then keep the key
                key = testKey;
                fitMeasure = newfitMeasure;
                checker = true;
            }
        }

    }
    
    return checker;

}
