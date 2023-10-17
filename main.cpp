#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include <string.h>
#include <unistd.h>
#include <algorithm>
#include <time.h>


using namespace std;

#define NNOMES 19567

clock_t tInicio, tFim, tDecorrido;

FILE *arq3;

FILE *arqff;

char legenda[35][100];

char auxtecido[100];

int igual(const char a[200], char b[200]){ //verifica se duas strings sao iguais //1 igual 0 diferente
    for(int i=0;;i++){
        if(i>1 and a[i]=='\0' and b[i]=='\0'){
            return 1;
        }
        if(a[i]!=b[i]){
            return 0;
        }
    }

}

int igual(char a[200], char b[200]){ //verifica se duas strings sao iguais //1 igual 0 diferente
    for(int i=0;;i++){
        if(i>1 and a[i]=='\0' and b[i]=='\0'){
            return 1;
        }
        if(a[i]!=b[i]){
            return 0;
        }
    }

}



int letecido(char nomeent[]){

    FILE *fh6;

    char link3[200];

    getcwd(link3,100);

    strcat(link3, "/direction/");
    strcat(link3, "tecido.txt");

    if((fh6 = fopen(link3, "r")) == NULL) {
        printf("Arquivo nao encontrado!5\n");
    }

    int cont=0;

    char pfinal[100];
    float ppontfinal=0;

    while (!feof(fh6)){//percorre todos os genes conectados ao gene corrente

        char a;

        char nome0[100];
        char nome1[100];

        fscanf(fh6, "%c", &a);

        int i=0;

        if(cont==1){
            while(a!='%'){
                nome0[i]=a;
                nome0[i+1]='\0';
                fscanf(fh6, "%c", &a);
                i++;
            }
        }
        if(cont==2 and igual(nome0, nomeent)){
            if(a=='X'){
                while(a!='\n'){
                    fscanf(fh6, "%c", &a);
                }
            }
            else{
                i=0;
                while(a!='%'){
                    nome1[i]=a;
                    nome1[i+1]='\0';
                    fscanf(fh6, "%c", &a);
                    i++;
                    if(a=='%'){
                        float aux1;
                        float aux2;
                        fscanf(fh6, "%f", &aux1);
                        fscanf(fh6, "%c", &a);
                        fscanf(fh6, "%f", &aux2);

                        if(aux2>ppontfinal){
                            ppontfinal=aux2;
                            for(int j=0;j<100;j++){
                                pfinal[j]=nome1[j];
                            }
                        }
     //                   cout<<nome0<<" "<<nome1<<" "<<aux2<<" ";
                    }
                }
            }
        }
        if(a=='%'){
            cont++;
        }
        if(a=='\n' and igual(nome0, nomeent)){
            //cont=0;
      //      cout<<endl;
        }
        if(a=='\n'){
            cont=0;
            //cout<<endl;
        }

    }

    for(int i=0;i<100;i++){
        auxtecido[i]=pfinal[i];
    }

    fclose(fh6);

    return 0;
}



float ledirecao(char nome1[], char nome2[], int tecido){

        char link2[200];

        getcwd(link2,100);


        char caractere[100];

        sprintf(caractere, "%d", tecido);


        strcat(link2, "/direction/network_");
        strcat(link2, caractere);


        FILE *fh5;
        FILE *fh11;

        if((fh11 = fopen(link2, "r")) == NULL) {
            printf("Arquivo nao encontrado!6\n");
        }

        char a;
        int linhas=0;
        while (!feof(fh11)){
            fscanf(fh11, "%c", &a);
            if(a=='\n')linhas++;
        }

        if((fh5 = fopen(link2, "r")) == NULL) {
            printf("Arquivo nao encontrado!9\n");
            fclose(fh5);
            return 1.0;
        }

        char nomeaux1[100];
        char nomeaux2[100];

        int linhas_aux=0;

        while (!feof(fh5)){
            linhas_aux++;
            int cont=0;
            for(int i=0;;i++){
                fscanf(fh5, "%c", &a);
                if(a==' '){
                    i=-1;
                    cont++;
                }
                if(cont==0){
                    nomeaux1[i]=a;
                    nomeaux1[i+1]='\0';
                }
                if(cont==1){
                    nomeaux2[i]=a;
                    nomeaux2[i+1]='\0';
                }
                if(cont==2){
                    float auxf;
                    fscanf(fh5, "%f", &auxf);

                    if(igual(nomeaux1,nome1) and igual(nomeaux2,nome2)){
                        fclose(fh11);
                        fclose(fh5);
                        if(auxf>0.1) return 1.0;
                        if(auxf<-0.1) return -1.0;
                        return auxf;
                    }
                    if(igual(nomeaux2,nome1) and igual(nomeaux1,nome2)){
                        fclose(fh11);
                        fclose(fh5);
                        if(auxf>0.1) return 1.0;
                        if(auxf<-0.1) return -1.0;
                        return auxf;
                    }
                    if(linhas_aux==linhas-1){
                        return 0;
                    }
                    fscanf(fh5, "%c", &a);

                    break;
                }
            }
        }

        fclose(fh11);
        fclose(fh5);

        return 0;

}




