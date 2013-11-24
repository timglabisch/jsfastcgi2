#include "sapi.h"
#include "sapi_fastcgi.h"
#include <string>
#include <fstream>
#include <iostream>
#include <streambuf>


#include "fcgio.h"

void SapiRequest_FastCgi::flush(std::string content) {
    
    fcgi_streambuf cout_fcgi_streambuf(this->fcgx_request->out);
    std::ostream fout(&cout_fcgi_streambuf);
    std::cout << content;
    
    fout << "Content-type: text/html\r\n" <<
               "\r\n" <<
               "<title>CGI Hello!</title>" <<
               "<h1>CGI Hello!</h1>" <<
               "Request number" << "\n" << std::endl;
    
    fout << content;
    std::cout << "uhh";
    
}

void SapiRequest_FastCgi::end() {
    std::cout << std::endl;
}

Sapi_FastCgi::Sapi_FastCgi() {
    int count = 0;
        
    this->fcgx_request = new FCGX_Request();
    
    FCGX_Init();
    FCGX_InitRequest(this->fcgx_request, 0, 0);

}

bool Sapi_FastCgi::accept(SapiRequest_FastCgi* request) {
    
    std::cout << "listen" << std::endl;
    
    int fxcg_accept = FCGX_Accept_r(this->fcgx_request);
    request->fcgx_request = this->fcgx_request;
        
    if(fxcg_accept != 0) {
        std::cout << "fxcg_accept is " << fxcg_accept << std::endl;
        return false;
    }
        
    
    std::cout << "after accept" << std::endl;
    
    /*
    #if HAVE_IOSTREAM_WITHASSIGN_STREAMBUF
        std::cin  = &cin_fcgi_streambuf;
        std::cout = &cout_fcgi_streambuf;
        std::cerr = &cerr_fcgi_streambuf;
    #else
        std::cin.rdbuf(&cin_fcgi_streambuf);
        std::cout.rdbuf(&cout_fcgi_streambuf);
        std::cerr.rdbuf(&cerr_fcgi_streambuf);
    #endif
     */
    
    
        
    std::string filename = FCGX_GetParam("SCRIPT_FILENAME", this->fcgx_request->envp);
    std::string script(std::istreambuf_iterator<char>(std::ifstream(filename.c_str()).rdbuf()), std::istreambuf_iterator<char>());
    
    std::cout << filename << std::endl;
    
    
    request->filename = filename;
    request->script = script;
        
    return true;
}