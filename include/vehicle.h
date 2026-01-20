#ifndef VEHICLE_H
#define VEHICLE_H

#include "common.h"

typedef struct {
    Vector3 position;
    Vector3 size;
    float speed;
    bool active;
    Color color;
} Vehicle;

void UpdateVehicle(Vehicle *vehicle, Vector3 forward, Vector3 right, float dt);
void DrawVehicle(Vehicle vehicle);

#endif
