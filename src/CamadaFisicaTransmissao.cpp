

using namespace std;
#include "../include/CamadaFisica.hpp"


vector<int> ConvertToBits(string mensagem){
    int i=0, j=0;
    // bitset<8>set(mensagem[x]);
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
    //int quadro[] = mensagem; //trabalhar em bits --- mudar
    //transformar a mensagem em bits e colocar em quadro.


    vector<int> quadro = ConvertToBits(mensagem);
    for(int i: quadro)
        cout << i;
    cout<<endl;
    CamadaFisicaTransmissora(quadro);
}
void AplicacaoTransmissora(){
    string mensagem;
    cout << "Digite uma mensagem: " << endl;
    getline (cin, mensagem);

    CamadaDeAplicacaoTransmissora(mensagem);
}

vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(vector<int>quadro){
    
    cout<< "\nCodificação Fisica Binaria: ";
    for(int i: quadro)
        cout << i;
    cout<<endl;
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
    cout<< "Codificacao Manchester: ";
    for(int k: fluxoBrutoDeBits)
        cout << k;
    cout<<endl;
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
    cout<< "Codificação Bipolar: ";
    for(int k: fluxoBrutoDeBits)
        cout << k;
    cout<<endl;
    return fluxoBrutoDeBits;
}

void CamadaFisicaTransmissora(vector <int> quadro){
    int tipoDeCodificacao = 2;
    vector <int> fluxoBrutoDeBits;

    switch (tipoDeCodificacao) {
        case 0:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
            break;
        case 1:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro);
            break;
        case 2:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBipolar(quadro);
            break;
    }

    MeioDeComunicacao(fluxoBrutoDeBits);
    // for(int i: fluxoBrutoDeBits)
    //     cout << i;
    // cout<<endl;
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

    cout<< "\nDecodificação Fisica Binaria: ";
    for(int i: quadro)
        cout << i;
    cout<<endl;
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
    cout<< "Decodificacao Manchester: ";
    for(int k: quadro)
        cout << k;
    cout<<endl;
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
    cout<< "Decodificacao Bipolar: ";
    for(int k: quadro)
        cout << k;
    cout<<endl;
    return quadro;
}

void CamadaFisicaReceptora(vector<int> quadro){
    int tipoDeDecodificacao = 2; // alterar de acordo com o teste
    vector<int> fluxoBrutoDeBits;

    switch (tipoDeDecodificacao) {
        case 0:
            fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoBinaria(quadro);
            break;
        case 1:
            fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoManchester(quadro);
            break;
        case 2:
            fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoBipolar(quadro);
            break;
    }
    cout << "camada fisica receptora"<<endl;
    CamadaDeAplicacaoReceptora(fluxoBrutoDeBits);
}



string DecodeToString(vector<int> quadro){
    int i=0, y=0, j=0, decimal=0;
    bitset<8> text;
    string mensagem;
    // i=quadro.size();
    int letra = 0;
    // cout << "quadro size: "<< quadro.size() << endl;
    
    // for(i=0; i < quadro.size(); i+=8){
    //     cout << "i: "<< i << endl;
    //     letra = 0;
    //     if(i >= quadro.size()-1)
    //         break;
    //     y=0;
    //     for(j=i; j<i+8; j++){
    //         cout << "j: "<< j << " quadro j: " << quadro[j]<< endl;
    //         // cout << "j%8: " << j%8 << endl;
    //         if(quadro[j%8]==1){
    //             cout << "test"<< endl;
    //             letra = letra + pow(2,7-y); 
    //             //text.set(j%8, 1);
                
    //         }
    //         y++;
    //     }
    //     cout << "letra: " << letra << endl;
    //     //mensagem += (char)letra;
    //     mensagem.push_back((char)letra);
    //     //reverse(mensagem.begin(), mensagem.end());
    //     cout << mensagem << endl;
    //     //text.reset();
    // }
    for (i = 0; i < (quadro.size() / 8); i++)
	{

		decimal = 0;

		y = 0;
        //111111 101010
		for (j = ((i * 8) + 7); j >= (i * 8); j--){

			if (quadro[j] == 1){

				decimal = decimal + pow(2, y);
			}

			y++;
		}

		mensagem.push_back((char)decimal);
	}
    cout << "Sua mensagem: "<< mensagem << endl;
    return mensagem;
}
void CamadaDeAplicacaoReceptora(vector<int> quadro){
    //string mensagem = quadro;
    //string mensagem = "";
    //int i;

    // for(i=0; i> < quadro.size(); i++){
    //     mensagem += quadro.to_string<char,std::string::traits_type,std::string::allocator_type>();
    // }
    // AplicacaoReceptora(mensagem)
    cout << "camada de aplicacao receptora" << endl;
    // string mensagem = DecodeToString(quadro);
    AplicacaoReceptora(DecodeToString(quadro));
}

void AplicacaoReceptora(string mensagem){
    cout << "A mensagem recebida foi: " << mensagem << endl;
}