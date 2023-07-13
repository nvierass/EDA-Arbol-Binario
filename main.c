#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct datosNodo{
	char nombre[16],nombre2[16],apellido[16],apellido2[16];
	int num1;
	int num2;
	int num3;
	struct datosNodo *hijoDerecho;
	struct datosNodo *hijoIzquierdo;
}nodo;

typedef struct datosArbol{
	int cantidadNodos;
	struct datosNodo* raiz;
}arbol;

//Firmas
//Compara los numeros de dos nodos, se utiliza para evitar redundancias en el arbol
int mismoNumero(nodo* n1,nodo* n2);
int nodoInsertado(nodo* buscado,arbol t);
int compararString(char str1[],char str2[]);
int buscarNumero(FILE* resultados,nodo* nombre,nodo* raiz)
int recorrerContactos(nodo* raiz);
//Compara dos nombres de nodos para verificar cual es mayor alfabeticamente comparando caracter a caracter sus valores ASCII
//En caso de ser iguales retorna el valor 2.
int mayorIgual(nodo* nodoNuevo,nodo* indice);
arbol insertarNodo(nodo* nodoNuevo,arbol arb);
nodo* crearNodo(char nombre[],char nombre2[],char apellido[],char apellido2[],int num1,int num2,int num3);
arbol crearArbol();
void printNumero(FILE* salida,nodo* n);
void inOrden(nodo* abb);
void liberarArbol(nodo* raiz);



