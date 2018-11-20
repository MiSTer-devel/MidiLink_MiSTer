#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <linux/soundcard.h>

#define USE_UDP

static struct sockaddr_in serv_addr;

///////////////////////////////////////////////////////////////////////////////////////
//
// int socket_client_connect(char * ipAddr, int port)
//
int socket_client_connect(char * ipAddr, int port)
{
    int sock = 0, valread;
#ifdef USE_UDP
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
#else
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
#endif
    {
        printf("Socket creation error\n");
        return -1;
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    //printf("TEST --> inet_pton\n");
    if(inet_pton(AF_INET, ipAddr, &serv_addr.sin_addr)<=0)
    {
        printf("Invalid address / Address not supported \n");
        return -1;
    }
#ifndef USE_UDP
    printf("CONNECT : %s port %d\n", ipAddr, port);
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("Connection Failed \n");
        return -1;
    }

    printf("Connected to %s port %d", ipAddr, port);
#endif
    return sock;
}

///////////////////////////////////////////////////////////////////////////////////////
//
// int socket_client_connect(char * ipAddr, int port)
//
void socket_write(int sock, char * buf, int bufLen)
{
#ifdef USE_UDP
        sendto(sock,
               (const char *) buf,
               bufLen,
               MSG_CONFIRM,
               (const struct sockaddr *) &serv_addr,
               sizeof(serv_addr));
#else
        send(sock, midiPacket, sizeof(midiPacket), 0);
#endif
}
