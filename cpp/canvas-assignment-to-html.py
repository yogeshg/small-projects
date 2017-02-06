import json
import sys
import codecs

def canvas_assignment_to_html(fname):
    j = json.load( open(fname) )
    return j['description']

def main(fname, oname=None, *args):
    if( oname is None ):
        sys.stdout.write(canvas_assignment_to_html(fname))
    else:
        with codecs.open(oname, 'w', encoding='utf8') as f:
            f.write(canvas_assignment_to_html(fname))
    return

if __name__ == '__main__':
    main(*sys.argv[1:])

