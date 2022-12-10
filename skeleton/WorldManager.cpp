#include "WorldManager.h"

WorldManager::WorldManager(PxScene* gScene_, PxPhysics* gPhysics_) {

	gScene = gScene_;
	gPhysics = gPhysics_;

	PxRigidStatic* Suelo = gPhysics->createRigidStatic(PxTransform({ 0,0,0 }));
	PxShape* shape = CreateShape(PxBoxGeometry(100, 0.1, 100));
	Suelo->attachShape(*shape);
	item = new RenderItem(shape, Suelo, { 0.8, 0.8, 0.8, 1 });
	Suelo->setName("sinEfecto");
	gScene->addActor(*Suelo);

	PxRigidStatic* Pared = gPhysics->createRigidStatic(PxTransform({ 10 , 10, -30 }));
	PxShape* shape_suelo = CreateShape(PxBoxGeometry(40, 20, 5));
	Pared->attachShape(*shape_suelo);
	item = new RenderItem(shape_suelo, Pared, { 0.8, 0.8, 0.8, 1 });
	Pared->setName("sinEfecto");
	gScene->addActor(*Pared);

}

void WorldManager::createRigidDynamic(Vector3 pos, Vector3 vel, PxShape* shape, double density, Vector4 color, char* name)
{

	PxRigidDynamic* new_solid;

	new_solid = gPhysics->createRigidDynamic(PxTransform(pos));
	new_solid->setLinearVelocity(vel);
	new_solid->setAngularVelocity({ 0,0,0 });
	new_solid->attachShape(*shape);
	PxRigidBodyExt::setMassAndUpdateInertia(*new_solid, density);
	item = new RenderItem(shape, new_solid, color);
	new_solid->setName(name);
	if (name == "") new_solid->setName("sinEfecto");
	gScene->addActor(*new_solid);

	RigidParticle* rp = new RigidParticle(new_solid, 10, item);

	rigidParticles.push_back(rp);

}

void WorldManager::collisionEfect(PxActor* actor1, PxActor* actor2)
{

	PxRigidActor* actor;

	auto i = rigidParticles.begin();

	while (i != rigidParticles.end()) {

		actor = (*i)->getActor();

		if (actor == actor1) {
			//(*i)->setAlive(false);
		}

		if (actor == actor2) {
			//v[1] = (*i);
		}

		++i;

	}
}

void WorldManager::addGen(TipoGen tipo)
{
	ParticleRigidGenerator* generator;
	std::uniform_real_distribution<double> radius(0.2, 2);

	std::uniform_real_distribution<PxReal> size(0.2, 2);

	PxMaterial* gMaterial = gPhysics->createMaterial(2.5f, 2.5f, 4.6f);

	switch (tipo)
	{
	case Gaussian:
		break;
	case Uniform:
		break;
	case Circle:
		break;
	case Standard:
		generator = new NormalParticleRigidGenerator(CreateShape(PxBoxGeometry(size(gen), size(gen), size(gen)), gMaterial), 
			"sinEfecto", 1, 0.8, 1, 9);
		generator->setMeans({ 0,100,0 }, { 0,-4,0 });
		break;
	}

	particleGen.push_back(generator);
}

void WorldManager::update(double t)
{
	auto i = rigidParticles.begin();

	while (i != rigidParticles.end()) {

		(*i)->integrate(t);

		if (!(*i)->viva()) {
			delete (*i);
			i = rigidParticles.erase(i);
		}

		else {
			++i;
		}
	}

	for (auto j : particleGen) {

		std::list<RigidParticle*> aux = j->generateParticles(gPhysics);

		for (auto i : aux) {
			gScene->addActor(*i->getActor());
			rigidParticles.push_back(i);
		}

	}
}

void WorldManager::deleteGenerators()
{
	auto i = particleGen.begin();

	while (i != particleGen.end()) {
		i = particleGen.erase(i);
	}
}

WorldManager::~WorldManager()
{

	auto i = rigidParticles.begin();

	while (i != rigidParticles.end()) {
		i = rigidParticles.erase(i);
	}

}
