#This program was made by me during my third semester, but it is not a suitable program to work with

#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>

void ingresar();
void borrar();
void imprimir();
void buscar();
void editar();
void cantidad();

struct inventario
{
	int codigo;
    char modelo[30];
	char marca[30];
	char color[30];
	float talla;
}zap;

int main()
{
	char opcion;
	do{
		system("clear");
		printf("----------ZAPATERIA-----------\n");
		printf("Ingresar zapato.............. A\n");
		printf("Borrar zapato................ B\n");
	    printf("Mostrar todos los zapatos.... C\n");
	    printf("Consultar un zapato.......... D\n");
	    printf("Editar un zapato............. E\n");
	    printf("Cantidad de zapatos.......... F\n");
	    printf("Salir de la aplicacion....... S\n");
	    opcion=toupper(getchar());
		switch(opcion){
			case 'A': ingresar();
		              break;
		    case 'B': borrar();
		              break;          
		    case 'C': imprimir();
		              break;
		    case 'D': buscar();
		             break;
		    case 'E': editar();
		              break;
		    case 'F': cantidad();
		              break;
	    }
	}while(opcion!='S');
	return 0;
}

void ingresar() {
    system("clear");
    FILE* inventario;
    char opc;
    inventario = fopen("inventario.txt", "a+");
    if (inventario != NULL) {
        do {
            printf("Codigo del zapato:\n");
            scanf("%i", &zap.codigo);
            getchar(); // consume the newline character left by scanf
            printf("Modelo del zapato: \n");
            fgets(zap.modelo, sizeof(zap.modelo), stdin);
            printf("Marca del zapato: \n");
            fgets(zap.marca, sizeof(zap.marca), stdin);
            printf("Color del zapato: \n");
            fgets(zap.color, sizeof(zap.color), stdin);
            printf("Talla del zapato: \n");
            scanf("%f", &zap.talla);
            getchar(); // consume the newline character left by scanf
            fwrite(&zap, sizeof(zap), 1, inventario);
            printf("\n\ndesea continuar agregando zapatos?... S/N: ");
            opc = toupper(getchar());
            system("clear");
        } while (opc != 'N');
        fclose(inventario);
    } else {
        printf("No fue posible realizar la captura\n");
        system("pause");
    }
    fclose(inventario);
}

void borrar() {
    int existe;
    int codigo_temporal;
    system("clear");
    FILE *inventario, *inventarioTemp;
    inventarioTemp = fopen("inventarioTEMP.txt", "a+");
    inventario = fopen("inventario.txt", "r");
    printf("Codigo del zapato que quieres borrar:\n");
    fflush(stdin);
    scanf("%i", &codigo_temporal);
    fread(&zap, sizeof(inventario), 1, inventario);
    do {
        if (codigo_temporal == zap.codigo) {
            printf("Zapato borrado\n");
            printf("Codigo  : %d\n", zap.codigo);
            printf("Modelo  : %s\n", zap.modelo);
            printf("Marca   : %s\n", zap.marca);
            printf("Color   : %s\n", zap.color);
            printf("Talla   : %.2f\n", zap.talla);
            existe = 1;
            system("pause");
        } else {
            fwrite(&zap, sizeof(inventario), 1, inventarioTemp);
        }
        fread(&zap, sizeof(inventario), 1, inventario);
    } while (feof(inventario) == 0);
    if (existe == 0) {
        printf("No existe un zapato con dicho codigo\n");
        system("pause");
    }
    fclose(inventario);
    fclose(inventarioTemp);
    remove("inventario.txt");
    rename("inventarioTEMP.txt", "inventario.txt");
}

void imprimir(){
    FILE *inventario;
    inventario=fopen("inventario.txt","r");
    if(!inventario){
        printf("Problema al abrir el archivo o no existe\n");
        return;
    }
    while(fread(&zap,sizeof(zap),1,inventario)){
        printf("\n Informacion del zapato\n\n");
        printf("Codigo  : %d\n",zap.codigo);
        printf("Modelo  : %s\n",zap.modelo);
        printf("Marca   : %s\n",zap.marca);
        printf("Color   : %s\n",zap.color);
        printf("Talla   : %.2f\n",zap.talla);
    }
    fclose(inventario);
    system("pause");
}

