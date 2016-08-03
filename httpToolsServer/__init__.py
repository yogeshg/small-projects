#!/usr/bin/python
from BaseHTTPServer import BaseHTTPRequestHandler,HTTPServer
import urlparse
import os
import importlib
import traceback

PORT_NUMBER = 8080
TOOLSDIR = '/Users/yogeshgarg/Code/code/'

gLastHandler = None

#This class will handles any incoming request from
#the browser 
class myHandler(BaseHTTPRequestHandler):
    
    #Handler for the GET requests
    def do_GET(self):
        global gLastHandler
        o = urlparse.urlparse(self.path)
        # print self.rfile.readlines()

        try:
            mod = importlib.import_module(o.path[1:])
            resp = mod.do_GET(**urlparse.parse_qs(o.query))
        except:
            resp = '<pre>\n'+traceback.format_exc()+'\n</pre>'

        self.send_response(200)
        self.send_header('Content-type','text/html')
        self.end_headers()
        # Send the html message
        self.wfile.write(resp)
        return


def main():
    try:
        #Create a web server and define the handler to manage the
        #incoming request
        server = HTTPServer(('', PORT_NUMBER), myHandler)
        print 'Started httpserver on port ' , PORT_NUMBER        
        #Wait forever for incoming htto requests
        server.serve_forever()
    except KeyboardInterrupt:
        print '^C received, shutting down the web server'
        server.socket.close()

if __name__ == '__main__':
    main()