class no_score{
public:

    float score;
    float dir;
    no_score * prox;

    no_score(){
        score=0;
        dir=1;
        prox=NULL;
    }
};


class fila_score{
public:

    no_score * raiz;

    fila_score(){
        raiz=NULL;
    }

    void adiciona(float valor, float dir2){

        no_score * novo = new no_score();
        novo->score=valor;
        novo->dir=dir2;

        no_score * antigo = raiz;

        if(raiz==NULL){
            raiz=novo;
            novo->prox=NULL;
            return;
        }
        else{
            if(novo->score>raiz->score){
                novo->prox=antigo;
                raiz=novo;
                return;
            }
            else{
                int dis=0;
                while(antigo->prox!=NULL){
                    if(novo->score>antigo->prox->score){
                        novo->prox=antigo->prox;
                        antigo->prox=novo;
                        return;
                    }
                    antigo=antigo->prox;
                }
                antigo->prox=novo;
            }
        }
    }

    void imprime_score(){

        no_score * n = raiz;

        int i=0;

        while(n!=NULL){
            cout<<"(D) "<<n->dir<<" ";
            cout<<"(S) "<<n->score<<" ";
            n=n->prox;
            i++;
            if(i>20) break;
        }
        cout<<endl;

    }

};


class no{
public:

    char nome[200];
    char nome2[200];
    no * prox;
    int nivel;
    float score;
    int qt;
    fila_score * s;
    int dir;

    no(char a[200]){
        for(int i=0;i<200;i++){
            nome[i]=a[i];
        }
        prox=NULL;
        score=0;
        qt=0;
        s=new fila_score();
        dir=1;
    }



    int calcula(){

        int qt2=qt;

        if(qt>20)qt2=20;

        float pscore[2][qt2];

        no_score * n = s->raiz;

        float total=n->score;
        float soma=0;
        float subtracao=1;

        int i=0;
        n=n->prox;
        i++;
        while(n!=NULL){
            soma=total+n->score;
            subtracao=total*n->score;
            total=soma-subtracao;
            n=n->prox;
            i++;
        }

        soma=total;

        score=soma;
        return 0;

    }

};




class dados{
public:

    no * raiz;

    int qt;

    dados(){
        raiz=NULL;
        qt=0;
    }

    void imprime(){
        no * aux = raiz;
        while(aux!=NULL){
            cout<<aux->nome<<" ";
            aux=aux->prox;
        }
        cout<<endl;
        cout<<endl;
    }



    void imprime_s(){
        no * aux = raiz;
        int arqi=0;
        int cont=0;
        while(aux!=NULL){
            if(aux->qt>=0 and arqi==0){
                if(aux->score>0.0001)cout<<aux->score<<" "<<aux->nome<<endl;//" qt: "<<aux->qt<<" scores: ";
                //aux->s->imprime_score();
                //cout<<endl;

                char auxs[]="https://pubmed.ncbi.nlm.nih.gov/?term=%28duchenne%5BText+Word%5D%29+AND+%28";
                char auxs2[]="%5BText+Word%5D%29&sort=";

                fprintf (arqff, "%f ", aux->score);
                fprintf (arqff, "%s", aux->nome);
                fprintf (arqff, " \n");

                cont++;
            }
            arqi++;
            if(arqi>0) arqi=0;
            aux=aux->prox;
        }
        cout<<endl;
        cout<<endl;
    }



