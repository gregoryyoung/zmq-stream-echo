/*  =========================================================================
    echoactorserver - description

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
    echoactorserver - 
@discuss
@end
*/

#include "ec_classes.h"

int main (int argc, char *argv [])
{
    bool verbose = false;
    int argn;
    for (argn = 1; argn < argc; argn++) {
        if (streq (argv [argn], "--help")
        ||  streq (argv [argn], "-h")) {
            puts ("echoactorserver [options] ...");
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
    //  Insert main code here
    if (verbose)
       zsys_info ("echoactorserver - ");
    zactor_t *srv = zactor_new (echosrv_actor, NULL);
    assert (srv);
    printf ("calling start\n");
    zstr_sendx (srv, "START", "", NULL);
    printf("Press enter to continue\n");
    char enter = 0;
    while (enter != '\r' && enter != '\n') { enter = getchar(); }
    printf ("stopping actorn");
    printf ("Destroying actor\n");
    zactor_destroy (&srv);
    return 0;
}
