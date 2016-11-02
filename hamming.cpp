#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "hamming.h"

using namespace std;

#define WORDSIZE 16
#define MAX_SIZE_WORD 20

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
    hamming.loadWords(word1, word2);
    hamming.placeCheckBitLocations();
    hamming.getCheckBits();
    hamming.getKBitCode();
    hamming.getInputWord();
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

void Hamming::loadWords(string word1, string word2){
    //Receives - two input words (from memory and to memory)
    //Task - place words in character arrays
    //Returns - nothing

    //store word in array
  for(int x = 0; x < WORDSIZE; x++){
    word[x] = word1[x];
  }
}

//******************************************************************************

void Hamming::placeCheckBitLocations(){
    //Receives - nothing
    //Task - places word in array with parity bits in location
    //Returns - nothing

  int count = 0;

    //build parity bit array
  for(int x = 0; x <= MAX_SIZE_WORD; x++){
      //if value is a parity bit, don't insert bit, use dash
    if(x == 5 || x == 13 || x == 17 || x== 19 || x == 20){
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

void Hamming::getCheckBits(){
    //Receives - nothing
    //Task - calculate check bits
    //Returns - nothing

  int currentNumber;

    //calculate check bits for decimal location 1
  for(int x = 0; x < wordParityBits.size(); x++){
    if(x == 18 || x == 16 || x == 14 || x == 12 || x == 10 ||
       x == 8 || x == 6 || x == 4 || x == 2 || x == 0){
         currentNumber = (int)wordParityBits[x] - 48; //store as integer
         parity1.push_back(currentNumber);
       }
  }

    //calulate check bits for decimal location 2
  for(int x = 0; x < wordParityBits.size(); x++){
    if(x == 2 || x == 3 || x == 6 || x == 7 || x == 10 || x == 11 ||
       x == 14 || x == 15 || x == 18){
         currentNumber = (int)wordParityBits[x] - 48; //store as integer
         parity2.push_back(currentNumber);
       }
  }

    //calculate check bits for decimal location 4
  for(int x = 0; x < wordParityBits.size(); x++){
    if(x == 0 || x == 1 || x == 6 || x == 7 || x == 8 || x == 9 ||
       x == 14 || x == 15 || x == 16){
         currentNumber = (int)wordParityBits[x] - 48; //store as integer
         parity4.push_back(currentNumber);
       }
  }

    //calculate check bits for decimal location 8
  for(int x = 0; x < wordParityBits.size(); x++){
    if(x == 6 || x == 7 || x == 8 || x == 9 || x == 10 ||
       x == 11 || x == 12){
         currentNumber = (int)wordParityBits[x] - 48; //store as integer
         parity8.push_back(currentNumber);
       }
  }

    //calculate check bits for decimal location 16
  for(int x = 0; x < wordParityBits.size(); x++){
    if(x == 0 || x == 1 || x == 2 || x == 3 || x == 4){
      currentNumber = (int)wordParityBits[x] - 48; //store as integer
      parity16.push_back(currentNumber);
    }
  }

    //reverse the vectors for printing
  //reverse(parity1.begin(), parity1.end());
  //reverse(parity2.begin(), parity2.end());
  //reverse(parity4.begin(), parity4.end());
  //reverse(parity8.begin(), parity8.end());
  //reverse(parity16.begin(), parity16.end());

  /*for(int y = 0; y < parity1.size(); y++){
    cout << parity1[y] << " ";
  }
  cout << endl;
  for(int y = 0; y < parity2.size(); y++){
    cout << parity2[y] << " ";
  }
  cout << endl;
  for(int y = 0; y < parity4.size(); y++){
    cout << parity4[y] << " ";
  }
  cout << endl;
  for(int y = 0; y < parity8.size(); y++){
    cout << parity8[y] << " ";
  }
  cout << endl;
  for(int y = 0; y < parity16.size(); y++){
    cout << parity16[y] << " ";
  }
  cout << endl;*/
}


//******************************************************************************

void Hamming::getKBitCode(){
    //Receives - nothing
    //Task - creates KBit word (syndrome word)
    //Returns - nothing

    //initialize count for creating check bits
  int count = 0;

    //check parity bit for decimal location 16
  for(int x = 0; x < parity16.size(); x++){
    if(parity16[x] == 1){
      count++;
    }
  }

    //if the value is even the resulting bit is a 0
  if(count % 2 == 0){
    kbitWord.push_back(0);
  }
    //resulting value is a 1
  else{
    kbitWord.push_back(1);
  }

  count = 0;  //reset count

    //check parity bit for decimal location 8
  for(int x = 0; x < parity8.size(); x++){
    if(parity8[x] == 1){
      count++;
    }
  }

    //resulting bit is a 0 if even
  if(count % 2 == 0){
    kbitWord.push_back(0);
  }
    //resulting bit is a 1 if odd
  else{
    kbitWord.push_back(1);
  }

  count = 0;  //reset count

    //check parity bit for decimal location 4
  for(int x = 0; x < parity4.size(); x++){
    if(parity4[x] == 1){
      count++;
    }
  }

    //resulting bit is a 0 if odd
  if(count % 2 == 0){
    kbitWord.push_back(0);
  }
    //resulting bit is a 1 if odd
  else{
    kbitWord.push_back(1);
  }

  count = 0;  //reset count

    //check parity bit for decimal location 2
  for(int x = 0; x < parity2.size(); x++){
    if(parity2[x] == 1){
      count++;
    }
  }

    //resulting bit is a 0 if even
  if(count % 2 == 0){
    kbitWord.push_back(0);
  }
    //resulting bit is a 1 if odd
  else{
    kbitWord.push_back(1);
  }

  count = 0;  //reset count

    //check parity bit for decimal location 1
  for(int x = 0; x < parity1.size(); x++){
    if(parity1[x] == 1){
      count++;
    }
  }

    //resulting bit is a 0 if even
  if(count % 2 == 0){
    kbitWord.push_back(0);
  }
    //resulting bit is a 1 if odd
  else{
    kbitWord.push_back(1);
  }

  count = 0;

  /*for(int x = 0; x < kbitWord.size(); x++){
    cout << kbitWord[x] << " ";
  }
  cout << endl;*/
}

//******************************************************************************

void Hamming::getInputWord(){
    //Receives - nothing
    //Task - creates input word to be stored
    //Returns - nothing

    //intialize count for adding parity bits to word
  int count = 0;

    //copy the original word for manipulation
  inputWord.swap(wordParityBits);

    //replace dashes with parity bits for word to be stored into memory
  for(int x = 0; x < inputWord.size(); x++){
      //if - is reached replace with correct bit value
    if(inputWord[x] == '-'){
      if(kbitWord[count] == 1){
        inputWord[x] = '1';
      }
      else{
        inputWord[x] = '0';
      }
        //increment for next value in k bit word
      count++;
    }
  }

    //concatenate a string for easy printing
  for(int x = 0; x < inputWord.size(); x++){
    inputWordFinal += inputWord[x];
  }

  for(int x = 0; x< inputWord.size(); x++){
    cout << inputWord[x];
  }
  cout << endl;
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
  outputFile << "         " << "        The Input Word was stored as:" << endl;
  outputFile << "                  -------------------------" << endl;
  outputFile << "                     " << inputWordFinal << endl;
}

//******************************************************************************
