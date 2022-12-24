#include "WorldManager.h"

WorldManager::WorldManager(PxScene* gScene_, PxPhysics* gPhysics_, ParticleSys* pSys_) {

	gScene = gScene_;
	gPhysics = gPhysics_;
	pSys = pSys_;

	PxRigidStatic* Suelo = gPhysics->createRigidStatic(PxTransform({ 0,0,0 }));
	PxShape* shape = CreateShape(PxBoxGeometry(200, 0.1, 200));
	Suelo->attachShape(*shape);
	item = new RenderItem(shape, Suelo, { 0.0, 0.8, 0.0, 1 });
	Suelo->setName("sinEfecto");
	gScene->addActor(*Suelo);

	RigidParticle* suelo = new RigidParticle(Suelo, false, item);

	PxRigidStatic* Cobertura = gPhysics->createRigidStatic(PxTransform({ 10 , 5, -30 }));
	PxShape* shape_cobertura = CreateShape(PxBoxGeometry(40, 5, 3));
	Cobertura->attachShape(*shape_cobertura);
	item = new RenderItem(shape_cobertura, Cobertura, { 0.8, 0.8, 0.8, 1 });
	Cobertura->setName("sinEfecto");
	gScene->addActor(*Cobertura);

	RigidParticle* cobertura = new RigidParticle(Cobertura, false, item);

	PxRigidStatic* L1 = gPhysics->createRigidStatic(PxTransform({ 200 , 0, 0 }));
	PxShape* shape_L1 = CreateShape(PxBoxGeometry(5, 100, 200));
	L1->attachShape(*shape_L1);
	item = new RenderItem(shape_L1, L1, { 1.0, 0.0, 0.0, 1 });
	L1->setName("sinEfecto");
	gScene->addActor(*L1);

	PxRigidStatic* L2 = gPhysics->createRigidStatic(PxTransform({ -200 , 0, 0 }));
	PxShape* shape_L2 = CreateShape(PxBoxGeometry(5, 100, 200));
	L2->attachShape(*shape_L2);
	item = new RenderItem(shape_L2, L2, { 1.0, 1.0, 0.0, 1 });
	L2->setName("sinEfecto");
	gScene->addActor(*L2);

	PxRigidStatic* L3 = gPhysics->createRigidStatic(PxTransform({ 0 , 0, 200 }));
	PxShape* shape_L3 = CreateShape(PxBoxGeometry(200, 100, 5));
	L3->attachShape(*shape_L3);
	item = new RenderItem(shape_L3, L3, { 1.0, 0.0, 0.0, 1 });
	L3->setName("sinEfecto");
	gScene->addActor(*L3);

	PxRigidStatic* L4= gPhysics->createRigidStatic(PxTransform({ 0 , 0, -200 }));
	PxShape* shape_L4 = CreateShape(PxBoxGeometry(200, 100, 5));
	L4->attachShape(*shape_L4);
	item = new RenderItem(shape_L4, L4, { 1.0, 1.0, 0.0, 1 });
	L4->setName("sinEfecto");
	gScene->addActor(*L4);

	RigidParticle* l1 = new RigidParticle(L1, false, item);
	RigidParticle* l2 = new RigidParticle(L2, false, item);
	RigidParticle* l3 = new RigidParticle(L3, false, item);
	RigidParticle* l4 = new RigidParticle(L4, false, item);

	rigidParticles.push_back(suelo);
	rigidParticles.push_back(cobertura);
    rigidParticles.push_back(l1);
    rigidParticles.push_back(l2);
    rigidParticles.push_back(l3);
    rigidParticles.push_back(l4);

	RFR = new RigidParticleForceRegistry();
	NM = new RigidParticlesNamesManager();

	rBuoyancy = new RigidBuoyancyGenerator(1, 100);

	contTimeGen = 0;
	contTimeReset = 0;
	resetTime = 5;
	genTime = 0.5;

	minSize = 6;
}

void WorldManager::addGen(TipoGen tipoGen, names nm)
{
	ParticleRigidGenerator* generator;

	PxMaterial* gMaterial = gPhysics->createMaterial(0.2f, 0.2f, 0.3f);

	switch (tipoGen)
	{
	case Gaussian:
		break;
	case Uniform:
		break;
	case Circle:
		break;
	case SpawnEnem:
		generator = new EnemiesSpawn(CreateShape(PxSphereGeometry(5), gMaterial), 5,
			nm, 5, 1.1, 1, 9);
		generator->setMeans({ -20,50, 50 }, { 0,-4,0 });
		break;
	case Standard:
		generator = new NormalParticleRigidGenerator(nullptr,
			nm, 5, 0.8, 1, 2);
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
	gScene->addActor(*new_solid);

	Proyectile* rp = new Proyectile(new_solid, 5, true, item);
	rp->setTypeName(nm);

	rigidParticles.push_back(rp);
}

void WorldManager::addForce(typeF tipoF)
{

	RigidForceGenerator* FG;

	if (rigidParticles.size() > 0) {
		switch (tipoF)
		{
		case Atraction:
			atractionActive = true;
			FG = new AtractionForce(80, Vector3(0,10,0));
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

void WorldManager::addForceInPos(typeF tipoF, Vector3 pos)
{
	RigidForceGenerator* FG;

	if (rigidParticles.size() > 0) {
		switch (tipoF)
		{
		case Expl:
			rExplosion = new RigidExplosion(1000000, 200, 100, pos);
			FG = rExplosion;
			break;
		}

		for (auto i : rigidParticles) {
			if (i->getDynamicP() != nullptr) RFR->addRegistry(FG, i);
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

	if (particula1->getTypeName() == Bomb) addForceInPos(Expl, particula1->getDynamicP()->getGlobalPose().p);

	particula2->onCollision(particula1->getTypeName(), pSys);

}

void WorldManager::update(double t)
{

	if (atractionActive) {
		if (rigidParticles.size() == minSize) {
			atractionActive = false;
			contTimeReset = 0;
		}
		contTimeReset += t;

		if (contTimeReset >= resetTime) {
			pSys->generateFireworkInPos(Vector3(0,10,0), Gaussian, 50);
			addForceInPos(Expl, Vector3(0, 10, 0));
		}
	}

	auto i = rigidParticles.begin();

	while (i != rigidParticles.end()) {

		(*i)->integrate(t);

		if (contTimeReset >= resetTime) {
			if((*i)->getDynamicP() != nullptr)(*i)->activeDestroyable();
		}

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

			auto k = aux.begin();
			auto enem = dynamic_cast<Enemy*>(*k);

			if (enem != nullptr) {
				rBuoyancy->setVolume(enem->getRadius());
			}

			for (auto i : aux) {
				gScene->addActor(*i->getActor());
				rigidParticles.push_back(i);

				if (enem != nullptr) {
					RFR->addRegistry(rBuoyancy, i);
				}
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
