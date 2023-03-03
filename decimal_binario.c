//Valero Silva Omar Misael
//Este programa transforma un número decimal a binario e invierte el numero binario
#include <stdio.h>
#include<stdlib.h> 
#include <conio.h>
#include<stdbool.h>
#define MAX 100

typedef struct pila
{
    int arreglo[MAX];
    int tope;
}pila;

bool esVacia(pila *s)
{
    if(s -> tope == -1)
        return(1);
    return(0);
}

bool esLlena(pila *s)
{
    if(s -> tope == MAX - 1)
        return(1);
    return(0);
}

void push(pila *s, int x)
{
    s -> tope = s -> tope + 1;
    s -> arreglo[s -> tope] = x;
}

int pop(pila *s)
{
    int x;
    x = s -> arreglo[s -> tope];
    s -> tope = s -> tope - 1;
    return(x);
}
void mostrar(pila s, int num){
    while(!esVacia(&s))
    {
        num = pop(&s);
        printf("%d", num);
    }
}

void convertir(pila s, int num)
{
    while((num != 0))
    {
        if(!esLlena(&s))
        {
            push(&s, num % 2);
            num = num / 2;
        }
        else
        {
            printf("Pila desbordada");
            exit(0);
        }
    }
    printf("Numero en binario: ");
    mostrar(s,num);
    printf("\n");
    printf("Numero binario invertido: ");
    for(int i=0; i<=s.tope; i++){
        printf("%d", s.arreglo[i]);
    }
    printf("\n");
}

int main()
{
    pila s; 
    int num;
    s.tope = -1;
    printf("Numero decimal a convertir: ");
    scanf("%d", &num);
    convertir(s,num);
    system("PAUSE");
    return 0;
}
