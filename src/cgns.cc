#include <node/node.h>
#include "Doc.h"

using v8::Local;
using v8::Object;

void InitAll(Local<Object> exports) {
  Doc::Init(exports);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, InitAll)
