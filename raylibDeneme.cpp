#include "raylib.h" // 4Life

int main(void)
{
    // Init
    const int screenWidth{800};
    const int screenHeight{450};

    const float speed{4.0f};

    int frameCounter{0};
    bool isPlayerDraw{true};

    InitWindow(screenWidth, screenHeight, "Game Dev Hello World Project");

    Vector2 ballPosition{ (float)screenWidth/2, 375 };
    const int playerRadius{50};

    SetTargetFPS(60); // Sets Max FPS

    // An enemy should spawn every two second and fall with gravity
    struct Enemy
    {
        const float gravity{4.0f};
        const int enemyRadius{20};

        bool isDraw{false};

        Vector2 enemyPosition;
        
        void draw()
        {
           if(isDraw) DrawCircleV(enemyPosition, enemyRadius, BLUE);
        }

        void fall()
        {
            enemyPosition.y += gravity;
        }

        void spawn()
        {  
            // Enemy radius is 20px and screenWidth is 800px so 800px-20px=780px is our max spawning point
            // Enemy only can spawn in a X coordinate between 0 and 720 because raylib starts counting from top left
            enemyPosition = { (float)GetRandomValue(20,780), 0 };
        }

    }; 
    // Struct END

    // Enemy Creation
    struct Enemy enemy1{};
    struct Enemy enemy2{};
    struct Enemy enemy3{};
    struct Enemy enemy4{};

    // Main Game Loop
    while(!WindowShouldClose())
    {
        // In this update section we want to update the screen/object before draw section.
        // Movement
        if(IsKeyDown(KEY_RIGHT) && isPlayerDraw) ballPosition.x += speed;
        if(IsKeyDown(KEY_LEFT) && isPlayerDraw) ballPosition.x -= speed;

        if(frameCounter == 120 && isPlayerDraw)
        { // Spawn enemy every two second, 1sec = 60 frames so 120 frames = 2sec 
            frameCounter = 0;

            enemy1.isDraw = true;
            enemy1.spawn();
        }
        else if(frameCounter == 90 && isPlayerDraw)
        {
            enemy2.isDraw = true;
            enemy2.spawn();
        }
        else if(frameCounter == 60 && isPlayerDraw)
        {
            enemy3.isDraw = true;
            enemy3.spawn();
        }
        else if(frameCounter == 30 && isPlayerDraw)
        {
            enemy4.isDraw = true;
            enemy4.spawn();
        }

        if(CheckCollisionCircles(ballPosition, playerRadius, enemy1.enemyPosition, enemy1.enemyRadius)) 
        { // Collision Check
            isPlayerDraw = false;
            enemy1.isDraw = false;
            enemy2.isDraw = false;
            enemy3.isDraw = false;
            enemy4.isDraw = false;
        }

        // We want the fall() command inside the while loop so it can be called in every game loop
        // Because adding a while inside struct freezes the code obiviously
        enemy1.fall();
        enemy2.fall();
        enemy3.fall();
        enemy4.fall();

        // In this draw section we want to redraw the screen for example after the move command.
        BeginDrawing();

            ClearBackground(RAYWHITE); // Sets background color

            DrawFPS(10, 10);
            DrawCircleV(ballPosition, playerRadius ,MAROON);

            // Enemy draws
            enemy1.draw();
            enemy2.draw();
            enemy3.draw();
            enemy4.draw();
           
            if(!isPlayerDraw) DrawText("GAME OVER", 300, 200, 30, RED);

            // This rect is the floor, position is 430 because thickness is 20 and screenHeight is 450 so basically 450px-20px=430px
            DrawRectangle(0, 430, screenWidth, 20, GREEN);

        EndDrawing();

        frameCounter += 1;

    }

    CloseWindow();

    return 0;
}

