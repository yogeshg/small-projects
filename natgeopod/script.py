import pod,requests,json,os,shutil
# from PIL import Image
# from StringIO import StringIO

def printj(jsono):
    print(json.dumps(jsono, indent=4))

def saveImgUrl2file(imgurl,fname):
    r = requests.get(imgurl, stream=True)
    if r.status_code == 200:
        with open(fname, 'wb') as f:
            r.raw.decode_content = True
            shutil.copyfileobj(r.raw, f)

j=pod.NatGeoPOD.parse('http://photography.nationalgeographic.com/photography/photo-of-the-day/');

path="/Users/yogeshgarg/Code2/proto/natgeopod/"

saveImgUrl2file(j['imglink'],path+j['symname'])

    # i = Image.open(StringIO(r.content))
    # i.save(path+j['symname'])

import argparse

parser = argparse.ArgumentParser(description='Process some integers.')
parser.add_argument('integers', metavar='N', type=int, nargs='+',
                   help='an integer for the accumulator')
parser.add_argument('--sum', dest='accumulate', action='store_const',
                   const=sum, default=max,
                   help='sum the integers (default: find the max)')

args = parser.parse_args()
print args.accumulate(args.integers)



link="http://apod.nasa.gov/apod/astropix.html"




soup.select('a[href*=image]')

# pubtime
(soup.select('a[href*=image]')[0]).parent.get_text().strip()
# imglink

# text

# heading

# subhead
soup.select('body > center > b')[0].parent

soup.find(is_text_backarrow)['href']


