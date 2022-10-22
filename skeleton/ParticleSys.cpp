#include "ParticleSys.h"
#include "GaussianParticleGen.h"
#include "UniformParticleGen.h"
#include "RenderUtils.hpp"

ParticleSys::ParticleSys()
{

}

void ParticleSys::update(double t)
{

	for (auto j : particleGen) {

		std::list<Particle*> aux = j->generateParticles();

		for (auto i : aux) {
			particles.push_back(i);
		}

	}

	auto i = particles.begin();

	while ( i != particles.end()) {

		(*i)->integrate(t);

		if (!(*i)->viva()) {
			delete (*i);
			i = particles.erase(i);
		}

		else {
			++i;
		}
	 }
}

void ParticleSys::addGen(TipoGen tipo)
{

	Camera* camera = GetCamera();

	switch (tipo)
	{
	case Gaussian:
		Particle* p;
		p->setParticle(Vector3(15, 40, 0), camera->getDir() * (-10), 0.8, Vector3(0, -9.8, 0), 440, CreateShape(physx::PxSphereGeometry(10)));
		particleGen.push_back(new GaussianParticleGen(p, 1, Vector3(0.1, 0.1, 10), Vector3(0.1, 0.1, 0.1), 0.8, 1));
		break;
	case Uniform:
		particleGen.push_back(new UniformParticleGen(Vector3(0, 40, 0), Vector3(0,0,0), 10, 0.1, Vector3(10, 10, 10), Vector3(3, 3, 3)));
		break;
	}

}
