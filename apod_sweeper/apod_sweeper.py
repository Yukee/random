import urllib.request
import os

# load HTML source from URL
url = "http://apod.nasa.gov/apod/astropix.html"
apod = urllib.request.urlopen(url)

# read HTML source line by line
line = apod.readline()
imgurl = ''
while(line):
    # convert bytes to characters
    linestr = str(line, encoding = 'utf8')
    # retrieve image URL
    #if 'IMG SRC' in linestr: # to retrieve the low res version
    if 'href=\"image' in linestr: # to retrieve the high res version
        imgurl = linestr.split('\"')[1]
        print(imgurl)
        break
    line = apod.readline()

# download image under the name "apod_daily"
if(imgurl): urllib.request.urlretrieve("http://apod.nasa.gov/apod/" + imgurl, "apod_daily.jpg")
else: print("Pas d'image aujourd'hui :-(")

# change wallpaper in GNOME 3
os.system("gsettings set org.gnome.desktop.background picture-uri file:////home/nicolas/Images/apod_daily.jpg")