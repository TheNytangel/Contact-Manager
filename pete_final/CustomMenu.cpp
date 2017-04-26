#include "CustomMenu.h"



CCustomMenu::CCustomMenu()
{
}


CCustomMenu::~CCustomMenu()
{
}


bool CCustomMenu::addMenuOption(char letter, string text)
{
	// Make sure letter is uppercase
	letter = toupper(letter);

	// Check if an option with that letter already exists
	if (find(optionList.begin(), optionList.end(), letter) != optionList.end())
	{
		return false;
	}

	// Make a new temporary option variable that will be added to the vector
	Option newOption;
	newOption.letter = letter;
	newOption.text = text;

	// Add the new option
	optionList.push_back(newOption);

	// Sort the list so it is in alphabetical order
	sort(optionList.begin(), optionList.end());

	return true;
}

void CCustomMenu::displayMenuOptions()
{
	// Loop through the added options
	for (vector<Option>::const_iterator it = optionList.begin(); it != optionList.end(); ++it)
	{
		// Display the option
		cout << "\t" << it->letter << ")  " << it->text;

		// If the option being displayed isn't the last one, add a newline
		if (it != optionList.end())
		{
			cout << endl;
		}
	}
}


bool CCustomMenu::contains(char letter)
{
	// Make sure letter is uppercase
	letter = toupper(letter);

	// Check if it can find the inputted value in the menu option list
	return find(optionList.begin(), optionList.end(), letter) != optionList.end();
}
