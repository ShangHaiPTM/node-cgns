#include <node/node.h>
#include "Doc.h"
#include "Base.h"
#include "Zone.h"
#include "Grid.h"
#include "Coord.h"
#include "Solution.h"
#include "v8Helper.h"

namespace cgns {
using v8::Local;
using v8::Object;

void InitAll(Local<Object> exports) {
    Doc::Init(exports);
    Base::Init(exports);
    Zone::Init(exports);
    Grid::Init(exports);
    Coord::Init(exports);
    Solution::Init(exports);

    V_ENUM_BEGIN(exports, "SimulationType");
        V_ENUM_ITEM("nullValue", 0);
        V_ENUM_ITEM("userDefined", 1);
        V_ENUM_ITEM("timeAccurate", 2);
        V_ENUM_ITEM("nonTimeAccurate", 3);
    V_ENUM_END();

    V_ENUM_BEGIN(exports, "ZoneType");
        V_ENUM_ITEM("nullValue", 0);
        V_ENUM_ITEM("userDefined", 1);
        V_ENUM_ITEM("structured", 2);
        V_ENUM_ITEM("unstructured", 3);
    V_ENUM_END();

    V_ENUM_BEGIN(exports, "DataType");
        V_ENUM_ITEM("nullValue", 0);
        V_ENUM_ITEM("userDefined", 1);
        V_ENUM_ITEM("integer", 2);
        V_ENUM_ITEM("realSingle", 3);
        V_ENUM_ITEM("realDouble", 4);
        V_ENUM_ITEM("character", 5);
        V_ENUM_ITEM("longInteger", 6);
    V_ENUM_END();

}

NODE_MODULE(NODE_GYP_MODULE_NAME, InitAll)
}