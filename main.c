#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "funcoes.h"

int main(){
    limparTerminal();

    FILE *boletim1Turno = fopen("Boletim1ºTurno.txt", "w");
    int votosBrancos = 0, votosNulos = 0, votosValidos = 0, votosTotais = 0;
    int quantChapas = quantidadeChapas();
    Chapa *chapas = NULL;

    chapas = registrarChapas(chapas); 

    quickSort(chapas, 0, quantChapas-1, criterioNumero);

    votacao(chapas, &votosBrancos, &votosNulos, quantChapas);

    boletimDeUrna(boletim1Turno, chapas, &votosBrancos, &votosNulos, &votosValidos, &votosTotais, quantChapas);

    quickSort(chapas, 0, quantChapas-1, criterioQuantidadeVotos);

    if(verificaSegundoTurno(boletim1Turno, chapas, &votosValidos)){
        limparTerminal();
        printf("Havera Segundo Turno");

        votosBrancos = votosNulos = votosValidos = votosTotais = 0;

        FILE *boletim2Turno = fopen("Boletim2ºTurno.txt", "w");

        Chapa *chapas2Turno = NULL;
        chapas2Turno = candidatosSegundoTurno(boletim1Turno, chapas, chapas2Turno);
        fflush(stdout);
        sleep(4);

        quickSort(chapas2Turno, 0, 1, criterioNumero);
        
        votacao(chapas2Turno, &votosBrancos, &votosNulos, 2); 

        boletimDeUrna(boletim2Turno, chapas2Turno, &votosBrancos, &votosNulos, &votosValidos, &votosTotais, 2);

        quickSort(chapas2Turno, 0, 1, criterioQuantidadeVotos);

        limparTerminal();
        defineCandidatoEleito(boletim2Turno, chapas2Turno, &votosValidos);

        free(chapas2Turno);
        fclose(boletim2Turno);
    }

    free(chapas);
    fclose(boletim1Turno);

    return 0;
}