# pod.py
# -*- coding: utf-8 -*-
"""Download Pictures of the Day for
    * National Geographic Photography
"""


from bs4 import BeautifulSoup, SoupStrainer
from urlparse import urljoin,urlparse
from collections import OrderedDict
import requests,os,json,argparse,sys,shutil

class NatGeoPOD:
    # TODO: Make init
    @staticmethod
    def parse(link):
        print 'Parsing link ',link
        data=OrderedDict()
        soup=BeautifulSoup(requests.get(link).text)
        prevlink=soup.select('.primary_photo a')[0]['href']
        prevlink=urljoin(link,prevlink)
        data['heading']=soup.select('#caption h2')[0].text
        data['subhead']=soup.select('.primary_photo img')[0]['alt']
        data['pubtime']=soup.select('#caption .publication_time')[0].text
        data['credits']=soup.select('#caption .credit')[0].text
        data['text']=soup.select('#caption')[0].text
        imglink=soup.select('.primary_photo img')[0]['src']
        imglink=urljoin(link,imglink)
        data['symname']=os.path.basename(os.path.dirname(urlparse(link).path))+os.path.splitext(imglink)[1]
        data['imgname']=os.path.basename(urlparse(imglink).path)
        data['imglink']=imglink
        data['prevlink']=prevlink
        # print(json.dumps(data, indent=4))
        # TODO: Make self
        return data

# link="http://apod.nasa.gov/apod/astropix.html"
class NasaAPOD:
    # TODO: Make init
    @staticmethod
    def parse(link):
        def is_text_backarrow(tag):
            return "<" == tag.text
        print 'Parsing link ',link
        data=OrderedDict()
        soup=BeautifulSoup(requests.get(link).text)
        prevlink=soup.find(is_text_backarrow)['href']
        prevlink=urljoin(link,prevlink)
        data['heading']=soup.select('body > center > b')[0].get_text().strip()
        data['subhead']=soup.select('body > center > b')[0].parent.get_text().strip()
        data['pubtime']=(soup.select('a[href*=image]')[0]).parent.get_text().strip()
        data['credits']=data['subhead']
        data['text']=soup.select('body > p')[0].get_text().strip()
        imglink=(soup.select('a[href*=image]')[0])['href']
        imglink=urljoin(link,imglink)
        data['symname']=os.path.basename(urlparse(imglink).path)
        data['imgname']=os.path.basename(urlparse(imglink).path)
        data['imglink']=imglink
        data['prevlink']=prevlink
        # print(json.dumps(data, indent=4))
        # TODO: Make self
        return data

def printj(jsono):
    print(json.dumps(jsono, indent=4))

def ensureDir(directory):
    if not os.path.exists(directory):
        os.makedirs(directory)

def ensurePdir(fname):
    ensureDir(os.path.dirname(fname))

def saveImgUrl2file(imgurl,fname):
    r = requests.get(imgurl, stream=True)
    if r.status_code == 200:
        ensurePdir(fname)
        with open(fname, 'wb') as f:
            r.raw.decode_content = True
            shutil.copyfileobj(r.raw, f)

def saveJson2file(obj,fname):
    ensurePdir(fname)
    with open(fname, 'wb') as f:
        f.write(json.dumps(obj, indent=4))

class POD:

    def __init__(self,d):
        # TODO: kwargs
        self.root=d.url
        self.num=d.num
        self.pods=[{}]*self.num

    def refresh(self):
        curr=self.root
        for i in range(self.num):
            self.pods[i]=NatGeoPOD.parse(curr)
            curr=self.pods[i]['prevlink']
        return 0

    def persist(self,dirname):
        for p in self.pods:
            self.savePOD(p,dirname)
        return 0

    def show(self):
        for p in self.pods:
            printj(p)

    def savePOD(self,p,dirname):
        fname=os.path.join(dirname,p['symname'])
        saveImgUrl2file(p['imglink'],fname)
        fname=os.path.splitext(fname)[0]+'.txt'
        saveJson2file(p,fname)

def main(args=None):
    # from pod import *
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('-n','--num',type=int,default=10,
        help='number of pictures to be downloaded [defaults to 10]')
    parser.add_argument('-w','--web',default="natgeo",
        help='which website to download from [nasa=apod]/[default=natgeo]')
    parser.add_argument('-u','--url',default="http://photography.nationalgeographic.com/photography/photo-of-the-day/",
        help='number of pictures to be downloaded [defaults to 10]')
    parser.add_argument('-d','--dir',default=".",
        help='directory where output should be stored [defaults to .]')
    p=parser.parse_args()
    # print p.__dict__
    l = POD(p)
    l.refresh()
    l.persist(p.dir)
    # l.show()
    return 0

if __name__ == '__main__':
    main(sys.argv[1:])