int mismoNumero(nodo* n1,nodo* n2){
	if(n1->num1==n2->num1 && n1->num2==n2->num2 && n1->num3==n2->num3){
		return 1;
	}
	return 0;
}
nodo* crearNodo(char nombre[],char nombre2[],char apellido[],char apellido2[],int num1,int num2,int num3){
	nodo* nuevo=(nodo*)malloc(sizeof(nodo));
	if(!nuevo){
		return NULL;
	}
	strcpy(nuevo->nombre,nombre);
	strcpy(nuevo->nombre2,nombre2);
	strcpy(nuevo->apellido,apellido);
	strcpy(nuevo->apellido2,apellido2);
	nuevo->num1=num1;
	nuevo->num2=num2;
	nuevo->num3=num3;
	nuevo->hijoDerecho=NULL;
	nuevo->hijoIzquierdo=NULL;
	return nuevo;
}
arbol crearArbol(){
	int i;
	arbol nuevo;
	nodo* buffer;
	char nombre[16],nombre2[16],apellido[16],apellido2[16];
	int num1,num2,num3;
	FILE* entrada=fopen("Telefonos.in","r");
	nuevo.raiz=NULL;
	if(!entrada){		
		return nuevo;
	}
	fscanf(entrada,"%d",&nuevo.cantidadNodos);
	for(i=1;i<=nuevo.cantidadNodos;i++){
		fscanf(entrada,"%s",nombre);
		fscanf(entrada,"%s",nombre2);
		fscanf(entrada,"%s",apellido);
		fscanf(entrada,"%s",apellido2);
		fgetc(entrada);fgetc(entrada);fgetc(entrada);fgetc(entrada);fgetc(entrada);
		fscanf(entrada,"%d",&num1);
		fscanf(entrada,"%d",&num2);
		fscanf(entrada,"%d",&num3);
		buffer=crearNodo(nombre,nombre2,apellido,apellido2,num1,num2,num3);
		if(!buffer){
			return nuevo;
		}
		if(!nodoInsertado(buffer,nuevo)){
			nuevo=insertarNodo(buffer,nuevo);
		}
		else{
			free(buffer);
		}
	}
	fclose(entrada);
	return nuevo;
}
void inOrden(nodo* abb){
    if(abb)
    {
        inOrden(abb->hijoIzquierdo);
        printf("%s %s %s %s +56 %d %d %d.\n", abb->nombre,abb->nombre2,abb->apellido,abb->apellido2,abb->num1,abb->num2,abb->num3);
        inOrden(abb->hijoDerecho);
    }
}
arbol insertarNodo(nodo* nodoNuevo,arbol arb){
	if(arb.raiz==NULL){
		arb.raiz=nodoNuevo;
		printf("Se ha insertado el numero +56 %d %d %d\n",nodoNuevo->num1,nodoNuevo->num2,nodoNuevo->num3);
		return arb;
	}
	int insertado=0;
	nodo* indice = arb.raiz;
	while(!insertado){
		if(mayorIgual(nodoNuevo,indice)){
			if(indice->hijoDerecho==NULL){
				indice->hijoDerecho=nodoNuevo;
				insertado=1;
				printf("Se ha insertado el numero +56 %d %d %d\n",nodoNuevo->num1,nodoNuevo->num2,nodoNuevo->num3);
			}
			indice=indice->hijoDerecho;
		}
		else{
			if(indice->hijoIzquierdo==NULL){
				indice->hijoIzquierdo=nodoNuevo;
				insertado=1;
				printf("Se ha insertado el numero +56 %d %d %d\n",nodoNuevo->num1,nodoNuevo->num2,nodoNuevo->num3);
			}
			indice=indice->hijoIzquierdo;
		}
	}
	return arb;
}
int nodoInsertado(nodo* buscado,arbol t){
	nodo* indice = t.raiz;
	int x;
	if(!indice){
		return 0;
	}
	int encontrado=0;
	while(!encontrado){
		x=mayorIgual(buscado,indice);
		if(x==1){
			if(indice->hijoDerecho==NULL){
				return 0;
			}
			indice=indice->hijoDerecho;
		}
		else if(x==2 && mismoNumero(buscado,indice)){
			return 1;
		}
		else{
			if(indice->hijoIzquierdo==NULL){
				return 0;
			}
			indice=indice->hijoIzquierdo;
		}
	}
	return 0;
}
int compararString(char str1[],char str2[]){
	int i=0;
	while(i <16){
		if((int)str1[i] > (int)str2[i]){
			return 1;
		}
		if((int)str1[i] == (int)str2[i]){
			i++;
		}
		if((int)str1[i] <(int)str2[i]){
			return 0;
		}
	}
	return 1;	
}
void liberarArbol(nodo* raiz){
	nodo* indiceIzq=raiz->hijoIzquierdo;
	nodo* indiceDer=raiz->hijoDerecho;
	free(raiz);
	if(indiceIzq!=NULL){
		liberarArbol(indiceIzq);
	}
	if(indiceDer!=NULL){
		liberarArbol(indiceDer);
	}
}
int mayorIgual(nodo* nodoNuevo,nodo* indice){
	if(strcmp(nodoNuevo->nombre,indice->nombre)==0){
		if(strcmp(nodoNuevo->nombre2,indice->nombre2)==0){
			if(strcmp(nodoNuevo->apellido,indice->apellido)==0){
				if(strcmp(nodoNuevo->apellido2,indice->apellido2)==0){
					return 2;
				}
				else{
					return compararString(nodoNuevo->apellido2,indice->apellido2);
				}
			}
			else{
				return compararString(nodoNuevo->apellido,indice->apellido);
			}
		}
		else{
			return compararString(nodoNuevo->nombre2,indice->nombre2);
		}
	}
	else{
		return compararString(nodoNuevo->nombre,indice->nombre);
	}
	return -1;
}
int buscarNumero(FILE* resultados,nodo* nombre,nodo* raiz){
	fprintf(resultados,"\n%s %s %s %s ",nombre->nombre,nombre->nombre2,nombre->apellido,nombre->apellido2);
	int comparados;
	nodo* indice = raiz;
	if(!indice){
		return 0;
	}
	while(indice!=NULL){
		comparados=mayorIgual(nombre,indice);
		if(comparados==2){ // Si los nombres son exactamente iguales se imprime el numero en el archivo de salida.
			printNumero(resultados,indice);
			indice=indice->hijoDerecho;//Se sigue recorriendo el subarbol derecho para verificar que no existe el mismo contacto con otro numero.
		}
		else if(comparados==1){
			indice=indice->hijoDerecho;
		}
		else{
			indice=indice->hijoIzquierdo;
		}
	}
	return 1;
}
int recorrerContactos(nodo* raiz){
	FILE* buscados=fopen("Buscados.in","r");
	FILE* resultados=fopen("TelefonosEncontrados.out","w"); 
	if(!buscados){
		printf("\nError en la lectura de numeros buscados.");
		return 0;
	}
	nodo* aux;
	int nBuscados,i;
	char n[16],n2[16],a[16],a2[16];
	fscanf(buscados,"%d",&nBuscados);
	for(i=0;i<nBuscados;i++){
		fscanf(buscados,"%s",n);
		fscanf(buscados,"%s",n2);
		fscanf(buscados,"%s",a);
		fscanf(buscados,"%s",a2);
		aux=crearNodo(n,n2,a,a2,0,0,0);
		buscarNumero(resultados,aux,raiz);
	}
	fclose(resultados);
	fclose(buscados);
	return 1;
}
void printNumero(FILE* salida,nodo* n){
	fprintf(salida,"- +56 %d ",n->num1);
	if(n->num2>=1000){
		fprintf(salida," %d",n->num2);
	}
	if(n->num2<1000 && n->num2>=100){
		fprintf(salida," 0%d",n->num2);
	}
	if(n->num2<100 && n->num2>=10){
		fprintf(salida," 00%d",n->num2);
	}
	if(n->num2<10 && n->num2>=0){
		fprintf(salida," 000%d",n->num2);
	}
	if(n->num3>=1000){
		fprintf(salida," %d",n->num3);
	}
	if(n->num3<1000 && n->num3>=100){
		fprintf(salida," 0%d",n->num3);
	}
	if(n->num3<100 && n->num3>=10){
		fprintf(salida," 00%d",n->num3);
	}
	if(n->num3<10 && n->num3>=0){
		fprintf(salida," 000%d",n->num3);
	}
}



int main(){
	time_t inicio,fin;
	inicio=time(NULL);
	arbol t=crearArbol();
	if(t.raiz==NULL){
		printf("Error en la lectura de contactos.\n");
		getchar();
		return -1;
	}
	printf("***************Recorrido inOrden********************\n");
	inOrden(t.raiz);
	printf("*************Fin Recorrido inOrden******************\n");
	recorrerContactos(t.raiz);
	liberarArbol(t.raiz);
	printf("\nSe ha terminado de buscar los numeros de contacto.");
	fin=time(NULL);
	printf("\nTiempo de ejecucion %f",difftime(fin,inicio));
	return 0;
}