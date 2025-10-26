Texture2D planet_texture;
Texture2D planet_gas_texture;
f32 gas_rotation = 0;

void init_planet()
{
  planet_texture     = LoadTexture("assets/planet.png");
  planet_gas_texture = LoadTexture("assets/planet_gas.png");
}

void update_planet(f32 dt)
{
  gas_rotation = Wrap(gas_rotation + dt, 0, 360);
}

void draw_planet()
{
  DrawTextureV(planet_texture, (Vector2){half_screen_width - 200, half_screen_height - 100}, WHITE);

  Vector2 position = {half_screen_width + 450, half_screen_height + 500};
  draw_texture_centered(planet_gas_texture, position, gas_rotation);
}