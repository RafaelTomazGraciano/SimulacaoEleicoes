# Simulação de Eleições

[![License: Unlicense](https://img.shields.io/badge/license-Unlicense-blue.svg)](LICENSE)
[![C](https://img.shields.io/badge/language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))

Simulação de uma eleição para o cargo de prefeito, desenvolvida como projeto para a disciplina de Estrutura de Dados na [UENP](https://uenp.edu.br/). O sistema permite o cadastro de chapas, realização de votação, apuração dos votos, geração de boletins de urna e verificação de segundo turno, utilizando conceitos fundamentais de estruturas de dados e algoritmos de ordenação.

## Funcionalidades

- Cadastro de chapas (candidato e vice)
- Validação de dados (número da chapa, data de nascimento, etc.)
- Processo de votação com votos válidos, brancos e nulos
- Geração de boletins de urna para 1º e 2º turnos
- Cálculo de porcentagem de votos
- Verificação automática de necessidade de segundo turno
- Ordenação das chapas por número e por quantidade de votos (QuickSort)

## Estrutura do Projeto

```
├── Boletim1ºTurno.txt         # Boletim gerado após o 1º turno
├── Boletim2ºTurno.txt         # Boletim gerado após o 2º turno (se houver)
├── funcoes.c                  # Implementação das funções principais
├── funcoes.h                  # Definições e protótipos das funções
├── main.c                     # Função principal e fluxo do programa
├── makefile                   # Automação da compilação
└── README.md                  # Este arquivo
```

## Como Compilar e Executar

1. **Pré-requisitos:**
	- GCC (compilador C)
	- Ambiente compatível com comandos do makefile

2. **Compilação:**

	Abra o terminal na pasta do projeto e execute:
	```sh
	make
	```

3. **Execução:**

	Após a compilação, execute o programa:
	```sh
	./main
	```

4. **Limpeza dos arquivos objeto:**
	```sh
	make clean
	```

