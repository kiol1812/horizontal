#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>

using namespace std;

const char* host = "192.168.1.43";
int port = 9090;

// ws2_32 library, refer to : https://stackoverflow.com/questions/15660203/inet-pton-identifier-not-found
int inet_pton(int af, const char *src, void *dst)
{
  struct sockaddr_storage ss;
  int size = sizeof(ss);
  char src_copy[INET6_ADDRSTRLEN+1];
//   wchar_t* src_copy_wchar;

  ZeroMemory(&ss, sizeof(ss));
  /* stupid non-const API */
  strncpy (src_copy, src, INET6_ADDRSTRLEN+1);
//   src_copy[INET6_ADDRSTRLEN] = 0;
//   wchar_t* src_copy_wc = new wchar_t[INET6_ADDRSTRLEN+1];
//   mbstowcs(src_copy_wc, src_copy, INET6_ADDRSTRLEN+1);

  if (WSAStringToAddress(src_copy, af, NULL, (struct sockaddr *)&ss, &size) == 0) {
    switch(af) {
      case AF_INET:
    *(struct in_addr *)dst = ((struct sockaddr_in *)&ss)->sin_addr;
    return 1;
      case AF_INET6:
    *(struct in6_addr *)dst = ((struct sockaddr_in6 *)&ss)->sin6_addr;
    return 1;
    }
  }
  return 0;
}

int main(){
    SOCKET sock;
    struct sockaddr_in serv_name;
    int status;
    char indata[1024]={0}, outdata[1024]={0};

    WSADATA wsa = {0};
    WORD wVer = MAKEWORD(2, 2);
    WSAStartup(wVer, &wsa);

    if(WSAStartup(MAKEWORD(2, 2), &wsa) != NO_ERROR){
        printf("Error: init winsock\n");
        exit(1);
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock==-1){
        perror("Socket creation error");
        exit(1);
    }

    serv_name.sin_family = AF_INET;
    inet_pton(AF_INET, host, &serv_name.sin_addr);
    serv_name.sin_port = htons(port);

    status = connect(sock, (struct sockaddr *) &serv_name, sizeof(serv_name));
    if(status==-1) {
        perror("Connection error");
        exit(1);
    }

    string message = "C++ socket test";
    for(int i=0; i<message.length(); i++) outdata[i]=message[i];
    while(1){
        printf("send %s\n", outdata);
        send(sock, outdata, strlen(outdata), 0);

        int nbytes = recv(sock, indata, sizeof(indata), 0);
        if(nbytes<=0){
            closesocket(sock);
            printf("server closed connection");
            break;
        }
        printf("recv: %s\n", indata);
        Sleep(1000);
    }
    WSACleanup();
    return 0;
}