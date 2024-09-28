#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "funcoes.h"

int quantChapas;
int segundoTurno = 0;

struct chapa
{
    char nome[50];
    int numero;
    int dataNascimento[3];
    char nomeVice[50];
    int quantidadeVotos;
};


void limparTerminal(){
    #ifdef _WIN32
        system("cls");
    #elif __linux__
        system("clear");
    #endif
}

int quantidadeChapas(){
    
    do{
        printf("Digite a quantidade de chapas que serao registaradas: ");
        scanf("%d", &quantChapas);
        setbuf(stdin, NULL);
        if(quantChapas < 1 || quantChapas > 99){
            printf("\nDigite um valor entre 1 e 99\n\n");
        }
    }while(quantChapas < 1 || quantChapas > 99);

    return quantChapas;
}

Chapa *registrarChapas(Chapa *chapas){

    chapas = (Chapa *) malloc(quantChapas * sizeof(Chapa));
    if(chapas == NULL){
        perror("Erro alocacao de memoria");
        exit(1);
    }

    for(int i = 0; i < quantChapas; i++){
        limparTerminal();

        printf("Digite o nome do candidato a prefeito: ");
        fgets(chapas[i].nome, 50, stdin);
        setbuf(stdin, NULL);
        corrigeFormatacao(chapas[i].nome);

        do{
            printf("Digite o numero do candidato: ");
            scanf("%d", &chapas[i].numero);
            setbuf(stdin, NULL); 
        }while(verificaNumero(chapas, i, quantChapas));

        do{
            printf("Digite o dia de nascimento do candidato no formato DD MM AAAA: ");
            scanf("%d %d %d", &chapas[i].dataNascimento[0], &chapas[i].dataNascimento[1], &chapas[i].dataNascimento[2]);
            setbuf(stdin, NULL);
        }while(verificaData(chapas[i].dataNascimento));

        printf("Digite o nome do vice: ");
        fgets(chapas[i].nomeVice, 50, stdin);
        setbuf(stdin, NULL);
        corrigeFormatacao(chapas[i].nomeVice);

        chapas[i].quantidadeVotos = 0;
    }

    return chapas;
}

int verificaNumero(Chapa *chapas, int pos, int quant){
    if(chapas[pos].numero <= 0 || chapas[pos].numero > 99){
        printf("\nO numero deve estar entre 1 e 99!\n\n");
        return 1;
    }

    for(int i = 0; i < quant; i++){
        if(i != pos && chapas[i].numero == chapas[pos].numero){
            printf("\nEste numero ja esta sendo usado!\n\n");
            return 1;
        }
    }
    return 0; 
}

int verificaData(int dataNasc[3]){
    struct tm data = {0};
    time_t agora = time(NULL);
    struct tm *tm_atual = localtime(&agora);

    int data_atual[] = {tm_atual->tm_mday, tm_atual->tm_mon + 1, tm_atual->tm_year + 1900};
      

    if (comparaIdade(data_atual, dataNasc)) {
        printf("\nData invalida! A pessoa ainda nao nasceu.\n\n");
        return 1; 
    }


    data.tm_mday = dataNasc[0];
    data.tm_mon = dataNasc[1] - 1;
    data.tm_year = dataNasc[2] - 1900;

    mktime(&data);

    if(data.tm_mday != dataNasc[0] || data.tm_mon != dataNasc[1] - 1 || data.tm_year != dataNasc[2] - 1900){
        printf("\nData invalida!\n\n");
        return 1;
    }
    return 0;
}

int comparaIdade(int data1[3], int data2[3]) {
    if (data1[2] < data2[2]) return 1; 
    if (data1[2] > data2[2]) return 0;
    if (data1[1] < data2[1]) return 1; 
    if (data1[1] > data2[1]) return 0;
    if (data1[0] < data2[0]) return 1; 
    return 0;
}

void corrigeFormatacao(char *str){
    str[strcspn(str, "\n")] = 0;
}

void votacao(Chapa *chapas, int *votosBrancos, int *votosNulos, int quant){
    int quantEleitores = quantidadeEleitores();
    int numeroVotado;

    for(int i = 0; i < quantEleitores; i++){

        limparTerminal();
        printf(" CANDIDATOS\n\n");
        printf(" NOME   |   NUMERO   |  VICE\n\n");
        ImprimeCandidatos(chapas, quant); 
        printf("\n");
        printf("Seu voto para prefeito: ");
        scanf("%d", &numeroVotado);

        atribuirVoto(chapas, numeroVotado, votosBrancos, votosNulos, quant);
        fflush(stdout);
        sleep(2); 
    }
}

