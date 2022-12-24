#include "ParticleSys.h"
#include "GaussianParticleGen.h"
#include "UniformParticleGen.h"
#include "CircleParticleGen.h"
#include "RenderUtils.hpp"
#include "GravityForceGenerator.h"
#include "BuoyancyForceGenerator.h"
#include <iostream>

ParticleSys::ParticleSys()
{
	FR = new ParticleForceRegistry();
	srand(time(NULL));
	explosionActive = false;
}

void ParticleSys::update(double t)
{
	auto i = particles.begin();

	while ( i != particles.end()) {

		(*i)->integrate(t);

		if (!(*i)->viva()) {

			auto fw = dynamic_cast<FireWork*>(*i);

			if (fw != nullptr) {
				auto explosion =  fw->explode();
				particles.insert(particles.end(), explosion.begin(), explosion.end());
			}

			FR->deleteParticleRegistry(*i);
			delete (*i);
			i = particles.erase(i);
			
		}

		else {
			++i;
		}
	}


	FR->updateForces(t);

	if (explosionActive) explosion->addConst(t);

	for (auto j : particleGen) {

		std::list<Particle*> aux = j->generateParticles();

		for (auto i : aux) {
			if(j->getTypeF() != nullptr)FR->addRegistry(j->getTypeF(), i);
			particles.push_back(i);
		}

	}
}

void ParticleSys::addGen(TipoGen tipo)
{
	Camera* camera = GetCamera();
	Particle* p = new Particle();

	ParticleGenerator* gen;
	typeF randTypeForce = static_cast<typeF>(rand() % ultimo);
	double radius = 0.5;

	switch (tipo)
	{
	case Gaussian:
		p->setParticle(Vector3(0,0,0), Vector3(0,0,0), 0.8, Vector3(0, 0, 0), 10, 
			CreateShape(physx::PxSphereGeometry(radius)), 100, Vector3(15, 40, 0), Vector3(60,60,60), false, false, radius);
		gen = new GaussianParticleGen(p, 5, Vector3(0.1, 0.1, 10), Vector3(0.1, 0.1, 0.1), 0.8, 1, randTypeForce);
		gen->setMeans(Vector3(15, 40, 0), camera->getDir() * (-10));
		break;
	case Uniform:
		p->setParticle(Vector3(0, 0, 0), Vector3(0, 0, 0), 0.8, Vector3(0, 0, 0), 440, 
			CreateShape(physx::PxSphereGeometry(radius)), 50, Vector3(0, 40, 0), Vector3(10, 15, 10), false, false, radius);
		gen = new UniformParticleGen(p, 10, 0.1, Vector3(10, 10, 10), Vector3(3, 3, 3), randTypeForce);
		gen->setMeans(Vector3(15, 30, 0), Vector3(0, 0, 0));
		break;
	case Circle:
		p->setParticle(Vector3(0, 0, 0), Vector3(0, 0, 0), 0.8, Vector3(0, 0, 0), 10, 
			CreateShape(physx::PxSphereGeometry(radius)), 100, Vector3(0, 40, 0), Vector3(50, 50, 50), false, false, radius);
		typeC randomType = static_cast<typeC>(rand()%ult);
		gen = new CircleParticleGen(p, 10, 0.8, 20, randomType, randTypeForce);
		gen->setMeans(Vector3(0, 40, 0), Vector3(0, 0, 0));
		break;
	}

	particleGen.push_back(gen);

}

