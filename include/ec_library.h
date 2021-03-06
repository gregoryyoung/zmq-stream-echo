/*  =========================================================================
    stream-echo - generated layer of public API

    The MIT License (MIT)                                                         
                                                                                  
    Copyright (c) 2016 Greg Young                                                 
                                                                                  
    Permission is hereby granted, free of charge, to any person obtaining a copy  
    of this software and associated documentation files (the "Software"), to deal 
    in the Software without restriction, including without limitation the rights  
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell     
    copies of the Software, and to permit persons to whom the Software is         
    furnished to do so, subject to the following conditions:                      
                                                                                  
    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.                               
                                                                                  
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR    
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE   
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER        
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
    SOFTWARE.                                                                     

################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
    =========================================================================
*/

#ifndef EC_LIBRARY_H_INCLUDED
#define EC_LIBRARY_H_INCLUDED

//  Set up environment for the application

//  External dependencies
#include <zmq.h>
#include <czmq.h>

//  EC version macros for compile-time API detection
#define EC_VERSION_MAJOR 0
#define EC_VERSION_MINOR 1
#define EC_VERSION_PATCH 0

#define EC_MAKE_VERSION(major, minor, patch) \
    ((major) * 10000 + (minor) * 100 + (patch))
#define EC_VERSION \
    EC_MAKE_VERSION(EC_VERSION_MAJOR, EC_VERSION_MINOR, EC_VERSION_PATCH)

#if defined (__WINDOWS__)
#   if defined EC_STATIC
#       define EC_EXPORT
#   elif defined EC_EXPORTS
#       define EC_EXPORT __declspec(dllexport)
#   else
#       define EC_EXPORT __declspec(dllimport)
#   endif
#else
#   define EC_EXPORT
#endif

//  Project has no stable classes, so we build the draft API
#undef  EC_BUILD_DRAFT_API
#define EC_BUILD_DRAFT_API

//  Opaque class structures to allow forward references
//  These classes are stable or legacy and built in all releases


//  Public classes, each with its own header file

#endif
/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/
