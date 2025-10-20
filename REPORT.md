[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/ZCO_vauY)
Repository for final lesson before mid term of computer graphic course

# Mid Term Report Result

### Name: Sabiyan Avril Chandrakanta
### NIM: 1313623020

I enhance the source code with perplexity ai. but the perplexity is off in the mid of my analysis. So i just use gemini to implement the code.

I started to change  the source code to fit my Qt since my Qt using a dark mode. 
so this is my change in the drawingcamvas.cpp:
i added setAutoFillBackground(true); in the constructor of the drawingcanvas, then i add  painter.fillRect(rect(), Qt::white); in the paintEvent to draw my canvas white in bacgkround.

to analyze what window is fit to detect a line segment, i consulted with perplexity and trying to understand the assignment. What i got is the intention is to build a detector of line segment intersection by using an ideal window pixel size to detect the intersection. 

so my plan is:

- create a scanner button to toggle it when it needed to detect an intersection

- when the button is clicked, the program can detect the location of the intersection (based on coordinates) and it can print the total of the intersection.

- when the button is clicked it created a mini window to scan all the canvas pixels that fit into this code.

the clue that i know, is the set width line of the source code is set **to 4 wide pixels.**

this is the time that is tart to use gemini:
so i ask gemini that clue, and it suggest me to use 5x5 pixel window size. 
why it should use 5x5 pixel size? its because the minimal size to check a line intersection is 3x3 pixel size in checking a 1 pixel size wide line. But in this current situation, the line is not 1 pixel wide, its 4 pixel wide. 
a 4 pixel wide line occupies 3-4 pixels in any direction around the central point. if we use 4x4 pixel window size, the lines will stil, cover all of the white pixel if there is any intersection, so it cannot possible.

the minimal window to detect 4 pixel wide line is 5x5 window size in pixel. it provides a 2 pixel margin on all sides of the central pixel that offers in four different directions.

but when i implementing the code, it turns out the code is not fulfill my plan.


