#pragma once

#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "BubbleSort.h"

#include <boost\archive\text_iarchive.hpp>
#include <boost\archive\text_oarchive.hpp>

using namespace std;

void updateContactLists(vector<shared_ptr<CContact>> & contactList, string & contactFileName)
{
	// Sort the list
	Chris::sort(contactList);

	// Output files for companies and people
	ofstream companiesFile(contactFileName + "Companies.txt", ios_base::trunc);
	ofstream peopleFile(contactFileName + "People.txt", ios_base::trunc);

	// Boost archive text files for both types of contacts
	boost::archive::text_oarchive companies(companiesFile);
	boost::archive::text_oarchive people(peopleFile);

	// Save the list to a file
	for (vector<shared_ptr<CContact>>::iterator it = contactList.begin(); it != contactList.end(); ++it)
	{
		// If it's a person, save it to the person file
		if ((*it)->classType() == "CPerson")
		{
			people << *(*it);
		}
		// If it's a company, save it to the company file
		else if ((*it)->classType() == "CCompany")
		{
			companies << *(*it);
		}
	}
}

// Uses a pointer to the contact list instead of a reference because threads don't work with references
void getContactList(vector<shared_ptr<CContact>> * contactList, string & contactFileName)
{
	// Try to open the file and read the archive. If it doesn't exist, it throws an exception
	try
	{
		ifstream companiesFile(contactFileName + "Companies.txt", ios_base::in);

		boost::archive::text_iarchive companies(companiesFile);

		try
		{
			// Infinitely read the archive. It throws an exception when there's nothing left to read
			while (true)
			{
				// Make the pointer to the company, (try) get everything from the archive, then add it to the contact list
				shared_ptr<CContact> tempCompany = make_shared<CCompany>(true);
				companies >> *tempCompany;
				contactList->push_back(tempCompany);
			}
		}
		// Nothing needs to be done with the exceptions. Either the file doesn't exist
		// and it doesn't matter, or it reached the end of the file and it doesn't matter
		catch (...)
		{
		}
	}
	catch (...)
	{
	}

	// Try to open the file and read the archive. If it doesn't exist, it throws an exception
	try
	{
		ifstream peopleFile(contactFileName + "People.txt", ios_base::in);

		boost::archive::text_iarchive people(peopleFile);

		try
		{
			// Infinitely read the archive. It throws an exception when there's nothing left to read
			while (true)
			{
				// Make the pointer to the person, (try) get everything from the archive, then add it to the contact list
				shared_ptr<CContact> tempPerson = make_shared<CPerson>(true);
				people >> *tempPerson;
				contactList->push_back(tempPerson);
			}
		}
		// Nothing needs to be done with the exceptions. Either the file doesn't exist
		// and it doesn't matter, or it reached the end of the file and it doesn't matter
		catch (...)
		{
		}
	}
	catch (...)
	{
	}

	// Sort the list once everything has been imported from the files
	Chris::sort(*contactList);
}
