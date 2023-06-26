#include <iostream>
#include <cstdlib>
#include<ctime>
#include <string>
using namespace std;

const int MAX_GUESSES = 8;

void PrintMessage(string message, bool printTop = true, bool printBottom = true)
{
    if (printTop)
    {
        cout << "+---------------------------------+" << endl;
        cout << "|";
    }
    else
    {
        cout << "|";
    }
    bool front = true;
    for (int i = message.length(); i < 33; i++)
    {
        if (front)
        {
            message = " " + message;
        }
        else
        {
            message = message + " ";
        }
        front = !front;
    }
    cout << message.c_str();

    if (printBottom)
    {
        cout << "|" << endl;
        cout << "+---------------------------------+" << endl;
    }
    else
    {
        cout << "|" << endl;
    }
}

void DrawHangman(int guessCount)
{
    if (guessCount >= 1)
        PrintMessage("|", false, false);
    else
        PrintMessage("", false, false);

    if (guessCount >= 2)
        PrintMessage("O", false, false);
    else
        PrintMessage("", false, false);

    if (guessCount == 3)
        PrintMessage("/  ", false, false);

    if (guessCount == 4)
        PrintMessage("/| ", false, false);

    if (guessCount >= 5)
        PrintMessage("/|\\", false, false);
    else
        PrintMessage("", false, false);

    if (guessCount == 6)
        PrintMessage("/", false, false);

    if (guessCount >= 7)
        PrintMessage("/ \\", false, false);
    else
        PrintMessage("", false, false);
}


/*
+---------------------------------+
|             HANG MAN            |
+---------------------------------+
|               |                 |
|               O                 |
|              /|\                |                               
|              / \                |
|         +----------+            |
|         |          |            |
+---------------------------------+
|        Available letters        |
+---------------------------------+
|     A B C D E F G H I J K L M   |
|     N O P Q R S T U V W X Y Z   |
+---------------------------------+
|         Guess the word          |
+---------------------------------+
| _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ |
+---------------------------------+
>
*/

void chooseRandWord(string words, string word)
{
    srand(time(NULL));
    int n = rand() % 10;
    word = words[n];
}

int letterFill(char guess, string secretWord, string& guessWord)
{
    int matches = 0;
    int len = secretWord.length();

    for (int i = 0; i < len; i++)
    {
        // Did we already match this letter in a previous guess?
        if (guess == guessWord[i])
            return 0;
        if (guess == secretWord[i])
        {
            guessWord[i] = guess;
            matches++;
        }
    }
    return matches;
}

int main()
{
    int index;
    char letter;
    int countWrongGuesses=0;
    string word;
    string words[] =
    {
        "among", // *****
        "amount",
        "amusement",
        "hamburger",
        "donkey",
        "anvil",
        "missionary",
        "doggy"
    };

    PrintMessage("HANGMAN");

    srand(time(NULL));
    int n = rand() % 10;
    word = words[n];

    string unknown(word.length(), '*');
    cout << unknown << endl;
    while (countWrongGuesses < MAX_GUESSES)
    {
        cout <<endl << "Guess Letter: ";
        cin >> letter;

        if (letterFill(letter, word, unknown) == 0)
        {
            cout << "Bukvata ne e tazi tupak" << endl;
            countWrongGuesses++;
            DrawHangman(countWrongGuesses);
        }
        else
        {
            for (size_t i = 0; i < word.length(); i++) {
                if (word[i] == letter) {
                    unknown[i] = letter;
                    cout << unknown << endl;
                }
            }
            cout << "Bravo! Pozna UwU" << endl;
        }

        //Guesses left
        cout << "Imash: " << MAX_GUESSES - countWrongGuesses << " ostanali. Stegni se." << endl;


        if (word == unknown)
        {
            cout << word << endl;
            cout << "YAAAY SPECHELI MANQK!!!!" << endl;
            break;
        }
    }

    if (countWrongGuesses == MAX_GUESSES)
    {
        cout << "TI UMRQ. REST IN PEACE!" << endl;
        cout << "Pravilnata duma beshe: " << word << endl;
    }

}