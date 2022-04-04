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

		attron(COLOR_PAIR(2));
		printw("Camada De Aplicacao Transmissora\n");
		attroff(COLOR_PAIR(2));

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
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_WHITE, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);

	attron(COLOR_PAIR(2));
	printw("Aplicação Transmissora\n");
	attroff(COLOR_PAIR(2));

	printw("Digite uma mensagem: ");

	getstr(a);
	
	int i = 0;
	while (a[i] != '\0')
	{
		mensagem.push_back(a[i]);
		i++;
	}
	printw("\n");
	attron(COLOR_PAIR(2));
	printw("Escolha o tipo de codificação\n");
	printw(" 0 - Binaria\n 1 - Manchester\n 2 - Bipolar\n\n");
	attroff(COLOR_PAIR(2));

	scanw("%c", &op);
	printw("\n");

	refresh();

	attron(COLOR_PAIR(1));
	printw("Mensagem a ser transmitida: ");
	attroff(COLOR_PAIR(1));
	printw("%s\n", mensagem);
	
	attron(COLOR_PAIR(1));
	if (op == '0')
	{
		printw("Codificação escolhida: ");
		attroff(COLOR_PAIR(1));
		printw("Binaria\n\n");
	}

	attron(COLOR_PAIR(1));
	if (op == '1')
	{
		printw("Codificação escolhida: ");
		attroff(COLOR_PAIR(1));
		printw("Manchester\n\n");
	}

	attron(COLOR_PAIR(1));
	if (op == '2')
	{
		printw("Codificação escolhida: ");
		attroff(COLOR_PAIR(1));
		printw("Bipolar\n\n");
	}
	attroff(COLOR_PAIR(1));

	CamadaDeAplicacaoTransmissora(mensagem);

	getch();

	endwin();
}

vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(vector<int>quadro){

	attron(COLOR_PAIR(2));
	printw("\nCamada Fisica Transmissora - Codificação Binaria: \n");
	attroff(COLOR_PAIR(2));

	for (int i : quadro)
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
		attron(COLOR_PAIR(2));
		printw("\nCamada Fisica Transmissora - Codificação Manchester: \n");
		attroff(COLOR_PAIR(2));

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
		attron(COLOR_PAIR(2));
		printw("\nCamada Fisica Transmissora - Codificação Bipolar: \n");
		attroff(COLOR_PAIR(2));

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

	attron(COLOR_PAIR(2));
	printw("\nCamada Fisica Receptora - Codificação Binaria: \n");
	attroff(COLOR_PAIR(2));

	for (int i : quadro)
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
		attron(COLOR_PAIR(2));
		printw("\nCamada Fisica Receptora - Codificação Manchester: \n");
		attroff(COLOR_PAIR(2));

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
		attron(COLOR_PAIR(2));
		printw("\nCamada Fisica Receptora - Codificação Bipolar: \n");
		attroff(COLOR_PAIR(2));

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
		attron(COLOR_PAIR(5));
		printw("\n\nCamada Fisica Receptora \n");
		attroff(COLOR_PAIR(5));
		printw("Sua mensagem foi recebida\n\n");

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

	// printw("\nSua mensagem: ");
	// for (int k : mensagem)
	// 	printw("%c", k);

	refresh();

	return mensagem;
}
void CamadaDeAplicacaoReceptora(vector<int> quadro){

	attron(COLOR_PAIR(5));
	printw("Camada de Aplicação Receptora\n");
	attroff(COLOR_PAIR(5));

	AplicacaoReceptora(DecodeToString(quadro));
}

void AplicacaoReceptora(string mensagem){

	attron(COLOR_PAIR(1));
	printw("A mensagem recebida foi: ");
	attroff(COLOR_PAIR(1));

	for (int k : mensagem)
		printw("%c", k);
	printw("\n");

	refresh();
}