    int adiciona(no * n){//adiciona no começo sem analisar nada
        no * aux = raiz;
        if(aux==NULL){
            raiz=n;
            qt++;
            return 1;
        }
        else{
            n->prox=raiz;
            raiz=n;
            qt++;
        }
        return 0;
    }


    int adiciona_valida(no * n){//adiciona no final, nao adiciona nos com nomes repetidos
        no * aux = raiz;
        if(aux==NULL){
            raiz=n;
            qt++;
            return 1;
        }
        while(aux!=NULL){
            if(igual(n->nome,aux->nome)==0){
                if(aux->prox==NULL){
                    aux->prox=n;
                    qt++;
                    return 1;
                }
                aux=aux->prox;
            }
            else {
                return 0;
            }
        }
        return 0;
    }



    int adiciona_valida_atualiza(no * n){ //igual o segundo adiciona mas caso o nome ja esteja na estrutura de ddos ele aumenta o score
        no * aux = raiz;
        if(aux==NULL){
            raiz=n;
            qt++;
            n->qt++;
            n->s->adiciona(n->score, n->dir);
            return 1;
        }
        while(aux!=NULL){
            if(igual(n->nome,aux->nome)==0){ //se nao for igual
                if(aux->prox==NULL){ //verifica se é o ultimo
                    aux->prox=n;// se for adiciona pq nao achou um igual
                    qt++;
                    n->qt++;
                    n->s->adiciona(n->score, n->dir);
                    return 1;
                }
                aux=aux->prox; // se nao for vai pro proximo
            }
            else { // se for igual atualuza oscore, nao aumenta o qt pq ele ja tava no no
                aux->score+=n->score;
                aux->s->adiciona(n->score, n->dir);
                aux->qt++;
                return 0;
            }
        }
        return 0;
    }


    void calcula(){
        no * aux = raiz;
        while(aux!=NULL){
            aux->calcula();
            aux=aux->prox;
        }
    }



};




void divide(const char a[], dados * d){ //recebe uma cadeia de genes e divide ela em varios genes gene1/nege2 -> gene1 gene2
    char gene[200];
    for(int i=0,j=0;;i++,j++){
        if(a[i]=='/' or a[i]=='\0'){
            j=-1;
            no* n=new no(gene);
            n->nivel=0;
            d->adiciona_valida(n);
        }
        else{
            gene[j]=a[i];
            gene[j+1]='\0';
        }

        if(a[i]=='\0')break;
    }
}


