#pragma once
#include "Particle.h"

enum TipoBala {PISTOL, ARTILLERY, FIREBALL};

class Proyectile : public Particle
{
public:
	Proyectile(TipoBala t);
	~Proyectile() {};
};

