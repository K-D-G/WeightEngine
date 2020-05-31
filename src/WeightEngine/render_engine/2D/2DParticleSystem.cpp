#include <WeightEngine/render_engine/2D/2DParticleSystem.h>

using namespace Weight;
using namespace RenderEngine;

ParticleSystem2D::ParticleSystem2D(unsigned int _max_particles):max_particles(_max_particles), max_index(_max_particles*6){
  particle_pool.reserve(max_particles);

  glGenVertexArrays(1, &vertex_array);
  glBindVertexArray(vertex_array);

  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(ParticleVertexRenderBuffer)*max_particles, nullptr, GL_DYNAMIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ParticleVertexRenderBuffer), (const void*)offsetof(ParticleVertexRenderBuffer, position));

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleVertexRenderBuffer), (const void*)offsetof(ParticleVertexRenderBuffer, colour));

  unsigned int indices[max_index];
  unsigned int offset=0;
  for(size_t i=0; i<max_index; i+=6){
    indices[i+0]=0+offset;
    indices[i+1]=1+offset;
    indices[i+2]=2+offset;
    indices[i+3]=2+offset;
    indices[i+4]=3+offset;
    indices[i+5]=0+offset;
    offset+=4;
  }

  glGenBuffers(1, &index_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

ParticleSystem2D::~ParticleSystem2D(){
  glDeleteVertexArrays(1, &vertex_array);
  glDeleteBuffers(1, &vertex_buffer);
  glDeleteBuffers(1, &index_buffer);
}

Particle2D* ParticleSystem2D::create_particle(Position2D position, Vector2D velocity, Vector2D velocity_variation, Colour begin_colour, Colour end_colour, float begin_size, float end_size, float size_variation, float life_time){
  return create_particle({position.x, position.y, 0.0f}, velocity, velocity_variation, begin_colour, end_colour, begin_size, end_size, size_variation, life_time);
}

Particle2D* ParticleSystem2D::create_particle(Position3D position, Vector2D velocity, Vector2D velocity_variation, Colour begin_colour, Colour end_colour, float begin_size, float end_size, float size_variation, float life_time){
  Particle2D* result=new Particle2D;

  result->position=position;
  result->velocity=velocity;
  result->velocity_variation=velocity_variation;
  result->begin_colour=begin_colour;
  result->end_colour=end_colour;
  result->begin_size=begin_size;
  result->end_size=end_size;
  result->size_variation=size_variation;
  result->life_time=life_time;

  result->life_remaining=0.0f;
  result->rotation=0.0f;
  result->active=false;

  return result;
}

void ParticleSystem2D::render(glm::mat4 mvp, float ts){
  std::vector<ParticleVertexRenderBuffer> particles;
  particles.reserve(particle_pool.size()*4);

  for(int i=0; i<particle_pool.size(); i++){
    if(particle_pool[i]->life_remaining<=0.0f){
      particle_pool[i]->active=false;
    }

    if(particle_pool[i]->active==false){
      particle_pool.erase(particle_pool.begin()+i);
      continue;
    }

    particle_pool[i]->life_remaining-=ts;
    particle_pool[i]->position.x+=particle_pool[i]->velocity.x*ts;
    particle_pool[i]->position.y+=particle_pool[i]->velocity.y*ts;
    particle_pool[i]->rotation+=0.1f*ts;

    float life=particle_pool[i]->life_remaining/particle_pool[i]->life_time;

    glm::vec4 colour=glm::lerp(glm::vec4(particle_pool[i]->end_colour.r, particle_pool[i]->end_colour.g, particle_pool[i]->end_colour.b, particle_pool[i]->end_colour.a), glm::vec4(particle_pool[i]->begin_colour.r, particle_pool[i]->begin_colour.g, particle_pool[i]->begin_colour.b, particle_pool[i]->begin_colour.a), life);
    Colour _colour={colour.x, colour.y, colour.z, colour.w};

    float size=glm::lerp(particle_pool[i]->end_size, particle_pool[i]->begin_size, life);

    ParticleVertexRenderBuffer v0={{particle_pool[i]->position.x, particle_pool[i]->position.y, particle_pool[i]->position.z}, _colour};
    ParticleVertexRenderBuffer v1={{particle_pool[i]->position.x, static_cast<float>(particle_pool[i]->position.y-size*0.5), particle_pool[i]->position.z}, _colour};
    ParticleVertexRenderBuffer v2={{static_cast<float>(particle_pool[i]->position.x+size*0.5), static_cast<float>(particle_pool[i]->position.y-size*0.5), particle_pool[i]->position.z}, _colour};
    ParticleVertexRenderBuffer v3={{static_cast<float>(particle_pool[i]->position.x+size*0.5), particle_pool[i]->position.y, particle_pool[i]->position.z}, _colour};

    float centre[2]={static_cast<float>(particle_pool[i]->position.x+size*0.5), static_cast<float>(particle_pool[i]->position.y-size*0.5)};

    //(v0.position.x-centre[0])
    //(v0.position.y-centre[1])
    //x_prime=static_cast<float>(((v0.position.y-centre[1])*sin(rotation)+(v0.position.x-centre[0])*cos(rotation))+centre[0]);
    //y_prime=static_cast<float>(((v0.position.y-centre[1])*cos(rotation)-(v0.position.x-centre[0])*sin(rotation))+centre[1]);

    float rotation=particle_pool[i]->rotation;
    v0.position.x=static_cast<float>(((v0.position.y-centre[1])*sin(rotation)+(v0.position.x-centre[0])*cos(rotation))+centre[0]);
    v0.position.y=static_cast<float>(((v0.position.y-centre[1])*cos(rotation)-(v0.position.x-centre[0])*sin(rotation))+centre[1]);

    v1.position.x=static_cast<float>(((v1.position.y-centre[1])*sin(rotation)+(v1.position.x-centre[0])*cos(rotation))+centre[0]);
    v1.position.y=static_cast<float>(((v1.position.y-centre[1])*cos(rotation)-(v1.position.x-centre[0])*sin(rotation))+centre[1]);

    v2.position.x=static_cast<float>(((v2.position.y-centre[1])*sin(rotation)+(v2.position.x-centre[0])*cos(rotation))+centre[0]);
    v2.position.y=static_cast<float>(((v2.position.y-centre[1])*cos(rotation)-(v2.position.x-centre[0])*sin(rotation))+centre[1]);

    v3.position.x=static_cast<float>(((v3.position.y-centre[1])*sin(rotation)+(v3.position.x-centre[0])*cos(rotation))+centre[0]);
    v3.position.y=static_cast<float>(((v3.position.y-centre[1])*cos(rotation)-(v3.position.x-centre[0])*sin(rotation))+centre[1]);

    particles.push_back(v0);
    particles.push_back(v1);
    particles.push_back(v2);
    particles.push_back(v3);
  }

  Particle2DShader::get()->bind();
  Particle2DShader::get()->set_matrix("mvp", mvp);;
  glBindVertexArray(vertex_array);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferSubData(GL_ARRAY_BUFFER, 0, particles.size()*sizeof(ParticleVertexRenderBuffer), particles.data());
  glDrawElements(GL_TRIANGLES, 6*particles.size()*0.25, GL_UNSIGNED_INT, nullptr);
}

void ParticleSystem2D::emit(Particle2D* p){
  p->active=1.0f;
  p->rotation=Random::get_float()*2.0f*glm::pi<float>();

  p->velocity.x+=p->velocity_variation.x*(Random::get_float()-0.5f);
  p->velocity.y+=p->velocity_variation.y*(Random::get_float()-0.5f);

  p->life_remaining=p->life_time;

  p->begin_size+=p->size_variation*(Random::get_float()-0.5f);

  particle_pool.push_back(p);
}
