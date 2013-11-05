#include "bootstrap.h"
#include <limits.h>
#include "gtest/gtest.h"

#include <v8.h>
#include <iostream>

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

int bootstrap(int argc, char* argv[]) {

    // Get the default Isolate created at startup.
    Isolate* isolate = Isolate::GetCurrent();

    // Create a stack-allocated handle scope.
    HandleScope handle_scope(isolate);
    
    // Create a new context.
    Handle<Context> context = Context::New(isolate);
    
    
    // Here's how you could create a Persistent handle to the context, if needed.
    Persistent<Context> persistent_context(isolate, context);

        
    // Enter the created context for compiling and
    // running the hello world script.     
    Context::Scope context_scope(context);

    
    
      
    
    
    
    
    
    // Create a string containing the JavaScript source code.
    Handle<String> source = String::New("'Hello' + ', World!'");

    // Compile the source code.
    Handle<Script> script = Script::Compile(source);

    // Run the script to get the result.
    Handle<Value> result = script->Run();

    // The persistent handle needs to be eventually disposed.
    persistent_context.Dispose();

    // Convert the result to an ASCII string and print it.
    String::AsciiValue ascii(result);
    printf("%s\n", *ascii);
    return 0;
}


GTEST_API_ int tests(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
