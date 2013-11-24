#include "request.h"

void request::getParamV8(const v8::FunctionCallbackInfo<v8::Value>& args) {
        
    v8::Local<v8::External> wrap = v8::Local<v8::External>::Cast(args.Holder()->GetInternalField(0));
    request* r = (request*)wrap->Value();
    
    // the parameter must be a string
    if(!args[0]->IsString()) {
        args.GetReturnValue().Set(v8::Undefined());
        return;
    }
    
    v8::String::AsciiValue paramKey(args[0]);
    
    // if the key doesnt exist, return undefined
    if(!r->hasParam(*paramKey)) {
        args.GetReturnValue().Set(v8::Undefined());
        return;
    }
    
    std::string res = r->getParam(*paramKey);
    args.GetReturnValue().Set(v8::String::New(res.c_str()));
}

bool request::hasParam(std::string key) {
    return this->params.count(key) == 1;
}

std::string request::getParam(std::string key) {
    return this->params[key];
}

v8::Local<v8::Object> request::getV8Instance() {
    return this->v8Instance;
}

void request::setParam(std::string key, std::string value) {
    this->params[key] = value;
}

request* request::newInstance() {
    //Isolate* isolate = Isolate::GetCurrent();
    //HandleScope handle_scope(isolate);
        
    v8::Local<v8::ObjectTemplate> o = v8::ObjectTemplate::New();
    o->SetInternalFieldCount(1);
    v8::Local<v8::FunctionTemplate> f = v8::FunctionTemplate::New(getParamV8);
    o->Set(v8::String::New("getParam"), f);
        
    request* r = new request;
        
    r->v8Instance = o->NewInstance();
    r->v8Instance->SetInternalField(0, v8::External::New((void*)r));
    
    return r;
}