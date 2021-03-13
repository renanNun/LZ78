//
// Created by Renan on 13/03/2021.
//

#include "LZ78.h"

LZ78::LZ78() = default;

LZ78::~LZ78() = default;

void LZ78::compressao(const string& inputCompress, const string& outputFile) {
    map<string,int> dicionario;
    string charstream; //Sequencia a ser comprimida
    string codestream; //Sequencia comprimida
    string caracter;
    string prefix;

    //cout << "Iniciando Compressao" << endl;

    charstream = fileRead(inputCompress);

    for(size_t i = 0; i < charstream.length(); i++)
    {
        cout << "For de compressoes" << endl;
        caracter = charstream.substr(i,1);

        if(dicionario.count(prefix+caracter))
            prefix += caracter;
        else{
            if(prefix.empty())
                codestream += "00000000";
            else
                codestream += decimalToBinario(dicionario[prefix]);

            codestream += stringToASCII(caracter);

            dicionario[prefix+caracter] = dicionario.size() + 1;

            prefix.clear();
        }
    }

    cout << "Taxa de Compressao: " << (double)codestream.length() / (charstream.length() * 8) << endl;
    fileWriteBin(outputFile,codestream);
}

void LZ78::descompressao(const string& fileToDecompress, const string& outputFile) {
    map<int,string> dicionario;
    string charstream;
    string codestream;
    string caracter;
    int codeword;

    codestream = fileRead(fileToDecompress);

    for(size_t i = 0; i < codestream.length(); ++++i)
    {
        codeword = BinarioToDecimal(codestream[i]);
        caracter = codestream.substr(i+1,1);

        if(codeword != 0)
        {
            charstream += dicionario[codeword];
        }
        charstream += caracter;

        if(codeword != 0)
            dicionario[dicionario.size() + 1] = dicionario[codeword] + caracter;
        else
            dicionario[dicionario.size() + 1] = caracter;
    }
    fileWrite(outputFile,charstream);
}

string LZ78::decimalToBinario(const int &input) {
    return bitset<8>(input).to_string();
}

int LZ78::BinarioToDecimal(const char &input) {
    bitset<8> dec(input);
    return dec.to_ulong();
}

string LZ78::stringToASCII(const string &input) {
    return bitset<8>(input[0]).to_string();
}

char LZ78::ASCIIToChar(const string &input){
    return (char)bitset<8>(input).to_ulong();
}

string LZ78::fileRead(const string& file) {
    ifstream inputFile(file);
    stringstream buffer;
    buffer << inputFile.rdbuf();

    string input = buffer.str();
    return input;
}

void LZ78::fileWrite(const string& file, const string& outputIn) {
    ofstream output(file);
    output << outputIn;
    output.close();
}

void LZ78::fileWriteBin(const string& file, const string& input) {
    string numBits;
    long tmp;
    char output;

    ofstream outFile(file);

    for(int i = 0; i < input.length(); i += 8)
    {
        numBits = input.substr(i,8);
        tmp = strtol(numBits.c_str(),0,2);
        output = tmp &  0xffl;
        outFile << output;
    }

    outFile.close();
}