int resposta(no * n, dados * m, dados * resp, int nei, int fus, int coo, int coe, int exp, int dat, int tex, float limiar, int nivel, float pont, int tnivel, char nome[2][NNOMES][50], dados * pas){

    int coments=0;//verifica se um gene depois possui medimedicamento, muda forma de print

    //ve se o medicamento tem vizinhos em potencial

    if(nivel<tnivel){

        char link[200];

        getcwd(link,100);

        strcat(link, "/gens/");
        strcat(link, n->nome);
        strcat(link, "-gens.txt");


        FILE *fh;

        if((fh = fopen(link, "r")) == NULL) {
            printf("Arquivo nao encontrado!1\n");
        }


        while (!feof(fh)){//percorre todos os genes conectados ao gene corrente
            char a;
            char cod1[200];
            char cod2[200];
            int aux=0;
            for(int i=0;;i++){
                fscanf(fh, "%c", &a);
                if(a==' '){
                    aux++;
                    i=-1;
                }
                if(aux==0){
                    cod1[i]=a;
                    cod1[i+1]='\0';
                }
                if(aux==2){
                    cod2[i]=a;
                    cod2[i+1]='\0';
                }
                if(aux==1)aux=2;
                if(aux==3)break;
            }
            int a1,a2,a3,a4,a5,a6,a7,a8;
            fscanf(fh, "%d %d %d %d %d %d %d %d ", &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8);
            float p=0.041;
            float s_1, s_2, s_3, s_4, s_5, s_6, s_7;
            float s_1_nop, s_2_nop, s_3_nop, s_4_nop, s_5_nop, s_6_nop, s_7_nop;
            float s_tot_1=1.0;
            if(nei==1 and a1>0){//le ponttuação
                s_1=a1;
                s_1=s_1/1000.0;
                s_1_nop = (s_1 - p) / (1.0 - p);
                s_tot_1 = s_tot_1 * (1.0 - s_1_nop);
            }
            if(fus==1 and a2>0){
                s_2=a2;
                s_2=s_2/1000.0;
                s_2_nop = (s_2 - p) / (1.0 - p);
                s_tot_1 = s_tot_1 * (1.0 - s_2_nop);
            }
            if(coo==1 and a3>0){
                s_3=a3;
                s_3=s_3/1000.0;
                s_3_nop = (s_3 - p) / (1.0 - p);
                s_tot_1 = s_tot_1 * (1.0 - s_3_nop);
            }
            if(coe==1 and a4>0){
                s_4=a4;
                s_4=s_4/1000.0;
                s_4_nop = (s_4 - p) / (1.0 - p);
                s_tot_1 = s_tot_1 * (1.0 - s_4_nop);
            }
            if(exp==1 and a5>0){
                s_5=a5;
                s_5=s_5/1000.0;
                s_5_nop = (s_5 - p) / (1.0 - p);
                s_tot_1 = s_tot_1 * (1.0 - s_5_nop);
            }
            if(dat==1 and a6>0){
                s_6=a6;
                s_6=s_6/1000.0;
                s_6_nop = (s_6 - p) / (1.0 - p);
                s_tot_1 = s_tot_1 * (1.0 - s_6_nop);
            }
            if(tex==1 and a7>0){
                s_7=a7;
                s_7=s_7/1000.0;
                s_7_nop = (s_7 - p) / (1.0 - p);
                s_tot_1 = s_tot_1 * (1.0 - s_7_nop);
            }

            float s_tot_2 = 1.0 - s_tot_1;
            float media2 = s_tot_2 + p * (1.0 - s_tot_2);

            float media=pont*(media2*0.5);

            if(media2>0.0001){
            if(media2>limiar or media2<0.00000000000000005){

                no * n3 = new no(cod2);

                n3->dir=1.0;

                int valid=0;

                if(valid==0){

                    n3->score=media;

                    coments+=resposta(n3, m, resp, nei, fus, coo, coe, exp, dat, tex, limiar, nivel+1, media, tnivel, nome, pas);//se for encontrado um gene com pontuação e nivel adequadoe  lançado na funça recursiva

                    int itrad=0;
                    int itrad2=0;
                    for(int i3=0;i3<NNOMES;i3++){
                        if(igual(n->nome,nome[1][i3])==1){//qual a traddução
                            itrad=i3;
                        }
                    }
                    for(int i3=0;i3<NNOMES;i3++){
                        if(igual(n3->nome,nome[1][i3])==1){//qual a traddução
                            itrad2=i3;
                        }
                    }

                    fprintf (arq3, "%s, %s, %f \n", nome[0][itrad], nome[0][itrad2], s_tot_2);

                }
            }
            }

        }

        fclose(fh);
    }

    //ve se o gene tem droga e calcula pontuaçao

    no * n2 = m->raiz; //vai percorrer todas os genes com drogas

    while(n2!=NULL){
        if(igual(n->nome, n2->nome)==1){//se tem droga
            for(int i=0;i<NNOMES;i++){
                if(igual(n->nome,nome[1][i])==1){//qual a traddução

                    for(int i=0;i<nivel;i++)
                       cout<<"     ";

                    cout<<nome[0][i]<<" Scorec: "<<pont<<" Level: "<<nivel<<" Direcao: ";//print em genes com droga
                    if(nivel==0)printf("\033[34m Gene with drug \033[0m");
                    if(nivel==1)printf("\033[31m Gene with drug \033[0m");
                    if(nivel==2)printf("\033[32m Gene with drug \033[0m");
                    if(nivel>2)printf("\033[33m Gene with drug \033[0m");
                    cout<<endl;

                    n2 = m->raiz; //vai percorrer todas os genes com drogas

                    while(n2!=NULL){
                        if(igual(n->nome, n2->nome)==1){//se tem droga
                            no * n3 = new no(n2->nome2);

                                n3->dir=n->dir;

                            n3->score=pont;
                            fprintf (arq3, "%s, %s, %f \n", n2->nome2, nome[0][i], n3->score);
                            resp->adiciona_valida_atualiza(n3);
                            pont=n3->score;
                        }
                        n2=n2->prox;
                    }
                    return 1;
                }
            }
        }
        n2=n2->prox;
    }


    if(coments>0){
            for(int i=0;i<NNOMES;i++){//tradução
                if(igual(n->nome,nome[1][i])==1){

                    for(int i=0;i<nivel;i++)
                        cout<<"     ";//print distancia em nivel

                    cout<<nome[0][i]<<" Score: "<<pont<<" Level: "<<nivel<<endl;//print em genes intermediarios
                    break;
                }
            }
            return 1;
    }

    return 0;

}


