#include <string>

#ifndef SAPI_H
#define	SAPI_H

class SapiRequest {
public:
    std::string filename;
    std::string script;
};

class Sapi {
    public:
        virtual bool accept(SapiRequest* sapiRequest) { return false; }
};   


#endif
