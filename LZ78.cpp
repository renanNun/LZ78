#include "LZ78.h"

/**
* Construtor da Classe LZ78
*/
LZ78::LZ78() = default;

/**
* Destrutor da Classe LZ78
*/
LZ78::~LZ78() = default;

/**
* Algoritmo de Compressão da Classe LZ78
* @param: inputCompress - Arquivo txt que contém os dados a serem comprimidos
* @param: outputFile - Arquivo que receberá a saída dos dados de compressão
*/
void LZ78::compressao(const string& inputCompress, const string& outputFile) {
    map<string,int> dicionario; //Dicionário de dados
    string charstream; //Sequencia a ser comprimida
    string codestream; //Sequencia comprimida
    string caracter;
    string prefix;

    //cout << "Iniciando Compressao" << endl;

    charstream = fileRead(inputCompress); //A sequencia a ser comprimida recebe todos os valores presentes no arquivo de entrada

    for(size_t i = 0; i < charstream.length(); i++) //Looping, não chega ao final enquanto a sequencia não terminar
    {
        //cout << "For de compressoes" << endl;
        caracter = charstream.substr(i,1); //Pega substring

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

/**
* Algoritmo de Descompressão da Classe LZ78
* @param: inputCompress - Arquivo txt que contém os dados a serem descomprimidos
* @param: outputFile - Arquivo que receberá a saída dos dados de descomprimidos
*/
void LZ78::descompressao(const string& fileToDecompress, const string& outputFile) {
    map<int,string> dicionario; //Dicionário de daos
    string charstream; //Sequencia descomprimida
    string codestream; //Sequencia comprimida
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

/*Funções auxiliares na compressão de dados*/

/**
* Função de conversão de decimal para binário
* @param: input - valor a ser convertido
* @return string
*/
string LZ78::decimalToBinario(const int &input) {
    return bitset<8>(input).to_string();
}

/**
* Função de conversão de Binário para decimal
* @param: input - valor a ser convertido
* @return int
*/
int LZ78::BinarioToDecimal(const char &input) {
    bitset<8> dec(input);
    return dec.to_ulong();
}

/**
* Função de conversão de string para ASCII
* @param: input - valor a ser convertido
* @return string
*/
string LZ78::stringToASCII(const string &input) {
    return bitset<8>(input[0]).to_string();
}

/**
* Função de conversão de ASCII para char
* @param: input - valor a ser convertido
* @return char
*/
char LZ78::ASCIIToChar(const string &input){
    return (char)bitset<8>(input).to_ulong();
}

/**
* Função de leitura de arquivo
* @param: file - valor a ser convertido
* @return string
*/
string LZ78::fileRead(const string& file) {
    ifstream inputFile(file);
    stringstream buffer;
    buffer << inputFile.rdbuf();

    string input = buffer.str();
    return input;
}

/**
* Função de escrita em arquivo
* @param: file - arquivo de escrita
* @param: outputIn - valores a serem escritos no arquivo
* @return 
*/
void LZ78::fileWrite(const string& file, const string& outputIn) {
    ofstream output(file);
    output << outputIn;
    output.close();
}

/**
* Função de escrita em arquivo binário
* @param: file - arquivo de escrita
* @param: outputIn - valores a serem escritos no arquivo
* @return 
*/
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
