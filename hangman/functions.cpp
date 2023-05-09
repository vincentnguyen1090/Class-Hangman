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
    // checks if guessed letter is not in no position
    return (word.find(letter) != std::string::npos);
}

void prompt(const std::string &message)
{
    std::cout << message;

}

std::string getWord(const std::vector<std::string> &words)
{
    //returns a random word from vector
    //rand() generates a random number up to number of words in vector
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
    std::cout << std::endl;
}

void updateLetterbank(std::vector<char> &letterbank, char guess)
{
    letterbank.push_back(guess);
}

void run()
{
    srand(time(0));
    std::vector<std::string> wordBank;
    std::vector<char> letterBank;
    std::vector<char> letterBank2;
    std::string board1, board2, realWord, realWord2, displayWord, displayWord2, menu;
    bool player1, player2;
    char input;
    char guess = ' '; //to display phrases
    int misses = 0, misses2 = 0, gameChoice;

    board1 = getDefaultBoard();
    board2 = getDefaultBoard();
    loadFromFile("words.txt", wordBank);
    realWord = getWord(wordBank);
    realWord2 = getWord(wordBank);
    displayWord = getDisplayWord(realWord);
    displayWord2 = getDisplayWord(realWord2);
    //display phrases
    updateWord(realWord, displayWord, guess);
    updateWord(realWord2, displayWord2, guess);
    displayMenu();
    inputGameChoice(gameChoice);
    //only first while loop runs
    if(gameChoice == 1){
        player1 = true;
        player2 = false;
    }
    //both while loops run
    if(gameChoice == 2){
        player1 = true;
        player2 = true;
    }
    do {
        //player1
        while(!gameOver(displayWord, misses) && player1) {
            std::cout << "\n";
            if(gameChoice == 2)
            {
                std::cout << "Player1's turn\n";
            }
            drawBoard(board1);
            prompt(displayWord);
            std::cout << std::endl;
            outputLetterbank(letterBank);
            prompt("Enter a letter for player1: ");
            getInput(input);
            if (!inWord(realWord, input)) {
                misses++;
                updateBoard(board1, misses);
                updateLetterbank(letterBank, input);
                if(gameChoice == 2)
                {
                    //draws an updated board before it switches over to player 2
                    drawBoard(board1);
                }
                outputLetterbank(letterBank);
                if (misses == 6) {
                    //draws the final leg
                    drawBoard(board1);
                }
                if(player2){
                    player1 = false;
                    break; //breaks out of while loop
                }
            }
            else
            {
                updateWord(realWord, displayWord, input);
            }
        }
        //player2
        while(!gameOver(displayWord2, misses2) && player2) {
            std::cout << "\n";
            std::cout << "Player2's turn\n";
            drawBoard(board2);
            prompt(displayWord2);
            std::cout << std::endl;
            outputLetterbank(letterBank2);
            prompt("Enter a letter for player2: ");
            getInput(input);
            if (!inWord(realWord2, input)) {
                misses2++;
                updateBoard(board2, misses2);
                drawBoard(board2);
                updateLetterbank(letterBank2, input);
                outputLetterbank(letterBank2);
                if (misses == 6) {
                    //draws the final leg
                    drawBoard(board2);
                }
                if(player2){
                    player1 = true;
                    break;
                }
            }
            else {
                updateWord(realWord2, displayWord2, input);
            }
        }
    } while(!gameOver(displayWord, misses) && !gameOver(displayWord2, misses2));

    onePlayerGameResult(gameChoice, displayWord);
    twoPlayerGameResult(gameChoice, displayWord, displayWord2, realWord, realWord2);

}
void printWord(const std::string &word)
{
    std::cout << word << std::endl;
}

void updateWord(const std::string &word, std::string& displayWord, char guess)
{
    if(inWord(word, guess)) //function call inWord
    {
        for (int i = 0; i < word.size(); ++i)
        {
            if(word[i] == guess)
            {
                displayWord[i] = guess; //replaces '_' with guess
            }
        }
    }
}

std::string getDisplayWord(const std::string &word)
{
    //returns a string with n number of '_' per letter in word
    return std::string (word.length(), '_');
}
bool gameOver(std::string displayWord, int misses)
{
    //returns true if '_' is in no position or misses = 6
    return (displayWord.find('_') == std::string::npos
    || misses == 6);
}
void displayMenu()
{
    std::cout << "Welcome to hangman!\n"
              << "Do you want to play a 1 or 2 player game? (Enter 1 or 2): ";
}
void inputGameChoice(int& gameChoice)
{
    std::cin >> gameChoice;
}
void onePlayerGameResult(int& gameChoice, std::string displayWord)
{
    if(gameChoice == 1)
    {
        if(displayWord.find('_') == std::string::npos)
        {
            std::cout << "Congrats! You win!";
        }
        else
            std::cout << "Game Over! You lose!";
    }
}
void twoPlayerGameResult(int& gameChoice, std::string displayWord, std::string displayWord2, std::string realWord, std::string realWord2)
{
    if(gameChoice == 2)
    {
        //checks if '_' is in no position
        if(displayWord.find('_') == std::string::npos){
            std::cout << "Player1 wins!\n";
            std::cout << "Player2's word is " << realWord2;
        }
        if(displayWord2.find('_') == std::string::npos){
            std::cout << "Player2 wins!\n";
            std::cout << "Player1's word is " << realWord;
        }
        //checks if '_' is not in no position
        else if(displayWord.find('_') != std::string::npos && displayWord2.find('_') != std::string::npos) {
            std::cout << "Both players lost!\n";
            std::cout << "Player1's word is " << realWord << std::endl;
            std::cout << "Player2's word is " << realWord2 << std::endl;
        }
    }
}

