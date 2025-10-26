void draw_texture_centered(Texture2D texture, Vector2 position, f32 rotation)
{
  Rectangle source = {0, 0, texture.width, texture.height};
  Rectangle destination = {position.x, position.y, texture.width, texture.height};
  Vector2 center = {texture.width / 2, texture.height / 2};
  Color tint = WHITE;

  DrawTexturePro(texture, source, destination, center, rotation, tint);
}

void draw_text(Font font, const char *text, Vector2 position, Color color)
{
  s32 font_size = 34, spacing = 1;
  DrawTextEx(font, text, (Vector2){position.x - (MeasureTextEx(font, text, font_size, spacing).x / 2.0), position.y}, font_size, spacing, color);
}

void draw_main_menu(Font font_title, Font font, f32 effect_timer)
{
  draw_text(font_title, TextToUpper(game_title), (Vector2){half_screen_width, half_screen_height - 150}, (Color){226, 232, 240, 255});

  draw_text(font, "Start", (Vector2){half_screen_width, half_screen_height}, menu_state == play && !effect_timer ? AQUA : WHITE);
  draw_text(font, "Controls", (Vector2){half_screen_width, half_screen_height + 40}, menu_state == controls && !effect_timer ? AQUA : WHITE);
  draw_text(font, "Exit", (Vector2){half_screen_width, half_screen_height + 40 * 2}, menu_state == exit && !effect_timer ? AQUA : WHITE);
}


void draw_score(Font font)
{
  switch(game_state)
  {
    case playing:
    case hit_stop:
    {
      draw_text(font, TextFormat("Score %d", score), (Vector2){280, 15}, WHITE);
    }
    break;
    case game_over:
    {
      draw_text(font, TextFormat("Score: %d", score), (Vector2){half_screen_width, half_screen_height - 50}, AQUA);
    }
    break;
    case main_menu:
    case controls_menu:
    case paused:
    break;
  }
}

void draw_highscore(Font font)
{
  draw_text(font, TextFormat("Highscore: %d", highscore), (Vector2){half_screen_width, half_screen_height - 100}, AQUA);
}

void draw_game_over_menu(Font font_title, Font font)
{
  draw_text(font_title, "GAME OVER", (Vector2){half_screen_width, half_screen_height - 150}, RED);
  draw_score(font);
  draw_highscore(font);
  draw_text(font, "Press Enter to play again", (Vector2){half_screen_width, half_screen_height}, WHITE);
}