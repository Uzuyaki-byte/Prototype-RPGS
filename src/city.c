#include "city.h"

void DrawCity3D(void) {
    DrawPlane((Vector3){ 500, 0, WORLD_SIZE/2.0f }, (Vector2){ 1000, WORLD_SIZE }, (Color){ 200, 200, 255, 255 });
    for (int i = 0; i < 30; i++) {
        float h = (float)(100 + (i * 13) % 300);
        Vector3 pos = { (float)(50 + (i * 37) % 850), h/2.0f, (float)(50 + (i * 97) % (WORLD_SIZE - 100)) };
        DrawCube(pos, 100, h, 100, DARKGRAY);
        DrawCubeWires(pos, 100, h, 100, BLACK);
    }

    DrawPlane((Vector3){ 1500, 0, WORLD_SIZE/2.0f }, (Vector2){ 1000, WORLD_SIZE }, (Color){ 255, 220, 150, 255 });
    for (int i = 0; i < 60; i++) {
        float h = (float)(40 + (i * 7) % 80);
        Vector3 pos = { (float)(1050 + (i * 23) % 900), h/2.0f, (float)(50 + (i * 53) % (WORLD_SIZE - 100)) };
        DrawCube(pos, 50, h, 50, BROWN);
        DrawCubeWires(pos, 50, h, 50, (Color){ 80, 40, 0, 255 });
    }

    DrawPlane((Vector3){ 2500, 0, WORLD_SIZE/2.0f }, (Vector2){ 1000, WORLD_SIZE }, (Color){ 20, 20, 80, 255 });
    for (int i = 0; i < 40; i++) {
        float h = (float)(200 + (i * 17) % 400);
        Vector3 pos = { (float)(2050 + (i * 31) % 900), h/2.0f, (float)(50 + (i * 67) % (WORLD_SIZE - 100)) };
        DrawCube(pos, 80, h, 80, DARKBLUE);
        DrawCubeWires(pos, 80, h, 80, SKYBLUE);
    }
}
