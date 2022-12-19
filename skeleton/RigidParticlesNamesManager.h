#pragma once
#include "RigidParticlesNames.h"

class RigidParticlesNamesManager
{
public:
	RigidParticlesNamesManager(){};
	~RigidParticlesNamesManager(){};
	char* enumToName(names m) {
		char* name;

		switch (m)
		{
		case NonEffect:
			name = "SinEfecto";
			break;
		case BulletFW:
			name = "BalaFA";
			break;
		case Enem:
			name = "Enemy";
			break;
		}

		return name;
	};
private:

};


