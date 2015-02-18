# -*- coding: utf-8 -*-
"""
Created on Wed Feb 18 17:06:23 2015

@author: nicolas

The Android application "SMS backup and restore" has been used 
to generate a file sms.xml containing text messages we wish to analize.
"""

# manipulating xml
from xml.dom import minidom
# regular expressions
import re
# counting occurences
from collections import Counter

# parse the xml file storing the text messages
xmldoc = minidom.parse('sms.xml')

# get the list of xml elements called 'sms'
smslist = xmldoc.getElementsByTagName('sms')
 
# list whose elements are the words of the text messages
wordslist = []
for sms in smslist:
    # grab the body of the text message
    bod = sms.attributes['body'].value
    # replace special characters by white spaces
    bod = re.sub("[,?;.:/!§&@'^()-0123456789\"]", ' ', bod)
    # split body into words
    words = bod.lower().split()
    # append the new words to the list of words
    wordslist += words

# a new counter to count word occurences
count = Counter(wordslist)

# examples
count.most_common(20)