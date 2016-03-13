/*  =========================================================================
    echoserver - description

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

/*
@header
    echoserver - simple echo server using ZMQ_STREAM for raw sockets
@discuss
    A sample app exploring how to use raw sockets with libzmq. As the name
    suggests it will simply echo back what you send it and close the socket.
    //TODO add usage
@end
*/

#include "czmq.h"


int main (int argc, char *argv [])
{
    bool verbose = false;
    int argn;
    for (argn = 1; argn < argc; argn++) {
        if (streq (argv [argn], "--help")
        ||  streq (argv [argn], "-h")) {
            puts ("echoserver [options] ...");
            puts ("  --verbose / -v         verbose test output");
            puts ("  --help / -h            this information");
            return 0;
        }
        else
        if (streq (argv [argn], "--verbose")
        ||  streq (argv [argn], "-v"))
            verbose = true;
        else {
            printf ("Unknown option: %s\n", argv [argn]);
            return 1;
        }
    }
    if (verbose)
        zsys_info ("echoserver - ");
    zctx_t *ctx = zctx_new();
    void *socket = zsocket_new (ctx, ZMQ_STREAM);
    assert (socket);
    int bound = zmq_bind (socket, "tcp://*:1111");
    assert (bound == 0);
    uint8_t id [256];
    size_t id_size = 256;
    uint8_t data [1024];
    size_t data_size = 1024;
    size_t received;
    while(3) {
        id_size = zmq_recv (socket, id, id_size, 0);
        assert (id_size > 0);
        char msg [256];
        zmq_send (socket, msg, strlen(msg), ZMQ_SNDMORE);
        do {
            received = zmq_recv (socket, data, data_size, 0);
            assert (received >= 0);
            if(received >0) {
                zmq_send (socket, id, id_size, ZMQ_SNDMORE);
                zmq_send (socket, data, received, ZMQ_SNDMORE);
            }
        } while (received == data_size);
    }

    return 0;
}
