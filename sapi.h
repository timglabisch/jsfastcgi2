#include <string>

#ifndef SAPI_H
#define	SAPI_H

class SapiRequest {
public:
    std::string filename;
    std::string script;
    virtual void flush(std::string content) {};
    virtual void end() {};
};

class Sapi {
    public:
        virtual bool accept(SapiRequest* sapiRequest) { return false; }
};   


#endif
