#include "FireWork.h"

FireWork::FireWork()
{

}

void FireWork::setFireWork(FireWork *p)
{

	list<shared_ptr <ParticleGenerator>> aux = p->getGens();

	for (auto i : aux) {
		_gens.push_back(i);
	}

	particleProperties pModel = p->getProperties();
	
	properties.pose = physx::PxTransform(pModel.pose.p.x, pModel.pose.p.y, pModel.pose.p.z);
	properties.vel = pModel.vel;
	properties.damping = pModel.damping;
	properties.aceleration = pModel.aceleration;
	properties.masa = pModel.masa;
	properties.shape = pModel.shape;
	properties.tiempoVida = pModel.tiempoVida;
	properties.compruebaRango = pModel.compruebaRango;
	properties.force = pModel.force;
	properties.inv_mass = pModel.inv_mass;
	properties.radius = pModel.radius;

	std::uniform_real_distribution<double> color(0, 1);

	properties.renderItem = new RenderItem(properties.shape, &properties.pose, { float(color(gen)), float(color(gen)), float(color(gen)), 1 });
}

void FireWork::setFireWork(Vector3 pos, Vector3 v, double damp, Vector3 acel, double m, 
	physx::PxShape* shape, double tiempoVida_, int nDiv, int nGen, shared_ptr <ParticleGenerator> gen)
{

	properties.pose.p = pos;
	properties.vel = v;
	properties.damping = damp;
	properties.aceleration = acel;
	properties.shape = shape;
	properties.tiempoVida = tiempoVida_;
	properties.force = { 0,0,0 };
	
	if (m == 0) properties.masa = 1;
	else {
		properties.masa = m;
		properties.inv_mass = 1 / m;
	}

	div = nDiv;
	divTotales = nGen;

	_gens.push_back(gen);
}

list<Particle*> FireWork::explode()
{
	list<Particle*> explosion;

	for (auto i : _gens) {

		i->setMeans(properties.pose.p, properties.vel);
		list<Particle*> cadena = i->generateParticles();

		for (auto j : cadena) {
			explosion.push_back(j);
		}

	};

	return explosion;
}
