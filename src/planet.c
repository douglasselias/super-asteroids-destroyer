Thing planet;
Thing planet_gas;

void init_planet()
{
  planet.texture     = LoadTexture("assets/planet.png");
  planet_gas.texture = LoadTexture("assets/planet_gas.png");

  planet.position     = (Vector2){half_screen_width - 200, half_screen_height - 100};
  planet_gas.position = (Vector2){half_screen_width + 450, half_screen_height + 500};

  planet.texture_color     = WHITE;
  planet_gas.texture_color = WHITE;
}

void update_planet(f32 dt)
{
  planet_gas.rotation = Wrap(planet_gas.rotation + dt, 0, 360);
}

void draw_planet()
{
  DrawTextureV(planet.texture, planet.position, planet.texture_color);
  draw_texture_centered(planet_gas.texture, planet_gas.position, planet_gas.rotation);
}