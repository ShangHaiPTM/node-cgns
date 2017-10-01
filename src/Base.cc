#include "Base.h"
#include "helper.h"
#include "v8Helper.h"

namespace cgns
{
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

Persistent<Function> Base::constructor;

Base::Base()
{
}

Base::~Base()
{
}

void Base::Init(Local<Object> exports)
{
    Isolate *isolate = exports->GetIsolate();

    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "CgnsBase"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    constructor.Reset(isolate, tpl->GetFunction());
    exports->Set(String::NewFromUtf8(isolate, "CgnsBase"),
                 tpl->GetFunction());
}

void Base::New(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();

    if (args.IsConstructCall())
    {
        Base *obj = new Base();
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
    }
    else
    {
        Local<Context> context = isolate->GetCurrentContext();
        Local<Function> cons = Local<Function>::New(isolate, Base::constructor);
        Local<Object> result =
            cons->NewInstance(context).ToLocalChecked();
        args.GetReturnValue().Set(result);
    }
}

Local<Object> Base::NewInstance(Local<Context> context, int handler, int baseId)
{
    Isolate *isolate = context->GetIsolate();
    Local<Function> cons = Local<Function>::New(isolate, Base::constructor);
    Local<Object> result =
        cons->NewInstance(context).ToLocalChecked();

    Base::Open(result, handler, baseId);

    return result;
}

void Base::Open(Local<Object> _this, int handler, int baseIndex)
{
    V_SET_BEGIN(_this);

    V_SET_NUMBER(_this, "index", baseIndex);

    double id;
    CGNS_CALL(cg_base_id(handler, baseIndex, &id));
    V_SET_NUMBER(_this, "id", id);

    char name[128];
    int cellDim;
    int pyhsDim;
    CGNS_CALL(cg_base_read(handler, baseIndex, name, &cellDim, &pyhsDim));
    V_SET_STRING(_this, "name", name);
    V_SET_NUMBER(_this, "cellDimension", cellDim);
    V_SET_NUMBER(_this, "physicalDimension", pyhsDim);

    SimulationType_t simulationType;
    CGNS_CALL(cg_simulation_type_read(handler, baseIndex, &simulationType));
    V_SET_NUMBER(_this, "simulationType", simulationType);

    int nzones = 0;
    CGNS_CALL(cg_nzones(handler, baseIndex, &nzones));
    V_ARRAY_BEGIN(_this, "zones");
    for (int i = 0; i < nzones; i++) {
        //V_ARRAY_ADD(Zone::NewInstance(baseIndex, i+1))
    }
    V_ARRAY_END();

    V_SET_END();
}
}
