#pragma once

#include <iostream>
#include <node/node.h>

namespace cgns {
inline bool isTrue(v8::Maybe<bool> value) {
    return value.IsJust() && value.ToChecked();
}

inline bool isFalse(v8::Maybe<bool> value) {
    return value.IsJust() && !value.ToChecked();
}

inline bool isNotTrue(v8::Maybe<bool> value) {
    return value.IsNothing() || !value.ToChecked();
}

inline bool isNotFalse(v8::Maybe<bool> value) {
    return value.IsNothing() || value.ToChecked();
}

inline v8::Maybe<bool>
_v8_IsError(v8::Maybe<bool> r, const char *file, const int line, const char *func, const char *command) {
    if (isTrue(r)) {
        return r;
    }

    std::string message_tag("V ERROR \n");
    std::cerr << message_tag;

    // Output message with an error string.
    std::cerr << "\t"
              << "FILE: " << file << " (" << line << ")" << std::endl;
    std::cerr << "\t"
              << "FUNC: " << func << std::endl;
    std::cerr << "\t"
              << "COMMAND: " << command << std::endl;
    return r;
}

#define V_CALL(command) _v8_IsError((command), __FILE__, __LINE__, __func__, #command)

#define V_SET_BEGIN(_this)                             \
    {                                                  \
        v8::Local<v8::Object> __this = _this;          \
        v8::Isolate *__isolate = __this->GetIsolate(); \
        v8::Local<v8::Context> __context = __isolate->GetCurrentContext()

#define V_SET(_this, name, value)  V_CALL(_this->Set(__context, v8::String::NewFromUtf8(__isolate, name), value))
#define V_SET_NUMBER(_this, name, value) V_SET(_this, name, v8::Number::New(__isolate, value))
#define V_SET_STRING(_this, name, value) V_SET(_this, name, v8::String::NewFromUtf8(__isolate, value))

#define V_SET_END() }

#define V_ARRAY_BEGIN(_this, name)                            \
{                                                             \
    v8::Local<v8::Array> __array = v8::Array::New(__isolate); \
    V_SET(_this, name, __array);                              \
    int __arrayIndex = 0

#define V_ARRAY_SET(index, item) V_CALL(__array->Set(__context, v8::Number::New(__isolate, index), item))
#define V_ARRAY_SET_NUMBER(index, item) V_ARRAY_SET(index, v8::Number::New(__isolate, item))
#define V_ARRAY_SET_STRING(index, item) V_ARRAY_SET(index, v8::String::NewFromUtf8(__isolate, item))
#define V_ARRAY_ADD(item) V_ARRAY_SET(__arrayIndex++, item)
#define V_ARRAY_ADD_NUMBER(item) V_ARRAY_ADD(v8::Number::New(__isolate, item))
#define V_ARRAY_ADD_STRING(item) V_ARRAY_ADD(v8::String::NewFromUtf8(__isolate, item))

#define V_ARRAY_END() }

#define V_ENUM_BEGIN(exports, enumName)                                    \
    {                                                                      \
        v8::Isolate *__isolate = exports->GetIsolate();                    \
        v8::Local<v8::Context> __context = __isolate->GetCurrentContext(); \
        v8::Local<v8::Object> __enumObject = v8::Object::New(__isolate);   \
        V_CALL(exports->Set(__context, v8::String::NewFromUtf8(__isolate, enumName), __enumObject))

#define V_ENUM_ITEM(itemName, itemValue)                                                                                       \
    V_CALL(__enumObject->Set(__context, v8::String::NewFromUtf8(__isolate, itemName), v8::Number::New(__isolate, itemValue))); \
    V_CALL(__enumObject->Set(__context, v8::Number::New(__isolate, itemValue), v8::String::NewFromUtf8(__isolate, itemName)))

#define V_ENUM_END() }
}