#define EXPLOSION_PARTICLES_COUNT 360
typedef struct
{
  Vector2 position;
  Vector2 velocity;
  s32 radius;
  Texture2D texture;
  f32 particles_timer;
  Thing explosion_particles[EXPLOSION_PARTICLES_COUNT];
} Meteor;

void spawn_meteor(Meteor *meteor);

#define METEOR_TEXTURES_COUNT 4
Texture2D meteors_textures[METEOR_TEXTURES_COUNT] = {};

#define METEORS_COUNT 20
Meteor meteors[METEORS_COUNT] = {};

void init_meteors()
{
  for(u32 i = 0; i < METEOR_TEXTURES_COUNT; i++)
  {
    meteors_textures[i] = LoadTexture(TextFormat("assets/meteor%d.png", i));
  }

  for(u32 i = 0; i < METEORS_COUNT; i++)
  {
    spawn_meteor(&meteors[i]);
  }
}

f32 explosion_particle_total_timeout = 1;
void set_explosion_particles(Vector2 meteor_center, Meteor* meteor)
{
  meteor->particles_timer = explosion_particle_total_timeout;

  for(s32 i = 0; i < EXPLOSION_PARTICLES_COUNT; i++)
  {
    f32 radians = i * DEG2RAD;
    meteor->explosion_particles[i] = (Thing){
      meteor_center,
      (Vector2){cos(radians) * GetRandomValue(50, 150), -sin(radians) * GetRandomValue(50, 150)},
    };
  }
}

void update_explosion_particles(Meteor *meteor, f32 dt, bool is_slowmotion, f32 slowmotion_factor)
{
  if(meteor->particles_timer > 0)
  {
    meteor->particles_timer -= dt * slowmotion_factor;
  }
  else
  {
    meteor->particles_timer = -1;
  }
  
  for(s32 i = 0; i < EXPLOSION_PARTICLES_COUNT; i++)
  {
    if(meteor->particles_timer > 0)
    {
      meteor->explosion_particles[i].position.x += meteor->explosion_particles[i].velocity.x * dt * slowmotion_factor;
      meteor->explosion_particles[i].position.y += meteor->explosion_particles[i].velocity.y * dt * slowmotion_factor;
    }
    else
    {
      meteor->explosion_particles[i].position = (Vector2){-1000, -1000};
      meteor->explosion_particles[i].velocity = (Vector2){0, 0};
    }
  }
}

void reset_meteors()
{
  for(s32 i = 0; i < METEORS_COUNT; i++)
  {
    spawn_meteor(&meteors[i]);
    meteors[i].particles_timer = -1;
    
    for(s32 j = 0; j < EXPLOSION_PARTICLES_COUNT; j++)
    {
      meteors[i].explosion_particles[j].position = (Vector2){-1000, -1000};
      meteors[i].explosion_particles[j].velocity = (Vector2){0, 0};
    }
  }
}

void draw_meteors()
{
  for(s32 i = 0; i < METEORS_COUNT; i++)
  {
    DrawTextureV(meteors[i].texture, meteors[i].position, WHITE);
    
    for(s32 j = 0; j < EXPLOSION_PARTICLES_COUNT; j++)
    {
      f32 timeout = meteors[i].particles_timer;
      
      if(timeout > 0)
      {
        f32 fade_percent = timeout / explosion_particle_total_timeout;
        DrawCircleV(meteors[i].explosion_particles[j].position, 1, (Color){255, 255, 255, 255 * fade_percent});
      }
    }
  }
}

void spawn_meteor(Meteor *meteor)
{
  // NOTE: Padding to keep the location inside the screen boundaries.
  s32 spawn_padding = 30;
  // NOTE: Offset to keep the location outside the screen boundaries.
  s32 spawn_offset = 30;

  Vector2 meteor_spawn_locations[12] =
  {
    // Top
    {spawn_padding,                -spawn_offset},
    {half_screen_width,            -spawn_offset},
    {screen_width - spawn_padding, -spawn_offset},
    
    // Right
    {screen_width + spawn_offset, spawn_padding},
    {screen_width + spawn_offset, half_screen_height},
    {screen_width + spawn_offset, screen_height - spawn_padding},
    
    // Bottom
    {spawn_padding,                screen_height + spawn_offset},
    {half_screen_width,            screen_height + spawn_offset},
    {screen_width - spawn_padding, screen_height + spawn_offset},
    
    // Left
    {-spawn_offset, spawn_padding},
    {-spawn_offset, half_screen_height},
    {-spawn_offset, screen_height - spawn_padding},
  };

  meteor->radius = 45;
  s32 location_index = GetRandomValue(0, 11);
  meteor->position = meteor_spawn_locations[location_index];

  f32 angle = 0;
  switch(location_index)
  {
    // NOTE: This logic follows the spawn locations order.
    // The hex numbers are here to just keep the code aligned :)

    // Top
    case 0x0: angle = GetRandomValue(270, 270 + 60); break;
    case 0x1: angle = GetRandomValue(190, 350);      break;
    case 0x2: angle = GetRandomValue(270 - 60, 270); break;

    // Right:
    case 0x3: angle = GetRandomValue(180, 180 + 60); break;
    case 0x4: angle = GetRandomValue(100, 170);      break;
    case 0x5: angle = GetRandomValue(180 - 60, 180); break;

    // Bottom:
    case 0x6: angle = GetRandomValue(90 - 60, 90);  break;
    case 0x7: angle = GetRandomValue(10, 170);      break;
    case 0x8: angle = GetRandomValue(90, 90  + 60); break;

    // Left:
    case 0x9: angle = GetRandomValue(360 - 60, 360);  break;
    case 0xa: angle = GetRandomValue(280, 270 + 160); break;
    case 0xb: angle = GetRandomValue(0, 60);          break;
  }

  angle *= DEG2RAD;
  s32 speed = GetRandomValue(50, 250);
  
  meteor->velocity = (Vector2){
    cos(angle)  * speed,
    -sin(angle) * speed,
  };

  meteor->texture = meteors_textures[GetRandomValue(0, 3)];
}