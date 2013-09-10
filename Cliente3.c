#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


//Mensaje de error standar para diferentes casos : D
void error(const char *msg)
{
	perror(msg);
	exit(0);
}
//Main del cliente el cual recibe como parametros el host(en nuestro caso la IP del equipo donde se ejecuta el server) y el numero de puerte designado para la comunicación

int main(int arguc, char *arguv[]) {

	//variables clasicas de los sockects, necesarias para su implementación, excepto por 'Mensaje' la cual es propia del programa, es 		usada para detectar errores de escritura o lectura en sockets

	int sockfd, portno, Mensaje;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	// Tamaño del mensaje a ser enviado
	char buffer[1000];

	// Se realiza la validacion de los argumentos enviados al main de cliente
	if (arguc < 3){
		fprintf(stderr,"El puerto host%s está en uso\n", arguv[0]);
		exit(0);
	}
	
	portno = atoi(arguv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
	//Mensaje de error en caso de fallo en la apertura del socket
	error("Ha ocurrido un error en la apertura socket");
	//Mediante la siguiente linea se optiene la ip del servidor que sera nuestra host
	server = gethostbyname(arguv[1]);

	//Mensaje de error en caso de fallo en la conexion con el host
	if (server == NULL){
	fprintf(stderr,"ERROR,no se ha podido encontrar ningun host \n");
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
	printf("Mensaje a enviar:");
	
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