void ParticleSys::addGenInPos(TipoGen tipo, Vector3 pos)
{
	Camera* camera = GetCamera();
	Particle* p = new Particle();

	ParticleGenerator* gen;
	double radius = 0.3;

	switch (tipo)
	{
	case Gaussian:
		p->setParticle(Vector3(0,0,0), Vector3(0,0,0), 0.8, Vector3(0, 0, 0), 10, 
			CreateShape(physx::PxSphereGeometry(radius)), 100, Vector3(15, 40, 0), Vector3(60,60,60), false, false, radius);
		gen = new GaussianParticleGen(p, 5, Vector3(0.1, 0.1, 10), Vector3(0.1, 0.1, 0.1), 0.8, 1, ultimo);
		gen->setMeans(Vector3(15, 40, 0), camera->getDir() * (-10));
		break;
	case Uniform:
		p->setParticle(Vector3(0, 0, 0), Vector3(0, 0, 0), 0.8, Vector3(0, 0, 0), 440, 
			CreateShape(physx::PxSphereGeometry(radius)), 50, Vector3(0, 40, 0), Vector3(10, 15, 10), false, false, radius);
		gen = new UniformParticleGen(p, 10, 0.1, Vector3(10, 10, 10), Vector3(3, 3, 3), ultimo);
		gen->setMeans(Vector3(15, 30, 0), Vector3(0, 0, 0));
		break;
	case Circle:
		p->setParticle(Vector3(0, 0, 0), Vector3(0, 0, 0), 0.8, Vector3(0, 0, 0), 10, 
			CreateShape(physx::PxSphereGeometry(radius)), 3, pos, Vector3(8, 8, 8), false, true, radius);
		gen = new CircleParticleGen(p, 1, 0.8, 20, FunteAgua, ultimo);
		gen->setMeans(pos, Vector3(0, 0, 0));
		break;
	}

	particleGen.push_back(gen);
}

void ParticleSys::addParticle()
{
	double randomMass = 1 + rand() % (401 - 1);
	double randomX, randomZ;

	randomX = rand() % 101;
	randomZ = rand() % 101;

	vector<int> pos = {-1, 1};

	int aux1 = rand() % 2;
	int aux2 = rand() % 2;

	Particle* p = new Particle();
	p->setParticle(Vector3(pos[aux1]*randomX, 0, pos[aux2]*randomZ), Vector3(0, 0, 0), 0.8, Vector3(0, 0, 0), randomMass,
		CreateShape(physx::PxSphereGeometry(randomMass/150)), 1000, 
		Vector3(0, 40, 0), Vector3(10, 15, 10), true, false, randomMass / 150);

	particles.push_back(p);
}

void ParticleSys::addExplosion()
{

	if (particles.size() > 0) {
		explosion = new Explosion(200, 200, 100, { 0, 0, 0 });
		explosionActive = true;
	}

	for (auto i : particles) {
		if (i->viva()) {
			FR->addRegistry(explosion, i);
		}
	}
}

void ParticleSys::addWind()
{
	if (particles.size() > 0) {
		wind  = new WindForceGenerator(1.8, 0.0, { 8.5,8.5,0 });
	}

	for (auto i : particles) {
		FR->addRegistry(wind, i);
	}
}

void ParticleSys::addGravity()
{
	if (particles.size() > 0) {
		gf = new GravityForceGenerator({ 0,-9.8,0 });
	}

	for (auto i : particles) {
		FR->addRegistry(gf, i);
	}
}

void ParticleSys::addK()
{
	if(fsp1 != nullptr) 
		fsp1->setK(5);
	if(fsp2 != nullptr) 
		fsp2->setK(5);
	if(fanch != nullptr) 
		fanch->setK(5);
}

void ParticleSys::quitRegistry()
{
	if (fsp1 != nullptr) {
		FR->deleteParticleRegistry(muelle1);
		FR->addRegistry(fsp1, muelle1);
	}
	if (fsp2 != nullptr) {
		FR->deleteParticleRegistry(muelle2);
		FR->addRegistry(fsp2, muelle2);
	}
}

