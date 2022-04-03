#ifndef CAMADA_FISICA
#define CAMADA_FISICA

void AplicacaoTransmissora();
void CamadaDeAplicacaoTransmissora(string mensagem);
void CamadaFisicaTransmissora(int* quadro);

// Codificação/Decodificação Binária
int *CamadaFisicaTransmissoraCodificacaoBinaria(int *quadro);
int *CamadaFisicaReceptoraDecodificacaoBinaria(int *quadro);

// Codificação/Decodificação Manchester
int *CamadaFisicaTransmissoraCodificacaoManchester(int *quadro);
int *CamadaFisicaReceptoraDecodificacaoManchester(int *quadro);

// Codificação/Decodificação Manchester Diferencial
int *CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(int *quadro);
int *CamadaFisicaReceptoraDecodificacaoManchesterDiferencial (int *quadro);

// Meio entre o transmissor e o receptor
void MeioDeComunicacao(int* fluxoBrutodeBits);

// simulador por parte do receptor
void CamadaFisicaReceptora(int* quadro);
void CamadaDeAplicacaoReceptora(int* quadro);

// simulação da aplicação final recebendo a mensagem enviada do transmissor
void AplicacaoReceptora(string mensagem);

#endif