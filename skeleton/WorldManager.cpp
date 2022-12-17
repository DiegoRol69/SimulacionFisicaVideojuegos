#include "WorldManager.h"

WorldManager::WorldManager(PxScene* gScene_, PxPhysics* gPhysics_, ParticleSys* pSys_) {

	gScene = gScene_;
	gPhysics = gPhysics_;
	pSys = pSys_;

	PxRigidStatic* Suelo = gPhysics->createRigidStatic(PxTransform({ 0,0,0 }));
	PxShape* shape = CreateShape(PxBoxGeometry(100, 0.1, 100));
	Suelo->attachShape(*shape);
	item = new RenderItem(shape, Suelo, { 0.8, 0.8, 0.8, 1 });
	Suelo->setName("sinEfecto");
	gScene->addActor(*Suelo);

	RigidParticle* suelo = new RigidParticle(Suelo, false, item);

	PxRigidStatic* Pared = gPhysics->createRigidStatic(PxTransform({ 10 , 10, -30 }));
	PxShape* shape_suelo = CreateShape(PxBoxGeometry(40, 20, 5));
	Pared->attachShape(*shape_suelo);
	item = new RenderItem(shape_suelo, Pared, { 0.8, 0.8, 0.8, 1 });
	Pared->setName("sinEfecto");
	gScene->addActor(*Pared);

	RigidParticle* pared = new RigidParticle(Pared, false, item);

	rigidParticles.push_back(suelo);
	rigidParticles.push_back(pared);
	
	//generar un spawn enemies
	//hacer que los fireworks/generadores aparezcan donde muere el solido rigido


	RFR = new RigidParticleForceRegistry();
	NM = new RigidParticlesNamesManager();

	contTimeGen = 0;
	genTime = 1;
}

void WorldManager::createRigidDynamic(Vector3 pos, Vector3 vel, PxShape* shape, double density,
	Vector4 color, names nm)
{
	PxRigidDynamic* new_solid;

	new_solid = gPhysics->createRigidDynamic(PxTransform(pos));
	new_solid->setLinearVelocity(vel);
	new_solid->setAngularVelocity({ 0,0,0 });
	new_solid->attachShape(*shape);
	PxRigidBodyExt::setMassAndUpdateInertia(*new_solid, density);
	item = new RenderItem(shape, new_solid, color);
	new_solid->setName(NM->enumToName(nm));
	gScene->addActor(*new_solid);

	RigidParticle* rp = new RigidParticle(new_solid, 10, true, item);

	rigidParticles.push_back(rp);
}

void WorldManager::addGen(TipoGen tipoGen, names nm)
{
	ParticleRigidGenerator* generator;
	std::uniform_real_distribution<double> radius(0.2, 2);

	std::uniform_real_distribution<PxReal> size(0.2, 2);

	PxMaterial* gMaterial = gPhysics->createMaterial(0.2f, 0.2f, 0.3f);

	switch (tipoGen)
	{
	case Gaussian:
		break;
	case Uniform:
		break;
	case Circle:
		break;
	case Standard:
		//CreateShape(PxBoxGeometry(size(gen), size(gen), size(gen))
		generator = new NormalParticleRigidGenerator(CreateShape(PxSphereGeometry(5), gMaterial),
			nm, 1, 0.8, 1, 9);
		generator->setMeans({ 0,100,0 }, { 0,-4,0 });
		break;
	}

	particleGen.push_back(generator);
}

void WorldManager::shootProyectile(Vector3 pos, Vector3 vel, PxShape* shape, double density,
	Vector4 color, names nm)
{
	PxRigidDynamic* new_solid;

	new_solid = gPhysics->createRigidDynamic(PxTransform(pos));
	new_solid->setLinearVelocity(vel);
	new_solid->setAngularVelocity({ 0,0,0 });
	new_solid->attachShape(*shape);
	PxRigidBodyExt::setMassAndUpdateInertia(*new_solid, density);
	item = new RenderItem(shape, new_solid, color);
	new_solid->setName(NM->enumToName(nm));
	gScene->addActor(*new_solid);

	Proyectile* rp = new Proyectile(new_solid, 10, true, item);
	rp->setTypeName(nm);

	rigidParticles.push_back(rp);
}

void WorldManager::addForce(typeF tipoF)
{

	RigidForceGenerator* FG;

	if (rigidParticles.size() > 0) {
		switch (tipoF)
		{
		case Gravity:
			break;
		case Wind:
			break;
		case Whirl:
			break;
		case Expl:
			rExplosion = new RigidExplosion(1000000, 200, 100, { 0, 0, 0 });
			FG = rExplosion;
			break;
		}

		for (auto i : rigidParticles) {
			if(i->getDynamicP() != nullptr) RFR->addRegistry(FG, i);
		}
	}

}


void WorldManager::collisionEfect(PxActor* actor1_, PxActor* actor2_)
{
	PxActor* actor;
	RigidParticle* particula1 = nullptr;
	RigidParticle* particula2 = nullptr;

	auto i = rigidParticles.begin();

	while ((particula1 == nullptr || particula2 == nullptr) && i != rigidParticles.end()) {

		actor = (*i)->getActor();

		if (actor == actor1_) {
			particula1 = (*i);
		}

		if (actor == actor2_) {
			particula2 = (*i);
		}

		++i;

	}

	particula1->onCollision(particula2->getTypeName(), pSys);
	particula2->onCollision(particula1->getTypeName(), pSys);

}

void WorldManager::update(double t)
{
	auto i = rigidParticles.begin();

	while (i != rigidParticles.end()) {

		(*i)->integrate(t);

		if (!(*i)->viva()) {
			RFR->deleteParticleRegistry(*i);
			gScene->removeActor(*(*i)->getActor());
			delete (*i);
			i = rigidParticles.erase(i);
		}

		else {
			++i;
		}
	}

	contTimeGen += t;
	if (contTimeGen >= genTime) {
		for (auto j : particleGen) {

			std::list<RigidParticle*> aux = j->generateParticles(gPhysics);

			for (auto i : aux) {
				gScene->addActor(*i->getActor());
				rigidParticles.push_back(i);
			}

		}

		contTimeGen = 0;
	}

	RFR->updateForces(t);

	if (rExplosion != nullptr) rExplosion->addConst(t);
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

	delete NM;
	delete RFR;

	auto i = rigidParticles.begin();

	while (i != rigidParticles.end()) {
		i = rigidParticles.erase(i);
	}
}
