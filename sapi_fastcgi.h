#ifndef SAPI_FASTCGI_H
#define	SAPI_FASTCGI_H

#include "fcgio.h"

class SapiRequest_FastCgi : public SapiRequest {  
public:
    virtual void flush(std::string content);
    virtual void end();
    FCGX_Request* fcgx_request;
};


class Sapi_FastCgi : public Sapi {
protected:
    FCGX_Request* fcgx_request;
    
public: 
    Sapi_FastCgi();
    virtual bool accept(SapiRequest_FastCgi* sapiRequest);
    
};   

#endif

