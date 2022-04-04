using namespace std;
#include "../include/CamadaFisica.hpp"

vector<int> ConvertToBits(string mensagem){
    int i=0, j=0;
    vector<int> quadro;

    for(i=0; i < mensagem.size(); i++){
        bitset<8> set (mensagem[i]);
        if (mensagem[i] == ' '){
            // um espaço vazio teve que virar um caso especial
            set.reset();   // todos são zero
            set.set(5, 1); // 32 == espaço
	    }

        for(j=7; j>= 0; j--){
            if(set.test(j)){
                quadro.push_back(1);
            }
            else{
                quadro.push_back(0);
            }
        }
    }

    return quadro;
}
void CamadaDeAplicacaoTransmissora(string mensagem){
    //transformar a mensagem em bits e colocar em quadro.
		vector<int> quadro = ConvertToBits(mensagem);
    for(int i: quadro)
        printw("%d", i);
		printw("\n");
		CamadaFisicaTransmissora(quadro);

		refresh();
}

char op;
void AplicacaoTransmissora(){
	
	char a[90];
	string mensagem;

	initscr();

	printw("Digite uma mensagem: ");
	getstr(a);
	
	int i = 0;
	while (a[i] != '\0')
	{
		mensagem.push_back(a[i]);
		i++;
	}
	printw("\n");
	printw(" 0 - Binaria\n 1 - Manchester\n 2 - Bipolar\n\n");
	scanw("%c", &op);
	printw("\n");

	refresh();
	CamadaDeAplicacaoTransmissora(mensagem);

	getch();

	endwin();

}

vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(vector<int>quadro){
    
    printw("\nCodificação Fisica Binaria: ");
    for(int i: quadro)
			printw("%d", i);
		printw("\n");

		refresh();
		return quadro;
}

vector<int> CamadaFisicaTransmissoraCodificacaoManchester(vector<int> quadro){
    // se for 0 -> 01
    // se for 1 -> 10
    vector<int> fluxoBrutoDeBits;
    int i, j;
    for(i=0; i < quadro.size(); i++){
        switch(quadro[i]){
            case 0:
                fluxoBrutoDeBits.push_back(0);
                fluxoBrutoDeBits.push_back(1);
                break;
            case 1:
                fluxoBrutoDeBits.push_back(1);
                fluxoBrutoDeBits.push_back(0);
                break;
            default:
                break;

        }
    }
    printw("\nCodificacao Manchester: ");
    for(int k: fluxoBrutoDeBits)
			printw("%d", k);
		printw("\n");
		refresh();

		return fluxoBrutoDeBits;
}


vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(vector<int> quadro){
    vector<int> fluxoBrutoDeBits;
    int i;
    int flag = 0;
    for(i=0; i<quadro.size(); i++){
        if(quadro[i] == 1){
            switch(flag){
                case 0:
                    flag =1;
                    fluxoBrutoDeBits.push_back(1);
                    break;
                case 1:
                    flag -= 1;
                    fluxoBrutoDeBits.push_back(-1);
                    break;
            }
        }
        else{
            fluxoBrutoDeBits.push_back(0);
         
        }
    }
    printw("\nCodificação Bipolar: ");
    for(int k: fluxoBrutoDeBits)
        printw("%d", k);
		printw("\n");

		refresh();

		return fluxoBrutoDeBits;
}

void CamadaFisicaTransmissora(vector <int> quadro){
    char tipoDeCodificacao = op;
    vector <int> fluxoBrutoDeBits;

    switch (tipoDeCodificacao) {
        case '0':
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
            break;
        case '1':
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro);
            break;
        case '2':
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBipolar(quadro);
            break;
    }

    MeioDeComunicacao(fluxoBrutoDeBits);
}

void MeioDeComunicacao(vector <int> fluxoBrutodeBits){

    vector <int>  fluxoBrutoDeBitsPontoA, fluxoBrutoDeBitsPontoB;
    int i;
    fluxoBrutoDeBitsPontoA = fluxoBrutodeBits;

  
    for(i = 0; i < fluxoBrutoDeBitsPontoA.size(); i++){
        fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA[i]); //BITS sendo transferidos
    }

    CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}

// //RECEPÇÃO
vector<int> CamadaFisicaReceptoraCodificacaoBinaria(vector<int> quadro){

    printw("\nDecodificação Fisica Binaria: ");
    for(int i: quadro)
        printw("%d", i);
		printw("\n");

		refresh();

		return quadro;
}
vector<int> CamadaFisicaReceptoraCodificacaoManchester(vector<int> fluxoBrutoDeBits){
    int i;
    vector<int> quadro;
    for(i=0; i<fluxoBrutoDeBits.size(); i+=2){
        if(fluxoBrutoDeBits[i]==0 && fluxoBrutoDeBits[i+1]==1){
            quadro.push_back(0);
        }
        else{
            quadro.push_back(1);
        }
    }
    printw("\nDecodificacao Manchester: ");
    for(int k: quadro)
        printw("%d", k);
		printw("\n");

		refresh();

		return quadro;
}

vector<int> CamadaFisicaReceptoraCodificacaoBipolar(vector<int> fluxoBrutoDeBits){
    int i;
    vector<int> quadro;

    for(i=0; i<fluxoBrutoDeBits.size(); i++){
        if(fluxoBrutoDeBits[i] == 1 || fluxoBrutoDeBits[i]==-1)
            quadro.push_back(1);
        else
            quadro.push_back(0);
    }
    printw("\nDecodificacao Bipolar: ");
    for(int k: quadro)
        printw("%d", k);
		printw("\n");

		refresh();

		return quadro;
}

void CamadaFisicaReceptora(vector<int> quadro){
    char tipoDeDecodificacao = op; // alterar de acordo com o teste
    vector<int> fluxoBrutoDeBits;

    switch (tipoDeDecodificacao) {
        case '0':
            fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoBinaria(quadro);
            break;
        case '1':
            fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoManchester(quadro);
            break;
        case '2':
            fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoBipolar(quadro);
            break;
    }
    printw("\ncamada fisica receptora");

		refresh();

		CamadaDeAplicacaoReceptora(fluxoBrutoDeBits);
}

string DecodeToString(vector<int> quadro)
{
	int i = 0, y = 0, j = 0;
	string mensagem;
	int letra = 0;
	for (i = 0; i < quadro.size(); i += 8)
	{
		letra = 0;
		y = 0;
		for (j = i; j < (8 + i); j++)
		{
			if (quadro[j] == 1)
				letra = letra + pow(2, 7 - y);

			y++;
		}
		mensagem.push_back((char)letra);
	}
	printw("\nSua mensagem: ");
	for (int k : mensagem)
		printw("%c", k);

	refresh();

	return mensagem;
}
void CamadaDeAplicacaoReceptora(vector<int> quadro){
    printw("\ncamada de aplicacao receptora");
    AplicacaoReceptora(DecodeToString(quadro));
}

void AplicacaoReceptora(string mensagem){
    printw("\nA mensagem recebida foi: ");
		for (int k : mensagem)
			printw("%c", k);
		printw("\n");

		refresh();
}