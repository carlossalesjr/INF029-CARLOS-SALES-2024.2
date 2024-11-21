// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Carlos Alberto Santos Sales Junior
//  email: carlossalesjr04@gmail.com
//  Matrícula: 20241160022
//  Semestre: 2

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include <stdio.h>
#include "CarlosSales-20241160022-T1.h" // Substitua pelo seu arquivo de header renomeado
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

DataQuebrada quebraData(char data[]);

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{
    int datavalida = 1;
    bool bissexto;

    DataQuebrada dataquebrada =  quebraData(data);

    if (dataquebrada.iAno % 400 == 0 || (dataquebrada.iAno % 4 == 0 && dataquebrada.iAno % 100 != 0))
    bissexto = true;

    if (dataquebrada.iMes > 12 || dataquebrada.iMes < 1)
    datavalida = 0;
    
    if (dataquebrada.iDia < 1)
    datavalida = 0;
    
    if (dataquebrada.iMes == 2){
        if (bissexto && dataquebrada.iDia > 29)
        datavalida = 0;
        else if (!bissexto && dataquebrada.iDia > 28)
        datavalida = 0;
    }else if ((dataquebrada.iMes == 4 || dataquebrada.iMes == 6 || dataquebrada.iMes == 9 || dataquebrada.iMes == 11) && dataquebrada.iDia > 30)
    datavalida = 0;
    else if (dataquebrada.iDia > 31)
    datavalida = 0;

    if (datavalida)
        return 1;
    else
        return 0;
}



/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{

    //calcule os dados e armazene nas três variáveis a seguir
    DiasMesesAnos dma;

    if (q1(datainicial) == 0){
      dma.retorno = 2;
      return dma;
    }else if (q1(datafinal) == 0){
      dma.retorno = 3;
      return dma;
    }else{
      //verifique se a data final não é menor que a data inicial
        DataQuebrada inicial, final;
        inicial = quebraData(datainicial);
        final = quebraData(datafinal);
        bool bissexto;
        int diasMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        if (final.iAno < inicial.iAno || (final.iAno == inicial.iAno && final.iMes < inicial.iMes) || 
        (final.iAno == inicial.iAno && final.iMes == inicial.iMes && final.iDia < inicial.iDia)){
            dma.retorno = 4;
            return dma;
        }
        
        //calcule a distancia entre as datas
        if (final.iAno % 400 == 0 || (final.iAno % 4 == 0 && final.iAno % 100 != 0))
        bissexto = true;

        if(bissexto)
        diasMes[1] = 29;

        dma.qtdAnos = final.iAno - inicial.iAno;
        dma.qtdMeses = final.iMes - inicial.iMes;
        dma.qtdDias = final.iDia - inicial.iDia;

        if (dma.qtdMeses < 0){
            dma.qtdAnos--;
            dma.qtdMeses += 12;
        }
        if (dma.qtdDias < 0){
            dma.qtdMeses--;
            dma.qtdDias += diasMes[final.iMes - 2];    
        }
        //se tudo der certo
        dma.retorno = 1;
        return dma;
        
        }
    }    

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
    int jcont;
    int qtdOcorrencias = 0;
    char copia[255];
    
    for (jcont = 0; texto[jcont] != '\0'; jcont++)
        copia[jcont] = texto[jcont];

    if (!isCaseSensitive){
        if (c >= 'a' && c <= 'z'){
           c = c - 32; 
        }
        toUpper(copia);
    }

    for (jcont = 0; copia[jcont]; jcont++){
        if(c == copia[jcont])
        qtdOcorrencias++;
    }

    return qtdOcorrencias;
}

void toUpper(char *copia)
{
    int icont;
    int upper = 32;
    for (icont = 0; copia[icont] != '\0'; icont++){
        if (copia[icont] >= 'a' && copia[icont] <= 'z')
        copia[icont] = copia[icont] - upper;
    }
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. 
    Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, 
    e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. 
    Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. 
    Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera".
     Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
   int qtdOcorrencias = 0;
    int pos = 0;
    int i, j;

    int lenTexto = strlen(strTexto);
    int lenBusca = strlen(strBusca);

    for (i = 0; i <= lenTexto - lenBusca; i++) {
        int achou = 1;
        for (j = 0; j < lenBusca; j++) {
            if (strTexto[i + j] == -61) { 
                i++;
            }
            if (strTexto[i + j] != strBusca[j]) {
                achou = 0;
                break;
            }
        }
        if (achou) {
            qtdOcorrencias++;
            posicoes[pos++] = i + 1;
            posicoes[pos++] = i + lenBusca;
            i += lenBusca - 1;
        }
    }

    return qtdOcorrencias;
}
/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{
    int invertido = 0;

    while (num != 0){
        invertido = invertido * 10 + num % 10;
        num /= 10;
    }
    num = invertido;
    return num;
} 

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
    int qtdOcorrencias = 0;
    int divisor = 1;

    while (numerobusca/divisor != 0)
    divisor *= 10;

    while(numerobase != 0){
        if (numerobase%divisor == numerobusca){
            qtdOcorrencias++;
            numerobase /= divisor;
        } else
            numerobase /= 10;
    }


    return qtdOcorrencias;
}




DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

	dq.valido = 1;
    
  return dq;
} 