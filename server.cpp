#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <thread>
#include <time.h>
#include <iostream>
#include <string.h>

#define PORT 5801
#define BUFFER_SIZE 1*800*600
using namespace std;


int main() {

    int sock;                         /* Socket */
    struct sockaddr_in broadcastAddr; /* Broadcast address */
    int broadcastPermission = 1;          /* Socket opt to set permission to broadcast */

    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        perror("UDP socket failed");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission, sizeof(broadcastPermission)) < 0)
    {
        perror("Could not set UDP permissions");
        exit(EXIT_FAILURE);
    }

    memset(&broadcastAddr, 0, sizeof(broadcastAddr));   /* Zero out structure */
    broadcastAddr.sin_family = AF_INET;                 /* Internet address family */
    broadcastAddr.sin_addr.s_addr = INADDR_BROADCAST;   /* Broadcast IP address */
    broadcastAddr.sin_port = htons(PORT);               /* Broadcast port */
    std::cout<<"Starting beacon"<<std::endl;


    string data = "maggie :3";

    while(1){

         sendto(sock, data.c_str(), data.length(), 0, (struct sockaddr *)&broadcastAddr, sizeof(broadcastAddr));


    }
}
