#ifndef _COWS_AND_BULLS_H
#define _COWS_AND_BULLS_H

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<cctype>
using namespace std;

#define MIN_WORD_LENGTH 3
#define MAX_WORD_LENGTH 8
#define DICT_FILE_NAME "/usr/share/dict/words"

typedef pair<int, int> cows_and_bulls;

class WordList
{
  vector<string> word_list;
public:
  WordList();
  string get_random_word(int length);
};

class Game
{
  int cows, bulls;
  string chosen_word;
  string guessed_word;
  string guessed_word_string_without_cows;
  string chosen_word_string_without_cows;
  bool game_won;
public:
  Game(string chosen_word);
  void check_guessed_word(string guessed_word);
  bool is_game_won() { return game_won; }
};

class Guess
{
  int cows, bulls;
  string guessed_word;
  string guessed_word_string_without_cows;
  string compute_cows(string chosen_word) ;
  void compute_bulls(string chosen_word_string_without_cows) ;

public:
  Guess(string guessed_word);
  cows_and_bulls check_guess(string chosen_word) ;
};

class GameSession
{
public:
  void run();
};

#endif
