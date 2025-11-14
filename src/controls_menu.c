Thing key_a;
Thing key_d;
Thing key_w;
Thing key_enter;
Thing key_space;

Thing text_controls;
Thing text_rotate;
Thing text_thrust;
Thing text_shoot;
Thing text_pause;
Thing text_back;

void init_controls_menu()
{
  key_a.texture_color     = WHITE;
  key_d.texture_color     = WHITE;
  key_w.texture_color     = WHITE;
  key_enter.texture_color = WHITE;
  key_space.texture_color = WHITE;

  key_a.position     = (Vector2){half_screen_width - 400, 280};
  key_d.position     = (Vector2){half_screen_width - 300, 280};
  key_w.position     = (Vector2){half_screen_width - 400, 280};
  key_enter.position = (Vector2){half_screen_width - 400, 280};
  key_space.position = (Vector2){half_screen_width - 400, 280};
  
  key_a.texture     = LoadTexture("assets/keyboard_a.png");
  key_d.texture     = LoadTexture("assets/keyboard_d.png");
  key_w.texture     = LoadTexture("assets/keyboard_w.png");
  key_enter.texture = LoadTexture("assets/keyboard_enter.png");
  key_space.texture = LoadTexture("assets/keyboard_space.png");

  text_controls.text = MemAlloc(20);
  text_rotate.text   = MemAlloc(20);
  text_thrust.text   = MemAlloc(20);
  text_shoot.text    = MemAlloc(20);
  text_pause.text    = MemAlloc(20);
  text_back.text     = MemAlloc(20);

  TextCopy(text_controls.text, "Controls");
  TextCopy(text_rotate.text,   "Rotate"  );
  TextCopy(text_thrust.text,   "Thrust"  );
  TextCopy(text_shoot.text,    "Shoot"   );
  TextCopy(text_pause.text,    "Pause"   );
  TextCopy(text_back.text,     "< Back"  );

  text_controls.position = (Vector2){half_screen_width      ,  70};
  text_rotate.position   = (Vector2){half_screen_width - 270, 280};
  text_thrust.position   = (Vector2){half_screen_width - 100, 280};
  text_shoot.position    = (Vector2){half_screen_width + 100, 280};
  text_pause.position    = (Vector2){half_screen_width + 250, 280};
  text_back.position     = (Vector2){half_screen_width      , 440};

  text_controls.color = WHITE;
  text_rotate.color   = WHITE;
  text_thrust.color   = WHITE;
  text_shoot.color    = WHITE;
  text_pause.color    = WHITE;
  text_back.color     = WHITE;
}

void draw_text(Font font, const char *text, Vector2 position, Color color);

void draw_text_thing(Font font, Thing thing)
{
  draw_text(font, text_controls.text, text_controls.position, text_controls.color);
}

void draw_control_thing(Thing thing)
{
  DrawTexture(thing.texture, thing.position.x, thing.position.y, thing.color);
}

void draw_controls_menu(Font font, bool effect_timer)
{
  draw_text_thing(font, text_controls);
  
  draw_text_thing(font, text_rotate);
  draw_control_thing(key_a);
  draw_control_thing(key_d);
  
  draw_text_thing(font, text_thrust);
  draw_control_thing(key_w);
  
  draw_text_thing(font, text_shoot);
  draw_control_thing(key_space);
  
  draw_text_thing(font, text_pause);
  draw_control_thing(key_enter);

  text_back.color = effect_timer ? WHITE : AQUA;
  draw_text_thing(font, text_back);
}