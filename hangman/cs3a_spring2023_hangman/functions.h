//
// Created by Dave R. Smith on 1/10/23.
//

#ifndef CS3A_SPRING2023_HANGMAN_FUNCTIONS_H
#define CS3A_SPRING2023_HANGMAN_FUNCTIONS_H
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <algorithm>

void getInput(char &letter);
char getInput();
std::string getDefaultBoard();
void drawBoard(const std::string& board);
void updateBoard(std::string& board, int misses);
bool inWord(const std::string& word, char letter);
void prompt(const std::string& message);
//get random word
std::string getWord(const std::vector<std::string>& words);
//load words from file
void loadFromFile(const std::string& filename, std::vector<std::string>& words);
//open a file for output returns false if file cannot open
bool openFile(std::ofstream& out, const std::string& filename);
//open a file for input returns false if file cannot open
bool openFile(std::ifstream& in, const std::string& filename);
//add word to file
void addWord(const std::string& word, const std::string& filename,
             std::vector<std::string>& words);
//close out file
void closeFile(std::ofstream& out);
//close input file
void closeFile(std::ifstream& in);

void outputLetterbank(const std::vector<char>& letterbank);
//update letterbank
void updateLetterbank(std::vector<char>& letterbank, char guess);
bool checkInVec(const std::vector<std::string>& words, const std::string& word);
void run();
void printWord(const std::string &word);
void updateWord(const std::string &word, std::string& displayWord, char guess);
std::string getDisplayWord(const std::string &word);
#endif //CS3A_SPRING2023_HANGMAN_FUNCTIONS_H
