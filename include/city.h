#ifndef CITY_H
#define CITY_H

#include "common.h"

void InitCity(void);
void DrawCity3D(Vector3 center, float drawDistance);
bool CheckCityCollision(Vector3 center, float radius);

#endif
