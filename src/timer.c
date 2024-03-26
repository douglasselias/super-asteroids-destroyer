#include <stdint.h>

typedef float f32;

typedef struct Timer Timer;
struct Timer {
  f32 total;
  f32 current;
  f32 limit;
  f32 percent;
  void (*update_fn)(Timer* timer, f32 dt);
  void (*end_fn)();
};

void start_timer(Timer* timer) {
  timer->current = timer->total;
}

void update_timer(Timer* timer, f32 dt) {
  if(timer->current > timer->limit) {
    timer->current -= dt;
    timer->percent = timer->current / timer->total;
    if(timer->update_fn)
      timer->update_fn(timer, dt);
  } else if(timer->current < timer->limit) {
    timer->current = 0;
    if(timer->end_fn)
      timer->end_fn();
  }
}
