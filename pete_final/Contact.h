#pragma once

#include <string>
#include <boost\archive\text_iarchive.hpp>
#include <boost\archive\text_oarchive.hpp>
#include <boost\serialization\string.hpp>
#include <boost\serialization\vector.hpp>

#include "CustomMenu.h"

class CContact
{
public:
	CContact();
	virtual ~CContact();
	virtual string classType() const = 0;
	virtual void display() = 0;
	virtual void displayName() = 0;
	virtual void getContactInformation() = 0;
	virtual bool contains(string & someName) = 0;
	virtual bool operator==(const string inName) const = 0;
	virtual std::string getSortableName() const = 0;
	friend bool operator>(CContact & lhs, CContact & rhs)
	{
		return lhs.greater(rhs);
	}

protected:
	friend class boost::serialization::access;

	virtual void generateMenus() = 0;

	CCustomMenu contactMenu;
	CCustomMenu phoneNumberMenu;
	CCustomMenu faxNumberMenu;
	CCustomMenu emailAddressMenu;

	virtual bool greater(CContact & right) = 0;

	// These need to be split into 2 functions because having 1 function requires it to be templated
	// which doesn't work with class inheritance too well
	virtual void save(boost::archive::text_oarchive & ar, const unsigned int version) const = 0;
	virtual void load(boost::archive::text_iarchive & ar, const unsigned int version) = 0;

	BOOST_SERIALIZATION_SPLIT_MEMBER()
};
