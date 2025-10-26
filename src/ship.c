Texture2D ship_texture;
Vector2 ship_acceleration = {300, 300};
s32 rotation_speed = 500;
Texture2D fire_texture;

Thing ship = {};

s32 energy = 3;
Sound lose_sfx;

bool is_fire_visible = false;

void init_ship()
{
  lose_sfx = LoadSound("assets/lose.wav");
  fire_texture = LoadTexture("assets/fire.png");
  ship_texture = LoadTexture("assets/ship.png");
  ship.position = screen_center;
  ship.radius = 10;
}

void accelerate_ship(f32 dt, f32 slowmotion_factor)
{
  f32 radians = ship.rotation * DEG2RAD;
  Vector2 direction = {sin(radians), -cos(radians)};
  is_fire_visible = true;

  ship.velocity.x += direction.x * ship_acceleration.x * dt * slowmotion_factor;
  ship.velocity.y += direction.y * ship_acceleration.y * dt * slowmotion_factor;
}

void update_ship(f32 dt, f32 slowmotion_factor)
{
  ship.position.x += ship.velocity.x * dt * slowmotion_factor;
  ship.position.y += ship.velocity.y * dt * slowmotion_factor;
  ship.position.x = Wrap(ship.position.x, 0, screen_width);
  ship.position.y = Wrap(ship.position.y, 0, screen_height);
}

void reset_ship()
{
  ship.position = screen_center;
  ship.velocity = (Vector2){0, 0};
  ship.rotation = 0;
  energy = 3;
}

void draw_ship()
{
  if(is_fire_visible)
  {
    DrawTexturePro(fire_texture,
      (Rectangle){0, 0, fire_texture.width, fire_texture.height},
      (Rectangle){ship.position.x, ship.position.y, fire_texture.width, fire_texture.height},
      (Vector2){fire_texture.width / 2.0, 0},
      ship.rotation, WHITE);
    is_fire_visible = false;
  }

  draw_texture_centered(ship_texture, ship.position, ship.rotation);
}

void draw_energy()
{
  Color SEA_GREEN = {60, 179, 113, 255};
  Color ORANGE_RED = {255, 69, 0, 255};
  s32 x = 20, y = 10;
  s32 width = 140, height = 40;
  s32 width_gap = 4, height_gap = 5;
  s32 thickness = 5;
  
  Color color = ORANGE_RED;
  switch(energy)
  {
    case 3: color = SEA_GREEN; break;
    case 2: color = ORANGE;    break;
  }
  
  f32 energy_block_size = (width - thickness * 2 - width_gap * 4) / 3.0;
  DrawRectangleLinesEx((Rectangle){x, y, width, height}, thickness, color);
  
  for(s32 i = 0; i < energy; i++)
  {
    DrawRectangleRec((Rectangle){
        x + thickness + width_gap * (i + 1) + energy_block_size * i,
        y + thickness + height_gap,
        energy_block_size,
        height - thickness * 2 - height_gap * 2,
      }, color);
  }
}