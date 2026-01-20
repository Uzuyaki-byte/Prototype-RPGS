#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"

typedef struct {
    Vector3 position;
    float speed;
    Color color;
    bool inVehicle;
    int vehicleIdx;
} Player;

void InitPlayer(Player *player);
void UpdatePlayer(Player *player, Vector3 forward, Vector3 right, float dt);
void DrawPlayer(Player player);

#endif
