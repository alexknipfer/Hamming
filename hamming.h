#ifndef HAMMING_H
#define HAMMING_H

#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Hamming{
  public:
    Hamming();
    void printOriginalWords(string, string, ofstream &);
    void placeParityBits();

  private:
    string word1Final;
    string word2Final;
    int recordCount;
    char word[17];
    vector<char> wordParityBits;
};

#endif
