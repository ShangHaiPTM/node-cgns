//
// Created by Han Colin on 2017/12/29.
//

#ifndef NODE_CGNS_COORD_H
#define NODE_CGNS_COORD_H

#include "cgnslib.h"
#include <iostream>
#include <string>
#include <node/node.h>
#include <node/node_object_wrap.h>


namespace cgns {
class Coord : public node::ObjectWrap {
public:
    static void Init(v8::Local<v8::Object> exports);

    static v8::Local<v8::Object> NewInstance(v8::Local<v8::Context> context, int handler, int baseIndex, int zoneIndex, int coordIndex);

private:
    explicit Coord();

    ~Coord();

    static void New(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void Open(v8::Local<v8::Object> _this, int handler, int baseIndex, int zoneIndex, int coordIndex);

private:
    static v8::Persistent<v8::Function> constructor;
};
}


#endif //NODE_CGNS_COORD_H
