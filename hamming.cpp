#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include "hamming.h"

using namespace std;

#define WORDSIZE 16
#define MAX_SIZE_WORD 20

int main(){
  ifstream inputFile("officialData.txt");
  ofstream outputFile("out.txt");
  string word1;
  string word2;
  int recordCount = 0;

    //read in 1st and 2nd word
  inputFile >> word1;
  inputFile >> word2;

    //make sure valid (ie not end of file)
  while(word1 != "-1"){
    recordCount++;
    Hamming hamming;
    hamming.loadWords(word1, word2);
    hamming.placeCheckBitLocations();
    hamming.getCheckBits();
    hamming.getKBitCode();
    hamming.getInputWord();
    hamming.syndromeWordComparison();
    hamming.printOriginalWords(word1, word2, recordCount, outputFile);
    hamming.detect(outputFile);
    inputFile >> word1;
    inputFile >> word2;
  }
  return 0;
}

//******************************************************************************

void Hamming::loadWords(string word1, string word2){
    //Receives - two input words (from memory and to memory)
    //Task - place words in character arrays
    //Returns - nothing

    //store word 1 in array (written into memory)
  for(int x = 0; x < WORDSIZE; x++){
    word1Array[x] = word1[x];
  }
    //store word 2 in array (read from memory)
  for(int y = 0; y < WORDSIZE; y++){
    word2Array[y] = word2[y];
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
      wordParityBits2.push_back('-');
    }

      //not a parity bit, place bit in array
    else{
        //add to parity bit vector
      wordParityBits.push_back(word1Array[count]);
      wordParityBits2.push_back(word2Array[count]);
      count++;
    }
  }

  /*for(int x = 0; x < wordParityBits.size(); x++){
    cout << wordParityBits[x];
  }
  cout << endl;
  for(int x = 0; x < wordParityBits.size(); x++){
    cout << wordParityBits2[x];
  }
  cout << endl;*/
}

//******************************************************************************

void Hamming::getCheckBits(){
    //Receives - nothing
    //Task - calculate check bits
    //Returns - nothing

  int numIntoMemory;
  int numFromMemory;

    //calculate check bits for decimal location 1
  for(int x = 0; x < wordParityBits.size(); x++){
    if(x == 18 || x == 16 || x == 14 || x == 12 || x == 10 ||
       x == 8 || x == 6 || x == 4 || x == 2 || x == 0){
         numIntoMemory = (int)wordParityBits[x] - 48; //store as integer
         numFromMemory = (int)wordParityBits2[x] - 48;
         parity1.push_back(numIntoMemory);
         _parity1.push_back(numFromMemory);
       }
  }

    //calulate check bits for decimal location 2
  for(int x = 0; x < wordParityBits.size(); x++){
    if(x == 2 || x == 3 || x == 6 || x == 7 || x == 10 || x == 11 ||
       x == 14 || x == 15 || x == 18){
         numIntoMemory = (int)wordParityBits[x] - 48; //store as integer
         numFromMemory = (int)wordParityBits2[x] - 48;
         parity2.push_back(numIntoMemory);
         _parity2.push_back(numFromMemory);
       }
  }

    //calculate check bits for decimal location 4
  for(int x = 0; x < wordParityBits.size(); x++){
    if(x == 0 || x == 1 || x == 6 || x == 7 || x == 8 || x == 9 ||
       x == 14 || x == 15 || x == 16){
         numIntoMemory = (int)wordParityBits[x] - 48; //store as integer
         numFromMemory = (int)wordParityBits2[x] - 48;
         parity4.push_back(numIntoMemory);
         _parity4.push_back(numFromMemory);
       }
  }

    //calculate check bits for decimal location 8
  for(int x = 0; x < wordParityBits.size(); x++){
    if(x == 6 || x == 7 || x == 8 || x == 9 || x == 10 ||
       x == 11 || x == 12){
         numIntoMemory = (int)wordParityBits[x] - 48; //store as integer
         numFromMemory = (int)wordParityBits2[x] - 48;
         parity8.push_back(numIntoMemory);
         _parity8.push_back(numFromMemory);
       }
  }

    //calculate check bits for decimal location 16
  for(int x = 0; x < wordParityBits.size(); x++){
    if(x == 0 || x == 1 || x == 2 || x == 3 || x == 4){
      numIntoMemory = (int)wordParityBits[x] - 48; //store as integer
      numFromMemory = (int)wordParityBits2[x] - 48;
      parity16.push_back(numIntoMemory);
      _parity16.push_back(numFromMemory);
    }
  }
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

  //***** NOW CALCULATE THE KBIT WORD FOR THE NUMBER READ FROM MEMORY **********

    //reset count
  count = 0;

    //check parity bit for decimal location 16
  for(int x = 0; x < _parity16.size(); x++){
    if(_parity16[x] == 1){
      count++;
    }
  }

    //if the value is even the resulting bit is a 0
  if(count % 2 == 0){
    kbitWord2.push_back(0);
  }
    //resulting value is a 1
  else{
    kbitWord2.push_back(1);
  }

  count = 0;  //reset count

    //check parity bit for decimal location 8
  for(int x = 0; x < _parity8.size(); x++){
    if(_parity8[x] == 1){
      count++;
    }
  }

    //resulting bit is a 0 if even
  if(count % 2 == 0){
    kbitWord2.push_back(0);
  }
    //resulting bit is a 1 if odd
  else{
    kbitWord2.push_back(1);
  }

  count = 0;  //reset count

    //check parity bit for decimal location 4
  for(int x = 0; x < _parity4.size(); x++){
    if(_parity4[x] == 1){
      count++;
    }
  }

    //resulting bit is a 0 if odd
  if(count % 2 == 0){
    kbitWord2.push_back(0);
  }
    //resulting bit is a 1 if odd
  else{
    kbitWord2.push_back(1);
  }

  count = 0;  //reset count

    //check parity bit for decimal location 2
  for(int x = 0; x < _parity2.size(); x++){
    if(_parity2[x] == 1){
      count++;
    }
  }

    //resulting bit is a 0 if even
  if(count % 2 == 0){
    kbitWord2.push_back(0);
  }
    //resulting bit is a 1 if odd
  else{
    kbitWord2.push_back(1);
  }

  count = 0;  //reset count

    //check parity bit for decimal location 1
  for(int x = 0; x < _parity1.size(); x++){
    if(_parity1[x] == 1){
      count++;
    }
  }

    //resulting bit is a 0 if even
  if(count % 2 == 0){
    kbitWord2.push_back(0);
  }
    //resulting bit is a 1 if odd
  else{
    kbitWord2.push_back(1);
  }
}

