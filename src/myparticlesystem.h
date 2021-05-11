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
   };
}
#endif