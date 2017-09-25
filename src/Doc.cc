#include "Doc.h"
#include "helper.h"

using std::string;
using v8::Persistent;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::Persistent;
using v8::String;
using v8::Value;
using v8::Context;
using v8::MaybeLocal;
using v8::Maybe;
using node::ObjectWrap;

Persistent<Function> Doc::constructor;

Doc::Doc(MaybeLocal<String> path)
    : m_handler(0)
{
    if (!path.IsEmpty())
    {
        this->open(path.ToLocalChecked());
    }
}

void Doc::Init(Local<Object> exports)
{
    Isolate *isolate = exports->GetIsolate();

    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "CgnsDoc"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // Prototype
    NODE_SET_PROTOTYPE_METHOD(tpl, "open", Open);

    constructor.Reset(isolate, tpl->GetFunction());
    exports->Set(String::NewFromUtf8(isolate, "CgnsDoc"),
                 tpl->GetFunction());
}

void Doc::New(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();

    if (args.IsConstructCall())
    {
        Local<Context> context = isolate->GetCurrentContext();
        // Invoked as constructor: `new MyObject(...)`
        MaybeLocal<String> path = args[0]->ToString(context);
        Doc *obj = new Doc(path);
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
    }
    else
    {
        // Invoked as plain function `MyObject(...)`, turn into construct call.
        const int argc = 1;
        Local<Value> argv[argc] = {args[0]};
        Local<Context> context = isolate->GetCurrentContext();
        Local<Function> cons = Local<Function>::New(isolate, constructor);
        Local<Object> result =
            cons->NewInstance(context, argc, argv).ToLocalChecked();
        args.GetReturnValue().Set(result);
    }
}

void Doc::Open(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    Local<Context> context = isolate->GetCurrentContext();
    Doc *obj = ObjectWrap::Unwrap<Doc>(args.Holder());
    obj->open(args[0]->ToString(context).ToLocalChecked());
}

void Doc::Close(const FunctionCallbackInfo<Value> &args)
{
    Doc *obj = ObjectWrap::Unwrap<Doc>(args.Holder());
    obj->close();
}

void Doc::open(Local<String> path)
{
    String::Utf8Value v(path);
    Local<Object> _This = this->handle();
    Isolate* isolate = _This->GetIsolate();
    Local<Context> context = isolate->GetCurrentContext();

    const int mode = CG_MODE_READ;
    CGNS_CALL(cg_open(*v, mode, &m_handler));

    float version;
    CGNS_CALL(cg_version(m_handler, &version));
    V8_CALL(_This->Set(context,
                               String::NewFromUtf8(isolate, "version"),
                               Number::New(isolate, version)));
}

void Doc::close()
{
    if (m_handler != 0)
    {
        CGNS_CALL(cg_close(m_handler));
        m_handler = 0;
    }
}
