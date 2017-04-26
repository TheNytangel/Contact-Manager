#include "UserInterface.h"


CUserInterface::CUserInterface()
{
	// Construct the menu options
	mainMenu.addMenuOption('A', "Add a contact");
	mainMenu.addMenuOption('B', "Remove a contact");
	mainMenu.addMenuOption('C', "Edit a contact");
	mainMenu.addMenuOption('D', "Search for a contact");
	mainMenu.addMenuOption('E', "Display all contacts");
	mainMenu.addMenuOption('F', "Exit");

	personOrCompanyMenu.addMenuOption('A', "Person");
	personOrCompanyMenu.addMenuOption('B', "Company");
	personOrCompanyMenu.addMenuOption('C', "Return to previous menu");
}


CUserInterface::~CUserInterface()
{
}


// A function to display the name, description, and instructions for the application
void CUserInterface::displayStartScreen()
{
	system("cls");

	cout << "+-----------------------------+" << "\n"
		 << "|                             |" << "\n"
		 << "|   Chris's Contact Manager   |" << "\n"
		 << "|                             |" << "\n"
		 << "+-----------------------------+" << endl;

	cout << endl << "Description:" << "\n" << "This is a contact manager. It stores and manages contacts." << endl;

	cout << endl << "Instructions:" << "\n" << "Navigate through the menus to add, remove, edit, and search for contacts. It automatically saves the contacts to a file every time a new one is added, edited, or removed, and loads them from a file when the program runs." << endl << endl;

	system("pause");
	system("cls");
}


// A function for displaying a main menu and getting the option the user chose
char CUserInterface::displayMainMenu()
{
	return CUserInterface::displayMenu(mainMenu);
}

// Whether the user wants to add a person or a company
char CUserInterface::displayContactChoiceMenu()
{
	return CUserInterface::displayMenu(personOrCompanyMenu);
}

// Function to display a custom menu
char CUserInterface::displayMenu(CCustomMenu & menu)
{
	system("cls");

	cout << "What would you like to do?" << endl << endl;

	// Display the options in the menu
	menu.displayMenuOptions();

	cout << endl << endl << "> ";

	char userInput;

	// Prompt the user for input
	do
	{
		cin >> userInput;
		cin.ignore(256, '\n');
		userInput = toupper(userInput);

		// If the menu doesn't contain the letter option that the user entered, output an error message and loop again
		if (!menu.contains(userInput))
		{
			cout << "Please enter a letter displayed in the list" << endl << "> ";
		}
	} while (!menu.contains(userInput));

	return userInput;
}

// Same thing as a menu, but also displays a vector of strings to choose from
void CUserInterface::displaySubMenu(CCustomMenu & menu, vector<string> & vectorOfItems, string type)
{
	bool exit = false;

	while (!exit)
	{
		char menuChoice = CUserInterface::displayMenu(menu);

		switch (menuChoice)
		{
			// Add a new "type" to the vector of strings (could be phone number/fax number/email address/address
		case 'A':
		{
			vectorOfItems.push_back(CUserInterface::getUserInput("New " + type + ": "));
			break;
		}
			// Remove something from the vector
		case 'B':
		{
			// Check if any strings even exist
			if (vectorOfItems.size() == 0)
			{
				cout << "You don't have any " << type << (type.back() == 's' ? "es" : "s") << " to remove" << endl;
				system("pause");
				break;
			}

			// Display everything so the user has something to choose from
			CUserInterface::displayVector<string>(vectorOfItems);

			// Prompt the user for which item the user wants to remove
			string itemToRemove = CUserInterface::getUserInput("Which " + type + " would you like to remove? ");
			// Try to find the string in the vector
			vector<string>::iterator foundItem = find(vectorOfItems.begin(), vectorOfItems.end(), itemToRemove);

			// If the iterator reached the end, the thing the user entered wasn't found
			if (foundItem == vectorOfItems.end())
			{
				cout << endl << "That " + type + " was not found" << endl;
				system("pause");
				break;
			}

			// It was found, so erase it
			vectorOfItems.erase(foundItem);

			// Give the user feedback that it was removed
			cout << endl << "The " + type + " was removed" << endl;

			system("pause");

			break;
		}
			// Return to previous menu
		case 'C':
		{
			exit = true;
			break;
		}
		}
	}
}

// Function to get user input
string CUserInterface::getUserInput(string message)
{
	string userInput;

	cout << message;

	getline(cin, userInput);

	return userInput;
}
