#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

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
	}
	else{
		if (opcion[0]=='N' || opcion[0]=='n')
			printf("\nGracias\n\n");
		else{
			printf ("\nPor favor digite unicamente S o N ");
		}
	}
	fclose(archivo);  
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
void menu(){
	int eleccion;
	printf("Menú:");
	printf("       1 Agregar amigos\n");
	printf("            2 Enviar un mensaje\n");
	printf("            3 Salir\n");
	scanf ("%d", &eleccion);
	if (eleccion==3){
		printf("Gracias por utilizar este servicio");
		exit(0);
	}
	
	if (eleccion == 1){
		AgregarAmigos(); //llama a la funcion agregarAmigos
	}
	else{
		printf ("enviar mensaje");
	}
	leerarchivo(); //llama a la funcion que lee el archivo txt
	ImprimirElementos(leerarchivo());
	BuscarELemento (leerarchivo(), "jef");	
}

void servidor1(){
	printf("hi");
	void error (const char * mensaje){
		fprintf(stderr,"%s", mensaje);
		exit(1);
	}

	//int fdsock, newfdsock, numpuerto;
	int fdsock, newfdsock;

	//DEclaración de variables referentes a sockets
	char buffer[300];
	//buffer en el que se almacenaran los mensajes 
	socklen_t lencliente;
	//numpuerto=atoi("3550");
	struct sockaddr_in servidor_addr, cliente_addr;
	//Crea los sockests en los que se basara el programa
	fdsock= socket(AF_INET, SOCK_STREAM, 0);
	if (fdsock<0){//Manejo de errores en la creación de sockets
		error("La apertura del socket ha fallado\n");	
	}
	bzero((char*)&servidor_addr, sizeof(servidor_addr));
	//Prepara el buffer para el uso estableciendo sus valores en ceros

	servidor_addr.sin_port = htons(55000);//No funciona
	//servidor_addr.sin_port = htons(numpuerto);//No funciona

	//Se asigna un puerto dandole formato con la función htons


	servidor_addr.sin_family = AF_INET;
	servidor_addr.sin_addr.s_addr = INADDR_ANY;
	//Protocolos para conexiones clientes
	if(bind(fdsock, (struct sockaddr *) &servidor_addr,sizeof(servidor_addr))<0){
		error("Error de Conexión\n");
	}
	//Enlace del servidor con el socket
	while(1){
	listen(fdsock,5);
	//Escucha las conexiones entrantes
	lencliente= sizeof(cliente_addr);
	newfdsock = accept(fdsock, (struct sockaddr*)&cliente_addr,&lencliente);
	//Accepta las conexiones entrantes


	if (newfdsock<0){
		error("Error al acceptar\n");
	}
	int mensaje;
	
	mensaje=read(newfdsock,buffer,299);
	if (mensaje<=0){
		error("Error al recibir el mensaje\n");
	}
	else{
		printf(	"\033[2K\r\033[01;32m""Mensaje Recibido:\033[01;32m %s", buffer);
		/* En la linea anterior se utiliza:
	--> \033[2K\r  -> para limpiar el prompt
	--> \033[01;32m  -> poner color verde (para mensaje recibido)
	*/		
	}

	//Detectan los errores
	
	/*if (strcmp(buffer, "salir")==0){
		int P1=getpid();
		printf("\nSesión Terminada\n");*/
//		kill(P1, SIGKILL);
//		break;
	}
}

int main(int argc, char *argv[]){
	printf("Bienvenidos al sistema Clon de Whatsapp\n");
	int control=1;
	servidor1();
	while (control==1){
		menu();
		char* continuar;
		printf("Desea Continuar [s/n]");
		scanf("%s", continuar);
		if(strcmp(continuar, "n")!=0){
			control=2;
		}
	}
	printf("Adios");
	return (1);
	}
	
	

	
	
	



	

	

	









