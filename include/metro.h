#ifndef METRO_H
#define METRO_H

#include "common.h"
#include "player.h"

typedef struct {
    Vector3 position;
    Vector3 size;
    Vector3 start;
    Vector3 end;
    float speed;
    float progress;
    bool going_forward;
    Color color;
} Metro;

void UpdateMetro(Metro *metro, Player *player, float dt);
void DrawMetro(Metro metro);

#endif
