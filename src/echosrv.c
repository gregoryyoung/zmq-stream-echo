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

/*
@header
    echosrv - 
@discuss
@end
*/

#include "ec_classes.h"

//  Structure of our actor

struct _echosrv_t {
    zsock_t *pipe;              //  Actor command pipe
    zpoller_t *poller;          //  Socket poller
    bool terminated;            //  Did caller ask us to quit?
    bool verbose;               //  Verbose logging enabled?
    zsock_t *tcp_server;        //  TCP socket server
    zctx_t *z_ctx;
};


//  --------------------------------------------------------------------------
//  Create a new echosrv instance

static echosrv_t *
echosrv_new (zsock_t *pipe, void *args)
{
    echosrv_t *self = (echosrv_t *) zmalloc (sizeof (echosrv_t));
    assert (self);

    self->pipe = pipe;
    self->terminated = false;
     

    self->z_ctx = zctx_new();
    self->tcp_server = (zsock_t *) zsocket_new (self->z_ctx, ZMQ_STREAM);
    assert (self->tcp_server);
    //TODO add arguments on create    


    self->poller = zpoller_new (self->pipe, self->tcp_server, NULL);
    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the echosrv instance

static void
echosrv_destroy (echosrv_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        echosrv_t *self = *self_p;
        //zsys_debug ("closing tcp server\n");
        //zmq_close (self->tcp_server); 
        zsys_debug ("destroying context\n");
        zctx_destroy (&self->z_ctx);

        zsys_debug ("destroying poller\n");
        zpoller_destroy (&self->poller);
        zsys_debug ("destroying self\n");
        free (self);
        *self_p = NULL;
    }
}


//  Start this actor. Return a value greater or equal to zero if initialization
//  was successful. Otherwise -1.

static int
echosrv_start (echosrv_t *self)
{
    assert (self);

    zsys_debug ("start called binding server\n");

    int bound = zmq_bind (self->tcp_server, "tcp://*:1111");
    assert (bound == 0);
    return 0;
}


//  Stop this actor. Return a value greater or equal to zero if stopping 
//  was successful. Otherwise -1.

static int
echosrv_stop (echosrv_t *self)
{
    assert (self);

    zsys_debug ("stop called\n");

    return 0;
}


static void
process_tcp (echosrv_t *self) 
{
    uint8_t id [256];
    size_t id_size = 256;
    uint8_t data [1024];
    size_t data_size = 1024;
    size_t received;

    id_size = zmq_recv (self->tcp_server, id, id_size, 0);
    assert (id_size > 0);
    do {
        received = zmq_recv (self->tcp_server, data, data_size, 0);
        assert (received >= 0);
        char *rec = (char *) data;
        if(rec[0] == 'e' && rec[1] == 'x' && rec[2] == 'i' && rec[3] == 't') {
            zmq_send (self->tcp_server, id, id_size, ZMQ_SNDMORE);
            zmq_send (self->tcp_server, data, 0, 0); 
        }
        if(received >0) {
            zmq_send (self->tcp_server, id, id_size, ZMQ_SNDMORE);
            zmq_send (self->tcp_server, data, received, ZMQ_SNDMORE);
        }
    } while (received == data_size);
}

static void
echosrv_recv_api (echosrv_t *self)
{
    //  Get the whole message of the pipe in one go
    zmsg_t *request = zmsg_recv (self->pipe);
    if (!request)
       return;        //  Interrupted

    char *command = zmsg_popstr (request);
    if (streq (command, "START"))
        echosrv_start (self);
    else
    if (streq (command, "STOP"))
        echosrv_stop (self);
    else
    if (streq (command, "VERBOSE"))
        self->verbose = true;
    else
    if (streq (command, "$TERM"))
        //  The $TERM command is send by zactor_destroy() method
        self->terminated = true;
    else {
        zsys_error ("invalid command '%s'", command);
        assert (false);
    }
    zstr_free (&command);
    zmsg_destroy (&request);
}


//  --------------------------------------------------------------------------
//  This is the actor which runs in its own thread.

void
echosrv_actor (zsock_t *pipe, void *args)
{
    echosrv_t * self = echosrv_new (pipe, args);
    if (!self)
        return;          //  Interrupted

    //  Signal actor successfully initiated
    zsock_signal (self->pipe, 0);

    while (!zctx_interrupted && !self->terminated) {
        zsock_t *which = (zsock_t *) zpoller_wait (self->poller, 0);
        if (which == self->pipe)
            echosrv_recv_api (self);
        if (which == self->tcp_server)
            process_tcp (self);
       //  Add other sockets when you need them.
    }
    echosrv_destroy (&self);
}


//  --------------------------------------------------------------------------
//  Self test of this actor.

void
echosrv_test (bool verbose)
{
    printf (" * echosrv: ");
    //  @selftest
    //  Simple create/destroy test
    zactor_t *echosrv = zactor_new (echosrv_actor, NULL);

    zactor_destroy (&echosrv);
    //  @end

    printf ("OK\n");
}
