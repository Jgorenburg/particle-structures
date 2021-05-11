// Bryn Mawr College, alinen, 2020
//

#include "AGL.h"
#include "AGLM.h"
#include <cmath>
#include "confetti.h"

using namespace std;
using namespace agl;
using namespace glm;

void Confetti::createParticles(int size) 
{
	mTexture = theRenderer.loadTexture("../textures/particle.png");
	// TODO: Create particles
	for (int i = 0; i < size; i++) {
		Particle p;
		p.pos = random_unit_cube();
		p.color = vec4(random_unit_cube() + vec3(0.5f), 1);
		p.vel = random_unit_cube();
		p.size = 0.25f;
	
		mParticles.push_back(p);
	}

	

}

void Confetti::update(float dt)
{
  // update particles


	for (int i = 0; i < mParticles.size(); i++) {
		Particle p = mParticles[i];


		//change pos
		p.pos = p.pos + p.vel * dt;

		//change vel
		if (p.pos[0] < -1 || p.pos[0] > 1) { p.vel[0] *= -1; }
		if (p.pos[1] < -1 || p.pos[1] > 1) { p.vel[1] *= -1; }
		if (p.pos[2] < -1 || p.pos[2] > 1) { p.vel[2] *= -1; }

		//update order
		if (i != 0) {
			Particle p2 = mParticles[i - 1];
			float dist1 = length(p.pos - theRenderer.cameraPosition());
			float dist2 = length(p2.pos - theRenderer.cameraPosition());

			if (dist1 > dist2) {
				mParticles[i - 1] = p;
				mParticles[i] = p2;
			}
			else {
				mParticles[i] = p;
			}
		}
		else {
			mParticles[i] = p;
		}
	}
	
}

