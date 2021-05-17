#ifndef ParticleStruct_H_
#define ParticleStruct_H_

#include "particlesystem.h"

namespace agl {

   class ParticleStruct : public ParticleSystem {
   public:
      virtual void createParticles(int size) override;
      virtual ~ParticleStruct();
      virtual void update(float dt) override;
      virtual void updateSize();
      //virtual void addParticles(vec3 cursorpos, float dt);
      virtual void buildCircle(vec3 origin, float radius, float scale = 0.1f);
      virtual void buildTriangle(vec3 first, vec3 second, vec3 third, float scale = 0.1f);

      // triggers the start of decaying
      // place is the location the particles decay towards
      // distribution decides how closely they head towards that point
      // speed is how fast they approach
      virtual void decayTo(vec3 place, float distribution = 1.0f, float speed = 0.3f);

      virtual void buildFromSphere(vec3 place, vec3 origin, float radius, float distribution = 1.0f, float speed = 0.3f, float scale = 0.1f);
      virtual float getSize();
      virtual void updateArrays();
      virtual float* positions();
      virtual float* normals();
      virtual void init(int size);
      virtual void draw();

   private:
       bool sizestart = true;
       float numParticles;
       vec3 colors = vec3(1);
       float fulltime = 0;
       float* pos;
       float* norm;

       bool decaying = false;
       bool building = false;

       float relPosFromLine(vec3 first, vec3 second, vec3 pos);
       void decay(float dt);
       void build(float dt);
       float RandomFloat(float a, float b);
       vec3 BezierInterp(const vec3 * points, float time);
   };
}
#endif