#include "CircleParticleGen.h"

CircleParticleGen::CircleParticleGen(Particle* p, int n, double _generation_probability_, double radius_, type tipo_)
{
    _model = p;
    radius = radius_;
    num_particles = n;
    _generation_probability = _generation_probability_;
    tipo = tipo_;
}

void CircleParticleGen::setPosCircle(double angle_) {

    switch (tipo)
    {
    case FunteChocolate:
        vel_result = { float(physx::PxCos(angle) * radius), float(0), float(physx::PxSin(angle) * radius) };
        break;
    case FunteAgua:
        vel_result = { float(physx::PxCos(angle) * radius), float(20), float(physx::PxSin(angle) * radius) };
        break;
    default:
        break;
    }    
}

std::list<Particle*> CircleParticleGen::generateParticles()
{
    std::uniform_real_distribution<double> generationDistr(0, 1);

    std::list<Particle*> particles;

    for (int i = 0; i < num_particles; i++) {
        if (generationDistr(gen) < _generation_probability) {

            setPosCircle(angle);
            
            FireWork* fw = dynamic_cast<FireWork*>(_model);
            if (fw != nullptr) {
                FireWork* p = new FireWork();
                p->setFireWork(fw);
                p->setPos(mean_pos);
                p->setVel(vel_result);
                particles.push_back(p);
            }
            else {
                Particle* p = _model->clone();
                p->setPos(mean_pos);
                p->setVel(vel_result);
                particles.push_back(p);
            }
            angle += 360 / num_particles;
        }
    }

    return particles;
}
