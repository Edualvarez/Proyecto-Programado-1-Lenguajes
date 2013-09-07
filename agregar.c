#include <stdio.h>
#include <stdlib.h>

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

int main ()
{
	AgregarAmigos(); //llama a la funcion agregarAmigos
	
	return 0;
}
