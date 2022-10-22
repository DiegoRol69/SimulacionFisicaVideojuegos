#include "UniformParticleGen.h"

UniformParticleGen::UniformParticleGen(Particle *p, int n, double _generation_probability_, Vector3 pos_width_, Vector3 vel_width_)
{
    _model = p;
    num_particles = n;
    _generation_probability = _generation_probability_;
    pos_width = pos_width_;
    vel_width = vel_width_;
}

void UniformParticleGen::setDistribution() {

    px = std::uniform_real_distribution<>(mean_pos.x - pos_width.x / 2, mean_pos.x + pos_width.x / 2);
    py = std::uniform_real_distribution<>(mean_pos.y - pos_width.y / 2, mean_pos.y + pos_width.y / 2);
    pz = std::uniform_real_distribution<>(mean_pos.z - pos_width.z / 2, mean_pos.z + pos_width.z / 2);

    vx = std::uniform_real_distribution<>(mean_vel.x - vel_width.x / 2, mean_vel.x + vel_width.x / 2);
    vy = std::uniform_real_distribution<>(mean_vel.y - vel_width.y / 2, mean_vel.y + vel_width.y / 2);
    vz = std::uniform_real_distribution<>(mean_vel.z - vel_width.z / 2, mean_vel.z + vel_width.z / 2);
}

std::list<Particle*> UniformParticleGen::generateParticles()
{
    std::uniform_real_distribution<double> generationDistr(0, 1);

    std::list<Particle*> particles;

    setDistribution();

    for (int i = 0; i < num_particles; i++) {
        if (generationDistr(gen) < _generation_probability) {

            pos_result = { float(px(gen)), float(py(gen)), float(pz(gen)) };
            vel_result = { float(vx(gen)), float(vy(gen)), float(vz(gen)) };

            FireWork* fw = dynamic_cast<FireWork*>(_model);
            if (fw != nullptr) {
                FireWork* p = new FireWork();
                p->setFireWork(fw);
                p->setPos(pos_result);
                p->setVel(vel_result);
                particles.push_back(p);
            }
            else {
                Particle* p = _model->clone();
                p->setPos(pos_result);
                p->setVel(vel_result);
                particles.push_back(p);
            }
        }
    }

    return particles;
}
