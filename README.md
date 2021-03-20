# monoCube888
Single colour 8x8x8 LED cube

I bought this cheap monochromatic LED cube from ebay (https://www.ebay.co.uk/itm/Blue-Green-Red-Yellow-8x8x8-LED-Cube-3D-Light-Square-Blue-LED-Electronic-DIY-Kit/293622809861) a few years ago (see layer of dust in photo).

Building it took a looooong time. It came with some preprogrammed patterns which were ok but I didn't think they really used the 3D nature of the cube very well. Also they were mainly hard-coded routines whereas some live maths with stochastic behaviour seemed more interesting to me.

I didn't really expect to be able to reprogram this thing because it didn't use a friendly microcontroller (arduino or raspPi etc) but after the effort of building it I thought it was worth a go. It's based on a STC12C5A60S2 chip which I was able to reprogram using a little USB programmer (CP2102?). Code was written in C and compiled using Keil u-Vision-v8.12-C51 and uploaded with stc-isp-15xx-c6.67.exe. 

There were challenges:
- Avoiding floating point arithmetic for speed. 
- Replacing Math functions with lookup tables.
- Space constraints on the MCU. 

I also struggled with unpredictable behavior. Possibly the settings on the compiler/uploader were not perfectly matched to the chip. However after a lot of trial an error I was pretty happy with the results.

Video at: https://youtu.be/FMFzVifCDEg

![PXL_20210320_171840810 MP (1)](https://user-images.githubusercontent.com/25584653/111881534-b6d73400-89a8-11eb-9afd-a40e3d7c09f2.jpg | width=300)