int quantidadeEleitores(){
    int quantEleitores;
    limparTerminal();
    if(segundoTurno == 0){
        printf("Digite a quantidade de eleitores: ");
        scanf("%d", &quantEleitores);
    }
    else{
        do{
            printf("Digite a quantidade de eleitores: ");
            scanf("%d", &quantEleitores);   
            if(quantEleitores < 10){
                printf("\nDigite um valor igual ou maior que 10\n\n");
            }
        }while(quantEleitores < 10);
    }

    return quantEleitores;
}

void ImprimeCandidatos(Chapa *chapas, int quant){
    for(int i = 0; i < quant; i++){
        printf("%s | %d | %s\n", chapas[i].nome, chapas[i].numero, chapas[i].nomeVice);
    }
}

void atribuirVoto(Chapa *chapas, int voto, int *votosBrancos, int *votosNulos, int quant){
    
    if(voto == 0){
        (*votosBrancos)++;
        printf("\nSeu voto em branco foi confirmado!");
        return;
    }

    int inicio = 0, meio, final = quant-1;

    while (inicio <= final){
        meio = (inicio + final)/2;
        if(voto > chapas[meio].numero){
            inicio = meio + 1;
        }
        else if(voto < chapas[meio].numero){
            final = meio - 1;
        }
        else{   
            chapas[meio].quantidadeVotos++;
            printf("\nSeu voto em %s com vice %s foi confirmado!", chapas[meio].nome, chapas[meio].nomeVice);
            return;
        }
    }

    (*votosNulos)++;
    printf("\nSeu voto nulo foi confirmado!");
}

void boletimDeUrna(FILE *boletim, Chapa *chapas, int *votosBrancos, int *votosNulos, int *votosValidos, int *votosTotais, int quant){

    for(int i = 0; i < quant; i++){
        (*votosValidos) += chapas[i].quantidadeVotos;
        fprintf(boletim, "Numero de votos no candidato %s: %d\n", chapas[i].nome, chapas[i].quantidadeVotos);
    }

    (*votosTotais) = (*votosBrancos) + (*votosNulos) + (*votosValidos);
    fprintf(boletim, "\nNumero de votos validos: %d\n", (*votosValidos));
    fprintf(boletim, "Numero de votos brancos: %d\n", (*votosBrancos));
    fprintf(boletim, "Numero de votos nulos: %d\n",  (*votosNulos));
    fprintf(boletim, "Numero de votos Totais: %d\n\n", (*votosTotais));

    porcentagemVotos(boletim, chapas, votosBrancos, votosNulos, votosValidos, votosTotais, quant);

}

void porcentagemVotos(FILE *boletim, Chapa *chapas, int *votosBrancos, int *votosNulos, int *votosValidos, int *votosTotais, int quant){

    fprintf(boletim,"Porcentagem de votos dos VOTOS TOTAIS\n");
    for(int i = 0; i < quant; i++){
        fprintf(boletim, "Porcentagem para o candidato %s: %.2f%%\n", chapas[i].nome, chapas[i].quantidadeVotos*100.0/(*votosTotais));
    }

    fprintf(boletim,"\nPorcentagem votos validos: %.2f%%\n", (*votosValidos)*100.0/(*votosTotais));
    fprintf(boletim,"Porcentagem votos brancos: %.2f%%\n", (*votosBrancos)*100.0/(*votosTotais));
    fprintf(boletim,"Porcentagem votos nulos: %.2f%%\n", (*votosNulos)*100.0/(*votosTotais));
    fprintf(boletim, "Porcentagem votos Totais: 100%%\n");

    fprintf(boletim,"\nPorcentagem de votos dos VOTOS VALIDOS\n");
    for(int i = 0; i < quant; i++){
        fprintf(boletim, "Porcentagem para o candidato %s: %.2f%%\n", chapas[i].nome, chapas[i].quantidadeVotos*100.0/(*votosValidos));
    }
}

int verificaSegundoTurno(FILE *boletim, Chapa *chapas, int *votosValidos){
    if(chapas[quantChapas-1].quantidadeVotos*100/(*votosValidos) < 50.0){
        segundoTurno = 1;
        return 1;
    }
    limparTerminal();
    fprintf(boletim, "\n\nO prefeito eleito e %s com o vice %s", chapas[quantChapas-1].nome, chapas[quantChapas-1].nomeVice);
    printf("\n\nO prefeito eleito e %s com o vice %s\n", chapas[quantChapas-1].nome, chapas[quantChapas-1].nomeVice);
    return 0;
}

