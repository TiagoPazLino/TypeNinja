#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

FILE *arquivo = NULL;

int tarefa = 0;

int TamanhoPalavra(char string[]){
    int contagem = 0;
    while (string[contagem]!= NULL){
        ++contagem;
    }
    return contagem;
}

void abre_arquivo(char *palavra[], int aleatorio){
    char letra;
    char *tipo;
    switch(tarefa){
        case 0:
            tipo = "a+";
        case 1:
            tipo = "a+";
            break;
        case 2:
            tipo = "r";
            break;
    }
    if (aleatorio == 1)
        letra = (rand()%28) + 65;
    else
        letra = toupper(palavra[0]);
    switch (letra) {
    case 'A':
        arquivo = fopen("./Palavras/A.txt", tipo);
        break;
    case 'B':
        arquivo = fopen("./Palavras/B.txt", tipo);
        break;
    case 'C':
        arquivo = fopen("./Palavras/C.txt", tipo);
        break;
    case 'D':
        arquivo = fopen("./Palavras/D.txt", tipo);
        break;
    case 'E':
        arquivo = fopen("./Palavras/E.txt", tipo);
        break;
    case 'F':
        arquivo = fopen("./Palavras/F.txt", tipo);
        break;
    case 'G':
        arquivo = fopen("./Palavras/G.txt", tipo);
        break;
    case 'H':
        arquivo = fopen("./Palavras/H.txt", tipo);
        break;
    case 'I':
        arquivo = fopen("./Palavras/I.txt", tipo);
        break;
    case 'J':
        arquivo = fopen("./Palavras/J.txt", tipo);
        break;
    case 'K':
        arquivo = fopen("./Palavras/K.txt", tipo);
        break;
    case 'L':
        arquivo = fopen("./Palavras/L.txt", tipo);
        break;
    case 'M':
        arquivo = fopen("./Palavras/M.txt", tipo);
        break;
    case 'N':
        arquivo = fopen("./Palavras/N.txt", tipo);
        break;
    case 'O':
        arquivo = fopen("./Palavras/O.txt", tipo);
        break;
    case 'P':
        arquivo = fopen("./Palavras/P.txt", tipo);
        break;
    case 'Q':
        arquivo = fopen("./Palavras/Q.txt", tipo);
        break;
    case 'R':
        arquivo = fopen("./Palavras/R.txt", tipo);
        break;
    case 'S':
        arquivo = fopen("./Palavras/S.txt", tipo);
        break;
    case 'T':
        arquivo = fopen("./Palavras/T.txt", tipo);
        break;
    case 'U':
        arquivo = fopen("./Palavras/U.txt", tipo);
        break;
    case 'V':
        arquivo = fopen("./Palavras/V.txt", tipo);
        break;
    case 'W':
        arquivo = fopen("./Palavras/W.txt", tipo);
        break;
    case 'X':
        arquivo = fopen("./Palavras/X.txt", tipo);
        break;
    case 'Y':
        arquivo = fopen("./Palavras/Y.txt", tipo);
        break;
    case 'Z':
        arquivo = fopen("./Palavras/Z.txt", tipo);
        break;
    default:
        arquivo = fopen("./Palavras/Desconhecido.txt", tipo);
        break;
    }
}

void escreve(char *palavra[]){
    abre_arquivo(palavra,0);
    if (arquivo != NULL){
        if(procura(palavra) == 0){
            fprintf(arquivo, "%s\n", strupr(palavra));
            fclose(arquivo);
            printf("Palavra gravada com sucesso !!!");
        }else{
            printf("Essa palavra já está nos arquivos !!! \n");
        }
    }else{
        printf("Nao foi possivel abrir o arquivo");
    }
}

int procura(char *palavra[]){
    abre_arquivo(palavra,0);
    if (arquivo != NULL){
        long tamanho;
        fseek(arquivo, 0, SEEK_END);
        tamanho = ftell(arquivo);
        fseek(arquivo, 0, SEEK_SET);
        char lendo[tamanho];
        while(fread(lendo, tamanho,1, arquivo) != EOF){
            if (strstr(lendo,strupr(palavra)) != NULL){
                fclose(arquivo);
                return 1;
            }
        if(lendo == EOF)
            fclose(arquivo);
        return 0;
        }
    }else{
        printf("Nao foi possivel abrir o arquivo");
    }
}

char* sorteio_aleatorio(char *palavra[]){
   abre_arquivo(palavra, 1);
   srand(time(NULL));
   if(arquivo != NULL){
        char carac;
        int linhas = 0,i;
        while((carac = fgetc(arquivo)) != EOF){
           if(carac == '\n')
               linhas++;
        }
        long tamanho;
        fseek(arquivo, 0, SEEK_END);
        tamanho = ftell(arquivo);
        fseek(arquivo, 0, SEEK_SET);
        char *aleatorio;
        int s = rand()%linhas;
        for (i=0; i<=s; i++){
            fscanf(arquivo, "%s\n", aleatorio);
        }
        return aleatorio;
        fflush(stdin);
        fclose(arquivo);
   }else{
        printf("Nao foi possivel abrir o arquivo");
   }
}

int main(){
    setlocale(LC_ALL,"Portuguese");
    srand(time(NULL));
    char palavra[100];
    char *aleatorio;
    int result = 0, loop = 0;
    while (loop == 0){
        printf("Escolha o que quer:\n0 : inserir\n1 : ler\n2 : Palavra aleatória\n");
        scanf("%d", &tarefa);
        fflush(stdin);
        switch(tarefa){
        case 0:
            printf("Digite a palavra a ser incluída no arquivo: \n");
            scanf ("%[^\n]", palavra);
            fflush(stdin);
            escreve(palavra);
            break;
        case 1:
            printf("Digite a palavra que deseja procurar: \n");
            scanf ("%[^\n]", palavra);
            fflush(stdin);
            result = procura(palavra);
            if (result != 0)
                printf("Essa palavra existe nos arquivos !!!\n");
            else
                printf("Essa palavra não existe nos arquivos !!!\n");
            break;
        case 2:
            aleatorio = sorteio_aleatorio(palavra);
            printf("%s\n", aleatorio);
            int pontos = TamanhoPalavra(aleatorio)*10;
            printf("Essa palavra tem %d pontos\n", pontos);
            break;
        }
        printf("\nDeseja Continuar ?\n0 - SIM\n1 - NÃO\n");
        scanf("%d", &loop);
        system("cls");
        fflush(stdin);
    }

    system("pause");
    return 0;
}
