#include "Zone.h"
#include "helper.h"
#include "v8Helper.h"
#include "Grid.h"
#include "Coord.h"
#include "Solution.h"

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

Persistent<Function> Zone::constructor;

Zone::Zone() {
}

Zone::~Zone() {
}

void Zone::Init(Local<Object> exports) {
    Isolate *isolate = exports->GetIsolate();

    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "CgnsZone"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    constructor.Reset(isolate, tpl->GetFunction());
    exports->Set(String::NewFromUtf8(isolate, "CgnsZone"),
                 tpl->GetFunction());
}

void Zone::New(const FunctionCallbackInfo<Value> &args) {
    Isolate *isolate = args.GetIsolate();

    if (args.IsConstructCall()) {
        Zone *obj = new Zone();
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
    } else {
        Local<Context> context = isolate->GetCurrentContext();
        Local<Function> cons = Local<Function>::New(isolate, Zone::constructor);
        Local<Object> result = cons->NewInstance(context).ToLocalChecked();
        args.GetReturnValue().Set(result);
    }
}

Local<Object> Zone::NewInstance(Local<Context> context, int handler, int baseIndex, int zoneIndex, int cellDimension) {
    Isolate *isolate = context->GetIsolate();
    Local<Function> cons = Local<Function>::New(isolate, Zone::constructor);
    Local<Object> result =
            cons->NewInstance(context).ToLocalChecked();

    Zone::Open(result, handler, baseIndex, zoneIndex, cellDimension);

    return result;
}

void Zone::Open(Local<Object> _this, int handler, int baseIndex, int zoneIndex, int cellDimension) {
    V_SET_BEGIN(_this);

        V_SET_NUMBER(_this, "index", zoneIndex);

        double id;
        CGNS_CALL(cg_zone_id(handler, baseIndex, zoneIndex, &id));
        V_SET_NUMBER(_this, "id", id);

        CGNS_ENUMT(ZoneType_t) type;
        CGNS_CALL(cg_zone_type(handler, baseIndex, zoneIndex, &type));
        V_SET_NUMBER(_this, "type", type);

        char name[128];
        int sizes[9];
        // cgsize_t rangeMin[3] = {1, 1, 1};
        cgsize_t rangeMax[3] = {1, 1, 1};
        CGNS_CALL(cg_zone_read(handler, baseIndex, zoneIndex, name, (int*)(void*)sizes));
        V_SET_STRING(_this, "name", name);
        V_ARRAY_BEGIN(_this, "sizes");
            if (type == CGNS_ENUMV(Structured)) {
                if (cellDimension == 2) {
                    for (int i = 0; i < 6; i++) {
                        V_ARRAY_ADD_NUMBER(sizes[i]);
                    }
                } else if (cellDimension == 3) {
                    for (int i = 0; i < 9; i++) {
                        V_ARRAY_ADD_NUMBER(sizes[i]);
                    }
                }
                rangeMax[0] = sizes[0]; // dimi
                rangeMax[1] = sizes[1]; // dimj
                rangeMax[2] = sizes[2]; // dimk
            } else {
                for (int i = 0; i < 3; i++) {
                    V_ARRAY_ADD_NUMBER(sizes[i]);
                }
                rangeMax[0] = sizes[0]; // nvertices
                rangeMax[1] = sizes[0]; // nvertices
                rangeMax[2] = sizes[0]; // nvertices
            }
        V_ARRAY_END();

        int indexDimension;
        CGNS_CALL(cg_index_dim(handler, baseIndex, zoneIndex, &indexDimension));
        V_SET_NUMBER(_this, "indexDimension", indexDimension);

        int ngrids = 0;
        CGNS_CALL(cg_ngrids(handler, baseIndex, zoneIndex, &ngrids));
        V_ARRAY_BEGIN(_this, "grids");
            for (int i = 0; i < ngrids; i++) {
                V_ARRAY_ADD(Grid::NewInstance(__context, handler, baseIndex, zoneIndex, i + 1));
                // V_ARRAY_ADD_NUMBER(i);
            }
        V_ARRAY_END();

        int ncoords = 0;
        CGNS_CALL(cg_ncoords(handler, baseIndex, zoneIndex, &ncoords));
        V_ARRAY_BEGIN(_this, "coordinates");
            for (int i = 0; i < ncoords; i++) {
                V_ARRAY_ADD(Coord::NewInstance(__context, handler, baseIndex, zoneIndex, i + 1));
            }
        V_ARRAY_END();

        int nsections = 0;
        CGNS_CALL(cg_nsections(handler, baseIndex, zoneIndex, &nsections));
        V_ARRAY_BEGIN(_this, "sections");
            for (int i = 0; i < nsections; i++) {
                V_ARRAY_ADD_NUMBER(i);
            }
        V_ARRAY_END();

        int nsolutions = 0;
        V_ARRAY_BEGIN(_this, "solutions");
            CGNS_CALL(cg_nsols(handler, baseIndex, zoneIndex, &nsolutions));
            for (int i = 0; i < nsolutions; i++) {
                V_ARRAY_ADD(Solution::NewInstance(__context, handler, baseIndex, zoneIndex, i + 1));
            }
        V_ARRAY_END();

    V_SET_END();
}
}
