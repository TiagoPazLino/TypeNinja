#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <SDL_ttf.h>

FILE *arquivo = NULL;

int modo = 0;
int ponto = 0;
char escrever[100];
char acento[];
char letra[];
int frameinimigo = 0;
char pontoss[];
int conta = 0;
int frameplay = 0;
char textodigitado[100];
int framebg = 0;
int framelua = 0;

typedef struct{
    SDL_Texture *imagem;
    SDL_Rect sprite;
    SDL_Rect posicao;
    int largura, altura, larguraTextura, AlturaTextura;
    int vel;
}Elemento;

Elemento btnJogar;
Elemento btnNivel;
Elemento btnConfig;
Elemento btnCreditos;
Elemento btnSair;
Elemento btnAdd;
Elemento Metal;
Elemento Ninja;
Elemento btnVoltar;
Elemento Lua;
Elemento creditos;
Elemento apresentacao;

typedef struct{
    Mix_Chunk *audio;
}Audio;

Audio errado;
Audio fundo;
Audio bop;
Audio certo;
Audio efeito;

typedef struct{
    SDL_Color cor;
    SDL_Color fundo;
    TTF_Font *fonte;
    SDL_Texture *texto;
    SDL_Rect tamanho;
    char *palavra;
    int altura, largura, larguraTextura, AlturaTextura;
}Texto;

Texto texto;
Texto menu;
Texto acaba;
Texto pontos;
Texto escolha;
Texto existe;
Texto digitado;
Texto digitado2;

Elemento inimigo;
Elemento jogador;
Elemento bg01;
Elemento bgadd;
Elemento bg02;

SDL_Texture *bgmenu;
SDL_Window *janela;
SDL_Event evento;
SDL_Renderer *render;

int loop;

int TamanhoPalavra(char string[]){
    int contagem = 0;
    while (string[contagem]!= NULL){
        ++contagem;
    }
    return contagem;
}

