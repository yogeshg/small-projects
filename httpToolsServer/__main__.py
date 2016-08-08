#!/usr/bin/python
import sys
from __init__ import *
import argparse
import logging

def main():
    #Create a web server and define the handler to manage the
    #incoming request
    p = argparse.ArgumentParser(__doc__)
    p.add_argument('port', type=int, help='Port to listen on')
    p.add_argument('-l', '--loglevel', default='INFO', type=str,
        choices=['DEBUG', 'INFO', 'WARNING', 'ERROR', 'CRITICAL'],
        help='Set the logging level')
    # p.add_argument('-f', '--logfile', default=sys.stdout, type=argparse.FileType('w'),
    #     help='log file to write the logs to')
    p.add_argument('-f', '--logfile', type=str,
        help='log file to write the logs to')
    a = p.parse_args()

    logging.basicConfig( filename=a.logfile, level=getattr(logging,a.loglevel) )
    logger = logging.getLogger(__name__)

    server = HTTPServer(('', a.port), myHandler)
    logger.info('Started httpserver on port {}'.format(a.port))
    try:
        #Wait forever for incoming http requests
        server.serve_forever()
    except KeyboardInterrupt:
        logger.info('KeyboardInterrupt received, shutting down the web server')
        server.socket.close()

if __name__ == '__main__':
    main()