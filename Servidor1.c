#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
int sockfd, newsockfd, portno;
//Variables referentes a sockets
socklen_t clilen;
char buffer[256];
//Buffer donde se almacenaran los mensajes
struct sockaddr_in serv_addr, cli_addr;
int n;
if (argc < 2){
fprintf(stderr,"Ha ocurrido un error, no hay puertos\n");
exit(1);
}
//Verifica si se ingresan los datos correctamente
sockfd = socket(AF_INET, SOCK_STREAM, 0);
//SE inicializa el socket
if (sockfd < 0)
printf("Ha ocurrido un error en la creación del socket");
//Captura errores en la aperturade sockets
bzero((char *) &serv_addr, sizeof(serv_addr));
//Establece los valores a "0"
portno = atoi(argv[1]);
//Se toma de los argumentos el numero de puerto
serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = INADDR_ANY;
serv_addr.sin_port = htons(portno);
//Se establecen los valores de la estructura del servidor (primeras 2 por default)
if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
printf("Ha ocurrido un error en la Conexión");
//Se enlaza en socket para recibir conexiones
listen(sockfd,5);
clilen = sizeof(cli_addr);
newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
//Escucha conexiones entrantes al servidor y las accepta
if (newsockfd < 0)
printf("Ha ocurrido un error al Accpetar");
//Captura los errores al tratar de acceptar conexiones entrantes
bzero(buffer,256);
n = read(newsockfd,buffer,255);
//Lee el mensaje entrante del socket
if (n < 0)
printf("Ha ocurrido un error en la lectura del socket");
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
