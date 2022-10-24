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

char message[256] = "It's a test";
int msgLen = sizeof(message);
char ans[256] = "";
int ansLen;
int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
struct sockaddr_in group;
struct in_addr localInterface;

int main(int argc, char *argv[]) { 

    pthread_t tid;
    
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

  
    bzero(&group, sizeof(group));
    group.sin_family = AF_INET;
    group.sin_port = htons(port);
    group.sin_addr.s_addr = inet_addr(adr);

    bind(sockfd,(sockaddr *)&group, sizeof(group));
    localInterface.s_addr = inet_addr("127.0.0.1");

    if ((setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_IF, &localInterface, sizeof(localInterface))) != 0) {
       perror("multicast");
       return -2;
    }
    cout << "Joined to multicast group." << endl;

    if(sendto(sockfd, message, msgLen, 0, (struct sockaddr*)&group, sizeof(group)) < 0) {
        perror("Sending message error");
    }
    else 
        cout << "Sending message ....OK\n" << endl;
    sleep(5);

  
    if(read(sockfd, ans, ansLen) < 0) {
        perror("Reading message error");
        close(sockfd);
        return 0;
    }

    if (recvfrom(sockfd, &ans, sizeof(ans)-1, 0, NULL, NULL) < 0) {
    perror("recvfrom");
    exit(EXIT_FAILURE);
    }

    cout << "Message from unicast: " << message << endl;

    //else {
      //  cout << "Reading message...OK.\n" << endl;
        //cout << "The message from unitcast is: \n" << answer << endl;
    //}

    close(sockfd);
    return 0;
};
