#include <v8.h>
#include <map>
#include <string>

#ifndef REQUEST_H
#define	REQUEST_H

class request {
 //   v8::String filename;
    std::map<std::string, std::string> params;
    v8::Local<v8::Object> v8Instance;
    
public:
    static request* newInstance();
    static void getParamV8(const v8::FunctionCallbackInfo<v8::Value>& args);
    std::string getParam(std::string key);
    bool hasParam(std::string key);
    v8::Local<v8::Object> getV8Instance();
    void setParam(std::string key, std::string value);
};


#endif