int adiciona(dados * d, dados * m, dados * resp, int nei, int fus, int coo, int coe, int exp, int dat, int tex, float limiar, int nivel, char nome[2][NNOMES][50]){ //evento recurivo para gerar a gcn

    no * n = d->raiz;

    while(n!=NULL){

        dados * pas = new dados();

        resposta(n, m, resp, nei, fus, coo, coe, exp, dat, tex, limiar, 0, 1.0*0.5, nivel, nome, pas);//chama a função processo com os genes que foram usados na entrada

        n=n->prox;

    }

    return 1;
}


void traduz(dados * d1, dados * d2, char nome[2][NNOMES][50]){ //recebe nome de gene e retorna seu codigo
    no * n = d1->raiz;
    while(n!=NULL){
        for(int i=0;i<NNOMES;i++){
            if(igual(n->nome, nome[0][i])==1){
                no * aux = new no(nome[1][i]);
                aux->nivel=n->nivel;
                aux->score=n->score;
                for(int j=0;j<100;j++)
                    aux->nome2[j]=n->nome2[j];
                d2->adiciona_valida(aux);

            }
        }
        n=n->prox;
    }

}




void help(){

cout<<endl;
cout<<"Execute: ./RGD + <parameters>"<<endl;

cout<<endl;
cout<<"  -----------------------------------------------------------------------------  "<<endl;

cout<<"-Gene list that will be used in drug search:"<<endl;
cout<<"-f gene1/gene2 "<<endl;
cout<<endl;
cout<<"Example: ./RGD -f ATXN1/ATXN3/ATXN7"<<endl;
cout<<"The example will perform the search using the ATXN1, ATN3, and ATXN7 genes."<<endl;

cout<<endl;
cout<<"  -----------------------------------------------------------------------------  "<<endl;

cout<<"--Parameters that evaluate the connection between genes (more info: string-db.org)"<<endl;
cout<<"Neighborhood: -nei 1 "<<endl;
cout<<"Fusion: -fus 1 "<<endl;
cout<<"Cooccurence: -coo 1 "<<endl;
cout<<"Coexpression: -coe 1 "<<endl;
cout<<"Experimental: -exp 1 "<<endl;
cout<<"Database: -dat 1 "<<endl;
cout<<"Textmining: -tex 1 "<<endl;
cout<<endl;
cout<<"Example: ./RGD -f ATXN3 -fus 1 -coo 1 -dat 0"<<endl;
cout<<"The example will perform the search using the Fusion and Coexpression parameters."<<endl;
cout<<endl;
cout<<"Standard: -nei 0 -fus 0 -coo 0 -coe 1 -exp 0 -dat 0 -tex 0"<<endl;
cout<<endl;

cout<<"  -----------------------------------------------------------------------------  "<<endl;
cout<<endl;

cout<<"-Modify the distance from one gene to one of the input genes in the network. Distance equal to x will consider neighbors with a distance x to the target."<<endl;
cout<<"-ni <level> "<<endl;
cout<<endl;
cout<<"Example: ./RGD -f ATXN3 -ni 2"<<endl;
cout<<"The example will perform the search using up to 2 neighbors of the ATXN3 gene"<<endl;
cout<<endl;
cout<<"Standard: -ni 3 "<<endl;
cout<<endl;

cout<<"  -----------------------------------------------------------------------------  "<<endl;
cout<<endl;

cout<<"-Minimum score a relationship must have to be considered on the network"<<endl;
cout<<"-li <limiar> com 0 <= limiar <= 1 "<<endl;
cout<<endl;
cout<<"-li <threshold> with 0 <= threshold <= 1"<<endl;
cout<<"The example will perform the search using neighbors relationship score greater than 0.2"<<endl;
cout<<endl;
cout<<"Standard: -li 0.3 "<<endl;
cout<<endl;

}