void buscar(){
    int codigo_temporal, existe = 0;
    system("clear");
    FILE *inventario = fopen("inventario.txt", "r");
    if(inventario != NULL){
        printf("Ingrese el codigo del zapato: ");
        scanf("%i", &codigo_temporal);
        while(fread(&zap, sizeof(zap), 1, inventario) == 1){
            if (codigo_temporal == zap.codigo){
                printf("\nInformacion del zapato:\n\n");
                printf("Codigo: %d\n",zap.codigo);
                printf("Modelo: %s\n",zap.modelo);
                printf("Marca: %s\n",zap.marca);
                printf("Color: %s\n",zap.color);
                printf("Talla: %.2f\n",zap.talla);
                existe = 1;
                break;
            }
        }
        fclose(inventario); // close the file pointer
        if (existe == 0) {
            printf("No existe un zapato con dicho codigo\n");
            system("pause");
        }
    } else {
        printf("No fue posible abrir el archivo\n");
        system("pause");
    }
}

void editar(){
    FILE *inventario;
    if ((inventario=fopen("inventario.txt","r+b")) == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }
    int opcion;
    system("clear");
    printf("Ingrese el codigo del zapato a editar: ");
    int tempcodigo;
    scanf("%i", &tempcodigo);
    int existe=0;
    while(fread(&zap, sizeof(zap), 1, inventario)) {
        if (tempcodigo==zap.codigo) {
           printf("\nEl zapato es:\n");
           printf("%-8d %-16s %-16s %-10s %.1f\n", zap.codigo, zap.marca, zap.modelo, zap.color, zap.talla);
           printf("\n[1]-Codigo");
           printf("\n[2]-Marca");
           printf("\n[3]-Modelo");
           printf("\n[4]-Color");
           printf("\n[5]-Talla");
           printf("\nSeleccione lo que desea editar: ");
           scanf("%d",&opcion);
           switch(opcion) {
               case 1:
                   printf("Dame el nuevo codigo:");
                   scanf("%d",&zap.codigo);
                   printf("\nSe ha modificado\n");
                   break;
               case 2:
                   printf("Dame la nueva marca:");
                   fflush(stdin);
                   fgets(zap.marca, sizeof(zap.marca), stdin);
                   printf("\nSe ha modificado\n");
                   break;
               case 3:
                   printf("Dame el nuevo modelo:");
                   fflush(stdin);
                   fgets(zap.marca, sizeof(zap.modelo), stdin);
                   printf("\nSe ha modificado\n");
                   break;
               case 4:
                   printf("Dame el nuevo color:");
                   fflush(stdin);
                   fgets(zap.marca, sizeof(zap.color), stdin);
                   printf("\nSe ha modificado\n");
                   break;
               case 5:
                   printf("Dame la nueva talla:");
                   scanf("%f",&zap.talla);
                   printf("\nSe ha modificado\n");
                   break;
           }
           int pos=ftell(inventario)-sizeof(zap);
           fseek(inventario,pos,SEEK_SET);
           fwrite(&zap, sizeof(zap), 1, inventario);
           existe=1;
           break;
        }
    }
    if (existe==0){
        printf("No existe el zapato con ese codigo\n");
    }
    fclose(inventario);
    system("pause");
}

void cantidad(){
	FILE *inventario;
    int numeroRegistros;
    inventario = fopen("inventario.txt", "rb");

    if (inventario == NULL) {
        printf("Error: no se pudo abrir el archivo\n");
        return;
    }

    fseek(inventario, 0, SEEK_END);
    long fileSize = ftell(inventario);
    int recordSize = sizeof(inventario); // replace with the actual data type used in the file
    numeroRegistros = fileSize / recordSize;
    printf("El numero de zapatos es %d\n", numeroRegistros);
    fclose(inventario);
    system("pause");
}
