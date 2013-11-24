#include "sapi_cli.h"
#include <string>

Sapi_Cli::Sapi_Cli(int argc, char** argv) {
    this->argc = argc;
    this->argv = argv;
}

std::string Sapi_Cli::getFilename() {
    if(this->argc < 2) {
        return "";
    }
    
    return this->argv[1];
}