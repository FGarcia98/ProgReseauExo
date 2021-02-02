//Include pour les sockets 
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h>
#include <string.h>


//d�finition additionnel pour un syst�me linux
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

//d�finition des typedef
//permet de r��crire une d�claration c'est une sorte d'alias.
// ainsi on utilise SOCKADDR_IN plut�t que de d�clarer une structure sockaddr_in c'est un raccourci


//cr�ation de socket --------------------
//prototype de la cr�ation de socket int socket(int domain, int type, int protocol);
//la fonction retourne un int �� tombe bien on � typedef int SOCKET de d�clarer en en-t�te

// on va donc l'utiliser c'est plus sympa d'avoir a �crire SOCKET que int mais c'est la m�me chose c'est un alias
int main() {
	


	SOCKET sock;
	sock = socket(AF_INET, SOCK_DGRAM, 0);

	SOCKADDR_IN destAddrUdp;
	destAddrUdp.sin_addr.s_addr = inet_addr("192.168.64.185");
	destAddrUdp.sin_family = AF_INET;
	destAddrUdp.sin_port = htons(9020);

	char buffer[6];
	buffer[0] = 'h';
	buffer[1] = 'e';
	buffer[2] = 'l';
	buffer[3] = 'l';
	buffer[4] = 'o';
	buffer[5] = '\0';

	int error_message;
	error_message = sendto(sock, buffer, sizeof(buffer), 0, 
	(SOCKADDR*)&destAddrUdp, sizeof(destAddrUdp));

	if (error_message == 0) {
		fprintf(stderr, "sendto message erreur : %s\n", strerror(errno));
	}
	close(sock);
}

