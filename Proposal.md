# Particle Structures

My goal for this project is to generate complex objects out of particles that can grow from and return to clouds of dust. Inspirations for this project include the 
dusting scene in Avengers Edgame and Nightcrawler in X-Men United. 

## Features

### Necessary
- Generating simple shapes using particles
- Particles can drift away and dissapear
- Particles can appear in random locations and move towards their proper place in the shape

### Good-to-have
- Diffuse and/or phong lighting
- Complex shapes
- Way to control where particles start/end so they all come from the around same place
- Camera controls
- Staggered growth/decay (e.g. a pillar growing from the bottom up)

### Reach
- Clumping of neighboring particles to make the decay look more realistic
- Ability to make growth/decay start at one location and spread outward
  - A more complicated version of staggered growth where the start of particle movement is triggered by other particles moving instead of time
- Randomized growth and decay
  - This is probably the most difficult task and least likely to complete
- Color changes as particles drift away
  - Shift towards grey as they disapear 
- Transition between mesh and particles for efficiency 


## Algorithms and Math
- Bezier curves
  - I need these to make control the movement of the particles
  - My current plan is to generate 4 points per particle, the last/first of which is inside the shape
  - The math for a 4-point curve isn't complicated, but my approach requires storing 4 points and a time for every particle
- Algorithm for detecting if a position is inside the shape
  - I need this to determine the positions particles should end/start at
  - I plan to implement this by sending a ray from a point outside the shape to the point and checking how many times the ray intersects the edge of the shape. An odd number of collisions tells us the point is inside the shape.
  - One potential issue is finding a point that is definitely outside the object
- Raytracer for particles
  - If I want to implement diffuse lighting I'll need a raytracer that can deal with particles
- Algorithm for detecting adjacent particles
  - This algorithm is needed to clumping and spreading growth/decay, both reach goals
  - I think I might implement this as a graph where particles are nodes with edges to all particles within a certain distance of them
  - If I am deliberate with the order in which particles are generated, creating this graph shouldn't be too difficult or time consuming




