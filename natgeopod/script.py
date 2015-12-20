from bs4 import BeautifulSoup, SoupStrainer
import requests

only_a_tags = SoupStrainer("a")
only_img_tags = SoupStrainer("img")
only_tags_with_id_link2 = SoupStrainer(id="link2")

# def is_short_string(string):
#     return len(string) < 10

# only_short_strings = SoupStrainer(string=is_short_string)

link='http://photography.nationalgeographic.com/photography/photo-of-the-day/';
soup=BeautifulSoup(requests.get().text)

soup.find("div", class_="primary_photo")

photo_div=soup.find("div", class_="primary_photo")

# photo_div.find("a")			# div.a
# photo_div.find("img")			# div.img

imgurl=photo_div.find("img")['src']
# u'//images.nationalgeographic.com/wpf/media-live/photos/000/933/cache/vultures-zebra-moon_93383_990x742.jpg'
# http://images.nationalgeographic.com/wpf/media-live/photos/000/933/cache/vultures-zebra-moon_93383_990x742.jpg


subhead=photo_div.find("img")['alt']

previmg=photo_div.find("a")['href']

cap=soup.find("div", id="caption")
heading=cap.find("h2").text
pubtime=cap.find("p", class_="publication_time").text
credits=cap.find("p", class_="credit").text
text=cap.text



