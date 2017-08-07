#include <stdio.h>
#include <stdlib.h> //biblioteca que chama o system("cls");
#include <conio.h> //uso da função rand

int pontUser, pontPC,contSOS,contSouO;//contadores


int** alocarMat(){
    pontUser = 0, pontPC = 0,contSOS=0,contSouO=0;//zerando contadores
    int i,j;

    int **m = (int**)malloc(3 * sizeof(int*));//definindo três linhas para a matriz

    for (i = 0; i < 3; i++){
        m[i] = (int*) malloc(11 * sizeof(int));//definindo 11 colunas para a matriz
        for (j = 0; j < 11; j++) m[i][j] = ' ';//preenchendo-a cada coluna com espaço
    }
    m[0][3]='|',m[0][7]='|',m[1][3]='|',m[1][7]='|',m[2][3]='|',m[2][7]='|'; //colocando as barras nos seus lugares
    return m; //Retorna o Ponteiro para a Matriz

    //desenho da matriz
    /*  - significa espaço
             ---|---|---
             ---|---|---
             ---|---|---
             Elementos que podem assumir S ou O
             m[0][1] m[0][5] m[0][9]
             m[1][1] m[1][5] m[1][9]
             m[2][1] m[1][5] m[2][9]
    */
}

//função para indicar a coluna correta, já que não temos uma matriz 3x3, mas 3x11.
int indice(int y){
    if (y==3) y=9;
    else if(y==2) y=5;
    return y;
}

void UpPont(int cond,int* vet,int** m){
    contSouO++;//contador para ver a quantidade de elemtos já foram jogados

    int cont=0;//contador local

    /////////////////////SOS na horizontal
    if(m[0][1]=='S' && m[0][5]=='O' &&  m[0][9]=='S' && vet[0]) cont++,vet[0]=0,contSOS++;
    if(m[1][1]=='S' && m[1][5]=='O' &&  m[1][9]=='S' && vet[1]) cont++,vet[1]=0,contSOS++;
    if(m[2][1]=='S' && m[2][5]=='O' &&  m[2][9]=='S' && vet[2]) cont++,vet[2]=0,contSOS++;
    /////////////////////SOS na vertical
    if(m[0][1]=='S' && m[1][1]=='O' &&  m[2][1]=='S' && vet[3]) cont++,vet[3]=0,contSOS++;
    if(m[0][5]=='S' && m[1][5]=='O' &&  m[2][5]=='S' && vet[4]) cont++,vet[4]=0,contSOS++;
    if(m[0][9]=='S' && m[1][9]=='O' &&  m[2][9]=='S' && vet[5]) cont++,vet[5]=0,contSOS++;
    ///////////////////// SOS na diagonal
    if(m[0][1]=='S' && m[1][5]=='O' &&  m[2][9]=='S' && vet[6]) cont++,vet[6]=0,contSOS++;
    if(m[0][9]=='S' && m[1][5]=='O' &&  m[2][1]=='S' && vet[7]) cont++,vet[7]=0,contSOS++;

    if(cond) pontUser+=cont;//se cond igual a 1, a pontuação acumulada em cont, acumula em pontUser
    else pontPC+=cont; // se não, em pontPC

}



/* a função JogaPC, sempre busca fazer uma jogada para impedir que o jogador faça SOS,
ela sempre busca jogar aos lados da posição jogada pelo Usuário*/
void JogaPC(int x,int y,int** m){
        int a= rand() % 3;
        int t[3]={1,5,9};
        int b = rand() % 3;

        while(m[a][t[b]]!=' ' && contSouO<9){
            a= rand() % 3;
            b = rand() % 3;
            //printf("%d %d\n",a,b);
        }

        int ch[2]={'S','O'};
        m[a][t[b]]=ch[rand()%2];

}

void comecaPC(int** m){
    int a= rand() % 3;
    int t[3]={1,5,9};
    int b = rand() % 3;
    m[a][t[b]] = 'S';

}


void imprimirTab(int** m){
    int i,j;
    printf("O tabuleiro tem %d SOS(s)\n",contSOS);
    for(i=0;i<3;i++){//linhas
        for(j=0;j<11;j++) printf("%c",m[i][j]);//colunas
        if(i!=2) printf("\n---+---+---\n");
    }

    printf("\nPlacar: Usuario %d x %d Computador\n",pontUser,pontPC);//pontuação
}


int main(){

    int** m=alocarMat();//inicializando Matriz
    int i,j;
    int* vet =(int*) malloc(sizeof(int)*8);//vetor de possibilidade de SOS, 3 na horizontal, 3 a vertical, 2 na diagonal
    for(i=0;i<8;i++) vet[i]=1;//colocando 1 para todas as posições, significa que não ninguém fez SOS nessa posição

    printf("*** Bem-vindo(a) ao Jogo do SOS! ***\n");
    int n;

    printf("Configuracao inicial:\n");
    printf("   |   |   \n---+---+---\n   |   |   \n---+---+---\n   |   |   \n");
    printf("Digite 1 se voce deseja comecar, ou 2 caso contrario: ");
    scanf("%d",&n);
    if(n==2){
        comecaPC(m);
        UpPont(0,vet,m);
    }

    while(1){
        system("cls");//limpa tela

        imprimirTab(m);//imprime o tabuleiro

        printf("\nDigite S ou O: ");
        char c;
        scanf("%c",&c);//leitura da quebra de linha
        scanf("%c",&c);//leitura do caractere




        int a,b;
        printf("Digite a linha: ");
        scanf("%d",&a);
        printf("Digite a coluna: ");
        scanf("%d",&b);
        a = a-1;//linha
        b =indice(b);//coluna

        m[a][b]= c ; // marcando valor

        UpPont(1,vet,m);

        JogaPC(a,b,m);
        UpPont(0,vet,m);

         if((contSouO==9 && n==2)|| (contSouO==10 && n==1)){
            system("cls");//limpa tela
            imprimirTab(m);//imprime o tabuleiro

            //resultado da partida
            if(pontUser==pontPC) printf("!!!!!!!Empate!!!!!!!\n");
            else if(pontUser>pontPC) printf("!!!!!!!Você ganhou!!!!!!!\n");
            else printf("!!!!!!!O computador ganhou!!!!!!!\n");

            int x;
            printf("Digite 1 para reiniciar o jogo: ");
            scanf("%d",&x);
            if(x){
                //liberando espaço de memória
                free(m);
                free(vet);
                //alocando espaço de memória
                m=alocarMat();
                vet =(int*) malloc(sizeof(int)*8);
                system("cls");
                imprimirTab(m);

                if(n==2)//se o usuário escolheu que o computador comece jogando
                    comecaPC(m), UpPont(0,vet,m);
            }else break;
        }

    }

    return 0;
}
