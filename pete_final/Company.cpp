#include "Company.h"



CCompany::CCompany()
{
	// Generate the menus for a company
	generateMenus();

	// Show the edit menu for the company
	getContactInformation();
}

CCompany::CCompany(bool notDefault)
{
	// Generate the menus for a company
	generateMenus();
}


CCompany::~CCompany()
{
}

// This is used when outputting to files
string CCompany::classType() const
{
	return "CCompany";
}

// Show the edit menu
void CCompany::getContactInformation()
{
	bool exit = false;

	while (!exit)
	{
		char mainMenuChoice = CUserInterface::displayMenu(contactMenu);

		switch (mainMenuChoice)
		{
		case 'A':
		{
			name = CUserInterface::getUserInput("Company name: ");
			break;
		}
		case 'B':
		{
			getPhoneNumbers();
			break;
		}
		case 'C':
		{
			getFaxNumbers();
			break;
		}
		case 'D':
		{
			getEmailAddresses();
			break;
		}
		case 'E':
		{
			address = CUserInterface::getUserInput("Address: ");
			break;
		}
		case 'F':
		{
			hours = CUserInterface::getUserInput("Hours: ");
			break;
		}
		case 'G':
		{
			website = CUserInterface::getUserInput("Website: ");
			break;
		}
		case 'H':
			exit = true;
			break;
		}
	}
}

// Make the menus for the company
void CCompany::generateMenus()
{
	contactMenu.addMenuOption('A', "Enter name");
	contactMenu.addMenuOption('B', "Edit phone numbers");
	contactMenu.addMenuOption('C', "Edit fax numbers");
	contactMenu.addMenuOption('D', "Edit email addresses");
	contactMenu.addMenuOption('E', "Enter address");
	contactMenu.addMenuOption('F', "Enter hours");
	contactMenu.addMenuOption('G', "Enter website");
	contactMenu.addMenuOption('H', "Finish editing contact");

	phoneNumberMenu.addMenuOption('A', "Add phone number");
	phoneNumberMenu.addMenuOption('B', "Remove phone number");
	phoneNumberMenu.addMenuOption('C', "Return to previous menu");

	faxNumberMenu.addMenuOption('A', "Add fax number");
	faxNumberMenu.addMenuOption('B', "Remove fax number");
	faxNumberMenu.addMenuOption('C', "Return to previous menu");

	emailAddressMenu.addMenuOption('A', "Add email address");
	emailAddressMenu.addMenuOption('B', "Remove email address");
	emailAddressMenu.addMenuOption('C', "Return to previous menu");
}

void CCompany::getPhoneNumbers()
{
	CUserInterface::displaySubMenu(phoneNumberMenu, phoneNumbers, "phone number");
}

void CCompany::getFaxNumbers()
{
	CUserInterface::displaySubMenu(faxNumberMenu, faxNumbers, "fax number");
}

void CCompany::getEmailAddresses()
{
	CUserInterface::displaySubMenu(emailAddressMenu, emailAddresses, "email address");
}

// Display every piece of information about a company
void CCompany::display()
{
	cout << "            Name:  " << name << "\n";
	cout << "   Phone Numbers:  " << (phoneNumbers.begin() == phoneNumbers.end() ? "\n" : "");
	for (vector<string>::const_iterator it = phoneNumbers.begin(); it != phoneNumbers.end(); ++it)
	{
		if (it != phoneNumbers.begin())
		{
			cout << "                   ";
		}

		cout << (*it) << "\n";
	}
	cout << "     Fax Numbers:  " << (faxNumbers.begin() == faxNumbers.end() ? "\n" : "");
	for (vector<string>::const_iterator it = faxNumbers.begin(); it != faxNumbers.end(); ++it)
	{
		if (it != faxNumbers.begin())
		{
			cout << "                   ";
		}

		cout << (*it) << "\n";
	}
	cout << " Email Addresses:  " << (emailAddresses.begin() == emailAddresses.end() ? "\n" : "");
	for (vector<string>::const_iterator it = emailAddresses.begin(); it != emailAddresses.end(); ++it)
	{
		if (it != emailAddresses.begin())
		{
			cout << "                   ";
		}

		cout << (*it) << "\n";
	}
	cout << "         Address:  " << address << "\n";
	cout << "           Hours:  " << hours << "\n";
	cout << "         Website:  " << website << endl << endl;
}

// Display just the name of the person
void CCompany::displayName()
{
	cout << "\t" << name << endl;
}

// Check if what was entered is the company name
bool CCompany::contains(string & someName)
{
	return boost::algorithm::to_upper_copy(name) == boost::algorithm::to_upper_copy(someName);
}

// Check if the name is equal to what was on the right
bool CCompany::operator==(const string inName) const
{
	return name == inName;
}

// Name to sort by. Just the name in this case
string CCompany::getSortableName() const
{
	return name;
}

// Ghetto greater than function because of class inheritance
bool CCompany::greater(CContact & right)
{
	return (getSortableName() > right.getSortableName());
}

// Serialize the class and save it to an archive
void CCompany::save(boost::archive::text_oarchive & ar, const unsigned int version) const
{
	ar << name;
	ar << phoneNumbers;
	ar << faxNumbers;
	ar << emailAddresses;
	ar << address;
	ar << hours;
	ar << website;
}

// Unserialize the class and load it into memory
void CCompany::load(boost::archive::text_iarchive & ar, const unsigned int version)
{
	ar >> name;
	ar >> phoneNumbers;
	ar >> faxNumbers;
	ar >> emailAddresses;
	ar >> address;
	ar >> hours;
	ar >> website;
}
