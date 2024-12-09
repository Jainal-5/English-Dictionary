
#include "Word.h"
#include <string>
#include <vector>
#include <iostream>

Word::Word(std::string p_word,
		std::string p_pos,
		std::vector<std::string> p_def) 
	:word(p_word),
	 pos(p_pos),
	 def(p_def)
{
	
}

std::string Word::getWord()
{
	return word;
}

std::string Word::getPos()
{
	return pos;
}

std::vector<std::string> Word::getDef()
{
	return def;
}

void Word::printDef()
{
	for(std::string _def : this->def)
	{
		std::cout << "\t" << _def << ";" <<  std::endl;
	}
}
