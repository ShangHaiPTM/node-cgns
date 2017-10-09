#include "Doc.h"
#include "helper.h"
#include "v8Helper.h"
#include "Base.h"

namespace cgns {
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
using v8::Array;
using v8::Context;
using v8::MaybeLocal;
using v8::Maybe;
using v8::Exception;
using node::ObjectWrap;

Persistent<Function> Doc::constructor;

Doc::Doc()
        : m_handler(0) {
}

Doc::~Doc() {
    this->close();
}

void Doc::Init(Local<Object> exports) {
    Isolate *isolate = exports->GetIsolate();
    Local<Context> context = isolate->GetCurrentContext();

    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "CgnsDoc"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // Prototype
    NODE_SET_PROTOTYPE_METHOD(tpl, "open", Open);

    constructor.Reset(isolate, tpl->GetFunction());
    V_CALL(exports->Set(context, String::NewFromUtf8(isolate, "CgnsDoc"),
                        tpl->GetFunction()));
}

void Doc::New(const FunctionCallbackInfo<Value> &args) {
    Isolate *isolate = args.GetIsolate();

    if (args.IsConstructCall()) {
        Doc *obj = new Doc();
        obj->Wrap(args.This());
        if (args.Length() >= 1 && args[0]->IsString()) {
            Local<Context> context = isolate->GetCurrentContext();
            MaybeLocal<String> path = args[0]->ToString(context);
            obj->open(args.This(), path.ToLocalChecked());
        }
        args.GetReturnValue().Set(args.This());
    } else {
        // Invoked as plain function `MyObject(...)`, turn into construct call.
        const int argc = 1;
        Local<Value> argv[argc] = {args[0]};
        Local<Context> context = isolate->GetCurrentContext();
        Local<Function> cons = Local<Function>::New(isolate, constructor);
        Local<Object> result = cons->NewInstance(context, argc, argv).ToLocalChecked();
        args.GetReturnValue().Set(result);
    }
}

void Doc::Open(const FunctionCallbackInfo<Value> &args) {
    Isolate *isolate = args.GetIsolate();
    Local<Context> context = isolate->GetCurrentContext();

    if (args.Length() != 1 || !args[0]->IsString()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "open('path/to/file.cgns')")));
        return;
    }

    Local<Object> _this = args.Holder();
    Doc *_This = ObjectWrap::Unwrap<Doc>(_this);
    Local<String> path = args[0]->ToString(context).ToLocalChecked();

    _This->open(_this, path);
}

void Doc::Close(const FunctionCallbackInfo<Value> &args) {
    Doc *_This = ObjectWrap::Unwrap<Doc>(args.Holder());
    _This->close();
}

void Doc::close() {
    if (m_handler != 0) {
        CGNS_CALL(cg_close(m_handler));
        m_handler = 0;
    }
}

void Doc::open(Local<Object> _this, Local<String> path) {
    V_SET_BEGIN(_this);
        String::Utf8Value v(path);

        const int mode = CG_MODE_READ;
        CGNS_CALL(cg_open(*v, mode, &m_handler));

        float version;
        CGNS_CALL(cg_version(m_handler, &version));
        V_SET_NUMBER(_this, "version", version);

        int nbases = 0;
        CGNS_CALL(cg_nbases(m_handler, &nbases));

        V_ARRAY_BEGIN(_this, "bases");
            for (int i = 0; i < nbases; i++) {
                V_ARRAY_ADD(Base::NewInstance(__context, this->m_handler, i + 1));
            }
        V_ARRAY_END();
    V_SET_END();
}
}