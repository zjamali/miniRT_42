# miniRT


## Index

* [Installation](#installation)
* [Usage](#usage)
  * [Definitions](#definitions)
  * [Keybindings](#keybindings)
* [Images](#images)

## Installation
Run `make` to compile the executable.

## Usage
To use the interactive interface run the executable with just a file as follows: `./minirt scene8.rt`.

If you wish to save an image of a scene run the command like this: `./minirt scene8.rt -—save`. The saved image will be the rendered image from the first camera defined.

Files have to meet the following requirements:
* one definition of both resolution and ambient lighting.
* one or more definition(s) for camera(s) and light(s).
* any amount of objects.

### Definitions

Resolution:	`R {width} {height}`
* X render size.
* Y render size.

Ambient lighting:	`A {ratio} {color}`
* Ambient lighting ratio in range [0.0,1.0].
* R,G,B colors in range [0-255].

Camera:	`c {position} {orientation} {FOV}`
* X,y,z coordinates of the view point.
* A vector with the the x,y,z axis in the range [-1,1].
* Horizontal field of view in degrees in range [0,180].

Light:	`l {position} {ratio} {color}`
* X,y,z coordinates of the light point.
* The light brightness ratio in range [0.0,1.0].
* R,G,B colors in range [0-255].

Sphere:	`sp {position} {size} {color}`
* X,y,z coordinates of the sphere center.
* The sphere diameter.
* R,G,B colors in range [0-255].

Plane:	`pl {position} {orientation} {color}`
* X,y,z coordinates.
* A vector with the the x,y,z axis in the range [-1,1].
* R,G,B colors in range [0-255].

Square:	`sq {position} {orientation} {side size} {color}`
* X,y,z coordinates of the square center.
* A vector with the the x,y,z axis in the range [-1,1].
* The square size side.
* R,G,B colors in range [0-255].

Cylinder:	`cy {position} {orientation} {diameter} {height} {color}`
* X,y,z coordinates for the cylinder center.
* A vector with the the x,y,z axis in the range [-1,1].
* R,G,B colors in range [0-255].
* The cylinder diameter.
* The cylinder height.

Triangle:	`tr {first point} {second point} {third point} {color}`
* X,y,z coordinates.
* X,y,z coordinates.
* X,y,z coordinates.
* R,G,B colors in range [0-255].

<strong>Transformation</strong>
Rotation:	`ro {rotaion angle xyz axis} `
* angle by x-axis,angle by y-axis,angle by z-axis.

translation:	`ts {transation} `
* X,y,z transation added to element position.


Example scene8.rt file:
```
R 		1080		720

A 		0.2			255,255,255

c 		50,0,1200 		0,0,-1 			90
c 		200,00,1200 	0,0,-1 			120
c 		0,800,400 		0,-1,0 			100
c 		0,0,1200 		0,0,-1 			90
c 		 0,100,400  	0,-1,0 			120
c 		100,0,1200 		0,0,-1 			90
c 		100,300,1200 	0,0,-1 			90
c 		200,00,1200 	0,0,-1 			90

l    	400,-20,1050    0.5           	255,255,255
l    	00,-20,1050     0.2           	255,255,255
l    	-400,20,1050    0.5           	255,255,255

sp      0,0,1400 50 	0,0,255 
sp       0,-95,400  	20   			150,150,150
cy      0,-140,400     	0,1,0    		150,150,150   	10 40    
cy      0,-110,400     	0,1,0    		150,150,150  	10 40    
ro      30,0,90
cy		0,-110,400     	0,1,0     		150,150,150  	10 40    
ro     -30,0,-90
cy      0,-140,400     	0,-1,0    		150,150,150  	10 40     
ro     30,100,90
cy      0,-140,400     	0,-1,0     		150,150,150  	10 40    
ro     -30,100,-90
sq       0,-170,400 	0,1,0  			300 255,0,0
sp     -300,200,-400   	90           	200,200,200        
sp     300,200,-400    	90           	200,200,200
sp     -300,-200,-400  	90           	200,200,200
sp     300,-200,-400   	90           	200,200,200
sp     -200,200,600    	50           	200,200,200
sp     200,200,600     	50           	200,200,200
sp     -200,-200,600   	50           	200,200,200
sp     200,-200,600    	50           	200,200,200
cy     -300,-1000,-400  0,1,0   		150,150,150   	50 10000     
ro     0,0,0
cy     300,-1000,-400   0,1,0   		150,150,150   	50  10000    
cy     -200,-1000,600   0,1,0   		200,200,200   	25  10000    
cy     200,-1000,600    0,1,0    		255,0,0   		25  10000 
pl     0,200,0         	0,-1,0          255,255,0
pl     0,320,-1000    	0,0,1           0,0,255
pl     0,-200,0         0,1,0           255,0,255
```

### Keybindings
There are a number of useful keybindings that are listed below.

**Exiting the application**

To exit the application press `esc`. You can also click the red `x` in the top left of the window.

**Camera**
To switch camera's you can use the `←`(previous) and `→`(next) keys.

### Images
<a href="https://ibb.co/YRxNfpJ"><img src="https://i.ibb.co/GxqdCcG/Screen-Shot-2020-11-25-at-19-21-31.png" alt="Screen-Shot-2020-11-25-at-19-21-31" border="0"></a> <br><br>
<a href="https://ibb.co/B6NS9NQ"><img src="https://i.ibb.co/JpQM9QG/Screen-Shot-2020-11-25-at-22-45-52.png" alt="Screen-Shot-2020-11-25-at-22-45-52" border="0"></a> <br><br>
<a href="https://ibb.co/xsttWbd"><img src="https://i.ibb.co/fSzzfWL/Screen-Shot-2020-11-25-at-22-49-34.png" alt="Screen-Shot-2020-11-25-at-22-49-34" border="0"></a><br>
<br>
different color of lights (blue light + red light + white light).<br>
<a href="https://ibb.co/SNRR55H"><img src="https://i.ibb.co/ZdWWGGv/Screen-Shot-2020-11-25-at-22-52-53.png" alt="Screen-Shot-2020-11-25-at-22-52-53" border="0"></a>

<br><br>
<strong>Resourses</strong><br>
http://www.cs.cornell.edu/courses/cs4620/2019fa/<br>
https://www.gabrielgambetta.com/computer-graphics-from-scratch/basic-ray-tracing.html <br>
https://www.youtube.com/watch?v=1HYhrx9bzP8<br>
https://github.com/ggambetta/computer-graphics-from-scratch/blob/master/Computer-Graphics-from-scratch.md<br>
https://computergraphicsguide.blogspot.com/2015/08/raycasting-and-phong-shading.html<br>
https://steveharveynz.wordpress.com/category/programming/c-raytracer/<br>
https://course.ccs.neu.edu/cs4300old/s11/lectures.html<br>
http://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm<br>
https://web.cs.hacettepe.edu.tr/~erkut/bco511.s12/w03-raytracing.pdf<br>
https://www.youtube.com/watch?v=62-pRVZuS5c<br>
https://pdfs.semanticscholar.org/0e97/152b766ecbe29f0850a419ba3ba725d38463.pdf?_ga=2.17519292.427919042.1589188046-1548235695.1589188046<br>
https://mrl.nyu.edu/~dzorin/rend05/lecture2.pdf<br>
https://mrl.nyu.edu/~dzorin/rend05/lecture1a.pdf<br>
https://mrl.nyu.edu/~dzorin/rend05/<br>
