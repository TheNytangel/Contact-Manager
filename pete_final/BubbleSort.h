#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Contact.h"

using namespace std;

namespace Chris
{
	// Bubble sort (short bubble)
	void sort(vector<shared_ptr<CContact>> & sortVector)
	{
		// This will allow the algorithm to not go through excess loops
		bool swapHappened = true;

		// This is the loop for the max number of times it will need to try sort
		for (unsigned int i = 0; i < sortVector.size() && swapHappened; ++i)
		{
			// A swap has not happened yet this iteration
			swapHappened = false;
			// Loop through the vector, but not up to the last one since when it sorts it does n+1
			for (vector<shared_ptr<CContact>>::iterator newIt = sortVector.begin(); newIt != sortVector.end() - 1; ++newIt)
			{
				// Check if the value inside the pointer was greater than the next value
				if (*(*newIt) > *(*(newIt + 1)))
				{
					// Swap the two
					shared_ptr<CContact> tempPtr = *newIt;
					*newIt = *(newIt + 1);
					*(newIt + 1) = tempPtr;

					// A swap happened, so it can't stop looping yet
					swapHappened = true;
				}
			}
		}
	}
}
