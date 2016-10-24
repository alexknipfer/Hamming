#include <iostream>
#include <fstream>
#include <string>
#include "hamming.h"

using namespace std;

#define WORDSIZE 16
#define MAX_SIZE_WORD 21

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
    hamming.placeParityBits();
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

  word1Final = word1;
  word2Final = word2;

    //store word in array
  for(int x = 0; x < WORDSIZE; x++){
    word[x] = word1[x];
  }
}

//******************************************************************************

void Hamming::placeParityBits(){
    //Receives - nothing
    //Task - places word in array with parity bits in location
    //Returns - nothing

  int count = 0;

    //build parity bit array
  for(int x = 0; x <= MAX_SIZE_WORD; x++){
      //if value is a parity bit, don't insert bit, use dash
    if(x == 5 || x == 13 || x == 17 || x== 19 || x == 21){
      wordParityBits.push_back('-');
    }

      //not a parity bit, place bit in array
    else{
      wordParityBits.push_back(word[count]);
      count++;
    }
  }

  for(int x = 0; x < wordParityBits.size(); x++){
    cout << wordParityBits[x];
  }
  cout << endl;
}

//******************************************************************************
