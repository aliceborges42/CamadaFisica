# Camada Fisica
Trabalho 1 de TR1 - Simulador da Camada Física
# Execução
- Para compilar o código, rode no terminal com a pasta CamadaFisica aberta 
	```
	g++ src/Simulador.cpp src/CamadaFisica.cpp -lncurses -o out 
	```
  <br />
- O executavel "out" será criado na pasta raiz do projeto
- Para rodar execute
	```
	./out  
	```
  <br />
- A flag `-lncurses` é utilizada para compilar o projeto junto com sua interface, caso não possua o Ncuses instalado o programa não será compilado e rodado corretamente
 <br />
- Durante o desenvolvimento foi utilizado o seguinte tutorial para instalação do Ncurses
	
 	https://ostechnix.com/how-to-install-ncurses-library-in-linux/
