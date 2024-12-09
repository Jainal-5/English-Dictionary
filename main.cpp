#include <iostream>
#include <map>
#include <fstream>
#include "Word.h"

/**Prints the main menu*/
void printMenu();

/**Search for word*/
void search();

/**Gets input for the menu*/
int getMenuChoice();

/**Greets the user farewell*/
void quit();

/**clear the screen*/
void clear();

/**Gets user input for their search*/
std::string getWordInput();

/**Converts string to lower character*/
std::string tolower(std::string word);

//parse Csv
Word parse(std::string line);

//parse definition
std::vector<std::string> parseDef(std::string rawDef)
{
	std::vector<std::string> defs;

	std::string def = "";

	for(char c : rawDef)
	{
		if(c != ';')
		{
			def += c;
		}else{
			defs.push_back(def);

			def = "";
		}
	}

	if(def != "")
	{
		defs.push_back(def);
	}

	return defs;
}

void clear()
{
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

std::string tolower(std::string word)
{
	std::string result = "";

	for(char c : word)
	{
		result += std::tolower(c);
	}

	return result;
}

Word* parse(std::string line,std::string userSearch)
{
	std::vector<std::string> splittedLine;

	std::string content = "";
	int column = 0;
	for(int i = 0;i < line.length();++i)
		{
		if(column != 2)
		{
			if(line[i] != ',')
			{
				content += line[i];
			}else
			{

				splittedLine.push_back(content);
				content = "";
				column++;
			}
		}else{
			content += line[i];
		}
	}
	splittedLine.push_back(content);

	//checks if it match the userSearch
	if(tolower(splittedLine[0]) == tolower(userSearch))
	{
		return new Word(
				splittedLine[0],
				splittedLine[1],
				parseDef(splittedLine[2]));
	}

	return NULL;
}

std::string getWordInput()
{
	std::string word;
	
	std::cin >> word;

	return word;
}

void search()
{
	clear();
	std::cout << "Please enter what you want to search: ";

	std::string userSearch = getWordInput();

	std::vector< Word* > results;

	std::ifstream file("english Dictionary.csv");

	std::string line;

	while(std::getline(file,line))
	{
		Word* result = parse(line,userSearch);
		if(result != nullptr) results.push_back(result);
	}

	file.close();

	std::cout << "There are " << results.size() << " result matching " << userSearch << std::endl;

	for(int i = 0;i < results.size();++i)
	{
		std::cout << std::endl;
		std::cout << i + 1 << ". " << results[i]->getWord() << "; " << results[i]->getPos() << std::endl;

		results[i]->printDef();
		std::cout << std::endl;
	}

	//halt execution
	std::cout << "Press any key to continue: ";
	std::cin.ignore();
	std::cin.get();

	for(Word* p : results)
	{
		delete p;
	}

	results.clear();
}

void quit()
{
	std::cout << "Quitting..." << std::endl;
	exit(0);
}

//function pointers
typedef void (*myFunc)();

void printMenu()
{
	//clear the screen;
	clear();

	std::cout << "Welcome to the english dictionary" << std::endl;
	std::cout << "Please enter the number coresponding to the operation that you want to perform" << std::endl;
	std::cout << std::endl << "1 - Search" << std::endl;
	std::cout << "2 - Quit" << std::endl;

	//The maximum number of choices
	int max = 2;
	std::map<int,myFunc> validC;

	validC[1] = search;
	validC[2] = quit;

	//get Input
	int choice = getMenuChoice();

	//process input
	if(choice > 0 && choice <= max)
	{
		validC[choice]();
	}
}

int getMenuChoice()
{
	int n;

	std::cout << "Enter Option: ";

	if(std::cin >> n)
	{
		return n;
	}else{
		std::cout << std::endl << "Only number is allowed here." << std::endl;
		std::cin.clear();
		std::cin.ignore();
	}

	return getMenuChoice();
}

int main()
{

	while(true)
	{
		printMenu();
	}
//

	return 0;
}
