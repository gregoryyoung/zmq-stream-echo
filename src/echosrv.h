/*  =========================================================================
    echosrv - 

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
    =========================================================================
*/

#ifndef ECHOSRV_H_INCLUDED
#define ECHOSRV_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _echosrv_t echosrv_t;

//  @interface
//  Create new echosrv actor instance.
//  @TODO: Describe the purpose of this actor!
//
//      zactor_t *echosrv = zactor_new (echosrv, NULL);
//
//  Destroy echosrv instance.
//
//      zactor_destroy (&echosrv);
//
//  Enable verbose logging of commands and activity:
//
//      zstr_send (echosrv, "VERBOSE");
//
//  Start echosrv actor.
//
//      zstr_sendx (echosrv, "START", NULL);
//
//  Stop echosrv actor.
//
//      zstr_sendx (echosrv, "STOP", NULL);
//
//  This is the echosrv constructor as a zactor_fn;
EC_EXPORT void
    echosrv_actor (zsock_t *pipe, void *args);

//  Self test of this actor
EC_EXPORT void
    echosrv_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
