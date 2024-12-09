#pragma once

#include <string>
#include <vector>

class Word
{
	public:
		Word(
				std::string p_word,
				std::string p_pos,
				std::vector<std::string> p_def);
		std::string getWord();
		std::vector<std::string> getDef();
		std::string getPos();
		void printDef();

	private:
		std::string word;
		std::string pos;
		std::vector<std::string> def;
};
