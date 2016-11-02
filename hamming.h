#ifndef HAMMING_H
#define HAMMING_H

#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Hamming{
  public:
    Hamming();
    void loadWords(string, string);
    void printOriginalWords(string, string, ofstream &);
    void placeCheckBitLocations();
    void getCheckBits();
    void getKBitCode();
    void getInputWord();

  private:
    string word1Final;
    string word2Final;
    string inputWordFinal;
    int recordCount;
    char word[17];
    vector<char> wordParityBits;
    vector<char> inputWord;
    vector<int> parity1;
    vector<int> parity2;
    vector<int> parity4;
    vector<int> parity8;
    vector<int> parity16;
    vector<int> kbitWord;
};

#endif
