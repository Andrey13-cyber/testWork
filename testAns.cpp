#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

using namespace std;

const int optval = 1;

char message[256] = "";
int msgLen;
int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
struct sockaddr_in local;
struct ip_mreq group;

int main(){
    /*char addrMulti[20] = "";
    int multiPort;
    char addrUni[20] = "";
    int uniPort;

    cout << "Input pair of multicast address and UDP port: " << endl;
    cin >> addrMulti >> multiPort;

    cout << "Input pair of unicast address and UDP port: " << endl;
    cin >> addrUni >> uniPort;

    cout << "Multicast address: " << addrMulti << endl;
    cout << "UDP Port: " << multiPort << endl;
    cout << "Unicast address: " << addrUni << endl;
    cout << "UDP Port: " << uniPort << endl;*/
    
    if (sockfd < 0)
    {
        perror("socket");
        return -1;
    }
    cout << "Socket is create." << endl;

   
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

  
    bzero(&local, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_port = htons(3245);
    local.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd,(sockaddr *)&local, sizeof(local));

    //struct ip_mreq localInterface;
    //localInterface.imr_interface.s_addr = INADDR_ANY; 
    //localInterface.imr_multiaddr.s_addr = inet_addr("237.7.7.7");
    group.imr_multiaddr.s_addr = inet_addr("226.1.1.1");
    group.imr_interface.s_addr = inet_addr("127.0.0.1");

    if ((setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &group, sizeof(group))) != 0)
    {
       perror("multicast");
       return -2;
    }
    cout << "Joined to multicast group." << endl;

    msgLen = sizeof(message);

    if(read(sockfd, message, msgLen) < 0){
        perror("Reading message error");
        close(sockfd);
        return 0;
    }
    else {
        cout << "Reading message...OK.\n" << endl;
        cout << "The message from multicast server is: \n" << message << endl;
    }

    close(sockfd);
    return 0;
};
