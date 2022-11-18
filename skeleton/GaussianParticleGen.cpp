#include "GaussianParticleGen.h"

GaussianParticleGen::GaussianParticleGen(Particle* p, int n, Vector3 dev_pos_, Vector3 dev_vel_, double _generation_probability_,
    double dev_t_, typeF tipoF_) {

    _model = p;

    num_particles = n;
    dev_pos = dev_pos_;
    dev_vel = dev_vel_;
    _generation_probability = _generation_probability_;
    dev_t = dev_t_;
    tipoF = tipoF_;

    setForceToClon();
}

void GaussianParticleGen::setDistribution() {
    px = std::normal_distribution<>(mean_pos.x, dev_pos.x);
    py = std::normal_distribution<>(mean_pos.y, dev_pos.y);
    pz = std::normal_distribution<>(mean_pos.z, dev_pos.z);

    vx = std::normal_distribution<>(mean_vel.x, dev_vel.x);
    vy = std::normal_distribution<>(mean_vel.y, dev_vel.y);
    vz = std::normal_distribution<>(mean_vel.z, dev_vel.z);
}

void GaussianParticleGen::setForceToClon()
{
    switch (tipoF)
    {
    case Gravity:
        fg = new GravityForceGenerator({ 0,-8.5,0 });
        break;
    case Wind:
       fg = new WindForceGenerator(0.8, 0.0, {8.5,0,0});
        break;
    case Whirl:
        fg = new Whirlwind(-10, { 15,30,0 });
        break;
    default:
        break;
    }
}

ForceGenerator *GaussianParticleGen::getTypeF()
{
    return fg;
}

std::list<Particle*> GaussianParticleGen::generateParticles()
{

    std::uniform_real_distribution<double> generationDistr(0, 1);
    std::normal_distribution<> t(_model->getProperties().tiempoVida, dev_t);

    setDistribution();

    std::list<Particle*> particles;

    for (int i = 0; i < num_particles; i++) {

        pos_result = { float(px(gen)), float(py(gen)), float(pz(gen)) };
        vel_result = { float(vx(gen)), float(vy(gen)), float(vz(gen)) };

        if (generationDistr(gen) < _generation_probability) {
            FireWork* fw = dynamic_cast<FireWork*>(_model);
            if (fw != nullptr){
                FireWork* p = new FireWork();
                p->setFireWork(fw);
                p->setPos(pos_result);
                p->setVel(vel_result);
                p->setTime(t(gen));
                particles.push_back(p);
            }
            else {
                Particle* p = _model->clone();
                p->setPos(pos_result);
                p->setVel(vel_result);
                p->setTime(t(gen));
                particles.push_back(p);
            }
        }
    }

    return particles;
}
