typedef unsigned long long score_t;
s32 SCORE_T_SIZE = sizeof(score_t);

score_t score     = 0;
score_t highscore = 0;

s32 METEOR_POINTS   = 10;
s32 VELOCITY_POINTS = 70;

char *save_file = "highscore.bin";

void update_score_meteor()
{
  score += METEOR_POINTS;
}

void save_highscore()
{
  SaveFileData(save_file, &highscore, SCORE_T_SIZE);
}

void load_highscore()
{
  if(FileExists(save_file))
  {
    u8 *bytes_highscore = LoadFileData(save_file, &SCORE_T_SIZE);
    highscore = *(score_t*)bytes_highscore;
    UnloadFileData(bytes_highscore);
  }
}