#ifndef SAPI_FASTCGI_H
#define	SAPI_FASTCGI_H

class Sapi_Fastcgi : public Sapi {
    protected:
int argc;
char** argv;
    
    
public: 
    Sapi_Fastcgi(int argc, char* argv[]);
    std::string getFilename();
    
}; 


#endif

