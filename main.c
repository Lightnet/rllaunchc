/*******************************************************************************************
*
*   raylib [core] example - Basic 3d example
*
*   Welcome to raylib!
*
*   To compile example, just press F5.
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2020 Ramon Santamaria (@raysan5)
*
********************************************************************************************/
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "./externals/raygui/raygui.h"


#include <stdio.h>                  // Required for: fopen(), fclose(), fputc(), fwrite(), printf(), fprintf(), funopen()
#include <time.h>                   // Required for: time_t, tm, time(), localtime(), strftime()

// Custom logging funtion
void LogCustom(int msgType, const char *text, va_list args)
{
    char timeStr[64] = { 0 };
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("[%s] ", timeStr);

    switch (msgType)
    {
        case LOG_INFO: printf("[INFO] : "); break;
        case LOG_ERROR: printf("[ERROR]: "); break;
        case LOG_WARNING: printf("[WARN] : "); break;
        case LOG_DEBUG: printf("[DEBUG]: "); break;
        default: break;
    }

    vprintf(text, args);
    printf("\n");
}

char textBoxTextAlias[128] = "Text box";
char textBoxTextPass[128] = "Text box";
bool textBoxAliasEditMode = false;
bool textBoxPassEditMode = false;


void drawlogin(){
    DrawText(TextFormat("Alias:"), 660, 200, 10, DARKGRAY);

    if (GuiTextBox((Rectangle){ 610, 220, 165, 30 }, textBoxTextAlias, 128, textBoxAliasEditMode)) textBoxAliasEditMode = !textBoxAliasEditMode;

    DrawText(TextFormat("Password:"), 660, 260, 10, DARKGRAY);

    if (GuiTextBox((Rectangle){ 610, 280, 165, 30 }, textBoxTextPass, 128, textBoxPassEditMode)) textBoxPassEditMode = !textBoxPassEditMode;

    if (GuiButton((Rectangle){ 650, 320, 115, 30 }, "Login")) { 
        printf("BUTTON EVENT  ///////////////\n");
    }
}


void updatetask(){
    printf("hello world");
}


int main() 
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    // First thing we do is setting our custom logger to ensure everything raylib logs
    // will use our own logger instead of its internal one
    SetTraceLogCallback(LogCustom);
    //SetTraceLog(LOG_INFO | LOG_WARNING); 
    //SetTraceLogLevel(LOG_NONE);

    TraceLog(LOG_DEBUG,"test//////////////////\n",0);

    SetConfigFlags(FLAG_WINDOW_UNDECORATED);

    printf("INIT WINDOW//////////////////////////////////////////////\n");

    InitWindow(screenWidth, screenHeight, "raylib");

    // General variables
    Vector2 mousePosition = { 0 };
    Vector2 windowPosition = { 500, 200 };
    Vector2 panOffset = mousePosition;
    bool dragWindow = false;

    SetWindowPosition(windowPosition.x, windowPosition.y);

    bool exitWindow = false;
    float progressValue = 0.5f;



    /*
    Camera camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 8.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.type = CAMERA_PERSPECTIVE;
    
    SetCameraMode(camera, CAMERA_ORBITAL);
    */
    //Vector3 cubePosition = { 0 };

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    //while (!WindowShouldClose())    // Detect window close button or ESC key
    while (!exitWindow && !WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        //UpdateCamera(&camera);
        mousePosition = GetMousePosition();
         if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mousePosition, (Rectangle){ 0, 0, screenWidth, 20 }))
            {
                dragWindow = true;
                panOffset = mousePosition;
                printf("GET MOUSE/////////////////////////\n");
            }
        }

        if (dragWindow)
        {            
            windowPosition.x += (mousePosition.x - panOffset.x);
            windowPosition.y += (mousePosition.y - panOffset.y);
            
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) dragWindow = false;

            SetWindowPosition(windowPosition.x, windowPosition.y);
            printf("MOSUE DRAG/////////////////////\n");
        }
        //----------------------------------------------------------------------------------
        updatetask();
        // Draw
        //----------------------------------------------------------------------------------
        progressValue=progressValue +0.001f;
        if(progressValue >= 1.0f){
            progressValue=0.0f;
        }
        //printf("progress value= %I",progressValue);
        //printf("progress value");


        BeginDrawing();

            ClearBackground(RAYWHITE);
            /*
            BeginMode3D(camera);

                DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
                DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
                DrawGrid(10, 1.0f);

            EndMode3D();
            */
            //DrawText("This is a raylib example", 10, 40, 20, DARKGRAY);

            exitWindow = GuiWindowBox((Rectangle){ 0, 0, screenWidth, screenHeight }, "#198# PORTABLE WINDOW");

            DrawText(TextFormat("progressValue: [ %.00f ]", progressValue), 10, 60, 10, DARKGRAY);

            DrawText(TextFormat("Mouse Position: [ %.0f, %.0f ]", mousePosition.x, mousePosition.y), 10, 40, 10, DARKGRAY);

            //progress bar
            //progressValue = GuiProgressBar((Rectangle){ 32, 380, 500, 20 }, NULL, NULL, progressValue, 0.0f, 100.0f);
            //progressValue = GuiProgressBar((Rectangle){ 32, 380, 500, 20 }, "begin", "end", progressValue, 0, 1);
            progressValue = GuiProgressBar((Rectangle){ 32, 380, 500, 20 }, NULL, NULL, progressValue, 0, 1);
            
            DrawText(TextFormat("Status:Pending..."), 32, 360, 10, DARKGRAY);

            DrawText(TextFormat("Status:Pending..."), 32, 410, 10, DARKGRAY);


            if (GuiButton((Rectangle){ 550, 380, 115, 30 }, "PLAY")) { 
                //exitWindow=true;
            }

            GuiSetStyle(RICON_TOOLS, TEXT_ALIGNMENT, GUI_TEXT_ALIGN_CENTER);
            if (GuiButton((Rectangle){ 700, 380, 80, 30 }, "#140#Options")) { 
                //exitWindow=true;
            }

            drawlogin();
            //DrawFPS(10, 20);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
