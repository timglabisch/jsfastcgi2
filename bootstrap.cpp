#include "bootstrap.h"
#include <limits.h>
#include "gtest/gtest.h"

#include <v8.h>
#include <iostream>
#include "request.h"

#include "sapi_cli.h"
#include "response.h"

TEST(Foo, FooBasic1) {
  EXPECT_EQ(1, 1);
  EXPECT_EQ(1, 1);
  EXPECT_GT(5, 0);
}

TEST(Foo, FooBasic2) {
  EXPECT_EQ(1, 1);
  EXPECT_EQ(1, 1);
  EXPECT_GT(5, 0);
}

TEST(Foo, FooBasic3) {
  EXPECT_EQ(1, 1);
  EXPECT_EQ(1, 1);
  EXPECT_GT(5, 0);
}


using namespace v8;

static void LogCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {
    std::cout << "???" << std::endl;
    
    args.GetReturnValue().Set(
        String::New("DAMN FUCKING SHIT!")
    );
}

void displayHelp() {
    std::cout << std::endl;
    std::cout << "usage program [FILENAME] " << std::endl;
    std::cout << std::endl;
}

void execute(Handle<Context>* context, request* request, response* resonse, std::string fileContent);

int bootstrap(int argc, char* argv[]) {

    Sapi* sapi = new Sapi_Cli(argc, argv);
    
    SapiRequest sapiRequest;
    
    while(sapi->accept(&sapiRequest) == true) {
    
        if(sapiRequest.filename == "") {
            displayHelp();
            return 0;
        }

        if(sapiRequest.script == "") {
            std::cout << std::endl << "File is empty or does not exist" << std::endl;
            return 0;
        } 


        // startup v8
        Isolate* isolate = Isolate::GetCurrent();
        HandleScope handle_scope(isolate);
        Handle<Context> context = Context::New(isolate);
        Persistent<Context> persistent_context(isolate, context);
        Context::Scope context_scope(context);

        request* request = request::newInstance();
        response* response = response::newInstance();

        execute(&context, request, response, sapiRequest.script);

        // The persistent handle needs to be eventually disposed.
        persistent_context.Dispose();

        // Convert the result to an ASCII string and print it.
        //String::AsciiValue ascii1(result1);
        //printf("%s\n", *ascii1);

        std::cout << response->getContent() << std::endl;

        delete request;
        delete response;
    
    }
    
    
    
    
    delete sapi;
   
    
    return 0;
}

void execute(Handle<Context>* context, request* request, response* response, std::string fileContent) {
    Local<ObjectTemplate> o = ObjectTemplate::New();
    o->Set(String::New("hello"), String::New("worldObject!"));
    
    Local<FunctionTemplate> f = FunctionTemplate::New(LogCallback);
    o->Set(String::New("sayHello"), f);
   
    (*context)->Global()->Set(String::New("hello"), String::New("world"));
    (*context)->Global()->Set(String::New("helloObj"), o->NewInstance());
    
    
    // request object
    
    request->setParam("hello", "worldParam2");
    
    (*context)->Global()->Set(String::New("request"), request->getV8Instance());
    
    // response object
    (*context)->Global()->Set(String::New("response"), response->getV8Instance());
    
    
    // Create a string containing the JavaScript source code.
    // Handle<String> source = String::New("9999999999999999 + 'Hello' + ', World!' + hello + helloObj.hello + helloObj.sayHello()");
    
    Handle<String> source = String::New(fileContent.c_str());

    // Compile the source code.
    Handle<Script> script = Script::Compile(source);

    // Run the script to get the result.
    Handle<Value> result1 = script->Run();
}


GTEST_API_ int tests(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

