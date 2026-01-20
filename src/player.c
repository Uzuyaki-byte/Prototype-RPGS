#include "player.h"

void InitPlayer(Player *player) {
    player->position = (Vector3){ 500, 2, 500 };
    player->speed = 15.0f;
    player->color = RED;
    player->inVehicle = false;
    player->vehicleIdx = -1;
}

void UpdatePlayer(Player *player, Vector3 forward, Vector3 right, float dt) {
    Vector3 move = { 0 };
    if (IsKeyDown(KEY_W)) move = Vector3Add(move, forward);
    if (IsKeyDown(KEY_S)) move = Vector3Subtract(move, forward);
    if (IsKeyDown(KEY_A)) move = Vector3Subtract(move, right);
    if (IsKeyDown(KEY_D)) move = Vector3Add(move, right);

    if (Vector3Length(move) > 0) {
        move = Vector3Normalize(move);
        player->position.x += move.x * player->speed * dt;
        player->position.z += move.z * player->speed * dt;
    }
}

void DrawPlayer(Player player) {
    DrawSphere(player.position, 2.0f, player.color);
    DrawSphereWires(player.position, 2.0f, 8, 8, BLACK);
}
