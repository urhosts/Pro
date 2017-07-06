/*************************************************************************
	> File Name: main.c
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Wed 05 Jul 2017 08:26:32 AM CST
 ************************************************************************/

#include "httpd.h"

static void usage(const char *proc)
{
    printf("Usage: %s [local_ip][local_port]", proc);
}

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        usage(argv[0]);
        return 1;
    }

    int listen_sock = startup(argv[1], atoi(argv[2]));
    while(1)
    {
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
        int new_sock = accept(listen_sock, (struct sockaddr*)&client, &len);
        if(new_sock < 0)
        {
            print_log("accept", FATAL);
            continue;
        }
        printf("get client [%s:%d]\n",\
              inet_ntoa(client.sin_addr),\
              ntohs(client.sin_port));
        pthread_t id;
        int ret = pthread_create(&id, NULL, handler_request, (void *)new_sock);
        if(ret != 0)
        {
            print_log("pthread_creat", FATAL);
            close(new_sock);
        }
        else
        {
            pthread_detach(id);
        }
    }
    close(listen_sock);
    return 0;
}
