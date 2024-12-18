#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//definir a estrutura para armazenar informacao de jogador
typedef struct {
    char nome[50];  //nome do jogador
    int vitorias;   //numero de vitorias do jogador
} Jogador;

//Funcao para criar o tabuleiro 3x3
char** criarTabuleiro() {
    char** tabuleiro = (char**)malloc(3 * sizeof(char*));  //Aloca memoria para 3 linhas
    for (int i = 0; i < 3; i++) 
        tabuleiro[i] = (char*)malloc(3 * sizeof(char));  //Aloca memoria para 3 colunas em cada linha

    //inicializa todas as posicoes do tabuleiro com espacos em branco (' ')
    for (int i = 0; i < 3; i++) 
        for (int j = 0; j < 3; j++) 
            tabuleiro[i][j] = ' ';  //posicoes vazias do tabuleiro

    return tabuleiro;  //retorna o tabuleiro criado
}

//funcao para exibir o tabuleiro
void exibirTabuleiro(char** tabuleiro) {

    //imprime o tabuleiro linha por linha
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", tabuleiro[i][j]);  //exibe o valor na posicao (i, j)
            if (j < 2) printf("|");  //imprime separador entre as colunas
        }
        printf("\n");
        if (i < 2) printf("---+---+---\n");  //imprime a linha separadora entre as linhas do tabuleiro
    }
}

//funcao para verificar se algum jogador venceu
int verVencedor(char** tabuleiro, char jogador) {
    //verifica se o jogador fez uma linha - coluna - diagonal completa
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == jogador && tabuleiro[i][1] == jogador && tabuleiro[i][2] == jogador) 
            return 1;
        //verifica colunas
        if (tabuleiro[0][i] == jogador && tabuleiro[1][i] == jogador && tabuleiro[2][i] == jogador) 
            return 1;
    }
    //verifica diagonais
   if (tabuleiro[0][0] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][2] == jogador) 
return 1;
    if (tabuleiro[0][2] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][0] == jogador) 
return 1;
    return 0;
}

//função para verificar se o tabuleiro está cheio (empate)
int tabuleiroCheio(char** tabuleiro) {
    //verifica se todas as posições do tabuleiro estão preenchidas
    for (int i = 0; i < 3; i++) 
        for (int j = 0; j < 3; j++) 
            if (tabuleiro[i][j] == ' ') 
                return 0;  //se houver espaço vazio, retorna 0
    return 1;  //retorna 1 se o tabuleiro estiver cheio
}

//função para a jogada do jogador
void jogarJogador(char** tabuleiro, char jogador) {
    int linha, coluna;
    //solicita ao jogador a posição da linha e coluna onde deseja jogar
    printf("jogador '%c', informe a linha (0-2) e informe a coluna (0-2): ", jogador);
    scanf("%d %d", &linha, &coluna);
    tabuleiro[linha][coluna] = jogador;  //coloca a jogada do jogador no tabuleiro
}

//funcao para a jogada do computador (aleatoria)
void jogarComputador(char** tabuleiro) {
    int linha, coluna;
    //gera números aleatórios para a jogada do computador
    linha = rand() % 3;  //gera uma linha aleatoria entre 0 e 2
    coluna = rand() % 3;  //gera uma coluna aleatoria entre 0 e 2

    //continua tentando ate encontrar uma posicao vazia
    while (tabuleiro[linha][coluna] != ' ') {
        linha = rand() % 3;  //gera uma linha aleatoria entre 0 e 2
        coluna = rand() % 3;  //gera uma coluna aleatoria entre 0 e 2
    }

    tabuleiro[linha][coluna] = 'O';  //coloca a jogada do computador no tabuleiro
}

//função para salvar o ranking do jogador em um arquivo
void salvarRanking(Jogador jogador) {
    FILE* arquivo = fopen("ranking.txt", "a");  //abre o arquivo para adicionar informações
    if (arquivo) {
        fprintf(arquivo, "%s %d\n", jogador.nome, jogador.vitorias);  //salva o nome e vitórias do jogador
        fclose(arquivo);  //fecha o arquivo
    }
}

//função para exibir o ranking
void exibirRanking() {
    FILE* arquivo = fopen("ranking.txt", "r");  //abre o arquivo de ranking para leitura
    if (arquivo) {
        char nome[50];
        int vitorias;
        //le e exibe as vitórias de todos os jogadores registrados no arquivo
        while (fscanf(arquivo, "%s %d", nome, &vitorias) != EOF) {
            printf("%s - %d vitorias\n", nome, vitorias);
        }
        fclose(arquivo);  //fecha o arquivo
    } else {
        printf("Nao possui ranking registrado.\n");  //caso não haja arquivo de ranking
    }
}

//funcao para exibir o menu de opcoes
void mostrarMenu() {
    printf("\nMenu:\n1. Jogar\n2. Ver Ranking\n3. Creditos\n4. Sair\n");
}

//funcao para exibir os creditos
void exibirCreditos() {
    printf("\nDesenvolvido: Leonardo, Heloisa e Ari\n");
}

//funcao principal
int main() {
    Jogador jogador = {"Jogador", 0};  //cria a estrutura do jogador e inicializa o nome e vitorias
    int opcao;
    printf("Digite seu nome: ");
    scanf("%s", jogador.nome);  //Le o nome do jogador

    srand(time(NULL));  //inicializa o gerador de números aleatórios (agora fora do laço de jogo)

    while (1) {
        mostrarMenu();  //exibe o menu de opcoes
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);  //Le a opção escolhida

        switch (opcao) {
            case 1: {
                char** tabuleiro = criarTabuleiro();  //cria o tabuleiro
                int jogoAtivo = 1;
                char jogadorAtual = 'X';  //inicia o jogo com o jogador 'X'

                while (jogoAtivo) {
                    exibirTabuleiro(tabuleiro);  //exibe o tabuleiro atual
                    if (jogadorAtual == 'X') 
                        jogarJogador(tabuleiro, jogadorAtual);  //jogada do jogador
                    else 
                        jogarComputador(tabuleiro);  //jogada do computador

                    if (verVencedor(tabuleiro, jogadorAtual)) {  //verifica se alguem venceu
                        exibirTabuleiro(tabuleiro);
                        printf("Jogador '%c' venceu!\n", jogadorAtual);
                        if (jogadorAtual == 'X') jogador.vitorias++;  //atualiza as vitorias do jogador
                        jogoAtivo = 0;  //termina o jogo
                    } else if (tabuleiroCheio(tabuleiro)) {  //verifica se o tabuleiro esta cheio (empate)
                        exibirTabuleiro(tabuleiro);
                        printf("Empate!\n");
                        jogoAtivo = 0;
                    }

                    jogadorAtual = (jogadorAtual == 'X') ? 'O' : 'X';  //alterna entre os jogadores
                }

                salvarRanking(jogador);  //salva o ranking do jogador
                break;
            }
            case 2: exibirRanking(); 
                break;  //exibe o ranking
            case 3: exibirCreditos(); 
                break;  //exibe os creditos
            case 4: 
                return 0;  //sai do programa
            default: printf("Opcao invalida tente novamente.\n");  //caso a opcao nao seja valida
        }
    }
    return 0;
}
