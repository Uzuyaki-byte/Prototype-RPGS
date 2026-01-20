#include "vehicle.h"

void UpdateVehicle(Vehicle *vehicle, Vector3 forward, Vector3 right, float dt) {
    if (!vehicle->active) return;

    Vector3 move = { 0 };
    if (IsKeyDown(KEY_W)) move = Vector3Add(move, forward);
    if (IsKeyDown(KEY_S)) move = Vector3Subtract(move, forward);
    if (IsKeyDown(KEY_A)) move = Vector3Subtract(move, right);
    if (IsKeyDown(KEY_D)) move = Vector3Add(move, right);

    if (Vector3Length(move) > 0) {
        move = Vector3Normalize(move);
        vehicle->position.x += move.x * vehicle->speed * dt;
        vehicle->position.z += move.z * vehicle->speed * dt;
    }
}

void DrawVehicle(Vehicle vehicle) {
    if (!vehicle.active) return;
    DrawCube(vehicle.position, vehicle.size.x, vehicle.size.y, vehicle.size.z, vehicle.color);
    DrawCubeWires(vehicle.position, vehicle.size.x, vehicle.size.y, vehicle.size.z, BLACK);
}
