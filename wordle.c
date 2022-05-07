///////////////////////////////////////////////////////////////////////////// 
// INTEGRITY STATEMENT (v3)
//
// By signing your name and ID below you are stating that you have agreed
// to the online academic integrity statement:a
// https://student.cs.uwaterloo.ca/~cs136/current/assignments/integrity.shtml
/////////////////////////////////////////////////////////////////////////////
// I received help from and/or collaborated with: 
 
// nobody 
//  
// Name: Stan Zhang 
// login ID: y3676zha 
///////////////////////////////////////////////////////////////////////////// 

#include "wordle.h"
#include <string.h>
#include <assert.h>

// see wordle.h
bool evaluate_guess(const char *secret, const char *guess, char *result) {
  assert(strlen(secret) == strlen(guess));
  int character[256] = {0};
  int len = 0;
  bool ans = true;
  while (secret[len]) {
    int temp = secret[len];
    character[temp] = 1;
    len++;
  }
  len = 0;
  while (guess[len]) {
    int temp2 = guess[len];
    if (guess[len] == secret[len]) {
      result[len] = guess[len] - 'a' + 'A';
    } else if (character[temp2] == 1) {
      ans = false;
      result[len] = guess[len];   
    } else {
      ans = false;
      result[len] = '.';
    }
    len++;
  }
  result[len] = '\0';
  return ans;
}


// see wordle.h
int find_in_list(const char *guess, char *word_list[], int num_words) {
  int min = 0;
  int max = num_words - 1;
  int mid = (min + max) / 2;
  while (min <= max) {
    int temp = strcmp(guess, word_list[mid]);
    if (temp == 0) {
      return mid;
    }
    if (temp > 0) {
      min = mid + 1;
      mid = (min + max) / 2;
    } else if (temp < 0) {
      max = mid - 1;
      mid = (min + max) / 2;
    }
  }
  return -1;
}


// see wordle.h
void available_letters(char *guesses[], char *results[], int num_guesses,
                       char *alphabet) {
  int characters[256] = {0};
  assert(num_guesses >= 0);
  for (int i = 0; i < num_guesses; i++) {
    int len = 0;
    while (results[i][len]) {
      int temp = 0;
      int temp2 = guesses[i][len];
      if (results[i][len] >= 97 && results[i][len] <= 122) {
        temp = results[i][len];    
      } else {
        temp = results[i][len] - 'A' + 'a';
      }
      if (results[i][len] != '.') {
        characters[temp] = 1;
      } else {
        characters[temp2] = 2;
      }
      len++;
    }
  }
  int len = 0;
  for (int i = 97; i <= 122; i++) {
    if (characters[i] == 0) {
      alphabet[len] = i;
    } else if (characters[i] == 1) {
      alphabet[len] = i - 'a' + 'A';
    } else {
      alphabet[len] = '.';
    }
    len++;
  }
  alphabet[len] = '\0';
}


// see wordle.h
bool valid_hard_guess(char *guesses[], char *results[], int num_guesses,
                      const char *next_guess) {
  assert(num_guesses >= 0);
  int characters[256] = {0};
  char must_use[256] = "";
  int len1 = 0;
  for (int i = 0; i < num_guesses; i++) {
    int len = 0;
    while (results[i][len]) {
      int temp = 0;
      int temp2 = guesses[i][len];
      if (results[i][len] >= 97 && results[i][len] <= 122) {
        temp = results[i][len];    
      } else {
        temp = results[i][len] - 'A' + 'a';
      }
      if (results[i][len] != '.') {
        characters[temp] = 1;
        must_use[len1] = temp;
        len1++;
      } else {
        characters[temp2] = 2;
      }
      len++;
    }  
  }
  
  must_use[len1] = '\0';
  for (int i = 0; i < num_guesses; i++) {
    int len = 0;
    while (results[i][len]) {
      int temp2 = next_guess[len];
      if (characters[temp2] == 2) {
        return false;
      }
      if (results[i][len] >= 65 && results[i][len] <= 90) {
        if (next_guess[len] != results[i][len] - 'A' + 'a' ) {
          return false;
        }
      } else if (characters[temp2] == 1) {
        if (next_guess[len] == guesses[i][len]) {
          return false;
        }
      }
      len++;
    } 
  }
  
  for (int i = 0; i < len1; i++) {
    int len = 0;
    bool flag = false;
    while (next_guess[len]) {
      if (next_guess[len] == must_use[i]) {
        flag = true;
      }
      len++;
    }
    if (flag == false) {
      return false;
    }
  }
  return true;
}

// find_helper(guesses, results, num_guesses, characters, must_use,
//   len1, next_guess) consumes the arrays of all the guesses and results
//   ,the array characters that is used to determine the right character in the word
//   and the arrays that contains all of the letters that must be used and its length
//   it returns true if the next_guess is a valid guess, otherwise returns false
// requires: num_guesses >= 0
// time: O(m*n) where m is the number of guesses and n is the length of the longest result.
bool find_helper(char *guesses[], char *results[], int num_guesses, 
                 int* characters, char* must_use, int len1,
                 char* next_guess) {
  for (int i = 0; i < num_guesses; i++) {
    int len = 0;
    while (results[i][len]) {
      int temp2 = next_guess[len];
      if (characters[temp2] == 2) {
        return false;
      }
      if (results[i][len] >= 65 && results[i][len] <= 90) {
        if (next_guess[len] != results[i][len] - 'A' + 'a' ) {
          return false;
        }
      } else if (characters[temp2] == 1) {
        if (next_guess[len] == guesses[i][len]) {
          return false;
        }
      }
      len++;
    } 
  }
  for (int i = 0; i < len1; i++) {
    int len = 0;
    bool flag = false;
    while (next_guess[len]) {
      if (next_guess[len] == must_use[i]) {
        flag = true;
      }
      len++;
    }
    if (flag == false) {
      return false;
    }
  }
  return true;
}

// see wordle.h
int find_solution(char *guesses[], char *results[], int num_guesses,
                  char *word_list[], int num_words,
                  char *solutions[], int max_solutions) {
  assert(max_solutions >= 1);
  assert(num_guesses >= 0);
  int word_count = 0;
  int characters[256] = {0};
  char must_use[256] = "";
  int len1 = 0;
  for (int i = 0; i < num_guesses; i++) {
    int len = 0;
    while (results[i][len]) {
      int temp = 0;
      int temp2 = guesses[i][len];
      if (results[i][len] >= 97 && results[i][len] <= 122) {
        temp = results[i][len];    
      } else {
        temp = results[i][len] - 'A' + 'a';
      }
      if (results[i][len] != '.') {
        characters[temp] = 1;
        must_use[len1] = temp;
        len1++;
      } else {
        characters[temp2] = 2;
      }
      len++;
    }  
  }
  must_use[len1] = '\0';
  for (int i = 0; i < num_words; i++) {
    if (word_count == max_solutions) {
      break;
    }
    if (find_helper(guesses, results, num_guesses, characters, must_use,
                    len1, word_list[i])) {
      solutions[word_count] = word_list[i];
      word_count++;
    }
  }
  return word_count;
}
