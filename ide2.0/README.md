Just trying the new Arduino IDE

A while ago I tried it and I was not that impressed, about a month ago I tried it and almost bricked my Portenta. It seemed to permanently block my serial port even on other computers. Placed issue [here](https://github.com/arduino/arduino-ide/issues/692) Randomly solved it on the forth computer without trying to get into bootloader mode managed to upload a blank sketch, then it was fine.


Now testing Arduino IDE 2.0.0-rc3

Generally seems farily good. I have a nack for finding issues. Here is my take on what I have found.

Download Arduino IDE 2.0.0-rc3 at  https://www.arduino.cc/en/software   scroll past the regular Arduino IDE

By the way I have many Arduino PortentaH7's as I teach a robotics class. I also have a huge library of examples specifically for this board. In the IDE search for the word "Community" and it should pop up as the ```Portenta Pro Community Solutions```. Every program has a "dot" number so you can find it.


## My first look at Arduino IDE 2.0.0-rc3

1. Zipped file downloads fast


2. Installing the zipped file into a sub folder. 

![image](https://user-images.githubusercontent.com/5605614/148804456-0f5f9907-5771-4e81-8c7d-f2ac524983b4.png)


3. Solution worked when I extracted it into c: drive

4. Running program for the first time. 
Very slow to load (first time)
Wants access to about 3 different things. Took about 10 minutes first time to load.


5. Using the zipped version, it found all my old libraries. Good!

6. Ran my hello blink program ([dot11-hello-blink](https://github.com/hpssjellis/portenta-pro-community-solutions/tree/main/examples/dot1-portentaH7-examples/dot11-hello-blink) - means first sub folder- first program in my library). Works fine, why does it say it is not connected?

![image](https://user-images.githubusercontent.com/5605614/148816022-a0ca4f48-7905-4f09-aca8-fbf4d136a8d2.png)


7. When you compile/upload a program nothing tells you it is running for about 10 seconds. After a bit this shows up in the bottom left corner. Note fixed this later with file --> preference --> show verbose during compile.   
![image](https://user-images.githubusercontent.com/5605614/148816489-aa4b784c-aaf2-4e70-bf7c-8ca75e119cf4.png)

8. Note: On re-compile/upload things are much faster.



9. Unloaded all sketches and loaded V2 again, took only about 40 seconds this time to load the software. That's good

10. Full computer reboot and loaded the V2IDE and also took only about 40 seconds to fully load.





11. Complaint:

I have many, many libraries, the old version used to remember the location in the examples menu of where you were. V2.0 always puts you at the top of the examples, meaning I have to scroll down ~5 pages of examples to get to my library.

which for my library portenta-pro-community-solutions is 23 mouse wheel scrolls since their is no page down command that works. 

![image](https://user-images.githubusercontent.com/5605614/148821703-405544d6-7ccd-4a84-9400-9c4a7c63398e.png)


12. Ran one of my Machine Learning programs. Plotter works but does not show a line


![image](https://user-images.githubusercontent.com/5605614/148822666-3a366820-4e44-4df3-933e-294f23891f6e.png)


13. I think it is compiling faster than the old version, however no proof that it has started is very irritating. Even if the upload button changed color that would be better than asolutely nothing happening for a while, for my really large Edgeimpulse.com machine learning program nothing has happened for 5 minutes. no idea if it is compilinhg or not.


14. Weird, just clued in when the upload button is pushed, it DOESN"T change color when you mouse over it. That is the only way that you can tell that the program is compilling. All the other buttons change color slightly when moused over.


15. Solution: the V2.0 IDE actually does tell you that the button has been pushed, but it is very subtle. The button does not change when moused over if it has been pushed. For my large program it could take 5 minutes of compiling before anything happens. If you mouse over the upload button, nothing happens meaning it has been pushed.

If you mouse over the button and it slightly gets brighter that means it has not yet been pushed and your program is not compiling.

this needs to be changed. It is too subtle.

![image](https://user-images.githubusercontent.com/5605614/148826438-100b5699-5761-4e8e-b87b-a7dd35870575.png)


16. A complex edge impulse machine learning program compiles fine on IDE 1.18.15. Note: the include file can be any edge impulse vision file but I am using this one [here](https://github.com/hpssjellis/portenta-pro-community-solutions/blob/main/zipped-libraries/edge-Impulse/arduino-exported/Portenta-Camera/ei-ei-v20unknown-1popgoright-2watergoleft-3fast-v2-0-0-arduino-1.0.7.zip) and the example is [here](https://github.com/hpssjellis/portenta-pro-community-solutions/tree/main/examples/dot5-portenta-machine-learning/dot51-portenta-edge-impulse-ml/dot511-vision-shield/dot5113-show-top-classification)

The examples I am testing are in the Portenta-pro-comunity solutions library  

![image](https://user-images.githubusercontent.com/5605614/148832497-87dbf41f-f4c3-4fcd-b91d-14ddee93f096.png)


does not compile on Version Arduino IDE V2.0   
![image](https://user-images.githubusercontent.com/5605614/148835239-234e67b0-1caa-4d59-ab3d-c72848c31607.png)

The problem looks like it is to do with the EdgeImpulse library, just not sure why the regular IDE can find the files.


17. When you unplug a programmed Portenta and then plug it back in it looks like the serial connection has not been extablished, however I think it is fine.

![image](https://user-images.githubusercontent.com/5605614/148836892-d464fa46-1549-4ea5-a041-767432ca0208.png)


18. Still testing multiple programs. Generally things seem positive.

19. Testing speed, on a fast computer my rocksetta ML sine wave took 1 min 16 s to compile. On the V1.18.15 IDE verison it took 1 min 25 seconds but the plotter worked. Most of this code is pre-compiled so doesn't really show much a speed improvement.

20. If in file-->preferences you set Verbose output during compile and upload, then you have a better feel for how the compile is going.

21. Generally I feel fairly good about the zipped version of the Arduino IDE V2.0.0 Jan 10th, 2022, a few complex things are not working, but it does have a nice modern feel about the program. Slow installation,  

22. On 64 bit Linux (ubuntu 18.04), fast download, fast extraction, openned terminal ran ```./arduino-ide```  loaded fast. Had a bit of an issue finding the latest mbed board 1.6.2 reloaded then found it. Installed my ```Portenta-pro-community-solutions``` library. Ran my hello-blink program, compiled fine. did not upload! This is a normal Linux serial permissions issue probably. 

24. My normal work around is to load with sudo, but it did not load the program. Next step is to allow serial access normally a bash.sh file loads that for us. Can't find it so after some searching I managed to make it work. Anyone interested in how that was done?


25. So by using super secret Ubuntu skills I got the serial port working. Like always Linux is faster and better in every way. Even my advanced edge impulse machine learning program worked fine on Linux. Which brings up the question why did it die on windows? Also Arduino for Linux defaults to verbose mode so you can tell when your sketch is compiling.



## Jan 12th, 2022

26. Checking out the plotter again  Regular Portenta PDM example seems to be fine using every color theme. 
 ![image](https://user-images.githubusercontent.com/5605614/149188716-13711d49-3244-4eef-ad34-a53b71a2c409.png)

Trying my "[dot521 rocksetta hello ml sine](https://github.com/hpssjellis/portenta-pro-community-solutions/tree/main/examples/dot5-portenta-machine-learning/dot52-portenta-rocksetta-ml/dot521-rocksetta-hello-ml-sine)" program on my Portenta pro community solutions library. 

this is not working but could easily be my code that is causing the issue as the PDM example works fine
![image](https://user-images.githubusercontent.com/5605614/149188344-2da42c94-dc20-4dcb-8c0a-92049d6f4948.png)

Here is what it looks like on the old 1.8.15 arduino IDE. the issue might be the multiple plots

![image](https://user-images.githubusercontent.com/5605614/149189414-2b38fe79-ecf3-429d-825b-851a1d28850c.png)




27.  Weird When going from the standard examples to find my library it only showed the standard examples, no other? Doing a reload.

### Where are the other examples??

![image](https://user-images.githubusercontent.com/5605614/149191540-2c28512f-2586-46fb-ad27-bc376dd15deb.png)


On reload it briefly only showed the basic examples, then seemed to load all the examples again.



28. One hack I like on arduino 1.8.15 is that you can load multiple instances of the IDE. That allows multiple serial monitors. On the new Arduino IDE 21.0.03rc you can't load multiple instances. Like always you can still load multiple windows it looks like you can load 2 serial monitors but they both read the same port even if one of them says it is reading the other port.  Too bad that was a nice hack.

![image](https://user-images.githubusercontent.com/5605614/149191093-8c463c89-dca7-48c4-b18d-286b226a41d4.png)






