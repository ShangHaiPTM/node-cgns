//
// Created by Han Colin on 2017/12/29.
//

#include "Coord.h"
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

Persistent<Function> Coord::constructor;

Coord::Coord() {
}

Coord::~Coord() {
}

void Coord::Init(Local<Object> exports) {
    Isolate *isolate = exports->GetIsolate();

    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "CgnsZone"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    constructor.Reset(isolate, tpl->GetFunction());
    exports->Set(String::NewFromUtf8(isolate, "CgnsZone"),
                 tpl->GetFunction());
}

void Coord::New(const FunctionCallbackInfo<Value> &args) {
    Isolate *isolate = args.GetIsolate();

    if (args.IsConstructCall()) {
        Coord *obj = new Coord();
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
    } else {
        Local<Context> context = isolate->GetCurrentContext();
        Local<Function> cons = Local<Function>::New(isolate, Coord::constructor);
        Local<Object> result = cons->NewInstance(context).ToLocalChecked();
        args.GetReturnValue().Set(result);
    }
}

Local<Object> Coord::NewInstance(Local<Context> context, int handler, int baseIndex, int zoneIndex, int coordIndex) {
    Isolate *isolate = context->GetIsolate();
    Local<Function> cons = Local<Function>::New(isolate, Coord::constructor);
    Local<Object> result =
            cons->NewInstance(context).ToLocalChecked();

    Coord::Open(result, handler, baseIndex, zoneIndex, coordIndex);

    return result;
}

void Coord::Open(Local<Object> _this, int handler, int baseIndex, int zoneIndex, int coordIndex) {
    V_SET_BEGIN(_this);

        V_SET_NUMBER(_this, "index", coordIndex);

        char name[128];
        CGNS_ENUMT(DataType_t) dataType;
        CGNS_CALL( cg_coord_info( handler, baseIndex, zoneIndex, coordIndex, &dataType, name ) );
        V_SET_STRING(_this, "name", name);
        V_SET_NUMBER(_this, "dataType", dataType);

        // TODO: Read other properties.

    V_SET_END();
}
}