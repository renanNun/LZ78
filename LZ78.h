/**
* Universidade Federal de Juiz de Fora
* Algoritmo LZ78
* @data: 13/03/2021
* @autor: Renan
* @version: 1.0
**/

#ifndef LZ78_LZ78_H
#define LZ78_LZ78_H

//Incluindo Bibliotecas a serem utilizadas no programa
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <bitset>

using namespace std;

class LZ78 {
public:
    LZ78(); //Construtor
    virtual ~LZ78(); //Destrutor

    static void compressao(const string& inputCompress, const string& outputFile);
    static void descompressao(const string& fileToDecompress,const string& outputFile);
private:
    static string decimalToBinario(const int& input) ;
    static int BinarioToDecimal(const char& input) ;
    static string stringToASCII(const string& input) ;
    static char ASCIIToChar(const string& input);

    static string fileRead(const string& file);

    static void fileWrite(const string& file,const string& outputIn);
    static void fileWriteBin(const string& file,const string& input);
};


#endif //LZ78_LZ78_H
