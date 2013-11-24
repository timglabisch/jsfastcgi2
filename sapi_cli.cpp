#include "sapi.h"
#include "sapi_cli.h"
#include <string>
#include <fstream>

Sapi_Cli::Sapi_Cli(int argc, char** argv) {
    this->argc = argc;
    this->argv = argv;
    this->requestCounter = 0;
}

bool Sapi_Cli::accept(SapiRequest* request) {
    this->requestCounter++;
    
    if(this->argc -1 < this->requestCounter) {
        return false;
    }
    
    std::string filename = this->argv[this->requestCounter];
    std::string script(std::istreambuf_iterator<char>(std::ifstream(filename.c_str()).rdbuf()), std::istreambuf_iterator<char>());
    
    request->filename = filename;
    request->script = script;
    
    return true;
}