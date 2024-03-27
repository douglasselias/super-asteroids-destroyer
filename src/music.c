static Music main_bgm;
static Music menu_bgm;

void music_fade_update(Timer* timer, float dt);
Timer music_fade_timer = {
  .total = 2,
  .update_fn = music_fade_update,
};

void music_fade_update(Timer* timer, float dt) {
  SetMusicVolume(menu_bgm, timer->percent);
  SetMusicVolume(main_bgm, 1 - timer->percent);
}

void init_music() {
  main_bgm = LoadMusicStream("assets/stargaze.ogg");
  menu_bgm = LoadMusicStream("assets/crazy_space.ogg");
  PlayMusicStream(menu_bgm);
}

void update_music(float dt) {
  UpdateMusicStream(menu_bgm);
  UpdateMusicStream(main_bgm);

  update_timer(&music_fade_timer, dt);
}

void fade_to_main_bgm_music() {
  PlayMusicStream(main_bgm);
  start_timer(&music_fade_timer);
}