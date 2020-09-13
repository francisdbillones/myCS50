import qrcode

image = qrcode.make("https://youtu.be/oHg5SJYRHA0")
image.save("scanthis.png", "PNG")