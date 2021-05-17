// Bryn Mawr College, alinen, 2020
//

#include "AGL.h"
#include "AGLM.h"
#include <cmath>
#include "particle-struct.h"

using namespace std;
using namespace agl;
using namespace glm;




void ParticleStruct::createParticles(int size)
{
   mTexture = theRenderer.loadTexture("../textures/particle.png");
   numParticles = size;

  
}

ParticleStruct::~ParticleStruct()
{
	for (int i = 0; i < mParticles.size(); i++) {
		delete[] mParticles[i].bezier;
	}
	delete[] pos;
	delete[] norm;
}

void ParticleStruct::init(int size)
{
	if (!theRenderer.initialized())
	{
		theRenderer.dynamicInit(size, "../shaders/billboard.vs", "../shaders/billboard.fs");
	}
	createParticles(size);
}

void ParticleStruct::draw()
{
	
	theRenderer.begin(mTexture, mBlendMode);

	theRenderer.particles(pos, norm, colors, numParticles);
}


// tells program to start decay
void ParticleStruct::decayTo(vec3 place, float distribution, float speed) {
	decaying = true;
	building = false;

	for (int i = 0; i < mParticles.size(); i++) {
		Particle p = mParticles[i];

		p.time = 0;
		p.speed = RandomFloat(speed / 2, 2 * speed);
		p.bezier = new vec3[4];
		p.bezier[0] = p.pos;
		p.bezier[3] = place + random_unit_sphere() * distribution;
		p.initSize = p.size;
		p.done = false;

		float minX = std::min(p.pos.x, place.x);
		float maxX = std::max(p.pos.x, place.x);
		float minY = std::min(p.pos.y, place.y);
		float maxY = std::max(p.pos.y, place.y);
		float minZ = std::min(p.pos.z, place.z);
		float maxZ = std::max(p.pos.z, place.z);

		p.bezier[1] = vec3(RandomFloat(minX, maxX), RandomFloat(minY, maxY), RandomFloat(minZ, maxZ));
		p.bezier[2] = vec3(RandomFloat(minX, maxX), RandomFloat(minY, maxY), RandomFloat(minZ, maxZ));

		mParticles[i] = p;
	}
}

void ParticleStruct::buildFromSphere(vec3 place, vec3 origin, float radius, float distribution, float speed, float scale) {
	building = true;
	decaying = false;

	if (radius <= 0) { return; }

	float minX = origin.x - radius;
	float maxX = origin.x + radius;
	float minY = origin.y - radius;
	float maxY = origin.y + radius;
	float minZ = origin.z - radius;
	float maxZ = origin.z + radius;

	float widthX = maxX - minX;
	float widthY = maxY - minY;
	float widthZ = maxZ - minZ;

	if (widthX * widthY * widthZ / pow(scale, 3.0f) > numParticles) {
		float downscale = cbrt(numParticles / (widthX * widthY * widthZ / pow(scale, 3.0f)));
		scale = scale / downscale;
	}

	for (int i = 0; i < mParticles.size(); i++) {
		delete[] mParticles[i].bezier;
	}
	mParticles.clear();

	for (float i = minZ; i <= maxZ; i = i + scale) {
		for (float j = minY; j <= maxY; j = j + scale) {
			for (float k = minX; k <= maxX; k = k + scale) {
				vec3 jitter = random_unit_cube() * scale;
				vec3 point(k, j, i);
				if (length(point - origin) <= radius) {
					Particle p;

					setColor(vec4(0, 128, 0, 1));
					p.color = vec4(0, 128, 0, 1);
					p.vel = vec3(0);
					p.initSize = scale * 2;
					p.size = 0.0f;

					p.bezier = new vec3[4];
					vec3 start = place + random_unit_sphere() * distribution;
					p.bezier[0] = start;
					p.bezier[3] = point + jitter;
					p.pos = start;
					p.done = false;
					p.speed = RandomFloat(speed / 2, 1.5 * speed);
					p.time = 0;

					float minX = std::min(p.pos.x, place.x);
					float maxX = std::max(p.pos.x, place.x);
					float minY = std::min(p.pos.y, place.y);
					float maxY = std::max(p.pos.y, place.y);
					float minZ = std::min(p.pos.z, place.z);
					float maxZ = std::max(p.pos.z, place.z);

					p.bezier[1] = vec3(RandomFloat(minX, maxX), RandomFloat(minY, maxY), RandomFloat(minZ, maxZ));
					p.bezier[2] = vec3(RandomFloat(minX, maxX), RandomFloat(minY, maxY), RandomFloat(minZ, maxZ));



					if (mParticles.size() < numParticles) {
						mParticles.push_back(p);
					}
				}
			}
		}
	}	
}



