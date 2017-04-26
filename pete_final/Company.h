#pragma once

#include <string>
#include <vector>

#include "Contact.h"
#include "UserInterface.h"

#include <boost\algorithm\string\case_conv.hpp>

using namespace std;

class CCompany :
	public CContact
{
public:
	CCompany();
	CCompany(bool notDefault);
	~CCompany();

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
	string name;
	vector<string> phoneNumbers;
	vector<string> faxNumbers;
	vector<string> emailAddresses;
	string address;
	string hours;
	string website;

	void generateMenus();

	void getPhoneNumbers();
	void getFaxNumbers();
	void getEmailAddresses();

	// Ghetto greater than function because of inheritance
	bool greater(CContact & right);
};

