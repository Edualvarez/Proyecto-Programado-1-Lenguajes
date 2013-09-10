#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
//Mensaje de error standar para diferentes casos : D
void error(const char *msg)
{
	perror(msg);
	exit(0);
}
int servidor(char* puertoser)
{
	int sockfd, newsockfd, portno;
	//Variables referentes a sockets
	socklen_t clilen;
	char buffer[256];
	//Buffer donde se almacenaran los mensajes
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	//Verifica si se ingresan los datos correctamente
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	//SE inicializa el socket
	if (sockfd < 0)
	error("Ha ocurrido un error en la creación del socket");
	//Captura errores en la aperturade sockets
	bzero((char *) &serv_addr, sizeof(serv_addr));
	//Establece los valores a "0"
	portno = atoi(puertoser);
	//Se toma de los argumentos el numero de puerto
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	//Se establecen los valores de la estructura del servidor (primeras 2 por default)
	if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
	error("Ha ocurrido un error en la Conexión");
	//Se enlaza en socket para recibir conexiones
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
	//Escucha conexiones entrantes al servidor y las accepta
	if (newsockfd < 0)
	error("Ha ocurrido un error al Accpetar");
	//Captura los errores al tratar de acceptar conexiones entrantes
	bzero(buffer,256);
	n = read(newsockfd,buffer,255);
	//Lee el mensaje entrante del socket
	if (n < 0)
	error("Ha ocurrido un error en la lectura del socket");
	//Captura errores en la lectura del socket
	printf("\033[2K\r\033[01;32m""Mensaje: %s",buffer);
	printf("\033[01;37m""\n");
	//Imprime el mensaje recibido en color verde
	//Codigo para imprimir en verde ->"\033[01;31m"
	//Codigo para imprimir en Blanco ->"\033[01;37m"
	n = write(newsockfd,"Mensaje recibido",18);
	//Envia un mensaje de confirmación en la recepción del mensaje
	if (n < 0)
	printf("Ha ocurrido un error en el envio del mensaje");
	//Captura errores a la hora de enviar el mensaje de confirmación
	close(newsockfd);
	close(sockfd);
	//Cierra el socket
	return 0;
}

//Main del cliente el cual recibe como parametros el host(en nuestro caso la IP del equipo donde se ejecuta el server) y el numero de puerte designado para la comunicación

int cliente(char* IP, char* puertocl) {

	//variables clasicas de los sockects, necesarias para su implementación, excepto por 'Mensaje' la cual es propia del programa, es 		usada para detectar errores de escritura o lectura en sockets

	int sockfd, portno, Mensaje;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	// Tamaño del mensaje a ser enviado
	char buffer[1000];
	portno = atoi(puertocl);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
	//Mensaje de error en caso de fallo en la apertura del socket
	error("Ha ocurrido un error en la apertura socket");
	//Mediante la siguiente linea se optiene la ip del servidor que sera nuestra host
	server = gethostbyname(IP);

	//Mensaje de error en caso de fallo en la conexion con el host
	if (server == NULL){
	fprintf(stderr,"Ha ocurrido un error,no se ha podido encontrar ningun host \n");
	exit(0);
	}
	//Se rellena con cero el char *
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	//Se copia la direccion en el char *
	bcopy((char *)server->h_addr,
	(char*)&serv_addr.sin_addr.s_addr,server->h_length);
	serv_addr.sin_port = htons(portno);

	//Valida si se logro establecer la conexión
	if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
	error("Ha ocurrido un error de conexion");
	printf("\033[2K\r\033[34m""Mensaje a enviar:");
	scanf("%s",&buffer[0]);
	printf("\033[37m""\n");
	
	//Nuevamente se rellena con 0's
	bzero(buffer,1000);

	//En esta linea se toma el mensaje de la entrada standar :3
	fgets(buffer,999,stdin);
	Mensaje = write(sockfd,buffer,strlen(buffer));
	//Valida si el mensaje fue escrito
	if (Mensaje < 0)
	error("Se ha producido un error al intentar 'escribir' en el socket");
	
	//Rellena con 0's
	bzero(buffer,1000);
	//Se lee el mensaje :3
	Mensaje = read(sockfd,buffer,999);
	//Se valida si el mensaje se logro 'leer'
	if (Mensaje < 0)
	error("Se ha producido un error al intentar 'leer' en el socket");
	printf("%s\n",buffer);
	close(sockfd);
	return 0;
	}
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
				//printf ("%s", resultado->username);
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
		printf("Gracias por utilizar este servicio \n");
		exit(0);
	}
	
	if (eleccion == 1){
		AgregarAmigos(); //llama a la funcion agregarAmigos
	}
	else{
		leerarchivo(); //llama a la funcion que lee el archivo txt
		char Username[20];
		char IP[20];
		char Puerto [20];
		apuntadorNodo resultado;
		printf ("Enviar mensaje\n");
		printf("Ingrese el username del destinatario: \n");
		scanf("%s",Username);
		BuscarELemento(leerarchivo(),Username);
		if (BuscarELemento(leerarchivo(),Username)==NULL){
			printf ("Este amigo no es encuentra en su agenda de contactos \n");	
		}else{
			resultado=BuscarELemento(leerarchivo(),Username);
			strcpy (IP,resultado->ip);
			strcpy(Puerto,resultado->puerto);
			printf("%s\n",IP);
			printf("%s\n",Puerto);
			cliente(IP,Puerto);
			menu();
			}
	
	}
	//leerarchivo(); //llama a la funcion que lee el archivo txt
	//ImprimirElementos(leerarchivo());
	//BuscarELemento (leerarchivo(), "jef");	
}



int main(int argc, char *argv[]){
	int proceso;
	char port[50];
	printf("Ingrese el puerto a utilizar:\n"); 
	scanf("%s", &port[0]);
	proceso=fork();
	if (proceso==-1){
		error("No hay fork");
	}
	// no hay fork

	if (proceso==0){
		servidor(port);
	}
	else{
	printf("Bienvenidos al sistema Clon de Whatsapp\n");
	int control=1;
	while (control==1){
		menu();
		char continuar[50];
		printf("\nDesea Continuar [s/n]\n");
		scanf("%s", &continuar[0]);
		if (continuar[0]=='n' || continuar[0]=='N'){
			control=2;
		}
	}
	}
	
	printf("Adios");
	return (1);
	}

	
