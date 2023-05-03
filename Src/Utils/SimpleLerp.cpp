#include "SimpleLerp.h"

using namespace me;

float SimpleLerp::Lerp(float a, float b, float f)
{
	return a + f * (b - a);
}