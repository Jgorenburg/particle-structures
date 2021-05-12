#ifndef MyParticleSystem_H_
#define MyParticleSystem_H_

#include "particlesystem.h"

namespace agl {

class MyParticleSystem : public ParticleSystem {
    public:
        virtual void createParticles(int size) override;
        virtual void update(float dt) override;
        virtual void updateSize();
        virtual void addParticles(vec3 cursorpos, float dt);

    private:
       bool sizestart = true;
       float numParticles;
       vec3 colors = vec3(1);
       float fulltime = 0;
   };
}
#endif