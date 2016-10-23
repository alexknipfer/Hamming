#include <iostream>
#include <fstream>
#include <string>
#include "hamming.h"

using namespace std;

int main(){
  Hamming hamming;
  ifstream inputFile("data.txt");
  ofstream outputFile("out.txt");
  string word1;
  string word2;

    //read in 1st and 2nd word
  inputFile >> word1;
  inputFile >> word2;

    //make sure valid (ie not end of file)
  while(word1 != "-1"){
      //go print the original words
    hamming.printOriginalWords(word1, word2, outputFile);
    inputFile >> word1;
    inputFile >> word2;
  }


  return 0;
}

//******************************************************************************

Hamming::Hamming(){
    //Recieves - nothing
    //Task - constructor - initialize private members
    //Returns - nothing

  recordCount = 0;
}

//******************************************************************************

void Hamming::printOriginalWords(string word1, string word2, ofstream &outputFile){
    //Receives - 1st word, 2nd word, output file
    //Task - Print original words and record #
    //Returns - nothing

  recordCount++;

    //print original words with record number
  outputFile << "Record # " << recordCount << "        Original input words are:" << endl;
  outputFile << "                  -------------------------" << endl;
  outputFile << "                     " << word1 << endl;
  outputFile << "                     " << word2 << endl;
  outputFile << endl;
}
