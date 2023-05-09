//
// Created by Dave R. Smith on 1/10/23.
//
#include "functions.h"
#include <iostream>

std::string getDefaultBoard()
{
    std::string board = "  +---+\n"
                        "  |   |\n"
                        "      |\n"
                        "      |\n"
                        "      |\n"
                        "      |\n"
                        "=========";
    return board;
}
void getInput(char &letter)
{
    std::cin >> letter;
}

char getInput()
{
    char letter;
    getInput(letter);
    return letter;
}
void drawBoard(const std::string& board)
{
    std::cout << board << std::endl;
}
void updateBoard(std::string& board, int misses)
{
    switch(misses)
    {
        case 1:
            board[18] = 'O';
        break;
        case 2:
            board[26] = '|';
        break;
        case 3:
            board[25] = '/';
        break;
        case 4:
            board[27] = '\\';
        break;
        case 5:
            board[33] = '/';
        break;
        case 6:
            board[35] = '\\';
        break;
    };



}

bool inWord(const std::string &word, char letter)
{
    return (word.find(letter) != std::string::npos);

}

void prompt(const std::string &message)
{
    std::cout << message;

}

std::string getWord(const std::vector<std::string> &words)
{
    return words.at(rand() % words.size());
}

void loadFromFile(const std::string &filename, std::vector<std::string> &words)
{
    std::ifstream fin;
    std::string next;
    if(openFile(fin, filename))
    {
        while(getline(fin,next))
            words.push_back(next);
    }
    closeFile(fin);
}

bool openFile(std::ofstream &out, const std::string &filename)
{
    out.open(filename);
    return !out.fail();
}

bool openFile(std::ifstream &in, const std::string &filename)
{
    in.open(filename);
    return !in.fail();
}

void addWord(const std::string &word, const std::string &filename, std::vector<std::string> &words)
{
    std::ofstream fout;
    if(openFile(fout,filename))
    {
        if(!checkInVec(words,word))
        {
            fout<<word<<std::endl;
            words.push_back(word);
        }
    }
    closeFile(fout);
}
bool checkInVec(const std::vector<std::string>& words, const std::string& word)
{

    for (int i = 0; i < words.size(); ++i)
    {
        if (words[i] == word)
            return true;
    }
    return false;
}


void closeFile(std::ofstream &out)
{
    out.close();
}

void closeFile(std::ifstream &in)
{
    in.close();
}

void outputLetterbank(const std::vector<char> &letterbank)
{
    for (int i = 0; i < letterbank.size(); ++i)
    {
        std::cout << letterbank[i] << " ";
    }
    std::cout << std::endl; //;)
}

void updateLetterbank(std::vector<char> &letterbank, char guess)
{
    letterbank.push_back(guess);
}

void run()
{
    
}

void printWord(const std::string &word)
{
    std::cout << word << std::endl;
}

void updateWord(const std::string &word, std::string& displayWord, char guess)
{
    if(inWord(word, guess))
    {
        for (int i = 0; i < word.size(); ++i)
        {
            if(word[i] == guess)
            {
                displayWord[i] = guess;
            }
        }
    }
}

std::string getDisplayWord(const std::string &word)
{
    return std::string (word.length(), '_');
}