#pragma once

#include "CustomMenu.h"

#include <iostream>
#include <string>

using namespace std;

class CUserInterface
{
private:
	CCustomMenu mainMenu;
	CCustomMenu personOrCompanyMenu;

public:
	CUserInterface();
	~CUserInterface();
	// A function to display the name, description, and instructions for the application
	void displayStartScreen();
	// A function for displaying a main menu and getting the option the user chose
	char displayMainMenu();
	char displayContactChoiceMenu();

	static char displayMenu(CCustomMenu & menu);
	static void displaySubMenu(CCustomMenu & menu, vector<string> & vectorOfItems, string type);
	static string getUserInput(string message);

	// Templated function to display everything in a vector. Usually strings.
	template <typename vect>
	static void displayVector(vector<vect> & vectorToDisplay)
	{
		cout << endl;

		for (vector<vect>::const_iterator it = vectorToDisplay.begin(); it != vectorToDisplay.end(); ++it)
		{
			cout << "\t" << *it << endl;
		}
		
		cout << endl;
	}
};

