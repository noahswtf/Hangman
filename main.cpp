#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>

int lives = 9;

std::string word;
std::string word_obf;
bool wordFound;
bool foundSomething;

std::string guess;
std::vector<std::string> guessList;

std::string hangman[9] =
{
	" +---+  \n"
	" |   |  \n"
	" |   o  \n"
	" |  -|- \n"
	" |  //  \n"
	" |_____ \n",

	" +---+  \n"
	" |   |  \n"
	" |   o  \n"
	" |  -|- \n"
	" |  /  \n"
	" |_____ \n",

	" +---+  \n"
	" |   |  \n"
	" |   o  \n"
	" |  -|- \n"
	" |      \n"
	" |_____ \n",

	" +---+  \n"
	" |   |  \n"
	" |   o  \n"
	" |  -|  \n"
	" |      \n"
	" |_____ \n",

	" +---+  \n"
	" |   |  \n"
	" |   o  \n"
	" |   |  \n"
	" |      \n"
	" |_____ \n",

	" +---+  \n"
	" |   |  \n"
	" |   o  \n"
	" |      \n"
	" |      \n"
	" |_____ \n",

	" +---+  \n"
	" |      \n"
	" |      \n"
	" |      \n"
	" |      \n"
	" |_____ \n",

	"        \n"
	" |      \n"
	" |      \n"
	" |      \n"
	" |      \n"
	" |_____ \n",

	"         \n"
	"        \n"
	"        \n"
	"        \n"
	"        \n"
	"  _____ \n",
};

std::string getWord()
{
	int amountOfLines = 0;

	std::string line;

	std::vector<std::string> vec;

	std::ifstream ifile("words.txt");

	while (std::getline(ifile, line))
	{
		amountOfLines++;
		vec.push_back(line);
	}

	srand(time(NULL));
	int randomNumber = rand() % amountOfLines;

	ifile.close();

	return vec[randomNumber];
}

int main()
{ 
	std::cout << "Welcome To Hangman" << std::endl << std::endl;
	std::cout << "Type 'Done' And Press Enter When You Think The Word Is Complete!" << std::endl << std::endl;

	word = getWord();

	int length = word.length();

	for (int i = 0; i < length; i++)
	{
		word_obf.push_back('_');
	}

	while (!wordFound)
	{
		std::cout << "Guess A Letter Or The Word: " << word_obf << std::endl;
		std::cin >> guess;

		guessList.push_back(guess);

		std::cout << "Current Guesses So Far: ";

		for (int i = 0; i < guessList.size(); i++)
		{
			std::cout << guessList[i] << " ";
		}

		std::cout << "\n";

		std::transform(guess.begin(), guess.end(), guess.begin(), ::tolower);

		if (word_obf == word || guess == word)
		{
			std::cout << "You Guessed Right!" << std::endl;
			wordFound = true;
			break;
		}
		else
		{
			foundSomething = false;

			for (int i = 0; i < length; i++)
			{
				if (word[i] == guess[guess.length() - 1])
				{
					foundSomething = true;

					word_obf[i] = guess[guess.length() - 1];
				}	
			}

			if (foundSomething)
				std::cout << "'" << guess[guess.length() - 1] << "'" << " Is In The Word." << std::endl << std::endl;
			else
			{
				lives -= 1;
				if (lives <= 0)
				{
					std::cout << std::endl << hangman[lives] << std::endl << std::endl;
					std::cout << "You Have 0 Lives! Better Luck Next Time. Word Was: " << word << std::endl;
					exit(0);
				}
				else
				{
					std::cout << "You Guessed Incorrectly, -1 Lives. You Now Have " << lives << " Lives." << std::endl << std::endl;
					std::cout << std::endl << hangman[lives] << std::endl << std::endl;
				}
			}
		}
	}
}