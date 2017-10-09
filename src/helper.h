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

namespace cgns {

#if defined(_DEBUG)
bool _cgns_IsError(const int error, const char *file, const int line, const char *func, const char *command);
#define CGNS_CALL(command)                                         \
    if (_cgns_IsError(command, __FILE__, __LINE__, __func__, #command)) \
    { /*KVS_BREAKPOINT;*/                                          \
    }
#else
#define CGNS_CALL(command) (command)
#endif // _DEBUG

const std::string indents(const int i);
}