Chapa *candidatosSegundoTurno(FILE *boletim, Chapa *chapas, Chapa *chapas2Turno){
    int maiorVoto = chapas[quantChapas-1].quantidadeVotos;
    int contagemEmpate = 0;
    Chapa candidatosEmpatados[quantChapas];

    chapas2Turno = (Chapa *) malloc(2 * sizeof(Chapa));

    for (int i = quantChapas-2; chapas[i].quantidadeVotos == maiorVoto; i--) {
        candidatosEmpatados[contagemEmpate++] = chapas[i];
    }

    if(contagemEmpate <= 1){
        printf("\nSegundo turno com os candidatos %s e %s\n", chapas[quantChapas-1].nome, chapas[quantChapas-2].nome);
        fprintf(boletim, "\nSegundo turno com os candidatos %s e %s\n", chapas[quantChapas-1].nome, chapas[quantChapas-2].nome);
        chapas2Turno[0] = chapas[quantChapas-1];
        chapas2Turno[1] = chapas[quantChapas-2];
    }
    else{
        Chapa maisVelho = candidatosEmpatados[0];
        Chapa segundoMaisVelho = candidatosEmpatados[1];

        for (int i = 1; i < contagemEmpate; i++) {
            if (comparaIdade(candidatosEmpatados[i].dataNascimento, maisVelho.dataNascimento)) {
                segundoMaisVelho = maisVelho;
                maisVelho = candidatosEmpatados[i];
            } 
            else if (comparaIdade(candidatosEmpatados[i].dataNascimento, segundoMaisVelho.dataNascimento)) {
                segundoMaisVelho = candidatosEmpatados[i];
            }
        }

        printf("\nSegundo turno com os candidatos %s e %s\n", maisVelho.nome, segundoMaisVelho.nome);
        fprintf(boletim, "\nSegundo turno com os candidatos %s e %s\n", maisVelho.nome, segundoMaisVelho.nome);
        chapas2Turno[0] = maisVelho;
        chapas2Turno[1] = segundoMaisVelho;
    }

    chapas2Turno[0].quantidadeVotos = 0;
    chapas2Turno[1].quantidadeVotos = 0;
    return chapas2Turno;
}

void defineCandidatoEleito(FILE *boletim2Turno, Chapa *chapas2Turno, int *votosValidos){
    if(chapas2Turno[1].quantidadeVotos*100/(*votosValidos) > 50.0){
        fprintf(boletim2Turno, "\n\nO prefeito eleito e %s com o vice %s", chapas2Turno[1].nome, chapas2Turno[1].nomeVice);
        printf("O prefeito eleito e %s com o vice %s\n", chapas2Turno[1].nome, chapas2Turno[1].nomeVice);
    }
    else{
        if(comparaIdade(chapas2Turno[0].dataNascimento, chapas2Turno[1].dataNascimento)){
            fprintf(boletim2Turno, "\n\nO prefeito eleito e %s com o vice %s", chapas2Turno[0].nome, chapas2Turno[0].nomeVice);
            printf("O prefeito eleito e %s com o vice %s\n", chapas2Turno[0].nome, chapas2Turno[0].nomeVice);
        }
        else{
            fprintf(boletim2Turno, "\n\nO prefeito eleito e %s com o vice %s", chapas2Turno[1].nome, chapas2Turno[1].nomeVice);
            printf("O prefeito eleito e %s com o vice %s\n", chapas2Turno[1].nome, chapas2Turno[1].nomeVice);
        }
    }
}

void quickSort(Chapa *chapas, int inicio, int fim, int (*criterio)(struct chapa, struct chapa)){
    if(inicio < fim){
        int pivo = particao(chapas, inicio, fim, criterio);
        quickSort(chapas, inicio, pivo-1, criterio);
        quickSort(chapas, pivo+1, fim, criterio);
    }
}

int particao(Chapa *chapas, int inicio, int fim, int (*criterio)(Chapa, Chapa)){
    int pivo_indice = (rand() % (fim-inicio+1)) + inicio;
    trocar(&chapas[fim], &chapas[pivo_indice]);

    Chapa pivo = chapas[fim];
    int indice = inicio;

    for(int i = inicio; i < fim; i++){
        if(criterio(chapas[i], pivo) <= 0){
            trocar(&chapas[i], &chapas[indice]);
            indice++;
        }
    }
    trocar(&chapas[fim], &chapas[indice]);

    return indice;
}

void trocar(Chapa *a, Chapa *b){
    Chapa temp = *a;
    *a = *b;
    *b = temp;
}

int criterioNumero(Chapa a, Chapa b){
    return a.numero - b.numero;
}


int criterioQuantidadeVotos(Chapa a, Chapa b){
    return a.quantidadeVotos - b.quantidadeVotos;
}