/*
	Christopher Peterson
	3/25/17
	Final Project - Contact Manager
*/

#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include "UserInterface.h"
#include "Contact.h"
#include "Company.h"
#include "Person.h"
#include "ContactList.h"

using namespace std;

int main()
{
	// User interface for the main menu and splash screen
	CUserInterface UI;
	// Uses a pointer to a contact so that it can store both CPerson and CCompany contacts
	vector<shared_ptr<CContact>> contactList;
	// Prefix for person and company contact files
	string contactFileName = "contactList";

	// Get the contact list from the files
	// Run this in a thread while the splash screen shows
	thread contactListFromFile(getContactList, &contactList, contactFileName);

	// Display the splash screen
	UI.displayStartScreen();

	// Join the thread so once the file finishes loading the menu gets displayed
	contactListFromFile.join();

	bool exit = false;
	while (!exit)
	{
		// Get the menu choice from the user
		char menuChoice = UI.displayMainMenu();

		switch (menuChoice) {
		// Add a contact
		case 'A':
		{
			// Prompt the user for the submenu choice (person or company)
			char subMenuChoice = UI.displayContactChoiceMenu();

			switch (subMenuChoice)
			{
				// Add a person
			case 'A':
				contactList.push_back(make_shared<CPerson>());
				updateContactLists(contactList, contactFileName);
				break;
				// Add a company
			case 'B':
				contactList.push_back(make_shared<CCompany>());
				updateContactLists(contactList, contactFileName);
				break;
				// Go back
			case 'C':
				break;
			}

			break;
		}
		// Remove a contact
		case 'B':
		{
			// Check if any contacts even exist
			if (contactList.size() == 0)
			{
				cout << "You don't have any contacts to remove" << endl;
				system("pause");
				break;
			}

			cout << endl;

			// Display all the contacts so the user can choose from one
			for (vector<shared_ptr<CContact>>::iterator it = contactList.begin(); it != contactList.end(); ++it)
			{
				(*it)->displayName();
			}

			cout << endl;

			// Prompt the user for the name of the contact they want to remove
			string contactName = CUserInterface::getUserInput("Enter the name of the person or company you would like to remove from the contact list:\n");

			// Set the "found contact" to the end of the vector
			vector<shared_ptr<CContact>>::iterator foundContact = contactList.end();

			// Loop through the vector and try to find what the user entered
			for (vector<shared_ptr<CContact>>::iterator it = contactList.begin(); it != contactList.end(); ++it)
			{
				// If the contact was found, set the "found contact" iterator to the current iterator
				if (*(*it) == contactName)
				{
					foundContact = it;
					break;
				}
			}

			// The contact wasn't found because "found contact" is still set to the end of the vector
			if (foundContact == contactList.end())
			{
				cout << endl << "That contact was not found in your contact list" << endl;
				system("pause");
				break;
			}

			// Erase the contact if it was found
			contactList.erase(foundContact);

			// Update the saved contact list now
			updateContactLists(contactList, contactFileName);

			cout << endl << "The contact was removed from your contact list" << endl;

			system("pause");
			break;
		}
		// Edit a contact
		case 'C':
		{
			// Check if any contacts even exist
			if (contactList.size() == 0)
			{
				cout << "You don't have any contacts to edit" << endl;
				system("pause");
				break;
			}

			cout << endl;

			// Display all the contacts so the user can pick from them to edit
			for (vector<shared_ptr<CContact>>::iterator it = contactList.begin(); it != contactList.end(); ++it)
			{
				(*it)->displayName();
			}

			cout << endl;

			// Prompt the user for the name of the contact to edit
			string contactName = CUserInterface::getUserInput("Enter the name of the person or company you would like to edit:\n");

			// Set the "found contact" to the end of the vector
			vector<shared_ptr<CContact>>::iterator foundContact = contactList.end();

			// Loop through the vector and try to find what the user entered
			for (vector<shared_ptr<CContact>>::iterator it = contactList.begin(); it != contactList.end(); ++it)
			{
				// If the contact was found, set the "found contact" iterator to the current iterator
				if (*(*it) == contactName)
				{
					foundContact = it;
					break;
				}
			}

			// The contact wasn't found because "found contact" is still set to the end of the vector
			if (foundContact == contactList.end())
			{
				cout << endl << "That contact was not found in your contact list" << endl;
				system("pause");
				break;
			}

			// Open the menu to edit contact information
			(*foundContact)->getContactInformation();

			// Sort the vector again in case the name changed. Also save new information to the file
			updateContactLists(contactList, contactFileName);
			
			break;
		}
		// Search for a contact
		case 'D':
		{
			system("cls");
			cout << "Enter the first name, last name, or company name of a contact:" << endl;

			// Get the name of the contact to find
			string contactName;
			getline(cin, contactName);

			cout << endl << "Found contacts:" << endl;

			bool found = false;

			// Loop through the vector and check to see if any of the contact names contain something the user entered
			// This could be first name, last name, first name + last name, or company name
			for (vector<shared_ptr<CContact>>::const_iterator it = contactList.begin(); it != contactList.end(); ++it)
			{
				if ((*it)->contains(contactName))
				{
					(*it)->displayName();
					found = true;
				}
			}

			// Nothing was found so display "none"
			if (!found)
			{
				cout << "None" << endl << endl;
			}
			
			cout << endl;

			system("pause");

			break;
		}
		// Display contacts
		case 'E':
		{
			system("cls");

			// Check if any contacts even exist
			if (contactList.size() == 0)
			{
				cout << "You don't have any contacts to display" << endl;
				system("pause");
				break;
			}

			cout << endl;

			// Loop through the contacts and display all of them
			for (vector<shared_ptr<CContact>>::iterator it = contactList.begin(); it != contactList.end(); ++it)
			{
				(*it)->display();
			}

			system("pause");

			break;
		}
		case 'F':
			exit = true;
			break;
		}
	}

	cout << endl << "Goodbye!" << endl;
	system("pause");
	return 0;
}
