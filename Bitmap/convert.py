from PIL import Image
import sys

im = Image.open("C:\\")
pix = im.load()
xSize = im.size[0]
ySize = im.size[1] / 8

ret = "{"
for x in range(xSize):
    for yPage in range(int(ySize)):
        value = 0
        for y in range(8):
            color = pix[x, 7-y + 8*yPage]
            value = value << 1
            if (color[0]+color[1]+color[2]) < 3*128:
                value += 1
        ret += hex(value) + ", "
    #ret += "\n"
ret = ret[:-2] + "}"
print(ret)