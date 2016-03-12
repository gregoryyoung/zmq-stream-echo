# zmq-stream-echo

This is a sample application of using zeromq with raw sockets (not with zeromq sockets). The place where this is useful is when you have to support an existing protocol but want to use zeromq (or need raw tcp for some other reason) also supporting actors. I couldn't find much documentation on it so this is a spike to understand it.
