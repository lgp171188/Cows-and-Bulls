#include "cows_and_bulls.h"

WordList::WordList()
{
  ifstream dict_file(DICT_FILE_NAME);
  if (!dict_file.is_open())
  {
    cout<<"Unable to open the dictionary file"<<endl;
    exit(1);
  }
  string word;
  while(getline(dict_file, word))
  {
    if(word.find("'") == string::npos)
    {
      word_list.push_back(word);
    }
  }
}

string WordList::get_random_word(int length)
{
  vector<string> words_of_length_n;
  for (vector<string>::const_iterator i=word_list.begin();
       i!=word_list.end();i++)
  {
    if((*i).length() == length)
    {
      words_of_length_n.push_back(*i);
    }
  }
  srand(time(0));
  int n = (rand() % (words_of_length_n.size()-1)) + 1;
  return words_of_length_n[n];
}



void string_to_lower(string& str)
{
  transform(str.begin(), str.end(), str.begin(), ::tolower);
}

Game::Game(string chosen_word)
{
  game_won = false;
  this->chosen_word = chosen_word;
}

Guess::Guess(string guessed_word)
{
  this->guessed_word = guessed_word;
  cows = 0;
  bulls = 0;
  guessed_word_string_without_cows = "";
}

string Guess::compute_cows(string chosen_word) 
{
  string chosen_word_string_without_cows = "";
  for (int i=0;i<guessed_word.length(); i++)
  {
    if (guessed_word[i] == chosen_word[i])
    {
      ++cows;
    }
    else
    {
      guessed_word_string_without_cows.push_back(guessed_word[i]);
      chosen_word_string_without_cows.push_back(chosen_word[i]);
    }
  }
  return chosen_word_string_without_cows;
}

void Guess::compute_bulls(string chosen_word_string_without_cows) 
{
  for (string::const_iterator i=guessed_word_string_without_cows.begin();
       i!=guessed_word_string_without_cows.end(); ++i)
  {
    for (string::const_iterator j=chosen_word_string_without_cows.begin();
         j!=chosen_word_string_without_cows.end(); ++j)
    {
      if (*i == *j)
      {
        ++bulls;
      }
    }
  }
}

cows_and_bulls Guess::check_guess(string chosen_word) 
{
  compute_bulls(compute_cows(chosen_word));
  cows_and_bulls cb = make_pair(cows, bulls);
  return cb;
}

void Game::check_guessed_word(string guessed_word)
{
  int cows, bulls;
  cows_and_bulls cb;
  Guess g(guessed_word);
  cb = g.check_guess(chosen_word);
  cows = cb.first;
  bulls = cb.second;
  cout<<cows<<" Cows and "<<bulls<<" bulls"<<endl;
  if (cows == chosen_word.length())
  {
    game_won = true;
  }
}


void GameSession::run()
{
  WordList a;
  int word_length;
  string current_word;
  string guessed_word;
  char another='y';
  int count;
  while (another == 'y')
  {
    cout<<"Enter the length of the word to be used to play("<<MIN_WORD_LENGTH
        <<"-"<<MAX_WORD_LENGTH<<"):";
    cin>>word_length;
    if (word_length < MIN_WORD_LENGTH || word_length > MAX_WORD_LENGTH)
    {
      cout<<"Enter a valid length to be used ("<<MIN_WORD_LENGTH
          <<"-"<<MAX_WORD_LENGTH<<")"<<endl;
    }
    current_word = a.get_random_word(word_length);
    string_to_lower(current_word);
    Game g(current_word);
    count = 0;
    while (!g.is_game_won())
    {
      cout<<"Guess the word:";
      cin>>guessed_word;
      ++count;
      g.check_guessed_word(guessed_word);
    }
    cout<<"Game won in "<<count<<" guesses!"<<endl;
    cout<<"Do you want to play again(y/n)?:";
    cin>>another;
  }

  
}


int main()
{
  GameSession g;
  g.run();
  return 0;
}