// builds a circle out of particles
void ParticleStruct::buildCircle(vec3 origin, float radius, float scale)
{
	if (radius <= 0) { return; }

	float minX = origin.x - radius;
	float maxX = origin.x + radius;
	float minY = origin.y - radius;
	float maxY = origin.y + radius;
	float minZ = origin.z - radius;
	float maxZ = origin.z + radius;

	float widthX = maxX - minX;
	float widthY = maxY - minY;
	float widthZ = maxZ - minZ;

	// sets a minimum scale based on max num of particles
	if (widthX * widthY * widthZ / pow(scale, 3.0f) > numParticles){
		float downscale = cbrt(numParticles / (widthX * widthY * widthZ / pow(scale, 3.0f)));
		scale = scale / downscale;
	}

	cout << scale << endl;
	cout << minZ << " " << maxZ << endl;

	for (float i = minZ; i <= maxZ; i = i + scale) {
		for (float j = minY; j <= maxY; j = j + scale) {
			for (float k = minX; k <= maxX; k = k + scale) {
				vec3 jitter = random_unit_cube() * scale;
				vec3 point(k, j, i);
				if (length(point - origin) <= radius) {
					setColor(vec4(0, 128, 0, 1));

					Particle p;
					p.pos = point + jitter;
					p.color = vec4(0, 128, 0, 1);
					p.vel = vec3(0);
					p.size = scale * 2;

					if (mParticles.size() < numParticles) {
						mParticles.push_back(p);
					}
				}
			}
		}
		cout << "salmon:" << i << endl;
	}
	cout << "out\n";
}

void ParticleStruct::buildTriangle(vec3 first, vec3 second, vec3 third, float scale) {

	float minX = std::min(std::min(first.x, second.x), third.x);
	float maxX = std::max(std::max(first.x, second.x), third.x);
	float minY = std::min(std::min(first.y, second.y), third.y);
	float maxY = std::max(std::max(first.y, second.y), third.y);
	float minZ = std::min(std::min(first.z, second.z), third.z);
	float maxZ = std::max(std::max(first.z, second.z), third.z);



}


float ParticleStruct::relPosFromLine(vec3 first, vec3 second, vec3 pos) {
	return (second[1] - first[1]) * (pos[0] - first[0]) - (second[0] - first[0]) * (pos[1] - first[1]);
}
/*
void ParticleStruct::addParticles(vec3 cursorPos, float dt) {
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

		*

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
*/
void ParticleStruct::update(float dt)
{
	if (decaying) {
		cout << "decay!\n";
		decay(dt);
	}
	else if (building) {
		cout << "build!\n";
		build(dt);
	}
	else {
		cout << "nothing\n";
	}
}

void ParticleStruct::decay(float dt)
{
	bool finished = true;
	for (int i = 0; i < mParticles.size(); i++) {		
		Particle p = mParticles[i];

		if (!p.done) {
			finished = false;

			p.time += dt * p.speed;

			if (p.time > 1) {
				p.color = vec4(0, 0, 0, 1);
				//setColor(vec4(0, 0, 0, 1));
				p.pos.z = -p.pos.z;
				p.done = true;
			}
			else {
				p.pos = BezierInterp(p.bezier, p.time);
				p.size = p.initSize * (1 - p.time);
			}

			mParticles[i] = p;
		}
	}

	decaying = !finished;
}

void ParticleStruct::build(float dt)
{
	bool finished = true;
	for (int i = 0; i < mParticles.size(); i++) {
		Particle p = mParticles[i];

		if (!p.done) {
			finished = false;

			p.time += dt * p.speed;

			if (p.time > 1) {
				//p.color = vec4(0, 0, 0, 1);
				p.pos = BezierInterp(p.bezier, 1.0f);
				p.size = p.initSize * 1.0f;
				p.done = true;
			}
			else {
				p.pos = BezierInterp(p.bezier, p.time);
				p.size = p.initSize * p.time;
			}

			mParticles[i] = p;
		}
	}

	//building = !finished;
}


vec3 ParticleStruct::BezierInterp(const vec3 * points, float t) {
	vec3 newPos = pow(1 - t, 3.0f) * points[0] + 3.0f * pow(1 - t, 2.0f) * t * points[1] + 3.0f * (1.0f - t) * pow(t, 2.0f) * points[2] + pow(t, 3.0f) * points[3];
	return newPos;
}






void ParticleStruct::updateSize() {
	sizestart = true;
}


// make sure to only call after updateArrays
float ParticleStruct::getSize() {
	return numParticles;
}

void ParticleStruct::updateArrays() {
	
	delete[] pos;
	delete[] norm;

	numParticles = mParticles.size();

	pos = new float[3.0f * numParticles];
	norm = new float[3.0f * numParticles];

	for (int i = 0; i < numParticles; i++) {
		int j = 3 * i;
		pos[j] = mParticles[i].pos.x;
		pos[j + 1] = mParticles[i].pos.y;
		pos[j + 2] = mParticles[i].pos.z;

		/*
		norm[j] = mParticles[i].pos.x;
		norm[j + 1] = mParticles[i].pos.y;
		norm[j + 2] = mParticles[i].pos.z;
		*/
		/*pos[j] = random_unit_cube().x;
		pos[j + 1] = random_unit_cube().y;
		pos[j + 2] = random_unit_cube().z;*/

		norm[j] = 0.0f;
		norm[j + 1] = 0.0f;
		norm[j + 2] = 0.0f;
	}
}

float* ParticleStruct::positions() {
	return pos;
}

float* ParticleStruct::normals() {
	return norm;
}

void ParticleStruct::setColor(vec4 newColor) {
	colors = newColor;
}


// code copied from StackExchange
// https://stackoverflow.com/questions/5289613/generate-random-float-between-two-floats
float ParticleStruct::RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}


