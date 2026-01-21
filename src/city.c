#include "city.h"

typedef struct {
  Vector3 position;
  Vector3 size;
  Color color;
  Color wireColor;
  BoundingBox box;
} Building;

#define MAX_BUILDINGS 200
static Building buildings[MAX_BUILDINGS];
static int buildingCount = 0;

void InitCity(void) {
  buildingCount = 0;

  // District 1
  for (int i = 0; i < 30; i++) {
    if (buildingCount >= MAX_BUILDINGS)
      break;
    float h = (float)(100 + (i * 13) % 300);
    Vector3 pos = {(float)(50 + (i * 37) % 850), h / 2.0f,
                   (float)(50 + (i * 97) % (WORLD_SIZE - 100))};
    Vector3 size = {100, h, 100};
    buildings[buildingCount].position = pos;
    buildings[buildingCount].size = size;
    buildings[buildingCount].color = DARKGRAY;
    buildings[buildingCount].wireColor = BLACK;
    buildings[buildingCount].box = (BoundingBox){
        (Vector3){pos.x - size.x / 2, pos.y - size.y / 2, pos.z - size.z / 2},
        (Vector3){pos.x + size.x / 2, pos.y + size.y / 2, pos.z + size.z / 2}};
    buildingCount++;
  }

  // District 2
  for (int i = 0; i < 60; i++) {
    if (buildingCount >= MAX_BUILDINGS)
      break;
    float h = (float)(40 + (i * 7) % 80);
    Vector3 pos = {(float)(1050 + (i * 23) % 900), h / 2.0f,
                   (float)(50 + (i * 53) % (WORLD_SIZE - 100))};
    Vector3 size = {50, h, 50};
    buildings[buildingCount].position = pos;
    buildings[buildingCount].size = size;
    buildings[buildingCount].color = BROWN;
    buildings[buildingCount].wireColor = (Color){80, 40, 0, 255};
    buildings[buildingCount].box = (BoundingBox){
        (Vector3){pos.x - size.x / 2, pos.y - size.y / 2, pos.z - size.z / 2},
        (Vector3){pos.x + size.x / 2, pos.y + size.y / 2, pos.z + size.z / 2}};
    buildingCount++;
  }

  // District 3
  for (int i = 0; i < 40; i++) {
    if (buildingCount >= MAX_BUILDINGS)
      break;
    float h = (float)(200 + (i * 17) % 400);
    Vector3 pos = {(float)(2050 + (i * 31) % 900), h / 2.0f,
                   (float)(50 + (i * 67) % (WORLD_SIZE - 100))};
    Vector3 size = {80, h, 80};
    buildings[buildingCount].position = pos;
    buildings[buildingCount].size = size;
    buildings[buildingCount].color = DARKBLUE;
    buildings[buildingCount].wireColor = SKYBLUE;
    buildings[buildingCount].box = (BoundingBox){
        (Vector3){pos.x - size.x / 2, pos.y - size.y / 2, pos.z - size.z / 2},
        (Vector3){pos.x + size.x / 2, pos.y + size.y / 2, pos.z + size.z / 2}};
    buildingCount++;
  }
}

void DrawCity3D(Vector3 center, float drawDistance) {
  DrawPlane((Vector3){500, 0, WORLD_SIZE / 2.0f}, (Vector2){1000, WORLD_SIZE},
            (Color){200, 200, 255, 255});
  DrawPlane((Vector3){1500, 0, WORLD_SIZE / 2.0f}, (Vector2){1000, WORLD_SIZE},
            (Color){255, 220, 150, 255});
  DrawPlane((Vector3){2500, 0, WORLD_SIZE / 2.0f}, (Vector2){1000, WORLD_SIZE},
            (Color){20, 20, 80, 255});

  for (int i = 0; i < buildingCount; i++) {
    float dist = Vector3Distance(center, buildings[i].position);
    if (dist <= drawDistance) {
      DrawCube(buildings[i].position, buildings[i].size.x, buildings[i].size.y,
               buildings[i].size.z, buildings[i].color);
      DrawCubeWires(buildings[i].position, buildings[i].size.x,
                    buildings[i].size.y, buildings[i].size.z,
                    buildings[i].wireColor);
    }
  }
}

bool CheckCityCollision(Vector3 center, float radius) {
  for (int i = 0; i < buildingCount; i++) {
    if (CheckCollisionBoxSphere(buildings[i].box, center, radius)) {
      return true;
    }
  }
  return false;
}
