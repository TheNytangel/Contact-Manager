#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CCustomMenu
{
private:
	struct Option
	{
		char letter;
		string text;

		// Used for algorithm::find()
		bool operator == (const char & rightSide) const
		{
			return this->letter == rightSide;
		}
		// Used for algorithm::sort()
		bool operator < (const Option & rightSide) const
		{
			return this->letter < rightSide.letter;
		}
	};

	vector<Option> optionList;

public:
	CCustomMenu();
	~CCustomMenu();
	bool addMenuOption(char letter, string text);
	void displayMenuOptions();
	bool contains(char letter);
};

