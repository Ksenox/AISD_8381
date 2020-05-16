// addon_3.cc
#include <node.h>
#include "cw/cw_methods.cpp"

namespace cw
{

using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;

//cw

TREE *tree = NULL;
long long time_of_test = 0;
long long time_of_test_2 = 0;
string elements_of_test = "";
int steps = 0;

void addon_build_tree(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    Local<String> arg0 = Local<String>::Cast(args[0]);
    Local<Number> arg1 = Local<Number>::Cast(args[1]);
    String::Utf8Value expr(arg0);

    string tree_str = "(",
           value;
    int count = (int)(arg1->NumberValue());
    string input = string(*expr);
    istringstream in(input);

    //for time
    chrono::time_point<chrono::system_clock> start;

    for (; count > 0; count--)
    {
        in >> value;

        //turns
        elements_of_test += value + " "; //elems for data
        start = chrono::system_clock::now();
        tree = insert(tree, value, steps);
        time_of_test += chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now() - start).count(); //time for data
    }

    bypass(tree, tree_str);

    Local<String> RET = String::NewFromUtf8(isolate, tree_str.c_str());
    args.GetReturnValue().Set(RET);
}

void addon_take_time(const FunctionCallbackInfo<Value> &args) //send time_of_test
{
    Isolate *isolate = args.GetIsolate();

    Local<Number> RET = Number::New(isolate, time_of_test);
    args.GetReturnValue().Set(RET);
}

void addon_take_time_2(const FunctionCallbackInfo<Value> &args) //send time_of_test_@
{
    Isolate *isolate = args.GetIsolate();

    Local<Number> RET = Number::New(isolate, time_of_test_2);
    args.GetReturnValue().Set(RET);
}

void addon_take_elems(const FunctionCallbackInfo<Value> &args) //send elements_of_test
{
    Isolate *isolate = args.GetIsolate();
    Local<String> RET = String::NewFromUtf8(isolate, elements_of_test.c_str());
    args.GetReturnValue().Set(RET);
}

void addon_zeroing(const FunctionCallbackInfo<Value> &args) //zeroing data
{
    Isolate *isolate = args.GetIsolate();

    tree = NULL;
    time_of_test = 0;
    time_of_test_2 = 0;
    elements_of_test = "";
    steps = 0;

    Local<String> RET = String::NewFromUtf8(isolate, to_string(time_of_test).c_str());
    args.GetReturnValue().Set(RET);
}

void addon_data_test(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    Local<String> arg0 = Local<String>::Cast(args[0]);
    Local<Number> arg1 = Local<Number>::Cast(args[1]);
    String::Utf8Value expr(arg0);

    TREE *tree_1 = NULL;
    TREE *tree_2 = NULL;
    int count = (int)(arg1->NumberValue());
    string value;
    elements_of_test = string(*expr);
    istringstream in(elements_of_test);

    chrono::time_point<chrono::system_clock> start;

    for (; count > 0; count--)
    {
        in >> value;

        //turns;
        start = chrono::system_clock::now();
        tree_1 = insert(tree_1, value, steps);
        time_of_test += chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now() - start).count(); //time for data

        //without turns
        start = chrono::system_clock::now();
        tree_2 = insert_2(tree_2, value);
        time_of_test_2 += chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now() - start).count(); //time for data
    }

    Local<String> RET = String::NewFromUtf8(isolate, "DONE");
    args.GetReturnValue().Set(RET);
}

void addon_data_random(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    Local<Number> arg0 = Local<Number>::Cast(args[0]);
    Local<String> RET = String::NewFromUtf8(isolate, gen_random((int)(arg0->NumberValue())).c_str());
    args.GetReturnValue().Set(RET);
}

void addon_take_steps(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();

    Local<Number> RET = Number::New(isolate, steps);
    args.GetReturnValue().Set(RET);
}

void Init(Local<Object> exports)
{
    //cw
    NODE_SET_METHOD(exports, "build_tree", addon_build_tree);
    NODE_SET_METHOD(exports, "take_time", addon_take_time);
    NODE_SET_METHOD(exports, "take_time_2", addon_take_time_2);
    NODE_SET_METHOD(exports, "take_steps", addon_take_steps);
    NODE_SET_METHOD(exports, "take_elems", addon_take_elems);
    NODE_SET_METHOD(exports, "zeroing", addon_zeroing);
    NODE_SET_METHOD(exports, "data_test", addon_data_test);
    NODE_SET_METHOD(exports, "data_rand", addon_data_random);
}

NODE_MODULE(addon, Init)

} // namespace cw
