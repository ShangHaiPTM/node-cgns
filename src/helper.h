/*****************************************************************************/
/**
 *  @file   CGNSLib.h
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#pragma once

#include <cgnslib.h>
#include <iostream>
#include <string>

#if defined(_DEBUG)
bool __IsError(const int error, const char *file, const int line, const char *func, const char *command);
#define CGNS_CALL(command)                                         \
    int status = command;                                          \
    if (__IsError(status, __FILE__, __LINE__, __func__, #command)) \
    { /*KVS_BREAKPOINT;*/                                          \
    }
#define V8_CALL(command)              \
    v8::Maybe<bool> result = command; \
    if (__IsError(result.IsJust() && result.ToChecked(), __FILE__, __LINE__, __func__, #command)) \
    { /**/ }
#else
#define CGNS_CALL(command) (command)
#define V8_CALL(command)                         \
    v8::Maybe<bool> result = command;            \
    if (!result.IsJust() || !result.ToChecked()) \
    { /**/ }
#endif // _DEBUG

const std::string indents(const int i);
