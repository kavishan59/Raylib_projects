#include "raylib.h"

#define WIDTH 1280
#define HEIGHT 720

Color Green = Color{38,185,154,255};
Color Dark_Green = Color{20,160,133,255};
Color Light_Green = Color{129,204,184,255};
Color Yellow = Color{243,213,91,255};

int player_score = 0;
int cpu_score = 0;

class Ball{
public:
  float x,y;
  int speed_x,speed_y;
  int radius;

  void Draw(){
    DrawCircle(x, y, radius, Yellow);
  }

  void Update() {
   x += speed_x;
   y += speed_y;
    
    //collision with top/bottom window
    if((y + radius) >= GetScreenHeight() || (y - radius) <= 0)
      speed_y *= -1;

    //collision with left/right window
    //cpu wins
    if(x + radius >= GetScreenWidth())
    {
      cpu_score++;
      ResetBall();
    }
    //player wins
    if(x - radius <= 0)
    {
      player_score++;
      ResetBall();
    }
  }
  
  void ResetBall()
  {
    x = (float)GetScreenWidth()/2;
    y = (float)GetScreenHeight()/2;
    int speed_choices[2] = {-1,1};
    speed_x *= speed_choices[GetRandomValue(0, 1)];
    speed_y *= speed_choices[GetRandomValue(0, 1)];
  }

};


class Paddle {

protected:
  void LimitMovement(){
    if (y <= 0)
      y = 0;
    if (y + height >= GetScreenHeight())
      y = GetScreenHeight() - height;

  }
  
public:
  float x,y;
  float width,height;
  int speed;
  
  void Draw(){
   DrawRectangleRounded(Rectangle{x,y,width,height}, 0.8, 0, WHITE);
  }

  void Update(){
    if (IsKeyDown(KEY_UP))
      y -= speed;
    if (IsKeyDown(KEY_DOWN))
      y += speed;

    //check collison with wall
    LimitMovement();
  }
};


class CpuPaddle: public Paddle {
  public :

  void Update(int ball_y){
   //basic ai 
    if (y + height/2 > ball_y)
      y -= speed;
    if (y + height/2 < ball_y)
      y += speed;
   
    //check colission with wall
    LimitMovement();
  } 
};

int main()
{
  Ball ball;
  Paddle player;
  CpuPaddle cpu;

  //init
  ball.radius = 20;
  ball.x = (float)WIDTH / 2;
  ball.y = (float)HEIGHT / 2;
  ball.speed_x = 7;
  ball.speed_y = 7;

  player.width = 25;
  player.height = 120;
  player.x = 10;
  player.y = (float)HEIGHT/2 - player.height/2;
  player.speed = 6;

  cpu.height = 120;
  cpu.width = 25;
  cpu.x = WIDTH - cpu.width - 10;
  cpu.y = (float)HEIGHT / 2;
  cpu.speed = 6;

  InitWindow(WIDTH, HEIGHT, "Pong");
  SetTargetFPS(60);

  while(WindowShouldClose() == false)
  {
    BeginDrawing();
  
    //update positions
    ball.Update();
    player.Update();
    cpu.Update(ball.y);

    //check for collisions
    if (CheckCollisionCircleRec(Vector2{ball.x,ball.y}, ball.radius, Rectangle{player.x,player.y,player.width,player.height}))
      ball.speed_x *= -1;
  
    if (CheckCollisionCircleRec(Vector2{ball.x,ball.y}, ball.radius, Rectangle{cpu.x,cpu.y,cpu.width,cpu.height}))
      ball.speed_x *= -1;
    
    ClearBackground(Dark_Green);
    DrawRectangle(0, 0, WIDTH/2, HEIGHT, Green);
    DrawCircle(WIDTH/2, HEIGHT/2, 150, Light_Green);
    DrawLine(WIDTH/2, 0, WIDTH/2, HEIGHT, WHITE);
    ball.Draw();
    player.Draw();
    cpu.Draw();
    DrawText(TextFormat("%i",cpu_score), WIDTH /4 - 20, 20, 80, WHITE);
    DrawText(TextFormat("%i",player_score), 3 * WIDTH /4 - 20, 20, 80, WHITE);

    EndDrawing();

  }

  CloseWindow();
  return 0;
}
