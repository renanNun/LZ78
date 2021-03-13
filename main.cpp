#include <iostream>

#include "LZ78.h"
using namespace std;

int main() {

    LZ78 teste;
    teste.compressao("entradaCompressao.txt","SaidaCompressao.txt");
    teste.descompressao("SaidaCompressao.txt","SaidaDescompressao.txt");

    return 0;
}
