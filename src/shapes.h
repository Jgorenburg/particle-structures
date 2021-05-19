#ifndef SHAPES_H
#define SHAPES_H

#include "AGL.h"
#include "AGLM.h"
#include "particlesystem.h"

using namespace std;
using namespace glm;
using namespace agl;


class shape {
public: 
	virtual bool inShape(vec3& pos);
	virtual vec3 getNormal(vec3& pos);
	virtual vec3 getMins();
	virtual vec3 getMaxs();
	virtual void setMinandMax();

public:
	vec3 mins;
	vec3 maxs;
	bool set = false;
};

class sphere : public shape {
public: 
	sphere() : origin(0), radius(0) {};
	sphere(vec3 cen, float r) :
		origin(cen), radius(r) {};

	bool inShape(vec3& pos) override {
		return (length(pos - origin) <= radius);
	}
	vec3 getNormal(vec3& pos) override {
		return pos - origin;
	}
	vec3 getMins() override {
		if (!set) {
			setMinandMax();
			set = true;
		}
		return mins;

	}
	vec3 getMaxs() override {
		if (!set) {
			setMinandMax();
			set = true;
		}
		return maxs;

	}
	void setMinandMax() override {
		float minX = origin.x - radius;
		float maxX = origin.x + radius;
		float minY = origin.y - radius;
		float maxY = origin.y + radius;
		float minZ = origin.z - radius;
		float maxZ = origin.z + radius;

		mins = vec3(minX, minY, minZ);
		maxs = vec3(maxX, maxY, maxZ);
	}
	


public:
	vec3 origin;
	float radius;
};



#endif



















