#pragma once

#include "cgnslib.h"
#include <iostream>
#include <string>
#include <node/node.h>
#include <node/node_object_wrap.h>

namespace cgns {
class Doc : public node::ObjectWrap {
public:
    static void Init(v8::Local<v8::Object> exports);

private:
    explicit Doc();

    ~Doc();

    static void New(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void Open(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void Close(const v8::FunctionCallbackInfo<v8::Value> &args);

    void open(v8::Local<v8::Object> _this, v8::Local<v8::String> path);

    void close();

private:
    int m_handler;

    static v8::Persistent<v8::Function> constructor;
};
}
