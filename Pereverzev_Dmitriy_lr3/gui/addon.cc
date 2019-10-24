// addon.cc
#include <node.h>
#include "lrs/lr_3/lr_3_methods.cpp"

namespace lr_3
{

using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;
int i = 0;
int *prefix_arr;
int len;

void addon_test(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    Local<String> arg0 = Local<String>::Cast(args[0]);
    String::Utf8Value expr(arg0);

    int ret = test(string(*expr));
    if (!ret)
    {
        i = 0;
        int j = 0;
        len = string(*expr).size();
        prefix_arr = new int[len];
        for (int elem : string(*expr))
            prefix_arr[j++] = elem;
    }
    Local<Number> RET = Number::New(isolate, ret);
    args.GetReturnValue().Set(RET);
}

void addon_step(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    Local<String> arg0 = Local<String>::Cast(args[0]);
    String::Utf8Value expr(arg0);

    prefix_arr = step(prefix_arr, &i, &len);
    string ret = " ";
    for (int j = 0; j < len; j++)
    {
        if (isnum(prefix_arr[j]) == 0)
        {
            ret += (char)prefix_arr[j];
            ret += ' ';
        }
        else
        {
            ret += to_string(prefix_arr[j] - '0') + ' ';
        }
    }
    Local<String> RET = String::NewFromUtf8(isolate, ret.c_str());
    args.GetReturnValue().Set(RET);
}

void addon_step_by_step(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    Local<String> arg0 = Local<String>::Cast(args[0]);
    String::Utf8Value expr(arg0);

    int ret = step_by_step(prefix_arr, &len);
    Local<Number> RET = Number::New(isolate, ret);
    args.GetReturnValue().Set(RET);
}

void Init(Local<Object> exports)
{
    NODE_SET_METHOD(exports, "tester", addon_test);
    NODE_SET_METHOD(exports, "step_up", addon_step);
    NODE_SET_METHOD(exports, "all_steps", addon_step_by_step);
}

NODE_MODULE(addon, Init)

} // namespace lr_3