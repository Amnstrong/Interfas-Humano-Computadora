#include "raylib.h"
#include <math.h>

int main()
{
    InitWindow(1000, 700, "Transformaciones Matemáticas - Raylib");

    SetTargetFPS(60);

    // Traslación
    float xTras = 50;

    // Rotación
    float angulo = 0;

    // Rebote
    float xRebote = 100;
    float velocidad = 5;

    // Movimiento senoidal
    float tiempo = 0;

    // Trayectoria
    float xTray = 0;

    // Órbita
    float anguloOrbita = 0;

    while (!WindowShouldClose())
    {

        // Traslación
        xTras += 2;

        if (xTras > 1000)
            xTras = -50;

        // Rotación
        angulo += 2;

        // Rebote
        xRebote += velocidad;

        if (xRebote >= 950 || xRebote <= 0)
        {
            velocidad *= -1;
        }

        // Movimiento senoidal
        tiempo += 0.05f;

        // Trayectoria parabólica
        xTray += 2;

        if (xTray > 1000)
            xTray = 0;

        // Órbita
        anguloOrbita += 0.02f;

        BeginDrawing();

        ClearBackground(BLACK);

        // 1. TRASLACIÓN
        DrawText("Traslacion", 50, 20, 20, WHITE);
        DrawRectangle(xTras, 60, 80, 50, RED);

        // 2. ROTACIÓN
        DrawText("Rotacion", 250, 20, 20, WHITE);

        Rectangle rect = {300, 100, 100, 50};

        DrawRectanglePro(
            rect,
            (Vector2){50, 25},
            angulo,
            BLUE
        );

        // 3. REBOTE
        DrawText("Rebote", 500, 20, 20, WHITE);

        DrawCircle(xRebote, 100, 25, GREEN);

        // 4. MOVIMIENTO SENOIDAL
        DrawText("Movimiento Senoidal", 50, 200, 20, WHITE);

        float ySeno = 250 + sin(tiempo * 2) * 50;

        DrawCircle(200, ySeno, 20, YELLOW);

        // 5. TRAYECTORIA PARABÓLICA
        DrawText("Trayectoria", 400, 200, 20, WHITE);

        float yTray = 0.01f * pow(xTray - 500, 2) + 250;

        DrawCircle(xTray, yTray, 15, ORANGE);

        // 6. ÓRBITA
        DrawText("Orbita", 700, 200, 20, WHITE);

        int centroX = 800;
        int centroY = 350;
        int radio = 100;

        float xOrbita = centroX + cos(anguloOrbita) * radio;
        float yOrbita = centroY + sin(anguloOrbita) * radio;

        DrawCircle(centroX, centroY, 20, WHITE);

        DrawCircle(xOrbita, yOrbita, 15, PURPLE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}