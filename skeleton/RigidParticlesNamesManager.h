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
		case SinEfecto:
			name = "SinEfecto";
			break;
		case BalaFA:
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


