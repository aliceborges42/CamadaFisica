
#include <iostream>
#include <string>
#include <stdlib.h>

void AplicacaoTransmissora(){
    string mensagem;
    cout << "Digite uma mensagem: " << endl;
    cin >> mensagem;

    CamadaDeAplicacaoTransmissora(mensagem);
}

void CamadaDeAplicacaoTransmissora(string mensagem){
    int quadro[] = mensagem; //trabalhar em bits --- mudar
    
    CamadaFisicaTransmissora(quadro);
}

void CamadaFisicaTransmissora(int *quadro){
    int tipoDeCodificacao = 0;
    int *fluxoBrutoDeBits;

    switch (tipoDeCodificacao) {
        case 0:
            //fluxoBrutoDeBits = CamadaFisicaTransmissoraCodifBinaria(quadro)
            break;
        case 1:
            //fluxoBrutoDeBits = CamadaFisicaTransmissoraCodifManchester(quadro);
            break;
        case 2:
            //fluxoBrutoDeBits = CamadaFisicaTransmissoraCodifBipolar(quadro);
            break;
    }

    MeioDeComunicacao(fluxoBrutoDeBits);

}

int * CamadaFisicaTransmissoraCodificacaoBinaria(int *quadro){}
int * CamadaFisicaTransmissoraCodificacaoManchester(int *quadro){}
int * CamadaFisicaTransmissoraCodificacaoBipolar(int *quadro){}

void MeioDeComunicacao(int *fluxoBrutodeBits){

    int *fluxoBrutoDeBitsPontoA, *fluxoBrutoDeBitsPontoB;

    fluxoBrutoDeBitsPontoA = fluxoBrutodeBits;

    while (fluxoBrutoDeBitsPontoB.lenght != fluxoBrutoDeBitsPontoA){
        fluxoBrutoDeBitsPontoB += fluxoBrutoDeBitsPontoA; //BITS sendo transferidos
    }
    

    CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}

//RECEPÇÃO

void CamadaFisicaReceptora(int *quadro){
    int tipoDeDecodificacao = 0; // alterar de acordo com o teste
    int *fluxoBrutoDeBits;

    switch (tipoDeDecodificacao) {
        case 0:
            fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoBinaria(int *quadro);
            break;
        case 1:
            fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoManchester(int *quadro);
            break;
        case 2:
            fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoBipolar(int *quadro);
            break;
    }

    CamadaDeAplicacaoReceptora(fluxoBrutoDeBits);
}

int * CamadaFisicaReceptoraCodificacaoBinaria(int *quadro){}
int * CamadaFisicaReceptoraCodificacaoManchester(int *quadro){}
int * CamadaFisicaReceptoraCodificacaoBipolar(int *quadro){}

void CamadaDeAplicacaoReceptora(int *quadro){
    string mensagem = quadro;

    AplicacaoReceptora(mensagem)
}

void AplicacaoReceptora(string mensagem){
    cout << "A mensagem recebida foi: " << mensagem << endl;
}