# CustomCodeCard
Arduino Sketch for getting basic control of the 2018 Oracle Code Card

Instructions:
1) Install the Arduino IDE: https://www.arduino.cc/en/Main/Software
2) Install support for for the ESP-12 chip on the card: https://github.com/esp8266/Arduino
3) Download the epaper library: https://github.com/ZinggJM/GxEPD (this might also require the adafruit gfx library)
4) Open the sketch provided here and choose
5) Select "NodeMCU 1.0 (ESP-12E Module)" default settings are fine (baudrate=115200)
6) The tricky part: hit upload code in the IDE BUT...you need to catch the chip in the right state for it to accept your code, it likes to power down to save power so play with the power switch and buttons to keep it active. Expect alot of failures here.
<p align="center">
  <img src="https://i.imgur.com/GfozTlD.jpg">
</p>
7) Great Success!
