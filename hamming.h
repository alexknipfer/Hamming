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
    void syndromeWordComparison();

  private:
    string word1Final;
    string word2Final;
    string inputWordFinal;
    string syndromeWordFinal;
    int recordCount;
    char word1Array[17];
    char word2Array[17];
    vector<char> wordParityBits;
    vector<char> wordParityBits2;
    vector<char> inputWord;
    vector<int> parity1;
    vector<int> parity2;
    vector<int> parity4;
    vector<int> parity8;
    vector<int> parity16;
    vector<int> _parity1;
    vector<int> _parity2;
    vector<int> _parity4;
    vector<int> _parity8;
    vector<int> _parity16;
    vector<int> kbitWord;
    vector<int> kbitWord2;
    vector<int> syndromeComparison;
};

#endif
