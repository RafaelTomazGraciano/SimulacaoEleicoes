#include <stdio.h>

typedef struct chapa Chapa;

void limparTerminal();

int quantidadeChapas();

Chapa *registrarChapas(Chapa *chapas);

void corrigeFormatacao(char *str);

void ImprimeCandidatos(Chapa *chapas); 

void votacao(Chapa *chapas, int *votosBrancos, int *votoNulos, int quant);

int quantidadeEleitores();

void atribuirVoto(Chapa *chapas, int voto, int *votosBrancos, int *votosNulos, int quant);

void boletimDeUrna(FILE *boletim, Chapa *chapas, int *votosBrancos, int *votosNulos, int *votosValidos, int *votosTotais, int quant);

void porcentagemVotos(FILE *boletim, Chapa *chapas, int *votosBrancos, int *votosNulos, int *votosValidos, int *votosTotais, int quant);

int verificaSegundoTurno(FILE *boletim1Turno, Chapa *chapas, int *votosValidos);

Chapa *candidatosSegundoTurno(FILE *boletim1Turno, Chapa *chapas, Chapa *chapas2Turno);

int comparaIdade(int data1[3], int data2[3]);

void defineCandidatoEleito(FILE *boletim2Turno, Chapa *chapas2Turno);

void quickSort(Chapa *chapas, int inicio, int fim, int (*criterio)(struct chapa, struct chapa));

int particao(Chapa *chapas, int inicio, int fim, int (*criterio)(struct chapa, struct chapa));

void trocar(Chapa *a, Chapa *b);

int criterioNumero(struct chapa a, struct chapa b);

int criterioQuantidadeVotos(struct chapa a, struct chapa b);

int criterioDataNascimento(Chapa a, Chapa b);
