#include <v8.h>
#include <map>
#include <string>
#include <sstream>

#ifndef RESPONSE_H
#define	RESPONSE_H

class response {
    
protected:
    std::map<std::string, std::string> params;
    std::stringstream content;
    v8::Local<v8::Object> v8Instance;
    
public:
    static response* newInstance();
    void addContent(std::string content);
    static void v8AddContent(const v8::FunctionCallbackInfo<v8::Value>& args);
    std::string getContent();
    v8::Local<v8::Object> getV8Instance();
    
};        

#endif

