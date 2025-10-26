#define STARS_COUNT 100
Thing stars[STARS_COUNT] = {};

void init_stars()
{
  for (s32 i = 0; i < STARS_COUNT; i++)
  {
    stars[i].position = (Vector2){
      GetRandomValue(-1000, screen_width  + 1000),
      GetRandomValue(-1000, screen_height + 1000),
    };
    stars[i].radius = GetRandomValue(1, 3);
  }
}

void update_stars()
{
  for (s32 i = 0; i < STARS_COUNT; i++)
  {
    stars[i].position.x = Wrap(++stars[i].position.x, 0, screen_width);
    stars[i].position.y = Wrap(++stars[i].position.y, 0, screen_height);
  }
}

void draw_stars()
{
  for (s32 i = 0; i < STARS_COUNT; i++)
  {
    DrawCircleV(stars[i].position, stars[i].radius, GRAY);
  }
}