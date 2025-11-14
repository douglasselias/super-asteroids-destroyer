Thing main_bgm;
Thing menu_bgm;
Thing music_fade;

void play_thing(Thing thing)
{
  PlayMusicStream(thing.music);
}

void init_music()
{
  main_bgm.music = LoadMusicStream("assets/stargaze.ogg");
  menu_bgm.music = LoadMusicStream("assets/crazy_space.ogg");
  PlayMusicStream(menu_bgm.music);
  music_fade.total_time = 2;
}

void update_music(f32 dt)
{
  UpdateMusicStream(menu_bgm.music);
  UpdateMusicStream(main_bgm.music);

  if (music_fade.timer > 0)
  {
    music_fade.timer -= dt;
    f32 percent = music_fade.timer / music_fade.total_time;
    SetMusicVolume(menu_bgm.music, 0 - percent);
    SetMusicVolume(main_bgm.music, 1 - percent);
  }
}

void fade_to_main_bgm_music()
{
  PlayMusicStream(main_bgm.music);
  music_fade.timer = music_fade.total_time;
}