int main( int argc, const char* argv[])
{

    tInicio = clock();

    cout<<"Lendo dados "<<endl;

    cout<<"   "<<"Lendo codigos "<<endl;

    char nome[2][NNOMES][50];

    FILE *fh;

    if((fh = fopen("infos.txt", "r")) == NULL) {
        printf("Arquivo nao encontrado!2\n");
    }

    int linha=-1;
    while (!feof(fh)){
   //for(int lala=0;lala<10;lala++){
        linha++;
        char a;
        char cod1[200];
        char cod2[200];
        char resto[10000];
        int aux=0;
        for(int i=0;;i++){
            fscanf(fh, "%c", &a);
            if(a=='\t'){
                aux++;
                i=-1;
            }
            if(aux==0){
                cod1[i]=a;
                cod1[i+1]='\0';
            }
            if(aux==2){
                cod2[i]=a;
                cod2[i+1]='\0';
            }
            if(aux==1)aux=2;
            if(a=='\n'){
                break;
            }
        }
        for(int i=0;i<200;i++){
            nome[0][linha][i]=cod2[i];
            nome[1][linha][i]=cod1[i];
        }
   }


    cout<<"   "<<"Lendo medicamentos "<<endl;



    if((fh = fopen("medicines.txt", "r")) == NULL) {
        printf("Arquivo nao encontrado!3\n");
    }

    dados * m2 = new dados();

    int cont2=0;

    while (!feof(fh)){
        char a;
        char cod1[200];
        char cod2[200];
        int cont=0;
        int j=0;
        for(int i=0;;i++,j++){

            fscanf(fh, "%c", &a);

            if(a=='\n'){
                break;
            }

            if(a==' ' and cont==0){
                cont++;
                j=0;
                fscanf(fh, "%c", &a);
            }


            if(cont==0){
                cod1[j]=a;
                cod1[j+1]='\0';
            }

            if(cont==1){
                cod2[j]=a;
                cod2[j+1]='\0';
            }

        }

        cont2++;

        no * aux = new no(cod1);

        for(int j=0;j<100;j++)
            aux->nome2[j]=cod2[j];

        m2->adiciona(aux);
   }


    cout<<"Processando dados "<<endl;

    //le entrada


    int nei=0;
    int fus=0;
    int coo=0;
    int coe=1;
    int exp=0;
    int dat=0;
    int tex=0;


    float limiar=0.3;

    int nivel=3;


    dados * d = new dados();
    dados * d2 = new dados();
    dados * d3 = new dados();

    for(int i=1;;i++){

        if(argv[1]==NULL){
            help();
            fclose(fh);
            return 0;
        }

        if(argv[i]==NULL)break;

        char conf1[]="-f";
        if(igual(argv[i],conf1)==1){
            divide(argv[i+1],d);
        }

        char conf2[]="-nei";
        if(igual(argv[i],conf2)){
            if(argv[i+1][0]=='1')
                nei=1;
            if(argv[i+1][0]=='0')
                nei=0;
            if(argv[i+1][0]!='0' and argv[i+1][0]!='1'){
                cout<<"Wrong parameter"<<endl;
                return 0;
            }
        }

        char conf3[]="-fus";
        if(igual(argv[i],conf3)){
            if(argv[i+1][0]=='1')
                fus=1;
            if(argv[i+1][0]=='0')
                fus=0;
            if(argv[i+1][0]!='0' and argv[i+1][0]!='1'){
                cout<<"Wrong parameter"<<endl;
                return 0;
            }
        }

        char conf4[]="-coo";
        if(igual(argv[i],conf4)){
            if(argv[i+1][0]=='1')
                coo=1;
            if(argv[i+1][0]=='0')
                coo=0;
            if(argv[i+1][0]!='0' and argv[i+1][0]!='1'){
                cout<<"Wrong parameter"<<endl;
                return 0;
            }
        }

        char conf5[]="-coe";
        if(igual(argv[i],conf5)){
            if(argv[i+1][0]=='1')
                coe=1;
            if(argv[i+1][0]=='0')
                coe=0;
            if(argv[i+1][0]!='0' and argv[i+1][0]!='1'){
                cout<<"Wrong parameter"<<endl;
                return 0;
            }
        }

        char conf6[]="-exp";
        if(igual(argv[i],conf6)){
            if(argv[i+1][0]=='1')
                exp=1;
            if(argv[i+1][0]=='0')
                exp=0;
            if(argv[i+1][0]!='0' and argv[i+1][0]!='1'){
                cout<<"Wrong parameter"<<endl;
                return 0;
            }
        }

        char conf7[]="-dat";
        if(igual(argv[i],conf7)){
            if(argv[i+1][0]=='1')
                dat=1;
            if(argv[i+1][0]=='0')
                dat=0;
            if(argv[i+1][0]!='0' and argv[i+1][0]!='1'){
                cout<<"Wrong parameter"<<endl;
                return 0;
            }
        }

        char conf8[]="-tex";
        if(igual(argv[i],conf8)){
            if(argv[i+1][0]=='1')
                tex=1;
            if(argv[i+1][0]=='0')
                tex=0;
            if(argv[i+1][0]!='0' and argv[i+1][0]!='1'){
                cout<<"Wrong parameter"<<endl;
                return 0;
            }
        }

        char conf9[]="-li";
        if(igual(argv[i],conf9)){
            float aux=stof(argv[i+1]);
            if(aux>=0 and aux<=1){
                limiar=aux;
            }else{
                cout<<"Wrong parameter"<<endl;
                return 0;
            }
        }

        char conf10[]="-ni";
        if(igual(argv[i],conf10)){
            float aux=stof(argv[i+1]);
            if(aux>=0){
                nivel=aux;
            }else{
                cout<<"Wrong parameter"<<endl;
                return 0;
            }
        }

        char conf11[]="-HELP";
        char conf12[]="-help";
        if(igual(argv[i],conf12) or igual(argv[i],conf11)){
            help();
            return 0;
        }


    }

    cout<<endl;

    cout<<"-Entry Genes: "<<endl;
    d->imprime();

    cout<<"-Parâmetros: "<<endl;
    cout<<"Neighborhood: "<<nei<<endl;
    cout<<"Fusion: "<<fus<<endl;
    cout<<"Cooccurence: "<<coo<<endl;
    cout<<"Coexpression: "<<coe<<endl;
    cout<<"Experimental: "<<exp<<endl;
    cout<<"Database: "<<dat<<endl;
    cout<<"Textmining: "<<tex<<endl;

    cout<<endl;

    cout<<"-Threshold: "<<limiar<<endl;

    cout<<endl;

    cout<<"-Network Level: "<<nivel<<endl;

    cout<<endl;


    traduz(d,d2,nome);


    //processo

    dados * resp = new dados();

    cout<<"Processo "<<endl;

    arq3 = fopen("output/graph.txt", "w");

    arqff = fopen("output/medicines.txt", "a");

    adiciona(d2, m2, resp, nei, fus, coo, coe, exp, dat, tex, limiar, nivel, nome);

    cout<<endl;

    resp->calcula();

    resp->imprime_s();

    tFim = clock();

    tDecorrido = ((tFim - tInicio) / (CLOCKS_PER_SEC / 1000));

    float timef = tDecorrido;

    FILE *arqx;
    arqx = fopen("output/time.txt", "a");
    if(arqx == NULL)
        printf("Erro, nao foi possivel abrir o arquivo\n");
    else{
        fprintf (arqx, "%f ms \n", timef);
        fclose(arqx);
    }

    fclose(fh);

    return 0;
}
