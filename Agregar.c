#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Se crea un struct llamado NodosLista para agrupar los datos de la lista
 
typedef struct NodosLista
{
	char username [20];
	char ip [20];
	char puerto [20];
	struct NodosLista *siguienteNodo;
} nodos;
 
typedef nodos *apuntadorNodo; // Puntero a NodosLista
typedef nodos *apuntadorLista;// Puntero a NodosLista
 

 // Función que crea un nodo y retorna un puntero al mismo
 
apuntadorNodo InsertarNodo(char user[20], char Ip [20], char puer [20])
{
	apuntadorNodo nuevo = (apuntadorNodo)malloc(sizeof(nodos)); // reserva memoria para almacenar el nodo de tipo struct
	if (nuevo != NULL){
		strcpy(nuevo->username, user); // Copia el parametro user en el campo username del nodo, strcpy para caracteres
		strcpy(nuevo->ip, Ip);
		strcpy(nuevo->puerto, puer);
		nuevo->siguienteNodo = NULL;//El punto siguiente apunta a nulo
    }
    return nuevo;
}
 
// Funcion que inserta nodos al final de la lista

void InsertaFinal(apuntadorLista *list, apuntadorNodo nodoAnterior, char user [20],char Ip [20],char puer [20])
{
	apuntadorNodo nuevo = InsertarNodo(user, Ip, puer);
	if (nodoAnterior != NULL){
		nuevo->siguienteNodo = nodoAnterior->siguienteNodo;
		nodoAnterior->siguienteNodo = nuevo;
	}else{
		if (*list!= NULL)
			nuevo->siguienteNodo = *list;
		*list = nuevo;
    }
}

// Funcion que revisa si la lista esta vacia

char VaciaLista(apuntadorLista *list)
{
	if (*list==NULL)
		return 1;
	else
		return 0;
}
 
// Funcion que imprime los elementos de la lista

void ImprimirElementos(apuntadorNodo nodoInsertar)
{
	if (nodoInsertar == NULL)
		printf("La lista no tiene elementos \n");
	else{
		while (nodoInsertar != NULL){
			printf("%s %s %s",nodoInsertar->username,nodoInsertar->ip,nodoInsertar->puerto);
            nodoInsertar = nodoInsertar->siguienteNodo;
             if (nodoInsertar != NULL)
                 printf(" - ");
        }
     }
} 

// Funcion que busca un username en la lista

apuntadorNodo BuscarELemento (apuntadorNodo nodoBuscar, char elemento[20]){
	
	apuntadorNodo resultado;
	if (nodoBuscar == NULL)
		printf("La lista no tiene elementos \n");
	else{
		while (nodoBuscar != NULL){
			int x=strcmp(nodoBuscar->username,elemento); // Compara el elemento con lo que está en el nodo en el campo username
			if (x==0){ // Si x es igual a 0, entonces el elemento si se encuentra en la lista
				resultado = nodoBuscar;
				printf ("%s", resultado->username);
				return resultado;
			}else
				nodoBuscar = nodoBuscar->siguienteNodo;
		}	
		resultado=NULL;
	}
	return resultado;
	
	
}

// Funcion que agrega los datos de los amigos correspondientes

int AgregarAmigos (){
	FILE * archivo;
	char opcion [2];
	archivo = fopen ("Amigos.txt", "a");
	char username [20];
	char ip [20];
	char puerto [20];
	printf("Ingrese el username: ");
	scanf("%s",username);
	printf("\nIngrese la IP: ");
	scanf("%s", ip);
	printf("\nIngrese el puerto: ");
	scanf("%s",puerto);
	fprintf(archivo,"%s%s%s%s%s\n",username,";",ip,";",puerto);	//almacena el username, ip y puerto en el txt	
	printf("\nAmigo agregado =D\n");
	printf ("¿Desea agregar otro amigo?\n");
	scanf("%s",opcion);
	if ((opcion[0]=='S')|| (opcion[0]=='s')){
		AgregarAmigos ();
		fclose(archivo);  
	}
	else{
		if (opcion[0]=='N' || opcion[0]=='n')
			printf("\nGracias\n\n");
		else{
			printf ("\nPor favor digite unicamente S o N ");
			AgregarAmigos ();
		}
	}
	return(0);
}

// Funcion que lee el archivo txt creado anteriormente e introduce los datos en la lista

apuntadorNodo leerarchivo(){
	struct datosAmigos {
		char Username[20];
		char IP[20];
		char Puerto [20];
	};
	
	struct datosAmigos datos;
	FILE* archivotxt;
	char cadenaTxt[100]; //linea del txt
	char* separadorLineas;
	nodos *nuevo=NULL;
	archivotxt = fopen ("Amigos.txt", "r");
	while (fscanf (archivotxt, "%s", cadenaTxt) != EOF) {
		separadorLineas = strtok (cadenaTxt,";"); //strtok separa linea de texto en partes, segun el separador definido
		strcpy (datos.Username, separadorLineas);
		separadorLineas = strtok (NULL, ";");
		strcpy (datos.IP, separadorLineas);
		separadorLineas = strtok (NULL, ";");
		strcpy (datos.Puerto, separadorLineas);
		InsertaFinal(&nuevo,nuevo,datos.Username,datos.IP,datos.Puerto);
	}
	fclose (archivotxt); 
	return nuevo;
	
}
 
int main ()
{
	int eleccion;
	printf("Bienvenidos al sistema Clon de Whatsapp\n");
	printf("Menú:");
	printf("       1 Agregar amigos\n");
	printf("            2 Enviar un mensaje\n");
	scanf ("%d", &eleccion);
	if (eleccion == 1)
		AgregarAmigos(); //llama a la funcion agregarAmigos
	else
		printf ("enviar mensaje");
	leerarchivo(); //llama a la funcion que lee el archivo txt
	ImprimirElementos(leerarchivo());
	BuscarELemento (leerarchivo(), "jef");
	return 0;
}
