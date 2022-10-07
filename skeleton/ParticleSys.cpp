#include "ParticleSys.h"
#include "GaussianParticleGen.h"

ParticleSys::ParticleSys(int n)
{
	for (int i = 0; i < n; i++) {

		particleGen.push_back(new GaussianParticleGen(Vector3(0, 0, -300), Vector3(90,89, 50), 50, Vector3(20,20, 10), 
			Vector3(25,25, 10), 0.8,  1,  3));

	}
}

void ParticleSys::update(double t)
{
	for (auto i = particles.begin(); i != particles.end(); ++i) {

		auto particle = *i;

		if (particle->viva()) {
			particle->integrate(t);
		}

		else {
			delete particle;
			i = particles.erase(i);
		}

	}

	for (auto j = particleGen.begin(); j != particleGen.end(); ++j) {

		auto gen = *j;

		std::list<Particle*> aux = gen->generateParticles();

		for (auto i = aux.begin(); i != aux.end(); ++i) {
			particles.push_back(*i);
		}

	}


}
