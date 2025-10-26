#pragma comment(lib, "user32")
#pragma comment(lib, "shell32")
#pragma comment(lib, "gdi32")
#pragma comment(lib, "winmm")
#pragma comment(lib, "opengl32")

#include "vendor/raylib.h"
#include "vendor/raymath.h"

#include "vendor/stb_perlin.h"

#include "src/constants.c"

typedef struct
{
  Vector2 position;
  Vector2 velocity;
  f32 rotation;
  f32 radius;
} Thing;

typedef enum
{
  main_menu,
  controls_menu,
  playing,
  paused,
  hit_stop,
  game_over,
} Game_State;

typedef enum
{
  play,
  controls,
  exit,
} Menu_State;

Game_State game_state = main_menu;
Menu_State menu_state = play;

#include "src/score.c"
#include "src/ui.c"
#include "src/camera.c"
#include "src/stars.c"
#include "src/meteors.c"
#include "src/planet.c"
#include "src/bullets.c"
#include "src/ship.c"
#include "src/controls_menu.c"
#include "src/music.c"

bool is_out_of_bounds(Vector2 position)
{
  f32 despawn_offset = 500;
  f32 top_despawn_zone    = -despawn_offset;
  f32 left_despawn_zone   = -despawn_offset;
  f32 right_despawn_zone  =  despawn_offset + screen_width;
  f32 bottom_despawn_zone =  despawn_offset + screen_height;

  if(position.y < top_despawn_zone
  || position.x > right_despawn_zone
  || position.y > bottom_despawn_zone
  || position.x < left_despawn_zone)
  {
    return true;
  }

  return false;
}

