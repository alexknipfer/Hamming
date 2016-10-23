#ifndef HAMMING_H
#define HAMMING_H

#include <fstream>
#include <string>

using namespace std;

class Hamming{
  public:
    Hamming();
    void printOriginalWords(string, string, ofstream &);

  private:
    int recordCount;
};

#endif
