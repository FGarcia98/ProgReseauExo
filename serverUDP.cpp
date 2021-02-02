
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include <string>
#include <sys/ioctl.h>

//d�finition additionnel pour un syst�me linux
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

SOCKADDR_IN InfoServer;

//d�finition des typedef
//permet de r��crire une d�claration c'est une sorte d'alias.
// ainsi on utilise SOCKADDR_IN plut�t que de d�clarer une structure sockaddr_in c'est un raccourci

//cr�ation de socket --------------------
//prototype de la cr�ation de socket int socket(int domain, int type, int protocol);
//la fonction retourne un int �� tombe bien on � typedef int SOCKET de d�clarer en en-t�te

// on va donc l'utiliser c'est plus sympa d'avoir a �crire SOCKET que int mais c'est la m�me chose c'est un alias
int main()
{

    SOCKET sock;
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    fprintf(stderr, "socket() message: %s\n", strerror(errno));

    InfoServer.sin_addr.s_addr = htonl(INADDR_ANY);
    InfoServer.sin_family = AF_INET;
    InfoServer.sin_port = htons(9020);
    printf("LISTAGE du port %d...\n", 9020);

    int error_message;
    bool etat = false;
    error_message = ::bind(sock, (SOCKADDR *)&InfoServer, sizeof(InfoServer));

    char buffer[1500];
    memset(buffer, '\0', 1500);
    SOCKADDR_IN _from;
    socklen_t fromlen = sizeof(_from);

    do
    {
        error_message = recvfrom(sock, buffer, 1500, 0, reinterpret_cast<SOCKADDR *>(&_from), &fromlen);
        if (buffer[0] != 'q' && buffer[1] != 'u' && buffer[2] != 'i' && buffer[3] != 't')
        {

            if (error_message < 1)
            {

                fprintf(stderr, "socket() MESSAGE: %s\n", strerror(errno));
            }
            else
            {
                printf(" IP : %s \n", inet_ntoa(_from.sin_addr));
                printf(" Port : %d \n", ntohs(_from.sin_port));
                printf("Reçu : %s \n", buffer);
            }
        }
        else
        {
            etat = true;
            printf(" IP : %s \n", inet_ntoa(_from.sin_addr));
            printf(" Port : %d \n", ntohs(_from.sin_port));
            printf("Reçu : %s \n", buffer);
            printf("fin du programme\n");
        }

    } while (etat != true);

    close(sock);
}
