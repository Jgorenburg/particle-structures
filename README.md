# Particle Structures

In this project I build a system that can generate spheres out of particles. These particles can then dissolve into nothingness or into other shapes with the click of a button. 

## Base
I used the GLM library and my previous particles project as a starting point for this system. 

## New Code
### Renderer
 I added one new method to *renderer* to increase the efficiency of rendering particles. The old system passed the location of every particle individually and loaded a quadrilateral at that location. My new method **particles** passes a list of locations as points rather than vertices of triangles. This left me generate 4 times as many particles in the same time. In addition, I passed an array of normals to accomidate phong shading.
 
 Quadrilateral based system:
 
 ![q](/images/firstexample.gif)
 
 Point based system:
 
 ![pb](/images/ColorChange.gif)
 
### Phong Shading
 I added new fragment and vertex shaders that allowed me to shade the particle spheres like normal phong shading for spheres. I used a pixel-based phong shader because my shape had no faces. The actual shaders were copied from my MeshViewer project with minimal changes.

![p](/images/Normal.jpeg)


### Particle Struct
I added a new particle system *ParticleStruct* based on *ParticleSystem*.
ParticleStruct included a few new methods:

**BuildSphere**

BuildSphere takes an vec3 origin, float radius, and float scale and generates a sphere out of particles around the origin. The scale is the distance between particles. If the distance is small enough that the sphere would require more particles than the max number given during init, a larger scale is used. 

**DecayTo**

DecayTo takes a vec3 place, float distribution and speed, and a vec4 color and sends the particles from their current location to a box around the given place. The distribution determines the size of the box and the speed provides a baseline speed the particles travel to get there (the actual speed is randomized between 0.5 * speed and 2 * speed). If the system is using the billboard shaders, the color of the particles will be set by color. The particles travel along a bezier curve from their current location to a random one within the box using two random points in between as the other two values of the curve. When they arrive at their location, they dissappear from view (but are not deleted). DecayTo can be run by pressing space.

![d](/images/Decay.gif)

**BuildFromSphere**

BuildFromSphere takes all the inputs of the last two functions. It then runs in the opposite of DecayTo to build up a sphere at the origin out of particles. BuildFromSphere can be run by pressing enter.

![b](/images/Build.gif)

**MoveToSphere**
 
 MoveToSphere takes the same inputs as BuildFromSphere except the vec3 place. It then moves runs identically to BuildFromSphere except the particles move from their current location instead of from a random one. If the particles have dissappeared because of a decay, they will reappear with the same x and y coordinates, but possibly a different z one. MoveToSphere can be run by pressing right shift.
 
![m](/images/Move.gif)
