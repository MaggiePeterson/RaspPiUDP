#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#define PORT 5801
#define MAX_BUFF 100000

using namespace std;

int main(){
    int bCastSock = 0;
    int srcaddrSize;
    struct sockaddr_in localUdp;
    struct sockaddr_in bCastRecv;
    socklen_t addrlen = sizeof(struct sockaddr_in);
    char  *buffHolder;
    char *hostIpString;
    const int bCastPort = 9999;
    char buffer[MAX_BUFF] = {0};
    ssize_t currPacket;
    struct sockaddr_in serv_addr;

    //setup udp sock
    if ((bCastSock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        perror("UDP socket failed");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(bCastSock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &srcaddrSize, sizeof(srcaddrSize)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    memset(&localUdp, '0', sizeof(serv_addr));
    localUdp.sin_family = AF_INET;
    localUdp.sin_addr.s_addr = INADDR_ANY;
    localUdp.sin_port = htons( bCastPort );

    bind(bCastSock, (struct sockaddr *)&localUdp,sizeof(localUdp));

    do{
        std::cout << "Waiting for broadcast..." <<std::endl;
        memset(&bCastRecv, '0', sizeof(bCastRecv));
        currPacket = recvfrom(bCastSock, buffer, MAX_BUFF, 0, (struct sockaddr *) &bCastRecv, &addrlen);
        cout<<"Packet: "<<currPacket<<endl;
       
    } while(currPacket != -1);
}
