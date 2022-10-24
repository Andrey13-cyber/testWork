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

char message[256] = "It's a test";
int msgLen = sizeof(message);
int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
struct sockaddr_in group;
struct in_addr localInterface;

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

  
    bzero(&group, sizeof(group));
    group.sin_family = AF_INET;
    group.sin_port = htons(3245);
    group.sin_addr.s_addr = inet_addr("226.1.1.1");

    bind(sockfd,(sockaddr *)&group, sizeof(group));

    //struct ip_mreq localInterface;
    //localInterface.imr_interface.s_addr = INADDR_ANY; 
    //localInterface.imr_multiaddr.s_addr = inet_addr("237.7.7.7");
    localInterface.s_addr = inet_addr("127.0.0.1");

    if ((setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_IF, &localInterface, sizeof(localInterface))) != 0)
    {
       perror("multicast");
       return -2;
    }
    cout << "Joined to multicast group." << endl;

    if(sendto(sockfd, message, msgLen, 0, (struct sockaddr*)&group, sizeof(group)) < 0) {
        perror("Sending message error");
    }
    else 
        cout << "Sending message ....OK\n" << endl;

    close(sockfd);
    return 0;
};
