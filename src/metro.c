#include "metro.h"

void UpdateMetro(Metro *metro, Player *player, float dt) {
    if (metro->going_forward) {
        metro->progress += metro->speed * dt;
        if (metro->progress >= 1.0f) metro->going_forward = false;
    } else {
        metro->progress -= metro->speed * dt;
        if (metro->progress <= 0.0f) metro->going_forward = true;
    }

    metro->position = Vector3Lerp(metro->start, metro->end, metro->progress);

    BoundingBox playerBox = {
        (Vector3){ player->position.x - 2, player->position.y - 1, player->position.z - 2 },
        (Vector3){ player->position.x + 2, player->position.y + 1, player->position.z + 2 }
    };
    BoundingBox metroBox = {
        (Vector3){ metro->position.x - metro->size.x/2, metro->position.y - metro->size.y/2, metro->position.z - metro->size.z/2 },
        (Vector3){ metro->position.x + metro->size.x/2, metro->position.y + metro->size.y/2, metro->position.z + metro->size.z/2 }
    };

    if (CheckCollisionBoxes(playerBox, metroBox)) {
        float metroMoveX = (metro->going_forward ? 1 : -1) * metro->speed * Vector3Distance(metro->start, metro->end) * dt;
        player->position.x += metroMoveX;
    }
}

void DrawMetro(Metro metro) {
    DrawCube(metro.position, metro.size.x, metro.size.y, metro.size.z, metro.color);
    DrawCubeWires(metro.position, metro.size.x, metro.size.y, metro.size.z, DARKGREEN);
}
