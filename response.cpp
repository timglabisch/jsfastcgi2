#include "response.h"


void response::addContent(std::string content) {
    this->content << content;
}

void response::v8AddContent(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Local<v8::External> wrap = v8::Local<v8::External>::Cast(args.Holder()->GetInternalField(0));
    response* r = (response*)wrap->Value();
    
    // the parameter must be a string
    if(!args[0]->IsString()) {
        args.GetReturnValue().Set(v8::False());
        return;
    }
    
    v8::String::AsciiValue content(args[0]);
    
    r->addContent(*content);
}

std::string response::getContent() {
    return this->content.str();
}

v8::Local<v8::Object> response::getV8Instance() {
    return this->v8Instance;
}

response* response::newInstance() {
    v8::Local<v8::ObjectTemplate> o = v8::ObjectTemplate::New();
    o->SetInternalFieldCount(1);
    v8::Local<v8::FunctionTemplate> f = v8::FunctionTemplate::New(v8AddContent);
    o->Set(v8::String::New("addContent"), f);
    
    response* r = new response;
    r->v8Instance = o->NewInstance();
    r->v8Instance->SetInternalField(0, v8::External::New((void*)r));
    
    return r;    
}

