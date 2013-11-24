#include <string>
#include "sapi.h"

#ifndef SAPI_CLI_H
#define	SAPI_CLI_H

class SapiRequest_Cli : public SapiRequest {
public:
    virtual void flush(std::string content);
    virtual void end();
};


class Sapi_Cli : public Sapi {
    protected:
int argc;
char** argv;
int requestCounter;
    
    
public: 
    Sapi_Cli(int argc, char* argv[]);
    bool accept(SapiRequest* sapiRequest);
    
};   


#endif
