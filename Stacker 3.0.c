#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "glut.h"

float frand()
{
    float k=1.0*rand()/RAND_MAX;
    while(k==1.0)
        k=1.0*rand()/RAND_MAX;
    return k;
}

int **matriz;   //las definimos como global, fuera del int main, para poder usarla con el glut.c y graficarla
int extD;

int main(int argc, const char **argv)
{
    FILE *file;
    file=fopen("puntos.txt","w");      //coordenadas de los puntos que terminan con un 1

    float p=0, r=0;
    int x=0, y=0, n=0, m=0, d=0, centro=0, flag=0;

    srand(time(NULL));
    for(int i=0; i<100; i++){rand();}

    printf("Introduzca el numero maximo de unos a generar\n");
    scanf("%d",&m);

    printf("Introduzca la dimension de la matriz\n");
    scanf("%d",&d);
    extD = d;

    centro=(d-1)/2;

    matriz=(int**) calloc(d, sizeof(int*)); //este int va con asterisco porque estoy asignandolo como otro pointer!
    for(int i=0; i<d; i++){
        matriz[i]=(int*) calloc(d, sizeof(int));
    }

    matriz[centro][centro]=1; //defino la matriz en 0 excepto por el elemento central

    glutStuff(argc, argv);

    while(n<m)           // si p<0.25 x++       si 0.25<p<0.5 y++
    {                   // si 0.5<p<0.75 x--   si 0.75<p<1   y--
        p=frand();
        callGlut();
//        usleep(0.01);

        if(flag==1){                 //si r<0.25 x=0 y=0          si 0.25<r<0.5 x=0 y=max
            r=frand();              //si 0.5<r<0.75 x=max y=0    si 0.75<r<1 x=max y=max
            if(r<0.25){            //la condicion de matriz[0][0]!=1 me arregla un bug donde se creaba un grupo en la esquina (0,0)
                x=(int)frand()*d;
                x= rand()%4;
                y=0;             //TODO ESTE IF ES PARA GENERAR LA ESQUINA ALEATORIA
                flag=0;
            }
            else if(r>=0.25 && r<0.5){
                x=0;
                y=d-1;
                flag=0;
            }
            else if(r>=0.5 && r<0.75){
                x=d-1;
                y=0;
                flag=0;
            }
            else{
                x=d-1;
                y=d-1;
                flag=0;
            }
        }

        if(p<0.25){
            if(x!=d-1){
                if(matriz[x+1][y]==0){
                    matriz[x][y]=0;
                    x++;
                    matriz[x][y]=1;
                }
                else if(matriz[x+1][y]==1){
                    matriz[x][y]=1;
                    fprintf(file,"%d,%d\n",x,y); //guardo el punto
                    flag=1;    //vuelve a empezar
                    n++;
                }
            }
            else{
                matriz[x][y]=0;
                x--;
                matriz[x][y]=1;
            }
        }
        else if(p>=0.25 && p<0.5){
            if(y!=d-1){
                if(matriz[x][y+1]==0){
                    matriz[x][y]=0;
                    y++;
                    matriz[x][y]=1;
                }
                else if(matriz[x][y+1]==1){
                    matriz[x][y]=1;
                    fprintf(file,"%d,%d\n",x,y);
                    flag=1;
                    n++;
                }
            }
            else{
                matriz[x][y]=0;
                y--;
                matriz[x][y]=1;
            }
        }
        else if(p>=0.5 && p<0.75){
            if(x!=0){
                if(matriz[x-1][y]==0){
                    matriz[x][y]=0;
                    x--;
                    matriz[x][y]=1;
                }
                else if(matriz[x-1][y]==1){
                    matriz[x][y]=1;
                    fprintf(file,"%d,%d\n",x,y);
                    flag=1;
                    n++;
                }
            }
            else{
                matriz[x][y]=0;
                x++;
                matriz[x][y]=1;
            }
        }
        else{
            if(y!=0){
                if(matriz[x][y-1]==0){
                    matriz[x][y]=0;
                    y--;
                    matriz[x][y]=1;
                }
                else if(matriz[x][y-1]==1){
                    fprintf(file,"%d,%d\n",x,y);
                    matriz[x][y]=1;
                    flag=1;
                    n++;
                }

            }
            else{
                matriz[x][y]=0;
                y++;
                matriz[x][y]=1;
            }
        }
    }

//    if(d<100){      //No quiero que se imprima una matriz muy grande en la consola
//        for(int i=0; i<d; i++){
//            for(int j=0; j<d; j++){printf("%d", matriz[i][j]);}
//        printf("\n");
//        }
//    }

    for(int i=0; i<d; i++){     //libero la memoria
        free(matriz[i]);
    }
    free(matriz);

    sleep(5); //si quiero ver el grafico

    return 0;
}