void abre_arquivo(char *palavra, int aleatorio){
    srand(time(NULL));
    char letra;
    char *tipo;
    tipo = "a+";
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

SDL_Texture* Carrega_Textura(char* caminho, SDL_Renderer* render){
    SDL_Texture *textura = NULL;
    SDL_Surface *superficie;
    superficie = IMG_Load(caminho);
    if (caminho != NULL){
        SDL_SetColorKey(superficie, SDL_TRUE, SDL_MapRGB(superficie->format,255,255,255));
        textura = SDL_CreateTextureFromSurface(render, superficie);
        if (textura != NULL){
            SDL_FreeSurface(superficie);
            return textura;
        }
        }else{
            printf("Erro ao otimizar imagem !!!\n");
    }
}

int pega_linhas(){
    char carac;
    int linhas = 0;
    while((carac = fgetc(arquivo)) != EOF){
    if(carac == '\n')
           linhas++;
    }
    rewind(arquivo);
    return linhas;
}

char verifica_acento(char letras){
    char letrass;
    if (acento[0] == '^'){
        if (letras == 'a'){
            acento[0] = NULL;
            letrass = 'Â';
        }else if(letras == 'e'){
            acento[0] = NULL;
            letrass = 'Ê';
        }else if(letras == 'o'){
            acento[0] = NULL;
            letrass = 'Ô';
        }else if(letras == 'u'){
            acento[0] = NULL;
            letrass = 'Û';
        }else{
            acento[0] = NULL;
            letrass = strupr(letras);
        }
    }else if(acento[0] == '~'){
         if (letras == 'a'){
            acento[0] = NULL;
            letrass = 'Ã';
        }else if(letras == 'o'){
            acento[0] = NULL;
            letrass = 'Õ';
        }else{
            acento[0] = NULL;
            letrass = strupr(&letras);
        }
    }else if(acento[0] == '´'){
        if (letras == 'a'){
            acento[0] = NULL;
            letrass = 'Á';
        }else if(letras == 'e'){
            acento[0] = NULL;
            letrass = 'É';
        }else if(letras == 'i'){
            acento[0] = NULL;
            letrass = 'Í';
        }else if(letras == 'o'){
             acento[0] = NULL;
            letrass = 'Ó';
        }else if(letras == 'u'){
             acento[0] = NULL;
            letrass = 'Ú';
        }else{
            acento[0] = NULL;
            letrass = strupr(letras);
        }
    }else if(letras == 'ç'){
        acento[0] = NULL;
        letrass = 'Ç';
    }else if(letras == NULL){
        letrass = NULL;
    }else{
        acento[0] = NULL;
        letrass = toupper(letras);
    }
    return letrass;
}

char* sorteio_aleatorio(char *palavra[]){
   abre_arquivo(palavra, 1);
   srand(time(NULL));
   if(arquivo != NULL){
        char carac;
        int linhas = pega_linhas(),i;
        long tamanho;
        fseek(arquivo, 0, SEEK_END);
        tamanho = ftell(arquivo);
        fseek(arquivo, 0, SEEK_SET);
        char *aleatorio[tamanho];
        int s = rand()%linhas;
        for (i=0; i<=s; i++){
              fscanf(arquivo, "%s\n" , aleatorio);
        }
        fclose(arquivo);
        fflush(stdin);
        return aleatorio;
   }else{
        printf("Nao foi possivel abrir o arquivo");
   }
}

void Inicializa_jogador(){
   jogador.imagem = Carrega_Textura("./Imagens/N_01.png",render);
   Metal.imagem = Carrega_Textura("./Imagens/metalgreymon.bmp",render);
   Ninja.imagem = Carrega_Textura("./Imagens/N_02.png",render);

   SDL_QueryTexture(jogador.imagem, NULL, NULL, &(jogador.larguraTextura),&(jogador.AlturaTextura));
   SDL_QueryTexture(Metal.imagem, NULL, NULL, &(Metal.larguraTextura),&(Metal.AlturaTextura));
   SDL_QueryTexture(Ninja.imagem, NULL, NULL, &(Ninja.larguraTextura),&(Ninja.AlturaTextura));

   jogador.altura = jogador.AlturaTextura/2;
   jogador.largura = jogador.larguraTextura/4;
   Metal.altura = Metal.AlturaTextura;
   Metal.largura = Metal.larguraTextura;
   Ninja.altura = Ninja.AlturaTextura;
   Ninja.largura = Ninja.larguraTextura;

   jogador.sprite.x = 0;
   jogador.sprite.y = 0;
   jogador.sprite.h = jogador.altura;
   jogador.sprite.w = jogador.largura;
   Metal.sprite.x = 0;
   Metal.sprite.y = 0;
   Metal.sprite.h = jogador.altura;
   Metal.sprite.w = jogador.largura;
   Ninja.sprite.x = 0;
   Ninja.sprite.y = 0;
   Ninja.sprite.h = jogador.altura;
   Ninja.sprite.w = jogador.largura;

   jogador.posicao.x = 40;
   jogador.posicao.y = 250;
   jogador.posicao.h = jogador.altura*1.5;
   jogador.posicao.w = jogador.largura*1.5;
   Metal.posicao.x = 200;
   Metal.posicao.y = 300;
   Metal.posicao.h = Metal.altura*1.5;
   Metal.posicao.w = Metal.largura*1.5;
   Ninja.posicao.x = 400;
   Ninja.posicao.y = 300;
   Ninja.posicao.h = Ninja.altura*1.5;
   Ninja.posicao.w = Ninja.largura*1.5;

   jogador.vel = 1;
   inicializa_fonte(&(escolha),"./Fontes/Pixel Digivolve.otf", 40, 0, 425, "Escolha um !!!", 0, 1);
}

void inicia_creditos(){
    creditos.imagem = Carrega_Textura("./Imagens/creditos.png", render);
    SDL_QueryTexture(creditos.imagem, NULL, NULL, &(creditos.larguraTextura),&(creditos.AlturaTextura));
    creditos.sprite.x = 0;
    creditos.sprite.y = 0;
    creditos.sprite.h = creditos.AlturaTextura;
    creditos.sprite.w = creditos.larguraTextura;
    creditos.posicao.x = 360 - creditos.larguraTextura/2;
    creditos.posicao.y = 30;
    creditos.posicao.h = creditos.AlturaTextura;
    creditos.posicao.w = creditos.larguraTextura;
}

void libera(){
	SDL_DestroyWindow(janela);
	SDL_DestroyTexture(jogador.imagem);
	SDL_DestroyTexture(btnJogar.imagem);
	SDL_DestroyTexture(btnNivel.imagem);
	SDL_DestroyTexture(btnCreditos.imagem);
	SDL_DestroyTexture(btnSair.imagem);
	SDL_DestroyTexture(escolha.texto);
	SDL_DestroyTexture(texto.texto);
	SDL_DestroyTexture(menu.texto);
	SDL_DestroyTexture(bg01.imagem);
	SDL_DestroyTexture(apresentacao.imagem);
	SDL_DestroyTexture(bgadd.imagem);
	SDL_DestroyTexture(inimigo.imagem);
	SDL_DestroyTexture(Lua.imagem);
	SDL_DestroyTexture(btnVoltar.imagem);
	SDL_DestroyTexture(acaba.texto);
	SDL_DestroyTexture(existe.texto);
	SDL_DestroyTexture(btnAdd.imagem);
	SDL_DestroyTexture(Metal.imagem);
	SDL_DestroyTexture(Ninja.imagem);
	SDL_DestroyTexture(digitado2.texto);
	SDL_DestroyTexture(creditos.imagem);
	SDL_DestroyTexture(digitado.texto);
	SDL_DestroyRenderer(render);
	TTF_CloseFont(texto.fonte);
	TTF_CloseFont(menu.fonte);
	TTF_CloseFont(existe.fonte);
	TTF_CloseFont(digitado.fonte);
	TTF_CloseFont(escolha.fonte);
	TTF_CloseFont(digitado2.fonte);
	TTF_CloseFont(acaba.fonte);
	Mix_FreeChunk(bop.audio);
	Mix_FreeChunk(fundo.audio);
	Mix_FreeChunk(efeito.audio);
	Mix_FreeChunk(certo.audio);
	Mix_FreeChunk(errado.audio);
}

void captura_eventos(){
    if (SDL_PollEvent(&evento)) {
			if (evento.type == SDL_QUIT)
				loop = 0;
			else if (evento.type == SDL_KEYUP && evento.key.keysym.sym == SDLK_ESCAPE)
				loop = 0;
            if (evento.type == SDL_MOUSEBUTTONDOWN){
                if (modo == 0){
                if ((evento.motion.x >= btnJogar.posicao.x && evento.motion.x <= btnJogar.posicao.x + btnJogar.posicao.w) &&
                    (evento.motion.y >= btnJogar.posicao.y && evento.motion.y <= btnJogar.posicao.y + btnJogar.posicao.h)){
                        modo = 3;
                        SDL_StartTextInput();
                        Inicializa_jogador();
                    }
                if ((evento.motion.x >= btnSair.posicao.x && evento.motion.x <= btnSair.posicao.x + btnSair.posicao.w) &&
                    (evento.motion.y >= btnSair.posicao.y && evento.motion.y <= btnSair.posicao.y + btnSair.posicao.h)){
                        loop = 0;
                   }
                if ((evento.motion.x >= btnCreditos.posicao.x && evento.motion.x <= btnCreditos.posicao.x + btnCreditos.posicao.w) &&
                    (evento.motion.y >= btnCreditos.posicao.y && evento.motion.y <= btnCreditos.posicao.y + btnCreditos.posicao.h)){
                        modo = 2;
                   }
                if ((evento.motion.x >= btnAdd.posicao.x && evento.motion.x <= btnAdd.posicao.x + btnAdd.posicao.w) &&
                    (evento.motion.y >= btnAdd.posicao.y && evento.motion.y <= btnAdd.posicao.y + btnAdd.posicao.h)){
                        modo = 4;
                        SDL_StartTextInput();
                 }
               }
                if (modo == 2){
                if ((evento.motion.x >= btnVoltar.posicao.x && evento.motion.x <= btnVoltar.posicao.x + btnVoltar.posicao.w) &&
                    (evento.motion.y >= btnVoltar.posicao.y && evento.motion.y <= btnVoltar.posicao.y + btnVoltar.posicao.h)){
                        modo = 0;
                        Inicializa_jogador();
                   }
                }
                if (modo == 4){
                     if ((evento.motion.x >= btnVoltar.posicao.x && evento.motion.x <= btnVoltar.posicao.x + btnVoltar.posicao.w) &&
                         (evento.motion.y >= btnVoltar.posicao.y && evento.motion.y <= btnVoltar.posicao.y + btnVoltar.posicao.h)){
                        modo = 0;
                        SDL_StopTextInput();
                   }
                }
                if (modo == 3){
                   if ((evento.motion.x >= Metal.posicao.x && evento.motion.x <= Metal.posicao.x + Metal.posicao.w) &&
                        (evento.motion.y >= Metal.posicao.y && evento.motion.y <= Metal.posicao.y + Metal.posicao.h)){
                        jogador.sprite.y = jogador.altura;
                        Mix_HaltChannel(1);
                        jogador.posicao.y = 250;
                        inimigo.sprite.y = inimigo.altura;
                        fundo.audio = Mix_LoadWAV("./Musicas/Butter Fly (16 bit).wav");
                        Mix_PlayChannel(1,fundo.audio,-1);
                        modo = 1;
                   }
                   if ((evento.motion.x >= Ninja.posicao.x && evento.motion.x <= Ninja.posicao.x + Ninja.posicao.w) &&
                        (evento.motion.y >= Ninja.posicao.y && evento.motion.y <= Ninja.posicao.y + Ninja.posicao.h)){
                        jogador.sprite.y = 0;
                        Mix_HaltChannel(1);
                        jogador.posicao.y = 260;
                        inimigo.sprite.y = 0;
                        fundo.audio = Mix_LoadWAV("./Musicas/Chun-nan Day Extended & Ripped by Master Emerald.WAV");
                        Mix_PlayChannel(1,fundo.audio,-1);
                        modo = 1;
                   }
                }
            }
            if (evento.type == SDL_TEXTINPUT){
                if (evento.text.text[0] == 135 || evento.text.text[0] == 128){
                   letra[0] = verifica_acento(evento.text.text[0]);
                }else if(evento.text.text[0] > 'z' || evento.text.text[0] < 'A' || evento.text.text[0] == '^'){
                   strcpy(acento,evento.text.text);
                   letra[0] = NULL;
                }else{
                   letra[0] = verifica_acento(evento.text.text[0]);
                }
                strcat(textodigitado,letra);
                Mix_PlayChannel(0,bop.audio,0);
                if(modo == 1){
                    if (strcmp(escrever, textodigitado) == 0){
                        Mix_PlayChannel(0,certo.audio,0);
                        ponto += TamanhoPalavra(escrever) * 3;
                        itoa(ponto,pontoss,10);
                        if (ponto >= inimigo.vel * 100){
                            inimigo.vel += 1;
                            bg01.vel +=1;
                        }
                        inicializa_fonte(&(pontos), "./Fontes/OCRAEXT.TTF", 30, 200, 50, pontoss, 0, 1);
                        strcpy(textodigitado,"");
                        inicializa_fonte(&(digitado), "./Fontes/OCRAEXT.TTF", 40, 360, 450, textodigitado, 0,1);
                        strcpy(escrever, sorteio_aleatorio(NULL));
                        inicializa_fonte(&(texto), "./Fontes/OCRAEXT.TTF", 50,250,390,escrever,1,1);
                        inimigo.posicao.x = 720;
                    }
                    printf("%s\n", texto.palavra);
                    fflush(stdin);
                    inicializa_fonte(&(digitado), "./Fontes/OCRAEXT.TTF", 40, 360, 450, textodigitado, 0,1);
                    }
                if (modo == 4){
                    inicializa_fonte(&(digitado2), "./Fontes/OCRAEXT.TTF", 40, 360, 240, textodigitado, 0,1);
                }
            }
            if (evento.type == SDL_KEYDOWN){
                    switch(evento.key.keysym.sym){
                    case SDLK_0:
                        switch (modo){
                        case 0:
                            modo = 1;
                            SDL_StartTextInput();
                            break;
                        case 1:
                            modo = 0;
                            SDL_StopTextInput();
                            break;
                        case 2:
                            modo = 0;
                        }
                        break;
                    case SDLK_BACKSPACE:
                        textodigitado[(strlen(textodigitado)-1)] = NULL;
                        if (modo == 1){
                           inicializa_fonte(&(digitado), "./Fontes/OCRAEXT.TTF", 40, 360, 450, textodigitado, 0,1);
                        }
                        if (modo == 4){
                           inicializa_fonte(&(digitado2), "./Fontes/OCRAEXT.TTF", 40, 360, 240, textodigitado, 0,1);
                        }
                        break;
                    case SDLK_RETURN:
                        if (modo == 3){
                            modo = 1;
                        }
                        if (modo == 4){
                            escreve(textodigitado);
                            Mix_PlayChannel(0, certo.audio, 0);
                            strcpy(textodigitado,"");
                            inicializa_fonte(&(digitado2), "./Fontes/OCRAEXT.TTF", 40, 360, 240, textodigitado, 0,1);
                        }
                    }
                }
        }
    }

void escreve(char *palavra[]){
    abre_arquivo(palavra,0);
    if (arquivo != NULL){
        if(procura(palavra) == 0){
            fprintf(arquivo, "%s\n", strupr(palavra));
            fclose(arquivo);
            inicializa_fonte(&(existe), "./Fontes/OCRAEXT.TTF", 40, 0, 350, "Sucesso !!", 0, 1);
        }else{
            inicializa_fonte(&(existe), "./Fontes/OCRAEXT.TTF", 40, 0, 350, "Essa palavra já existe !!", 0, 1);
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

void atualiza_janela(){
    SDL_RenderClear(render);
    switch (modo){
    case 0:
        SDL_RenderCopy(render, bgmenu, NULL, NULL);
        SDL_RenderCopy(render, menu.texto, NULL, &(menu.tamanho));
        SDL_RenderCopy(render, btnJogar.imagem, &(btnJogar.sprite), &(btnJogar.posicao));
        SDL_RenderCopy(render, btnConfig.imagem, &(btnConfig.sprite), &(btnConfig.posicao));
        SDL_RenderCopy(render, btnNivel.imagem, &(btnNivel.sprite), &(btnNivel.posicao));
        SDL_RenderCopy(render, btnCreditos.imagem, &(btnCreditos.sprite), &(btnCreditos.posicao));
        SDL_RenderCopy(render, btnSair.imagem, &(btnSair.sprite), &(btnSair.posicao));
        SDL_RenderCopy(render, btnAdd.imagem, &(btnAdd.sprite), &(btnAdd.posicao));
        break;
    case 1:
        SDL_RenderCopy(render, bg02.imagem, &(bg02.sprite),&(bg02.posicao));
        SDL_RenderCopy(render, Lua.imagem, &(Lua.sprite),&(Lua.posicao));
        SDL_RenderCopy(render, bg01.imagem, &(bg01.sprite),&(bg01.posicao));
        SDL_RenderCopy(render, texto.texto, NULL, &(texto.tamanho));
        SDL_RenderCopy(render, inimigo.imagem, &(inimigo.sprite), &(inimigo.posicao));
        SDL_RenderCopy(render, jogador.imagem, &(jogador.sprite), &(jogador.posicao));
        SDL_RenderCopy(render, digitado.texto, NULL, &(digitado.tamanho));
        SDL_RenderCopy(render,pontos.texto, NULL, &(pontos.tamanho));
        break;
    case 2:
        SDL_RenderCopy(render, bg02.imagem, &(bg02.sprite),&(bg02.posicao));
        SDL_RenderCopy(render, Lua.imagem, &(Lua.sprite),&(Lua.posicao));
        SDL_RenderCopy(render, creditos.imagem, &(creditos.sprite), &(creditos.posicao));
        SDL_RenderCopy(render, bg01.imagem, &(bg01.sprite),&(bg01.posicao));
        SDL_RenderCopy(render, jogador.imagem, &(jogador.sprite),&(jogador.posicao));
        SDL_RenderCopy(render, btnVoltar.imagem, &(btnVoltar.sprite),&(btnVoltar.posicao));
        break;
    case 3:
        SDL_RenderCopy(render, bg02.imagem, &(bg02.sprite),&(bg02.posicao));
        SDL_RenderCopy(render, apresentacao.imagem, &(apresentacao.sprite),&(apresentacao.posicao));
        SDL_RenderCopy(render, Metal.imagem, &(Metal.sprite),&(Metal.posicao));
        SDL_RenderCopy(render, Ninja.imagem, &(Ninja.sprite),&(Ninja.posicao));
        SDL_RenderCopy(render, escolha.texto, NULL,&(escolha.tamanho));
        break;
    case 4:
        SDL_RenderCopy(render, bgadd.imagem, &(bgadd.sprite),&(bgadd.posicao));
        SDL_RenderCopy(render, digitado2.texto, NULL, &(digitado2.tamanho));
        SDL_RenderCopy(render, btnVoltar.imagem, &(btnVoltar.sprite),&(btnVoltar.posicao));
        SDL_RenderCopy(render, existe.texto, NULL, &(existe.tamanho));
    }
    SDL_RenderPresent(render);
}

TTF_Font* abrir_fonte(char* caminho, int tamanho){
    return TTF_OpenFont(caminho, tamanho);
}

void inicializa_fonte(Texto *coisa, char *caminho[], int tamanho,int x, int y, char *isso,int aleatorio,int centralizado){
    coisa->fundo.r = 255;
    coisa->fundo.g = 0;
    coisa->fundo.b = 0;
    coisa->fundo.a = 0;
    coisa->fonte = abrir_fonte(caminho, tamanho);
    fflush(stdin);
    fflush(stdout);
    SDL_Surface *SupTexto = NULL;
   if (aleatorio == 1){
        strcpy(escrever,sorteio_aleatorio(NULL));
        SupTexto = TTF_RenderText_Solid(coisa->fonte, escrever, coisa->fundo);
        printf("%s\n", escrever);
    }else{
        SupTexto = TTF_RenderText_Solid(coisa->fonte, isso, coisa->fundo);
    }
    coisa->texto = SDL_CreateTextureFromSurface(render,SupTexto);
    SDL_FreeSurface(SupTexto);
    SDL_QueryTexture(coisa->texto, NULL, NULL, &(coisa->tamanho.w), &(coisa->tamanho.h));
    if (centralizado == 1){
        coisa->tamanho.x = 360 - coisa->tamanho.w/2;
        coisa->tamanho.y = y;
    }else{
        coisa->tamanho.x = x;
        coisa->tamanho.y = y;
    }
}

void inicia_menu(){
    btnVoltar.imagem = Carrega_Textura("./Imagens/voltar.bmp", render);
    bgmenu = Carrega_Textura("./Imagens/fundo_azul.jpg", render);
    btnCreditos.imagem = Carrega_Textura("./Imagens/Creditos.bmp",render);
    btnConfig.imagem = Carrega_Textura("./Imagens/config.bmp",render);
    btnJogar.imagem = Carrega_Textura("./Imagens/Play.bmp",render);
    btnAdd.imagem = Carrega_Textura("./Imagens/add.bmp", render);
    btnNivel.imagem = Carrega_Textura("./Imagens/Nivel.bmp",render);
    btnSair.imagem = Carrega_Textura("./Imagens/Sair.bmp",render);

    SDL_QueryTexture(btnJogar.imagem, NULL, NULL, &(btnJogar.larguraTextura),&(btnJogar.AlturaTextura));
    SDL_QueryTexture(btnVoltar.imagem, NULL, NULL, &(btnVoltar.larguraTextura),&(btnVoltar.AlturaTextura));
    SDL_QueryTexture(btnConfig.imagem, NULL, NULL, &(btnConfig.larguraTextura),&(btnConfig.AlturaTextura));
    SDL_QueryTexture(btnAdd.imagem, NULL, NULL, &(btnAdd.larguraTextura),&(btnAdd.AlturaTextura));
    SDL_QueryTexture(btnCreditos.imagem, NULL, NULL, &(btnCreditos.larguraTextura),&(btnCreditos.AlturaTextura));
    SDL_QueryTexture(btnNivel.imagem, NULL, NULL, &(btnNivel.larguraTextura),&(btnNivel.AlturaTextura));
    SDL_QueryTexture(btnSair.imagem, NULL, NULL, &(btnSair.larguraTextura),&(btnSair.AlturaTextura));

    btnJogar.sprite.x = 0;
    btnAdd.sprite.x = 0;
    btnVoltar.sprite.x = 0;
    btnConfig.sprite.x = 0;
    btnNivel.sprite.x = 0;
    btnCreditos.sprite.x = 0;
    btnSair.sprite.x = 0;
    btnJogar.sprite.y = 0;
    btnAdd.sprite.y = 0;
    btnVoltar.sprite.y = 0;
    btnConfig.sprite.y = 0;
    btnNivel.sprite.y = 0;
    btnCreditos.sprite.y = 0;
    btnSair.sprite.y = 0;

    btnJogar.sprite.h = btnJogar.AlturaTextura;
    btnJogar.sprite.w = btnJogar.larguraTextura;
    btnVoltar.sprite.h = btnJogar.AlturaTextura;
    btnVoltar.sprite.w = btnJogar.larguraTextura;
    btnAdd.sprite.h = btnAdd.AlturaTextura;
    btnAdd.sprite.w = btnAdd.larguraTextura;
    btnConfig.sprite.h = btnConfig.AlturaTextura;
    btnConfig.sprite.w = btnConfig.larguraTextura;
    btnNivel.sprite.h = btnNivel.AlturaTextura;
    btnNivel.sprite.w = btnNivel.larguraTextura;
    btnCreditos.sprite.h = btnCreditos.AlturaTextura;
    btnCreditos.sprite.w = btnCreditos.larguraTextura;
    btnSair.sprite.h = btnSair.AlturaTextura;
    btnSair.sprite.w = btnSair.larguraTextura;

    btnJogar.posicao.x = 62;
    btnJogar.posicao.y = 350;
    btnAdd.posicao.x = 640;
    btnAdd.posicao.y = 20;
    btnConfig.posicao.x = 187;
    btnConfig.posicao.y = 350;
    btnCreditos.posicao.x = 312;
    btnCreditos.posicao.y = 350;
    btnNivel.posicao.x = 437;
    btnNivel.posicao.y = 350;
    btnSair.posicao.x = 562;
    btnSair.posicao.y = 350;
    btnVoltar.posicao.x = 600;
    btnVoltar.posicao.y = 400;

    btnJogar.posicao.h = btnJogar.AlturaTextura;
    btnJogar.posicao.w = btnJogar.larguraTextura;
    btnAdd.posicao.h = btnAdd.AlturaTextura/2;
    btnAdd.posicao.w = btnAdd.larguraTextura/2;
    btnVoltar.posicao.h = btnVoltar.AlturaTextura;
    btnVoltar.posicao.w = btnVoltar.larguraTextura;
    btnConfig.posicao.h = btnConfig.AlturaTextura;
    btnConfig.posicao.w = btnConfig.larguraTextura;
    btnNivel.posicao.h = btnNivel.AlturaTextura;
    btnNivel.posicao.w = btnNivel.larguraTextura;
    btnCreditos.posicao.h = btnCreditos.AlturaTextura;
    btnCreditos.posicao.w = btnCreditos.larguraTextura;
    btnSair.posicao.h = btnSair.AlturaTextura;
    btnSair.posicao.w = btnSair.larguraTextura;

    inicializa_fonte(&(menu), "./Fontes/Raiderz.ttf", 120, 80,150,"Type Fight",0,1);
}

void inicia_bgadd(){
    bgadd.imagem = Carrega_Textura("./Imagens/add_palavra.png", render);
    SDL_QueryTexture(bgadd.imagem, NULL, NULL, &(bgadd.larguraTextura),&(bgadd.AlturaTextura));
    bgadd.sprite.x = 0;
    bgadd.sprite.y = 0;
    bgadd.sprite.w = bgadd.larguraTextura;
    bgadd.sprite.h = bgadd.AlturaTextura;
    bgadd.posicao.x = 0;
    bgadd.posicao.y = 0;
    bgadd.posicao.h = bgadd.AlturaTextura;
    bgadd.posicao.w = bgadd.larguraTextura;
}

void inicia_apresentacao(){
    apresentacao.imagem = Carrega_Textura("./Imagens/informacoes.bmp", render);
    SDL_QueryTexture(apresentacao.imagem, NULL, NULL, &(apresentacao.larguraTextura),&(apresentacao.AlturaTextura));
    apresentacao.sprite.x = 0;
    apresentacao.sprite.y = 0;
    apresentacao.sprite.w = apresentacao.larguraTextura;
    apresentacao.sprite.h = apresentacao.AlturaTextura;
    apresentacao.posicao.x = 360 - apresentacao.larguraTextura/2;
    apresentacao.posicao.y = apresentacao.AlturaTextura/2;
    apresentacao.posicao.h = apresentacao.AlturaTextura;
    apresentacao.posicao.w = apresentacao.larguraTextura;
}

void Inicializa_SDL(){
   SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
   int imgflag = IMG_INIT_JPG|IMG_INIT_PNG;
   IMG_Init(imgflag);
   TTF_Init();
   Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
   fundo.audio = Mix_LoadWAV("./Musicas/Chun-nan Day Extended & Ripped by Master Emerald.WAV");
   efeito.audio = Mix_LoadWAV("./Musicas/4512__noisecollector__dragon8.wav");
   errado.audio = Mix_LoadWAV("./Musicas/errado.wav");
   certo.audio = Mix_LoadWAV("./Musicas/certo.wav");
   bop.audio = Mix_LoadWAV("./Musicas/bop.wav");
   janela = SDL_CreateWindow("Type Fight", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 540, SDL_WINDOW_SHOWN);
   render = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void inicia_bg(){
    bg01.imagem = Carrega_Textura("./Imagens/arvores.png",render);
    bg02.imagem = Carrega_Textura("./Imagens/estrelas.png",render);
    SDL_QueryTexture(bg01.imagem, NULL, NULL, &(bg01.larguraTextura),&(bg01.AlturaTextura));
    SDL_QueryTexture(bg02.imagem, NULL, NULL, &(bg02.larguraTextura),&(bg02.AlturaTextura));
    bg01.largura = 720;
    bg02.largura = 720;
    bg01.vel = 3;
    bg01.sprite.x = 0;
    bg01.sprite.y = 0;
    bg01.sprite.w = bg01.largura;
    bg01.sprite.h = bg01.AlturaTextura;
    bg02.sprite.x = 0;
    bg02.sprite.y = 0;
    bg02.sprite.w = bg02.largura;
    bg02.sprite.h = bg02.AlturaTextura;
    bg01.posicao.x = 0;
    bg01.posicao.y = 0;
    bg01.posicao.h = bg01.AlturaTextura;
    bg01.posicao.w = bg01.largura;
    bg02.posicao.x = 0;
    bg02.posicao.y = 0;
    bg02.posicao.h = bg02.AlturaTextura;
    bg02.posicao.w = bg02.largura;
}

void frame_rate(){
    frameplay++;
    frameinimigo++;
    framebg++;
    framelua++;
        if (frameinimigo == 10){
            frameinimigo = 0;
            inimigo.sprite.x += inimigo.largura;
            if (inimigo.sprite.x >= inimigo.larguraTextura - inimigo.largura){
                    inimigo.sprite.x = 0;
            }
        }
        if (frameplay == 5){
            frameplay = 0;
            jogador.sprite.x += jogador.largura;
            if (jogador.sprite.x >= (jogador.larguraTextura)-jogador.largura){
                jogador.sprite.x = 0;
            }
        }
        if (modo == 2){
            jogador.posicao.x += jogador.vel;
            creditos.posicao.y -= 1;
            if (jogador.posicao.x >= 720){
                jogador.posicao.x = -100;
            }
            if (creditos.posicao.y <= -300){
                creditos.posicao.y = 500;
            }
        }
        if (framebg == 2){
            framebg = 0;
            bg01.sprite.x += bg01.vel;
            if (bg01.sprite.x >= bg01.larguraTextura /2){
                bg01.sprite.x = 0;
            }
             if (modo == 1){
                inimigo.posicao.x -= inimigo.vel;
            if (inimigo.posicao.x <= jogador.posicao.x + jogador.largura){
                Mix_PlayChannel(2,errado.audio, 0);
                Lua.sprite.x += Lua.largura;
                if(Lua.sprite.x >= Lua.larguraTextura-Lua.largura){
                    inicializa_fonte(&(acaba), "./Fontes/Fighting Spirit 2 bold.ttf", 40,250,250,"G A M E  O V E R",0,1);
                    SDL_RenderCopy(render, acaba.texto, NULL, &(acaba.tamanho));
                    ponto = 0;
                    strcpy(pontoss, "0");
                    inicializa_fonte(&(pontos), "./Fontes/OCRAEXT.TTF", 30, 200, 50, pontoss, 0, 1);
                    SDL_Delay(3000);
                    modo = 0;
                    inicia_inimigo();
                    inicia_bg();
                    acaba.texto = NULL;
                    Inicia_lua();
                    SDL_StopTextInput();
                }
                strcpy(textodigitado, "");
                inicializa_fonte(&(digitado), "./Fontes/OCRAEXT.TTF", 40, 360, 450, textodigitado, 0,1);
                inicializa_fonte(&(texto), "./Fontes/OCRAEXT.TTF", 50,250,390,NULL,1,1);
                inimigo.posicao.x = 720;
            }
            }
        }
        if (framelua >= 3){
            framelua = 0;
            Lua.posicao.x -= 1;
            if (Lua.posicao.x <= 0){
                Lua.posicao.x = 625;
            }
        }
}

void inicia_inimigo(){
    inimigo.imagem = Carrega_Textura("./Imagens/inimigo.png", render);
    SDL_QueryTexture(inimigo.imagem, NULL, NULL, &(inimigo.larguraTextura), &(inimigo.AlturaTextura));
    inimigo.altura = inimigo.AlturaTextura/2;
    inimigo.largura = inimigo.larguraTextura/4;
    inimigo.sprite.x = 0;
    inimigo.sprite.y = inimigo.altura;
    inimigo.sprite.w = inimigo.largura;
    inimigo.sprite.h = inimigo.altura;
    inimigo.posicao.x = 720;
    inimigo.posicao.y = 270;
    inimigo.posicao.h = inimigo.altura*1.5;
    inimigo.posicao.w = inimigo.altura*1.5;
    inimigo.vel = 1;
}

void Inicia_lua(){
    Lua.imagem = Carrega_Textura("./Imagens/Lua.bmp",render);
    SDL_QueryTexture(Lua.imagem, NULL, NULL, &(Lua.larguraTextura),&(Lua.AlturaTextura));
    Lua.largura = Lua.larguraTextura/5;
    Lua.altura = Lua.AlturaTextura;
    Lua.sprite.x = 0;
    Lua.sprite.y = 0;
    Lua.sprite.h = Lua.altura;
    Lua.sprite.w = Lua.largura;
    Lua.posicao.x = 625;
    Lua.posicao.y = 30;
    Lua.posicao.h = Lua.altura;
    Lua.posicao.w = Lua.largura;
}

int main(int argc, char *argv[])
{
   Inicializa_SDL();
   loop = 1;
   inicia_menu();
   Inicia_lua();
   inicia_inimigo();
   inicia_bg();
   inicia_creditos();
   inicia_apresentacao();
   inicia_bgadd();
   strcpy(escrever, sorteio_aleatorio(NULL));
   strcpy(pontoss, "0");
   inicializa_fonte(&(pontos), "./Fontes/OCRAEXT.TTF", 30, 200, 50, pontoss, 0, 1);
   inicializa_fonte(&(texto), "./Fontes/OCRAEXT.TTF", 50,250,390,escrever,1,1);
   Inicializa_jogador();
   Mix_FadeInChannel(1,fundo.audio, -1, 5000);
   acento[0] = NULL;
   while(loop == 1){
        atualiza_janela();
        if (modo != 0){
            frame_rate();
        }
        captura_eventos();
   }
   libera();

   Mix_Quit();
   IMG_Quit();
   TTF_Quit();
   SDL_Quit();
   return 0;
}
