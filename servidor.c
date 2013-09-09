#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
	void error (const char * mensaje){
		perror(mensaje);
		exit(1);
	}

	int fdsock, newfdsock, numpuerto;
	//DEclaración de variables referentes a sockets
	char buffer[300];
	//buffer en el que se almacenaran los mensajes 
	socklen_t lencliente;
	numpuerto=atoi("172.26.100.164:34315");
	struct sockaddr_in servidor_addr, cliente_addr;
	//Crea los sockests en los que se basara el programa
	fdsock= socket(AF_INET, SOCK_STREAM, 0);
	if (fdsock<0){//Manejo de errores en la creación de sockets
		error("La apertura del socket ha fallado\n");	
	}
	bzero((char*)&servidor_addr, sizeof(servidor_addr));
	//Prepara el buffer para el uso estableciendo sus valores en ceros

	servidor_addr.sin_port = htons(numpuerto);//No funciona
	//Se asigna un puerto dandole formato con la función htons


	servidor_addr.sin_family = AF_INET;
	servidor_addr.sin_addr.s_addr = INADDR_ANY;
	//Protocolos para conexiones clientes
	if(bind(fdsock, (struct sockaddr *) &servidor_addr,sizeof(servidor_addr))<0){
		error("Error de Conexión\n");
	}
	//Enlace del servidor con el socket
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
	printf("ola ke ase");

	//Detectan los errores
	return 1;
}	
	
	
	



	

	

	









