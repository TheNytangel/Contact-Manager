#include "Person.h"



CPerson::CPerson()
{
	// Generate the menus for a person
	generateMenus();

	// Show the edit menu for the person
	getContactInformation();
}

CPerson::CPerson(bool notDefault)
{
	// Generate the menus for a person
	generateMenus();
}


CPerson::~CPerson()
{
}

// This is used when outputting to files
string CPerson::classType() const
{
	return "CPerson";
}

// Display every piece of information about a person
void CPerson::display()
{
	cout << "            Name:  " << firstName << " " << lastName << "\n";
	cout << "         Company:  " << company << "\n";

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

	cout << "       Addresses:  " << (addresses.begin() == addresses.end() ? "\n" : "");
	for (vector<string>::const_iterator it = addresses.begin(); it != addresses.end(); ++it)
	{
		if (it != addresses.begin())
		{
			cout << "                   ";
		}

		cout << (*it) << "\n";
	}

	cout << "        Birthday:  " << birthday << "\n";
	cout << "         Website:  " << website << endl << endl;
}

// Display just the name of the person
void CPerson::displayName()
{
	cout << "\t" << firstName << " " << lastName << endl;
}

// Show the edit menu
void CPerson::getContactInformation()
{
	bool exit = false;

	while (!exit)
	{
		char mainMenuChoice = CUserInterface::displayMenu(contactMenu);

		// Edit each piece of information based on what the user chose
		switch (mainMenuChoice)
		{
		case 'A':
		{
			firstName = CUserInterface::getUserInput("First name: ");
			lastName = CUserInterface::getUserInput("Last name: ");
			break;
		}
		case 'B':
		{
			company = CUserInterface::getUserInput("Company: ");
			break;
		}
		case 'C':
		{
			getPhoneNumbers();
			break;
		}
		case 'D':
		{
			getFaxNumbers();
			break;
		}
		case 'E':
		{
			getEmailAddresses();
			break;
		}
		case 'F':
		{
			getAddresses();
			break;
		}
		case 'G':
		{
			birthday = CUserInterface::getUserInput("Birthday: ");
			break;
		}
		case 'H':
		{
			website = CUserInterface::getUserInput("Website: ");
			break;
		}
		case 'I':
			exit = true;
			break;
		}
	}
}

// Check if the name is equal to what was on the right
bool CPerson::operator==(const string inName) const
{
	return (firstName + " " + lastName) == inName;
}

// Check if what was entered is anywhere in the names
bool CPerson::contains(string & someName)
{
	return (boost::algorithm::to_upper_copy(someName) == boost::algorithm::to_upper_copy(firstName)
			|| boost::algorithm::to_upper_copy(someName) == boost::algorithm::to_upper_copy(lastName)
			|| boost::algorithm::to_upper_copy(someName) == boost::algorithm::to_upper_copy(firstName + " " + lastName));
}

// Make the menus for the person
void CPerson::generateMenus()
{
	contactMenu.addMenuOption('A', "Enter name");
	contactMenu.addMenuOption('B', "Enter company");
	contactMenu.addMenuOption('C', "Edit phone numbers");
	contactMenu.addMenuOption('D', "Edit fax numbers");
	contactMenu.addMenuOption('E', "Edit email addresses");
	contactMenu.addMenuOption('F', "Edit addresses");
	contactMenu.addMenuOption('G', "Enter birthday");
	contactMenu.addMenuOption('H', "Enter website");
	contactMenu.addMenuOption('I', "Finish editing contact");

	phoneNumberMenu.addMenuOption('A', "Add phone number");
	phoneNumberMenu.addMenuOption('B', "Remove phone number");
	phoneNumberMenu.addMenuOption('C', "Return to previous menu");

	faxNumberMenu.addMenuOption('A', "Add fax number");
	faxNumberMenu.addMenuOption('B', "Remove fax number");
	faxNumberMenu.addMenuOption('C', "Return to previous menu");

	emailAddressMenu.addMenuOption('A', "Add email address");
	emailAddressMenu.addMenuOption('B', "Remove email address");
	emailAddressMenu.addMenuOption('C', "Return to previous menu");

	addressMenu.addMenuOption('A', "Add address");
	addressMenu.addMenuOption('B', "Remove address");
	addressMenu.addMenuOption('C', "Return to previous menu");
}

void CPerson::getPhoneNumbers()
{
	CUserInterface::displaySubMenu(phoneNumberMenu, phoneNumbers, "phone number");
}

void CPerson::getFaxNumbers()
{
	CUserInterface::displaySubMenu(faxNumberMenu, faxNumbers, "fax number");
}

void CPerson::getEmailAddresses()
{
	CUserInterface::displaySubMenu(emailAddressMenu, emailAddresses, "email address");
}

void CPerson::getAddresses()
{
	CUserInterface::displaySubMenu(addressMenu, addresses, "address");
}

// Name to sort by. "FirstName Lastname"
string CPerson::getSortableName() const
{
	return firstName + " " + lastName;
}

// Ghetto greater than function because of class inheritance
bool CPerson::greater(CContact & right)
{
	return (getSortableName() > right.getSortableName());
}

// Serialize the class and save it to an archive
void CPerson::save(boost::archive::text_oarchive & ar, const unsigned int version) const
{
	ar << firstName;
	ar << lastName;
	ar << company;
	ar << phoneNumbers;
	ar << faxNumbers;
	ar << emailAddresses;
	ar << addresses;
	ar << birthday;
	ar << website;
}

// Unserialize the class and load it into memory
void CPerson::load(boost::archive::text_iarchive & ar, const unsigned int version)
{
	ar >> firstName;
	ar >> lastName;
	ar >> company;
	ar >> phoneNumbers;
	ar >> faxNumbers;
	ar >> emailAddresses;
	ar >> addresses;
	ar >> birthday;
	ar >> website;
}
