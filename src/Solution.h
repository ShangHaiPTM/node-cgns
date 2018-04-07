//
// Created by Han Colin on 2017/12/30.
//

#ifndef NODE_CGNS_SOLUTION_H
#define NODE_CGNS_SOLUTION_H


#include "cgnslib.h"
#include <iostream>
#include <string>
#include <node/node.h>
#include <node/node_object_wrap.h>

namespace cgns {
class Solution : public node::ObjectWrap {
public:
    static void Init(v8::Local<v8::Object> exports);

    static v8::Local<v8::Object> NewInstance(v8::Local<v8::Context> context, int handler, int baseIndex, int zoneIndex, int cellDimension);

private:
    explicit Solution();

    ~Solution();

    static void New(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void Open(v8::Local<v8::Object> _this, int handler, int baseIndex, int zoneIndex, int solutionIndex);

private:
    static v8::Persistent<v8::Function> constructor;
};
}

#endif //NODE_CGNS_SOLUTION_H