void ParticleSys::deleteGenerators()
{
	auto i = particleGen.begin();

	while (i != particleGen.end()) {
		i = particleGen.erase(i);
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

	p->setParticle(Vector3(15, 40, 0), Vector3(0, 10, 0), 0.8, Vector3(0, -9.8, 0), 440,
		CreateShape(physx::PxSphereGeometry(0.5)), 3, Vector3(15, 40, 0), Vector3(1000, 1000, 1000),  false, false, 0.5);
	
	typeC randomType = static_cast<typeC>(rand() % ult);
	typeF randTypeForce = static_cast<typeF>(rand() % ult);

	shared_ptr <ParticleGenerator> gen(new CircleParticleGen(p, 20, 0.8, 20, randomType, randTypeForce));
	fw->setFireWork(Vector3(15, 40, 0), Vector3(0, 10, 0), 0.8, Vector3(0, -5, 0),
		440, CreateShape(physx::PxSphereGeometry(0.5)), 3, 10, 5, gen);
	firework_pool.push_back(fw);

	fw = new FireWork();

	shared_ptr <ParticleGenerator> gen2(new GaussianParticleGen(firework_pool[0], 20, Vector3(0.1, 0.1, 0.1), Vector3(10, 10, 10), 0.8, 1, randTypeForce));
	fw->setFireWork(Vector3(15, 40, 0), Vector3(0, 10, 0), 0.8, Vector3(0, -2, 0),
		440, CreateShape(physx::PxSphereGeometry(0.5)), 3, 10, 5, gen2);
	firework_pool.push_back(fw);

	fw = new FireWork();

	shared_ptr <ParticleGenerator> gen3(new GaussianParticleGen(p, 15, Vector3(0.1, 0.1, 0.1), Vector3(10, 10, 10), 0.8, 1, randTypeForce));
	fw->setFireWork(Vector3(15, 40, 0), Vector3(0, 10, 0), 0.8, Vector3(0, -2, 0),
		440, CreateShape(physx::PxSphereGeometry(0.5)), 0.5, 10, 5, gen3);
	firework_pool.push_back(fw);
}

void ParticleSys::generateFireworkInPos(Vector3 pos, TipoGen type, int n)
{
	Particle* p = new Particle();
	FireWork* fw = new FireWork();

	p->setParticle(Vector3(15, 40, 0), Vector3(0, 10, 0), 0.8, Vector3(0, -9.8, 0), 440,
		CreateShape(physx::PxSphereGeometry(0.5)), 10, Vector3(15, 40, 0), Vector3(1000, 1000, 1000), false, false, 0.5);

	ParticleGenerator* pGen;

	switch (type)
	{
	case Gaussian:
		pGen = new GaussianParticleGen(p, n, Vector3(0.1, 0.1, 0.1), Vector3(10, 10, 10), 0.8, 1, ultimo);
		break;
	case Uniform:
		break;
	case Circle:
		pGen = new CircleParticleGen(p, n, 0.8, 20, FunteChocolate, ultimo);
		break;
	case Standard:
		break;
	default:
		break;
	}

	shared_ptr <ParticleGenerator> gen(pGen);
	fw->setFireWork(pos, Vector3(0, 0, 0), 0.8, Vector3(0, -2, 0),
		440, CreateShape(physx::PxSphereGeometry(0.5)), 0.0, 10, 5, gen);
	
	fw->setFireWork(fw);

	particles.push_back(fw);
}

void ParticleSys::Spring()
{
	double radius = 1;

	muelle1 = new Particle();
	muelle1->setParticle(Vector3(-10, 10, 0), Vector3(0, 0, 0), 0.8, Vector3(0, 0, 0), 10,
		CreateShape(physx::PxSphereGeometry(radius)), 100,
		Vector3(15, 40, 0), Vector3(60, 60, 60), true, false, radius);
	muelle2 = new Particle();
	muelle2->setParticle(Vector3(10, 10, 0), Vector3(0, 0, 0), 0.8, Vector3(0, 0, 0), 10,
		CreateShape(physx::PxSphereGeometry(radius)), 100,
		Vector3(15, 40, 0), Vector3(60, 60, 60), true, false, radius);

	fsp1 = new SpringForceGenerator(200, 10, muelle2);
	FR->addRegistry(fsp1, muelle1);

	fsp2 = new SpringForceGenerator(200, 10,  muelle1);
	FR->addRegistry(fsp2, muelle2);

	particles.push_back(muelle2);
	particles.push_back(muelle1);
}

void ParticleSys::Anchored()
{

	Particle* p = new Particle();
	double radius = 1;

	p->setParticle(Vector3(-10, 20, 0), Vector3(0, 0, 0), 0.8, Vector3(0, 0, 0), 2,
		CreateShape(physx::PxSphereGeometry(radius)), 100,
		Vector3(15, 40, 0), Vector3(60, 60, 60), true, false, radius);

	fanch = new AnchoredSpringForceGenerator(5,10,{10,20,0});
	FR->addRegistry(fanch, p);
	particles.push_back(p);
}

void ParticleSys::Slinky()
{
	double radius = 2;

	Particle* p2 = new Particle();

	p2->setParticle(Vector3(0, 20, 0), Vector3(0, 0, 0), 0.8, Vector3(0, 0, 0), 5,
		CreateShape(physx::PxSphereGeometry(radius)), 100,
		Vector3(15, 40, 0), Vector3(60, 60, 60), true, false, radius);

	Particle* p3 = new Particle();

	p3->setParticle(Vector3(0, 10, 0), Vector3(0, 0, 0), 0.8, Vector3(0, 0, 0), 5,
		CreateShape(physx::PxSphereGeometry(radius)), 100,
		Vector3(15, 40, 0), Vector3(60, 60, 60), true, false, radius);

	Particle* p4 = new Particle();

	p4->setParticle(Vector3(0, 0, 0), Vector3(0, 0, 0), 0.8, Vector3(0, 0, 0), 5,
		CreateShape(physx::PxSphereGeometry(radius)), 100,
		Vector3(15, 40, 0), Vector3(60, 60, 60), true, false, radius);

	Particle* p5 = new Particle();

	p5->setParticle(Vector3(0, -10, 0), Vector3(0, 0, 0), 0.8, Vector3(0, 0, 0), 5,
		CreateShape(physx::PxSphereGeometry(radius)), 100,
		Vector3(15, 40, 0), Vector3(60, 60, 60), true, false, radius);

	Particle* p6 = new Particle();

	p6->setParticle(Vector3(0, -20, 0), Vector3(0, 0, 0), 0.8, Vector3(0, 0, 0), 5,
		CreateShape(physx::PxSphereGeometry(radius)), 100,
		Vector3(15, 40, 0), Vector3(60, 60, 60), true, false, radius);

	AnchoredSpringForceGenerator* f1 = new AnchoredSpringForceGenerator(30, 5, { 0,30,0 });
	FR->addRegistry(f1, p2);
	SpringForceGenerator* f2 = new SpringForceGenerator(30, 5, p2);
	//2,3
	FR->addRegistry(f2, p3);
	SpringForceGenerator* f3 = new SpringForceGenerator(30, 5, p3);
	FR->addRegistry(f3, p2);
	//3,4
	FR->addRegistry(f3, p4);
	SpringForceGenerator* f4 = new SpringForceGenerator(30, 5, p4);
	FR->addRegistry(f4, p3);
	//4,5
	FR->addRegistry(f4, p5);
	SpringForceGenerator* f5 = new SpringForceGenerator(30, 5, p5);
	FR->addRegistry(f5, p4);
	//5,6
	FR->addRegistry(f5, p6);
	SpringForceGenerator* f6 = new SpringForceGenerator(30, 5, p6);
	FR->addRegistry(f6, p5);

	particles.push_back(p2);
	particles.push_back(p3);
	particles.push_back(p4);
	particles.push_back(p5);
	particles.push_back(p6);

}

void ParticleSys::Buoyancy()
{

	Particle* p = new Particle();
	p->setParticle(Vector3(20, 40, 20), Vector3(0, 0, 0), 0.8, Vector3(0, 0, 0), 100,
		CreateShape(physx::PxBoxGeometry(1,1,1)), 100,
		Vector3(15, 40, 0), Vector3(60, 60, 60), true, false, 2);

	BuoyancyForceGenerator* by = new BuoyancyForceGenerator(1, 7, 0.05, 7, 1000);
	GravityForceGenerator *g = new GravityForceGenerator({ 0,-9.8,0 });
	ParticleDragGenerator* drg = new ParticleDragGenerator(100,0);

	FR->addRegistry(by, p);
	FR->addRegistry(g,p);
	FR->addRegistry(drg, p);

	particles.push_back(p);

}
