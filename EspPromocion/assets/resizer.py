import os, re
from PIL import Image
from resizeimage import resizeimage

ancho = 250

files = os.listdir('./originales')

for image in files:
    if re.search(r'\.jpg$',image) is not None:
        with open(''.join(['./originales/',image])) as f:
            with Image.open(f) as baseimage:
                thumbnail = resizeimage.resize_thumbnail(baseimage,[250,250])
                thumbnail.save("".join(["./fotos/",image]),format='JPEG')