//******************************************************************************

void Hamming::syndromeWordComparison(){
    //Receives - nothing
    //Task - calculates final syndrome word comparison
    //Returns - nothing

    //go through the syndrome words to compare
  for(int x = 0; x < kbitWord.size(); x++){
      //use exclusive OR to compare syndrome word bits
    syndromeFinal.push_back(kbitWord[x]^kbitWord2[x]);
  }
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
}

//******************************************************************************

void Hamming::detect(ofstream &outputFile){
    //Receives - output file
    //Task - print hamming code correction message
    //Returns - nothing

  vector<int> tempSyndrome = syndromeFinal;
  vector<char> tempInputWord = inputWord;
  int decimalValue = 0;

  reverse(tempSyndrome.begin(), tempSyndrome.end());
  reverse(tempInputWord.begin(), tempInputWord.end());

  outputFile << "                  OUTPUT MESSAGE" << endl;
  outputFile << "                  --------------" << endl;

    //convert binary to decimal
  for(int x = 0; x < tempSyndrome.size(); x++){
    decimalValue += tempSyndrome[x] * pow(2, x);
  }

  if(decimalValue > 21){
    outputFile << "The value of the syndrome word indicates that the error" << endl;
    outputFile << "cannot be corrected. Output data is unreliable." << endl;
  }

  if(decimalValue == 0){
    outputFile << "A comparison of the syndrome words indicates that the" << endl;
    outputFile << "word read from memory is correct." << endl;
  }

  else if(decimalValue % 2 == 0){
    outputFile << "The value of the syndrome word indicates that the error" << endl;
    outputFile << "cannot be corrected. Output data is unreliable." << endl;
  }

  else if(decimalValue >= 1 && decimalValue <= 21){
    char found;
    for(int x = 0; x < tempInputWord.size(); x++){
      if(x == decimalValue){
        found = tempInputWord[x];
      }
    }

    if(found == '1'){
      outputFile << "      The syndrome word indicates that the bit in position " << decimalValue << endl;
      outputFile << "      of the word read from memory is an error. It was read " << endl;
      outputFile << "      as a 1 and must be inverted to a 0." << endl;
    }
    else{
      outputFile << "      The syndrome word indicates that the bit in position " << decimalValue << endl;
      outputFile << "      of the word read from memory is an error. It was read " << endl;
      outputFile << "      as a 0 and must be inverted to a 1." << endl;
    }
  }
  outputFile << endl;
  outputFile << endl;
  outputFile << endl;
  outputFile << endl;
}

//******************************************************************************

void Hamming::printOriginalWords(string word1, string word2, int recordCount, ofstream &outputFile){
    //Receives - 1st word, 2nd word, record count, output file
    //Task - Print original words and record #
    //Returns - nothing

    //print formatted output
  outputFile << "Record # " << recordCount << "        Original input words are:" << endl;
  outputFile << "                  -------------------------" << endl;
  outputFile << "                     " << word1 << endl;
  outputFile << "                     " << word2 << endl;
  outputFile << endl;
  outputFile << "         " << "        The Input Word was stored as:" << endl;
  outputFile << "                  -------------------------" << endl;
  outputFile << "                     " << inputWordFinal << endl;
  outputFile << endl;
  outputFile << "         " << "        The two SYNDROME code words are:" << endl;
  outputFile << "                  -------------------------" << endl;
  outputFile << "     K-Bit code written into memory  ---  ";
  for(int x = 0; x < kbitWord.size(); x++){
    outputFile << kbitWord[x] << " ";
  }
  outputFile << endl;
  outputFile << "     K-bit code read from memory     ---  ";
  for(int x = 0; x < kbitWord2.size(); x++){
    outputFile << kbitWord2[x] << " ";
  }
  outputFile << endl;
  outputFile << endl;
  outputFile << "         " << "        SYNDROME Word comparison is" << endl;
  outputFile << "                  -------------------------" << endl;
  outputFile << "                         ";
  for(int x = 0; x < syndromeFinal.size(); x++){
    outputFile << syndromeFinal[x] << " ";
  }
  outputFile << endl;
  outputFile << endl;
}

//******************************************************************************
