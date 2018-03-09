//
// Created by Han Colin on 2017/12/30.
//

#include "Solution.h"
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

Persistent<Function> Solution::constructor;

Solution::Solution() {
}

Solution::~Solution() {
}

void Solution::Init(Local<Object> exports) {
    Isolate *isolate = exports->GetIsolate();

    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "CgnsZone"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    constructor.Reset(isolate, tpl->GetFunction());
    exports->Set(String::NewFromUtf8(isolate, "CgnsZone"),
                 tpl->GetFunction());
}

void Solution::New(const FunctionCallbackInfo<Value> &args) {
    Isolate *isolate = args.GetIsolate();

    if (args.IsConstructCall()) {
        Solution *obj = new Solution();
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
    } else {
        Local<Context> context = isolate->GetCurrentContext();
        Local<Function> cons = Local<Function>::New(isolate, Solution::constructor);
        Local<Object> result = cons->NewInstance(context).ToLocalChecked();
        args.GetReturnValue().Set(result);
    }
}

Local<Object> Solution::NewInstance(Local<Context> context, int handler, int baseIndex, int zoneIndex, int cellDimension) {
    Isolate *isolate = context->GetIsolate();
    Local<Function> cons = Local<Function>::New(isolate, Solution::constructor);
    Local<Object> result =
            cons->NewInstance(context).ToLocalChecked();

    Solution::Open(result, handler, baseIndex, zoneIndex, cellDimension);

    return result;
}

void Solution::Open(Local<Object> _this, int handler, int baseIndex, int zoneIndex, int solutionIndex) {
    V_SET_BEGIN(_this);

        V_SET_NUMBER(_this, "index", solutionIndex);

        char name[128];
        CGNS_ENUMT(GridLocation_t) gridLocation;
        CGNS_CALL(cg_sol_info(handler, baseIndex, zoneIndex, solutionIndex, name, &gridLocation));
        V_SET_STRING(_this, "name", name);
        V_SET_NUMBER(_this, "gridLocation", gridLocation);

        int nfields;
        V_ARRAY_BEGIN(_this, "fields");
            CGNS_CALL( cg_nfields( handler, baseIndex, zoneIndex, solutionIndex, &nfields ) );
            for (int i = 0; i < nfields; i++) {
                V_ARRAY_ADD_NUMBER(i);
            }
        V_ARRAY_END();

    V_SET_END();
}
}