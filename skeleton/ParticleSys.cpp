#include "ParticleSys.h"
#include "GaussianParticleGen.h"
#include "UniformParticleGen.h"
#include "CircleParticleGen.h"
#include "RenderUtils.hpp"
#include "GravityForceGenerator.h"

ParticleSys::ParticleSys()
{
	FR = new ParticleForceRegistry();
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

		FR->updateForces(t);
		(*i)->integrate(t);

		if (!(*i)->viva()) {

			auto fw = dynamic_cast<FireWork*>(*i);

			if (fw != nullptr) {
				auto explosion =  fw->explode();
				particles.insert(particles.end(), explosion.begin(), explosion.end());
			}

			delete (*i);
			i = particles.erase(i);
		}

		else {
			++i;
		}
	 }
}

void ParticleSys::addGen(TipoGen tipo, TipoFuerza f)
{
	srand(time(NULL));
	Camera* camera = GetCamera();
	Particle* p = new Particle();

	ParticleGenerator* gen;

	switch (tipo)
	{
	case Gaussian:
		p->setParticle(Vector3(0,0,0), Vector3(0,0,0), 0.8, Vector3(0, -9.8, 0), 440, 
			CreateShape(physx::PxSphereGeometry(0.5)), 3, Vector3(15, 40, 0), Vector3(20, 20, 20), false, true);
		addForceGen(f, p);
		gen = new GaussianParticleGen(p, 1, Vector3(0.1, 0.1, 10), Vector3(0.1, 0.1, 0.1), 0.8, 1);
		gen->setMeans(Vector3(15, 40, 0), camera->getDir() * (-10));
		break;
	case Uniform:
		p->setParticle(Vector3(0, 0, 0), Vector3(0, 0, 0), 0.8, Vector3(0, 9.8, 0), 440, 
			CreateShape(physx::PxSphereGeometry(0.5)), 3, Vector3(0, 40, 0), Vector3(10, 15, 10), false, true);
		addForceGen(f, p);
		gen = new UniformParticleGen(p, 10, 0.1, Vector3(10, 10, 10), Vector3(3, 3, 3));
		gen->setMeans(Vector3(0, 40, 0), Vector3(0, 0, 0));
		break;
	case Circle:
		p->setParticle(Vector3(0, 0, 0), Vector3(0, 0, 0), 0.8, Vector3(0, -9.8, 0), 440, 
			CreateShape(physx::PxSphereGeometry(0.5)), 3, Vector3(0, 40, 0), Vector3(50, 50, 50), false, true);
		addForceGen(f, p);
		type randomType = static_cast<type>(rand()%ult);
		gen = new CircleParticleGen(p, 10, 0.8, 20,  randomType);
		gen->setMeans(Vector3(0, 40, 0), Vector3(0, 0, 0));
		break;
	}

	particleGen.push_back(gen);

}

void ParticleSys::addForceGen(TipoFuerza f, Particle *p)
{
	GravityForceGenerator* fg = new GravityForceGenerator({ 8.5,8.5,8.5 });

	switch (f)
	{
	case GRAVITY:
		FR->addRegistry(fg, p);
		break;
	case DRAG:
		break;
	default:
		break;
	}
}

void ParticleSys::shootFirework(int type)
{
	FireWork* fw = new FireWork();
	fw->setFireWork(firework_pool[type]);
	particles.push_back(fw);
}

void ParticleSys::generateFireworkSystem()
{

	Particle* p = new Particle();
	FireWork* fw = new FireWork();

	p->setParticle(Vector3(15, 40, 0), Vector3(0, 10, 0), 0.8, Vector3(0, -9.8, 0), 440, CreateShape(physx::PxSphereGeometry(0.5)), 3, Vector3(15, 40, 0), Vector3(1000, 1000, 1000),  false, false);
	
	type randomType = static_cast<type>(rand() % ult);

	shared_ptr <ParticleGenerator> gen(new CircleParticleGen(p, 20, 0.8, 20, randomType));
	fw->setFireWork(Vector3(15, 40, 0), Vector3(0, 10, 0), 0.8, Vector3(0, -5, 0),
		440, CreateShape(physx::PxSphereGeometry(0.5)), 3, 10, 5, gen);
	firework_pool.push_back(fw);

	fw = new FireWork();

	shared_ptr <ParticleGenerator> gen2(new GaussianParticleGen(firework_pool[0], 20, Vector3(0.1, 0.1, 0.1), Vector3(10, 10, 10), 0.8, 1));
	fw->setFireWork(Vector3(15, 40, 0), Vector3(0, 10, 0), 0.8, Vector3(0, -2, 0),
		440, CreateShape(physx::PxSphereGeometry(0.5)), 3, 10, 5, gen2);
	firework_pool.push_back(fw);


}
