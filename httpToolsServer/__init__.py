#!/usr/bin/python
from BaseHTTPServer import BaseHTTPRequestHandler,HTTPServer
import urlparse
import os
import importlib
import traceback
import logging

#This class will handles any incoming request from
#the browser 
class myHandler(BaseHTTPRequestHandler):
    
    #Handler for the GET requests
    def do_GET(self):
        o = urlparse.urlparse(self.path)
        logging.debug('Processing request {}'.format(o))
        try:
            mod = importlib.import_module(o.path[1:])
            resp = mod.do_GET(**urlparse.parse_qs(o.query))
        except Exception as e:
            logging.exception(e)
            resp = '<pre>\n'+traceback.format_exc()+'\n</pre>'

        self.send_response(200)
        self.send_header('Content-type','text/html')
        self.end_headers()
        # Send the html message
        self.wfile.write(resp)
        return
