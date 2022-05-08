# Wordle
A wordle game that contains over 2000 words and has different difficulty levels

This game is fully developed in C++

# What is Wordle?

The aim of the game is to find a 5 letter word by guessing

# Rules

The game allows infinity attempts and has several difficulty levels

Easy level: You can guess whatever words you want from the hint given

Medium level: INVALID guess includes words that you have already guessed and words that include the character that cannot be included in the word shown by hint

Hard level: INVALID guess includes the Medium level cases and include the words that have the character that is not in the right position as indicated by hint

output: In the 5 character output Capitalized mean the character is in the right position and in the word. And lowercase character means that it is in the word but not in the right position. And dots means that the character is not in the word

Example:

word: Apple

guess one: Abhor

output: A....
