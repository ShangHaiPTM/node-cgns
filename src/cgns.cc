#include <node/node.h>
#include "Doc.h"
#include "Base.h"
#include "v8Helper.h"

namespace cgns
{
using v8::Local;
using v8::Object;

void InitAll(Local<Object> exports)
{
  Doc::Init(exports);
  Base::Init(exports);

  V_ENUM_BEGIN(exports, "SimulationType");
    V_ENUM_ITEM("nullValue", 0);
    V_ENUM_ITEM("userDefined", 1);
    V_ENUM_ITEM("timeAccurate", 2);
    V_ENUM_ITEM("nonTimeAccurate", 3);
  V_ENUM_END();
}

NODE_MODULE(NODE_GYP_MODULE_NAME, InitAll)
}