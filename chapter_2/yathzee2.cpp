/*************************************************************************
 * Copyright (C) 2008 by liukaipeng                                      *
 * liukaipeng at gmail dot com                                           *
 *************************************************************************/
/* @JUDGE_ID 00000 10149 C++ "Yahtzee" */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;
int const ncategories = 13;
int const nrounds = 13;
int const ndices = 5;
int const ncombinations = 8192; /* 1 << 13 + 1 */
int const nupper = 64; /* 63 + 1 */
int nmapped[ncombinations];
int ones(int dices[]) 
{
  int score = 0;
  for (int i = 0; i < ndices; ++i) {
    if (dices[i] == 1) {
      score += 1;
    }
  }
  return score;
}
int twos(int dices[]) 
{
  int score = 0;
  for (int i = 0; i < ndices; ++i) {
    if (dices[i] == 2) {
      score += 2;
    }
  }
  return score;
}
int threes(int dices[]) 
{
  int score = 0;
  for (int i = 0; i < ndices; ++i) {
    if (dices[i] == 3) {
      score += 3;
    }
  }
  return score;
}
int fours(int dices[]) 
{
  int score = 0;
  for (int i = 0; i < ndices; ++i) {
    if (dices[i] == 4) {
      score += 4;
    }
  }
  return score;
}
int fives(int dices[]) 
{
  int score = 0;
  for (int i = 0; i < ndices; ++i) {
    if (dices[i] == 5) {
      score += 5;
    }
  }
  return score;
}
int sixes(int dices[]) 
{
  int score = 0;
  for (int i = 0; i < ndices; ++i) {
    if (dices[i] == 6) {
      score += 6;
    }
  }
  return score;
}
int chance(int dices[]) 
{
  int score = 0;
  for (int i = 0; i < ndices; ++i) {
    score += dices[i];
  }
  return score;
}
int three_kind(int dices[]) 
{
  int score = 0;
  if (dices[0] == dices[2] || 
      dices[1] == dices[3] || 
      dices[2] == dices[4]) {
    for (int i = 0; i < ndices; ++i) {
      score += dices[i];
    }
  }
  return score;
}
int four_kind(int dices[]) 
{
  int score = 0;
  if (dices[0] == dices[3] || 
      dices[1] == dices[4]) {
    for (int i = 0; i < ndices; ++i) {
      score += dices[i];
    }
  }
  return score;
}
int five_kind(int dices[]) 
{
  int score = 0;
  if (dices[0] == dices[4]) {
    score = 50;
  }
  return score;
}
int short_straight(int dices[]) 
{
  int score = 0;
  if (dices[0] == dices[1]-1 && 
      dices[1] == dices[2]-1 && 
      dices[2] == dices[3]-1 ||
      dices[1] == dices[2]-1 && 
      dices[2] == dices[3]-1 && 
      dices[3] == dices[4]-1) {
    score = 25;
  }
  return score;
}
int long_straight(int dices[]) 
{
  int score = 0;
  if (dices[0] == dices[1]-1 && 
      dices[1] == dices[2]-1 &&
      dices[2] == dices[3]-1 && 
      dices[3] == dices[4]-1) {
    score = 35;
  }
  return score;
}
int full_house(int dices[]) 
{
  int score = 0;
  if (dices[0] == dices[1] && 
      dices[2] == dices[4] ||
      dices[0] == dices[2] && 
      dices[3] == dices[4]) {
    score = 40;
  }
  return score;
}
      
struct mapping
{
  int map;
  int upper;
};
void best_categorization(int scores[][ncategories], int categorization[], 
                         int& bonus, int& score)
{
  int best[ncombinations][nupper];
  mapping previous[ncombinations][nupper];
  for (int i = 0; i < ncombinations; ++i) {
    for (int j = 0; j < nupper; ++j) {
      best[i][j] = numeric_limits<int>::min();
    }
  }
  best[0][0] = 0;
  for (int r = 0; r < nrounds; ++r) {
    for (int c = 0; c < ncategories; ++c) {
      int score = scores[r][c];
      int upper = c < 6 ? score : 0;
      for (int map = 0, add = 1 << c; map < ncombinations; ++map) {
        if (nmapped[map] != r || map & add) continue;
        for (int u = 0; u < nupper; ++u) {
          int newscore = score + best[map][u];
          int newupper = upper + u < nupper ? upper + u : nupper - 1;
          if (newscore > best[map|add][newupper]) {
            best[map|add][newupper] = newscore;
            previous[map|add][newupper].map = map;
            previous[map|add][newupper].upper = u;
          }
        }
      }
    }
  }
  int map = ncombinations - 1;
  int upper = nupper - 1;
  bonus = 35;
  score = best[map][upper] + bonus;
  for (int u = 0; u < nupper; ++u) {
    if (score < best[map][u]) {
      bonus = 0;
      score = best[map][u];
      upper = u;
    }
  }
  
  while (map) {
    mapping pre = previous[map][upper];
    int c = 0;
    for (int add = map ^ pre.map; add >>= 1; ++c) /* NOP */;
    categorization[c] = best[map][upper] - best[pre.map][pre.upper];
    map = pre.map;
    upper = pre.upper;
  }
}
int main(int argc, char *argv[])
{
#ifndef ONLINE_JUDGE
  filebuf in, out;
  cin.rdbuf(in.open((string(argv[0]) + ".in").c_str(), ios_base::in));
  cout.rdbuf(out.open((string(argv[0]) + ".out").c_str(), ios_base::out));
#endif
  
  /* calculate the number of "used categories" for each combination*/
  for (int i = 0; i < ncombinations; ++i) {
    for (int j = 0; j < ncategories; ++j) {
      nmapped[i] += (i & (1 << j)) ? 1 : 0;
    }
  }
  typedef int (*scorer)(int []);
  scorer scorers[ncategories] = { 
    &ones, &twos, &threes, &fours, &fives,  &sixes, &chance, 
    &three_kind, &four_kind, &five_kind, &short_straight, &long_straight, 
    &full_house, 
  };
  
  int dices[ndices];
  int scores[nrounds][ncategories];
  int d = 0, r = 0, g = 0;
  while (cin >> dices[d++ % ndices]) {
    if (d / ndices > r) {
      sort(dices, dices + ndices);
      for (int c = 0; c < ncategories; ++c) {
        scores[r % nrounds][c] = scorers[c](dices);
      }
      r = d / ndices;
    }
    if (r / nrounds > g) {
      g = r / nrounds;
      int categorization[ncategories];
      int bonus = 0;
      int score = 0;
      best_categorization(scores, categorization, bonus, score);
      for (int c = 0; c < ncategories; ++c) {
        cout << categorization[c] << ' ';
      }
      cout << bonus << ' ' << score << '\n';
    }
  }
  return 0;
}
