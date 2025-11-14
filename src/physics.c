
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

bool things_collided(Thing a, Thing b)
{
  return CheckCollisionCircles(a.position, a.radius, b.position, b.radius);
}