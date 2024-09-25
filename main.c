#include <stdio.h>
#include <stdlib.h>
#include "funcoes.c"

int main(){
    FILE *boletim1Turno = fopen("Boletim1ºTurno.txt", "w");

    int votosBrancos = 0, votosNulos = 0, votosValidos = 0, votosTotais = 0;
    int quantChapas = quantidadeChapas();

    Chapa *chapas = (Chapa *) malloc(quantChapas * sizeof(Chapa));
    if(chapas == NULL){
        perror("Erro alocacao de memoria");
        exit(1);
    }

    chapas = registrarChapas(chapas); 

    quickSort(chapas, 0, quantChapas-1, criterioNumero);

    votacao(chapas, &votosBrancos, &votosNulos, quantChapas);

    boletimDeUrna(boletim1Turno, chapas, &votosBrancos, &votosNulos, &votosValidos, &votosTotais, quantChapas);

    quickSort(chapas, 0, quantChapas-1, criterioQuantidadeVotos);

    if(verificaSegundoTurno(boletim1Turno, chapas, &votosValidos)){
        printf("Havera Segundo Turno");

        votosBrancos = votosNulos = votosValidos = votosTotais = 0;

        FILE *boletim2Turno = fopen("Boletim2ºTurno.txt", "w");

        Chapa *chapas2Turno = (Chapa *) malloc(2 * sizeof(Chapa));
        chapas2Turno = candidatosSegundoTurno(boletim1Turno, chapas, chapas2Turno);

        quickSort(chapas, 0, 1, criterioNumero);
        
        votacao(chapas, &votosBrancos, &votosNulos, 2);

        boletimDeUrna(boletim1Turno, chapas, &votosBrancos, &votosNulos, &votosValidos, &votosTotais, 2);

        quickSort(chapas, 0, 1, criterioQuantidadeVotos);

        defineCandidatoEleito(boletim2Turno, chapas2Turno);

        free(chapas2Turno);
        fclose(boletim2Turno);
    }

    free(chapas);
    fclose(boletim1Turno);

    return 0;
}