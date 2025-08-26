#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum requestMethod{
    GET,
    POST,
    PUT,
    DELETE
};

struct Request{
    short status;
    enum requestMethod reqMet;
    char reqURI[128];
    char HttpVer[9];
};

int parseRequest(void* buffer){

    return 0;
}