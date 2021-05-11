// Bryn Mawr College, alinen, 2020
//

#include "AGL.h"
#include "AGLM.h"
#include <cmath>
#include "myparticlesystem.h"

using namespace std;
using namespace agl;
using namespace glm;

bool sizestart = true;
float numParticles;
vec3 colors(1);
float fulltime = 0;

void MyParticleSystem::createParticles(int size) 
{
   mTexture = theRenderer.loadTexture("../textures/particle.png");
   numParticles = size;

  
}

void MyParticleSystem::addParticles(vec3 cursorPos, float dt) {
	int limit = std::min(std::max(numParticles * 0.5f * dt, 1.0f), numParticles - mParticles.size());

	for (int i = 0; i < limit; i++) {
		Particle p;
		p.pos = cursorPos - vec3(0.5f, -0.5f, -2.0f);
		
		//random color
		//p.color = vec4(random_unit_cube() + vec3(0.5f), 1);

		//changing color
		/*fulltime += dt;
		colors[0] = abs(sin(fulltime));
		colors[1] = abs(cos(fulltime));
		colors[2] = abs((sin(fulltime) + cos(fulltime)) / sqrt(2));
		p.color = vec4(colors, 1);

		*/

		//two-color
		float rand = random_unit_cube()[0];
		if (rand < 0) {
			p.color = vec4(0.8f, 0.2f, 0.6f, 1.0f);
		}
		else {
			p.color = vec4(0.4f, 0.5f, 0.9f, 1.0f);
		}

		p.vel = random_unit_cube();
		p.size = (random_unit_cube()[0] + 0.5f) / 10;

		mParticles.push_back(p);
	}
}

void MyParticleSystem::update(float dt)
{
	// update particles
	for (int i = 0; i < mParticles.size(); i++) {
		Particle p = mParticles[i];



		//change size and remove particle if too small
		
		if (sizestart) { p.size = p.size * (1 - dt); }
		if (p.size < 0.001f) {
			mParticles.erase(mParticles.begin() + i);
			i--;
		}
		else {

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
}

void MyParticleSystem::updateSize() {
	sizestart = true;
}

