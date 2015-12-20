from bs4 import BeautifulSoup, SoupStrainer
from urlparse import urljoin,urlparse
import requests
import json
from collections import OrderedDict

only_a_tags = SoupStrainer("a")
only_img_tags = SoupStrainer("img")
only_tags_with_id_link2 = SoupStrainer(id="link2")

# def is_short_string(string):
#     return len(string) < 10

# only_short_strings = SoupStrainer(string=is_short_string)


def parseNatGeoPOD(link):
    data=OrderedDict()
    soup=BeautifulSoup(requests.get(link).text)
    prevlink=soup.select('.primary_photo a')[0]['href']
    prevlink=urljoin(link,prevlink)
    data['heading']=soup.select('#caption h2')[0].text
    data['subhead']=soup.select('.primary_photo img')[0]['alt']
    data['pubtime']=soup.select('#caption .publication_time')[0].text
    data['credits']=soup.select('#caption .credit')[0].text
    data['text']=soup.select('#caption')[0].text
    data['symname']=os.path.basename(os.path.dirname(urlparse(link).path))
    imglink=soup.select('.primary_photo img')[0]['src']
    imglink=urljoin(link,imglink)
    data['imgname']=os.path.basename(urlparse(imglink).path)
    data['imglink']=imglink
    data['prevlink']=prevlink
    print(json.dumps(data, indent=4))
    return data

j=parseNatGeoPOD('http://photography.nationalgeographic.com/photography/photo-of-the-day/');