s32 main()
{
  SetTraceLogLevel(LOG_WARNING);
  InitWindow(screen_width, screen_height, game_title);
  SetTargetFPS(120);
  InitAudioDevice();

  ChangeDirectory("..");

  Font font       = LoadFontEx("assets/kenney_pixel.ttf",    34, 0, 250);
  Font font_title = LoadFontEx("assets/not_jam_slab_14.ttf", 34, 0, 250);
  SetTextLineSpacing(34);

  Sound hurt_sfx    = LoadSound("assets/hurt.wav");
  Sound click_sfx   = LoadSound("assets/click.wav");
  Sound select_sfx  = LoadSound("assets/select.wav");
  Sound booster_sfx = LoadSound("assets/booster.ogg");

  f32 select_effect_timer = 0;
  f32 select_effect_total_time = 0.6f;

  init_music();
  init_controls_menu();
  init_camera();
  init_stars();
  init_meteors();
  init_planet();
  init_bullets();
  init_ship();

  f32 slowmotion_timer = 0;
  load_highscore();

  while (!WindowShouldClose())
  {
    f32 dt = GetFrameTime();

    bool is_slowmotion = slowmotion_timer > 0;
    f32 slowmotion_factor = is_slowmotion ? 0.05 : 1;

    switch(game_state)
    {
      case main_menu:
      {
        if (IsKeyPressed(KEY_W) && select_effect_timer == 0)
        {
          PlaySound(click_sfx);
          
          if(--menu_state == -1)
          {
            menu_state = 2;
          }
        }

        if (IsKeyPressed(KEY_S) && select_effect_timer == 0)
        {
          PlaySound(click_sfx);
          
          if(++menu_state == 3)
          {
            menu_state = 0;
          }
        }

        if (IsKeyPressed(KEY_ENTER))
        {
          PlaySound(select_sfx);
          select_effect_timer = select_effect_total_time;

          if (menu_state == play)
          {
            fade_to_main_bgm_music();
          }
        }
      }
      break;
      case controls_menu:
      {
        if (IsKeyPressed(KEY_ENTER))
        {
          PlaySound(select_sfx);
          select_effect_timer = select_effect_total_time;
        }
      }
      break;
      case playing:
      {
        if (IsKeyDown(KEY_A))
        {
          ship.rotation -= rotation_speed * dt * slowmotion_factor;
        }

        if (IsKeyDown(KEY_D))
        {
          ship.rotation += rotation_speed * dt * slowmotion_factor;
        }

        if (IsKeyDown(KEY_W))
        {
          accelerate_ship(dt, slowmotion_factor);
          score += VELOCITY_POINTS;

          if(!IsSoundPlaying(booster_sfx))
          {
            PlaySound(booster_sfx);
          }
        }
        else
        {
          StopSound(booster_sfx);
        }

        if(IsKeyPressed(KEY_SPACE))
        {
          shoot_bullet(ship.position, ship.rotation);
        }

        if (IsKeyPressed(KEY_ENTER))
        {
          game_state = paused;
          PauseMusicStream(main_bgm);
        }
      }
      break;
      case paused:
      {
        if (IsKeyPressed(KEY_ENTER))
        {
          game_state = playing;
          PlayMusicStream(main_bgm);
        }
      }
      break;
      case hit_stop:
      {

      }
      break;
      case game_over:
      {
        if (IsKeyPressed(KEY_ENTER))
        {
          PlaySound(select_sfx);
          game_state = playing;
          score = 0;
          reset_meteors();
          reset_bullets();
          reset_ship();
          PlayMusicStream(main_bgm);
        }
      }
      break;
    }

    update_music(dt);

    if (select_effect_timer > 0)
    {
      select_effect_timer -= dt;
      
      if (select_effect_timer < 0)
      {
        select_effect_timer = 0;
        switch(game_state) {
          case playing:
          case paused:
          case hit_stop:
          case game_over: break;
          case controls_menu:
          {
            game_state = main_menu;
          }
          break;
          case main_menu:
          {
            switch(menu_state)
            {
              case play:
              {
                game_state = playing;
              }
              break;
              case controls:
              {
                game_state = controls_menu;
              }
              break;
              case exit:
              {
                CloseWindow();
              }
              break;
            }
          }
          break;
        }
      }
    }
    
    if(is_slowmotion)
    {
      slowmotion_timer -= dt;
    }
    
    if(!is_slowmotion && game_state == hit_stop)
    {
      game_state = game_over;

      if(score > highscore)
      {
        highscore = score;
        save_highscore();
      }
    }

    update_camera(dt);
    update_stars();
    update_planet(dt);

    if(game_state == playing)
    {
      update_ship(dt, slowmotion_factor);
      update_bullets(dt, slowmotion_factor);

      for(s32 i = 0; i < METEORS_COUNT; i++)
      {
        meteors[i].position.x += meteors[i].velocity.x * dt * slowmotion_factor;
        meteors[i].position.y += meteors[i].velocity.y * dt * slowmotion_factor;

        update_explosion_particles(&meteors[i], dt, is_slowmotion, slowmotion_factor);

        if(is_out_of_bounds(meteors[i].position))
        {
          spawn_meteor(&meteors[i]);
        }

        Vector2 meteor_center = {meteors[i].position.x + meteors[i].texture.width / 2.0, meteors[i].position.y + meteors[i].texture.height / 2.0};
        if(CheckCollisionCircles(meteor_center, meteors[i].radius, ship.position, ship.radius))
        {
          PlaySound(hurt_sfx);
          set_explosion_particles(meteor_center, &meteors[i]);
          spawn_meteor(&meteors[i]);

          if(--energy == 0)
          {
            game_state = hit_stop;
            StopMusicStream(main_bgm);
            PlaySound(lose_sfx);
          }

          slowmotion_timer = 1;
          update_score_meteor();
          shake_camera();
        }

        bullets_check_collision_with_meteor(meteor_center, &meteors[i]);
      }
    }

    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(camera);

    draw_stars();
    draw_planet();

    if (game_state == playing || game_state == hit_stop)
    {
      draw_meteors();
      draw_bullets();
      draw_ship();
      draw_energy();
    }

    draw_score(font);

    EndMode2D();

    bool effect_timer = 0.1 < select_effect_timer && 0.5 < select_effect_timer;

    switch(game_state)
    {
      case main_menu:
      {
        draw_main_menu(font_title, font, effect_timer);
      }
      break;
      case controls_menu:
      {
        draw_controls_menu(font, effect_timer);
      }
      break;
      case game_over:
      {
        draw_game_over_menu(font_title, font);
      }
      break;
      case paused:
      {
        draw_text(font_title, "PAUSED", (Vector2){half_screen_width, half_screen_height}, WHITE);
      }
      break;
      case playing:
      case hit_stop: break;
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}