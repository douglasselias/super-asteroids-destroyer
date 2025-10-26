Camera2D camera = {};
f32 current_shake_strength = 0;
f32 noise_time_acc = 0;

f32 shake_strength   = 60 * 0.4;
f32 shake_decay_rate = 3;
f32 shake_speed      = 30;

f32 noise_2d(f32 x, f32 y);

void init_camera()
{
  camera.target = screen_center;
  camera.zoom   = 1;
}

void update_camera(f32 dt)
{
  current_shake_strength = Lerp(current_shake_strength, 0, shake_decay_rate * dt);
  noise_time_acc += shake_speed * dt;
  camera.offset.x = screen_center.x + noise_2d(1,   noise_time_acc) * current_shake_strength;
  camera.offset.y = screen_center.y + noise_2d(100, noise_time_acc) * current_shake_strength;
}

void shake_camera()
{
  current_shake_strength = shake_strength;
}

f32 noise_2d(f32 x, f32 y)
{
  f32 z = 0, lacunarity = 2, gain = 0.5, octaves = 3;
  return stb_perlin_fbm_noise3(x, y, z, lacunarity, gain, octaves);
}