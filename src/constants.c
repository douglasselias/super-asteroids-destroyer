#include <stdint.h>

typedef uint8_t   u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t    s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef int64_t  s64;
typedef float    f32;
typedef double   f64;

char *game_title = "Super Asteroids Destroyer";
const s32 screen_width  = 1280;
const s32 screen_height = 720;
#define half_screen_width  (screen_width  / 2)
#define half_screen_height (screen_height / 2)
#define screen_center ((Vector2){half_screen_width, half_screen_height})
#define AQUA ((Color){0, 255, 255, 255})