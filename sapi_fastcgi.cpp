#include "sapi_cli.h"
#include "sapi_fastcgi.h"
#include <string>

Sapi_Fastcgi::Sapi_Fastcgi(int argc, char** argv) {
    this->argc = argc;
    this->argv = argv;
}

std::string Sapi_Fastcgi::getFilename() {
    if(this->argc < 2) {
        return "";
    }
    
    return this->argv[1];
}