#pragma once

enum names{SinEfecto, BalaFA, ult};

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
		}

		return name;
	};
private:

};


