#ifndef CAMADA_FISICA
#define CAMADA_FISICA
#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <bits/stdc++.h>
#include <bitset>
using namespace std;
void AplicacaoTransmissora();
void CamadaDeAplicacaoTransmissora(string mensagem);
vector<int> ConvertToBits(string mensagem);
void CamadaFisicaTransmissora(vector<int> quadro);

// // Codificação/Decodificação Binária
vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(vector<int> quadro);
vector<int> CamadaFisicaReceptoraDecodificacaoBinaria(vector<int> quadro);

// // Codificação/Decodificação Manchester
vector<int> CamadaFisicaTransmissoraCodificacaoManchester(vector<int> quadro);
vector<int> CamadaFisicaReceptoraDecodificacaoManchester(vector<int> fluxoBrutoDeBits);

// // Codificação/Decodificação Bipolar
vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(vector<int> quadro);
vector<int> CamadaFisicaReceptoraDecodificacaoBipolar (vector<int> quadro);

// // Meio entre o transmissor e o receptor
void MeioDeComunicacao(vector <int>  fluxoBrutodeBits);

// // simulador por parte do receptor
void CamadaFisicaReceptora(vector<int> quadro);
void CamadaDeAplicacaoReceptora(vector<int> quadro);

// // simulação da aplicação final recebendo a mensagem enviada do transmissor
void AplicacaoReceptora(string mensagem);

#endif