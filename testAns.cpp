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
#include <pthread.h>

using namespace std;

const int optval = 1;

char message[256] = "";
//char ans[256];
//int ansLen;
int msgLen = 256;
int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
struct sockaddr_in local;
struct ip_mreq group;

int main(int argc, char *argv[]){
    
   if (argc != 3) {
       cout << "You should input multicast address and port\n" << endl;
       return 1;
    }

    char* adr = argv[1]; 
    int port = atoi(argv[2]);
    
    if (sockfd < 0) {
        perror("socket");
        return -1;
    }
    cout << "Socket is create." << endl;

   
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    bzero(&local, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_port = htons(port);
    local.sin_addr.s_addr = inet_addr(adr);

    bind(sockfd,(sockaddr *)&local, sizeof(local));

    group.imr_multiaddr.s_addr = inet_addr(adr);
    group.imr_interface.s_addr = inet_addr("127.0.0.1");

    if ((setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &group, sizeof(group))) != 0) {
       perror("multicast");
       return -2;
    }
    cout << "Joined to multicast group." << endl;

    /* //msgLen = sizeof(message);

    //проверка предположения
    if ((setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &group, sizeof(group))) != 0) {
       perror("multicast");
       return -2;
    } */

    
    socklen_t flag;
    if(recvfrom(sockfd, message, msgLen, 0, (struct sockaddr*)&local, &flag) < 0) {
        perror("Reading message error");
        close(sockfd);
        return 0;
    }
    else {
        cout << "Reading message...\n" << endl;
        cout << "The message from multicast server is: \n" << message << endl;
    }

    //cout << "Input message to send multicast:" << endl;
    //cin >> ans;

    if(sendto(sockfd, message, msgLen, 0, (struct sockaddr*)&local, sizeof(local)) < 0) {
        perror("Sending message error");
    }
    else 
        cout << "Sending message...\n" << endl; 

    sleep(10);
    close(sockfd);
    return 0;
};
