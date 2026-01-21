#include "player.h"
#include "city.h"

void InitPlayer(Player *player) {
  player->position = (Vector3){-50, 2, -50};
  player->speed = 15.0f;
  player->radius = 2.0f;
  player->color = RED;
  player->inVehicle = false;
  player->vehicleIdx = -1;
}

void UpdatePlayer(Player *player, Vector3 forward, Vector3 right, float dt) {
  Vector3 move = {0};
  if (IsKeyDown(KEY_W))
    move = Vector3Add(move, forward);
  if (IsKeyDown(KEY_S))
    move = Vector3Subtract(move, forward);
  if (IsKeyDown(KEY_A))
    move = Vector3Subtract(move, right);
  if (IsKeyDown(KEY_D))
    move = Vector3Add(move, right);

  if (Vector3Length(move) > 0) {
    move = Vector3Normalize(move);
    Vector3 newPos = player->position;
    newPos.x += move.x * player->speed * dt;
    newPos.z += move.z * player->speed * dt;

    // Check if new position is valid
    if (!CheckCityCollision(newPos, player->radius)) {
      player->position = newPos;
    } else {
      // Try sliding along X
      Vector3 testX = player->position;
      testX.x = newPos.x;
      if (!CheckCityCollision(testX, player->radius)) {
        player->position.x = newPos.x;
      } else {
        // Try sliding along Z
        Vector3 testZ = player->position;
        testZ.z = newPos.z;
        if (!CheckCityCollision(testZ, player->radius)) {
          player->position.z = newPos.z;
        }
      }
    }
  }
}

void DrawPlayer(Player player) {
  DrawSphere(player.position, 2.0f, player.color);
  DrawSphereWires(player.position, 2.0f, 8, 8, BLACK);
}
