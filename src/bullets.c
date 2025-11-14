s32 bullet_radius = 10;
Texture2D bullet_texture;

#define BULLETS_COUNT 100
Thing bullets[BULLETS_COUNT] = {};
s32 next_bullet_index = 0;

Sound explosion_sfx;

void reset_bullet(s32 index)
{
  Thing *bullet = &bullets[index];
  bullet->position = (Vector2){-30, -30};
  bullet->velocity = (Vector2){0, 0};
  bullet->radius   = bullet_radius;
}

void reset_bullets()
{
  for(s32 i = 0; i < BULLETS_COUNT; i++)
  {
    reset_bullet(i);
  }
}

void init_bullets()
{
  explosion_sfx = LoadSound("assets/boom.wav");
  bullet_texture = LoadTexture("assets/bullet.png");
  reset_bullets();
}

void shoot_bullet(Vector2 position, f32 rotation)
{
  f32 radians = rotation * DEG2RAD;
  Vector2 direction = {sin(radians) * 500, -cos(radians) * 500};

  bullets[next_bullet_index] = (Thing){
    position,
    direction,
    rotation,
  };

  next_bullet_index = (next_bullet_index + 1) % (BULLETS_COUNT - 1);
}

bool is_out_of_bounds(Vector2 position);

void update_bullets(f32 dt, f32 slowmotion_factor)
{
  for(s32 i = 0; i < BULLETS_COUNT; i++)
  {
    bullets[i].position.x += bullets[i].velocity.x * dt * slowmotion_factor;
    bullets[i].position.y += bullets[i].velocity.y * dt * slowmotion_factor;

    if(is_out_of_bounds(bullets[i].position))
    {
      reset_bullet(i);
    }
  }
}

void update_score_meteor();

void bullets_check_collision_with_meteor(Vector2 meteor_center, Meteor* meteor)
{
  for(s32 i = 0; i < BULLETS_COUNT; i++)
  {
    // TODO: Meteor position is not center!
    if(CheckCollisionCircles(meteor_center, meteor->radius, bullets[i].position, bullet_radius))
    // if(things_collided(meteor, bullets[i]))
    {
      shake_camera();
      update_score_meteor();
      PlaySound(explosion_sfx);
      set_explosion_particles(meteor_center, meteor);
      spawn_meteor(meteor);
      reset_bullet(i);
    }
  }
}

void draw_bullets()
{
  for(s32 i = 0; i < BULLETS_COUNT; i++)
  {
    Thing bullet = bullets[i];
    draw_texture_centered(bullet_texture, bullet.position, bullet.rotation);
  }
}