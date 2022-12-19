#pragma once

#include <ctype.h>
#include <PxPhysicsAPI.h>
#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "ParticleSys.h"
#include "WorldManager.h"
#include "RigidParticle.h"

#include <iostream>

using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation* gFoundation = NULL;
PxPhysics* gPhysics = NULL;


PxMaterial* gMaterial = NULL;

PxPvd* gPvd = NULL;

PxDefaultCpuDispatcher* gDispatcher = NULL;
PxScene* gScene = NULL;

ParticleSys* sysParticle = NULL;

WorldManager* world = NULL;

ContactReportCallback gContactReportCallback;

int bulletType = 0;

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	sysParticle = new ParticleSys();
	sysParticle->generateFireworkSystem();

	world = new WorldManager(gScene, gPhysics, sysParticle);
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);
	sysParticle->update(t);

	if (t < 0.1) {
		world->update(t);
	}
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();

	delete world;

	gFoundation->release();
}

void mousePress(int x, int y, const PxTransform& camera) {
	PX_UNUSED(camera);

	Camera* camera_ = GetCamera();
	Vector3 posCamera = camera_->getTransform().p;

	names bullet;
	PxShape* shape;

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	double density;

	if (bulletType % 2 == 0) {
		bullet = BulletFW;
		shape = CreateShape(physx::PxSphereGeometry(0.5), gMaterial);
		density = 9;
	}
	else {
		bullet = Bomb;
		shape = CreateShape(physx::PxSphereGeometry(4), gMaterial);
		density = 300;
	}

	world->shootProyectile(posCamera, 80 * camera_->getDir(),
		shape, density, { 1,0,0, 1 }, bullet);

}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	Camera* camera_ = GetCamera();
	Vector3 posCamera = camera_->getTransform().p;

	switch (toupper(key))
	{
	 //PARTICULAS NO FISICAS
	case 'G':
		sysParticle->addGen(Gaussian);
		break;
	case 'U':
		sysParticle->addGen(Uniform);
		break;
	case 'C':
		sysParticle->addGen(Circle);
		break;
	case 'F':
		sysParticle->shootFirework(0);
		break;
	case 'E':
		sysParticle->shootFirework(1);
		break;
	case 'P':
		sysParticle->addParticle();
		break;
	case 'X':
		sysParticle->addExplosion();
		world->addForce(Expl);
		break;
	case 'H':
		sysParticle->addWind();
		break;
	case 'Y':
		sysParticle->addGravity();
		break;
	case 'M':
		sysParticle->Spring();
		break;
	case 'K':
		sysParticle->addK();
		break;
	case 'Q':
		sysParticle->quitRegistry();
		break;
	case 'L':
		sysParticle->Anchored();
		break;
	case 'O':
		sysParticle->Slinky();
		break;
	case 'B':
		sysParticle->Buoyancy();
		break;
	//PARTICULAS FISICAS
	case 'R':
		//posCamera, 80 * camera_->getDir()
		world->createRigidDynamic({0,100,0}, {0,0,0},
			CreateShape(physx::PxSphereGeometry(2)), 7, { 1,0,0, 1 }, Enem);
		break;
	case '7':
		bulletType++;
		break;
	case 'Z':
		world->deleteGenerators();
		sysParticle->deleteGenerators();
		break;
	case '1':
		world->addGen(SpawnEnem, Enem);
		break;
	case '2':
		world->addGen(Standard, NonEffect);
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);

	world->collisionEfect(actor1, actor2);
}


int main(int, const char* const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for (PxU32 i = 0; i < frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}