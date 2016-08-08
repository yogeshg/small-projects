Http Tools Server
=================

This is a simple http server to call python tools via http.


Usage
-----
It can be used by calling the following Http Get request:

    http://<HOST>:<PORT>/<TOOL>?[ARGS]

    HOST    := string
            : host name of the server
    PORT    := integer
            : port of the server
    TOOL    := string
            : python module name, this module is imported and its do_GET method is called
    ARGS    := <ARG1>=<VAL1>&[ARGS] | None
            : all the arguments are passed as python named arguments (keyword parameter)

Example
-------
    start.sh
    curl http://localhost:8080/feed?url=http://google.com&authText=HTTPBasicAuth:u:p
    stop.sh

