//
// Created by Han Colin on 2017/12/29.
//

#include "Grid.h"
#include "helper.h"
#include "v8Helper.h"

namespace cgns {
using v8::Isolate;
using v8::Local;
using v8::Maybe;
using v8::MaybeLocal;
using v8::Context;
using v8::Value;
using v8::String;
using v8::Object;
using v8::Number;
using v8::Function;
using v8::FunctionTemplate;
using v8::FunctionCallbackInfo;
using v8::Persistent;

Persistent<Function> Grid::constructor;

Grid::Grid() {
}

Grid::~Grid() {
}

void Grid::Init(Local<Object> exports) {
    Isolate *isolate = exports->GetIsolate();

    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "CgnsZone"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    constructor.Reset(isolate, tpl->GetFunction());
    exports->Set(String::NewFromUtf8(isolate, "CgnsZone"),
                 tpl->GetFunction());
}

void Grid::New(const FunctionCallbackInfo<Value> &args) {
    Isolate *isolate = args.GetIsolate();

    if (args.IsConstructCall()) {
        Grid *obj = new Grid();
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
    } else {
        Local<Context> context = isolate->GetCurrentContext();
        Local<Function> cons = Local<Function>::New(isolate, Grid::constructor);
        Local<Object> result = cons->NewInstance(context).ToLocalChecked();
        args.GetReturnValue().Set(result);
    }
}

Local<Object> Grid::NewInstance(Local<Context> context, int handler, int baseIndex, int zoneIndex, int gridIndex) {
    Isolate *isolate = context->GetIsolate();
    Local<Function> cons = Local<Function>::New(isolate, Grid::constructor);
    Local<Object> result =
            cons->NewInstance(context).ToLocalChecked();

    Grid::Open(result, handler, baseIndex, zoneIndex, gridIndex);

    return result;
}

void Grid::Open(Local<Object> _this, int handler, int baseIndex, int zoneIndex, int gridIndex) {
    V_SET_BEGIN(_this);

    V_SET_NUMBER(_this, "index", gridIndex);

    char name[128];
    CGNS_CALL(cg_grid_read(handler, baseIndex, zoneIndex, gridIndex, name));
    V_SET_STRING(_this, "name", name);

    V_SET_END();
}
}
