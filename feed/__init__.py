import sys
import requests as r
import re
import logging

import PyRSS2Gen

DOCLINK = 'localhost:19001/bm.xml'

def processAuthText(authText):
    authList = authText.split(':',2)
    return getattr(r.auth, authList[0])( *authList[1:] )

def parseResponse(respText):
    docTitle = ''
    title = ''
    link = ''
    description = ''
    items = [ (title,link,description) for (title,link) in re.findall( '\[(.*)\]\((.*)\)', respText ) ]
    logging.debug( '{} items found.'.format(len(items)) )
    return (docTitle, items)

def main(url=None, authText=None):
    logging.basicConfig( level=logging.DEBUG )
    auth = processAuthText(authText)
    req = r.request('GET', url, auth=auth)
    (docTitle, items) = parseResponse( req.text )
    rssItems = [PyRSS2Gen.RSSItem(t,l,d) for (t,l,d) in items]
    rss = PyRSS2Gen.RSS2( title=docTitle, link=DOCLINK, description=docTitle, items=rssItems )    
    return rss.to_xml()

def do_GET(url=[],authText=[]):
    return main(url=url[0],authText=authText[0])

if __name__ == '__main__':
    print main( url=sys.argv[1], authText=sys.argv[2] )
