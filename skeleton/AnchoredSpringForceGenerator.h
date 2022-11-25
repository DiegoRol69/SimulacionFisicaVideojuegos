#pragma once
#include "SpringForceGenerator.h"
#include "core.hpp"

class AnchoredSpringForceGenerator:public SpringForceGenerator
{

public:

	AnchoredSpringForceGenerator(double k,
		double resting, const Vector3& anchorPos);

	~AnchoredSpringForceGenerator() { delete other; };


};

