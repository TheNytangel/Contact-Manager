#pragma once

#include <string>
#include <vector>

#include "Contact.h"
#include "UserInterface.h"

#include <boost\algorithm\string\case_conv.hpp>

using namespace std;

class CPerson :
	public CContact
{
public:
	CPerson();
	CPerson(bool notDefault);
	~CPerson();

	string classType() const;

	void display();
	void displayName();
	void getContactInformation();
	bool contains(string & someName);
	bool operator==(const string inName) const;

	// Name that is used to sort the contacts
	string getSortableName() const;

	// These need to be split into 2 functions because having 1 function requires it to be templated
	// which doesn't work with class inheritance too well
	void save(boost::archive::text_oarchive & ar, const unsigned int version) const;
	void load(boost::archive::text_iarchive & ar, const unsigned int version);

	BOOST_SERIALIZATION_SPLIT_MEMBER()

private:
	string firstName;
	string lastName;
	string company;
	vector<string> phoneNumbers;
	vector<string> faxNumbers;
	vector<string> emailAddresses;
	vector<string> addresses;
	string birthday;
	string website;

	void generateMenus();

	CCustomMenu addressMenu;

	void getPhoneNumbers();
	void getFaxNumbers();
	void getEmailAddresses();
	void getAddresses();

	// Ghetto greater than function because of inheritance
	bool greater(CContact & right);
};

