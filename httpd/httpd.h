/*************************************************************************
	> File Name: httpd.h
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Wed 05 Jul 2017 08:26:01 AM CST
 ************************************************************************/

#ifndef _HTTPD_H
#define _HTTPD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <assert.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <pthread.h>

#define SUCCESS 0
#define NOTICE  1
#define WARMING 2
#define ERROR   3
#define FATAL   4 

#define SIZE 1024


int startup(const char *_ip, int _port);
void *handler_request(void *sock);
void printf_log(const char *msg, int level);

#endif
