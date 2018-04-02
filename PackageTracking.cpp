//
//  PackageTracking.cpp
//  Project2
//
//  Created by Han, Wenlin on 2/13/18.
//  Copyright © 2018 Han, Wenlin. All rights reserved.
//

#include "PackageTracking.h"
#include <iostream>
#include <string>

PackageTracking::PackageTracking(const string& strnum)//Constructor that takes in the package's tracking number and then sends it to
	                                             //m_readTrackingFile so it can be read.
{
	/*string filename = strnum + ".txt";
	m_readTrackingFile(filename);*/
}

// adds a new update by creating an obeject s of ShippingStatus and pushing it the front of the list. Everytime this function is called
//it points temp to the top of the stack.
void PackageTracking::m_addUpdate(const string& status, const string& location, const time_t& timeUpdated) 
{
	ShippingStatus s(status, location, timeUpdated);
	mylist.push_front(s); 
	temp = mylist.begin();
	n++;//variable to keep track of the number of updates.
}

bool PackageTracking::m_moveBackward()//move iterator one step earlier in time
{
	if (mylist.empty())			//Checks if list is empty, if empty returns false
	{
		throw std::length_error("List is empty!");
		return false;
	}

	else if (temp == mylist.end())		//Checks if iterator is at the earliest shipping status
	{
		throw std::invalid_argument("You are at the earliest shipping update!");
		return false;
	}

	else
	{
		temp++;				//Moves iterator to earlier shipping status
		return true;
	}
	
	
}

bool PackageTracking::m_moveForward()//move iterator one step forward in time
{
	if (temp == mylist.begin())			//If at the beginning of list, throws error message and false
	{
		throw std::invalid_argument("You are at the most recent shipping update!");
		return false;
	}

	else if (mylist.empty())			//If list is empty, returns error message and false
	{
		throw std::length_error("List is empty!");
		return false;
	}
	else
	{
		temp--;
		return true;				//Iterates backwards once
	}
}

string PackageTracking::m_getLocation()//return the location of the current update
{
	if (mylist.empty()) throw std::length_error("List is empty!");		//Checks if list is empty, if not return location
	return temp->_location;
}

time_t PackageTracking::m_getTime()//return the time of the current update
{
	if (mylist.empty()) throw std::length_error("List is empty!");		//Checks if list is empty, if not return time
	return temp->_time;
}

string PackageTracking::m_getStatus()//return the status of the current update
{
	if (mylist.empty()) throw std::length_error("List is empty!");		//Checks if list is empty, if not return status
	return temp->_status;
}

int PackageTracking::m_getNumofUpdate() const // get the total numbers of shipping status updates
{
	return n;		//Return private variable n that counts the number of updates
}

void PackageTracking::m_printPreviousUpdates() //print all previous updates in the shipping chain when the package was shipped, all the way up to (but not including) the current update you are viewing (may not be the most recent update)
{
	if (mylist.empty()) throw std::length_error("List is empty!");			//Checks if list is empty, if empty throws error message
	list<ShippingStatus>::iterator it = temp;					//Creates local iterator and initializes to location of temp
	while (it != mylist.end())							
	{
		it++;
		if (it != mylist.end())
		{
			//Outputs values at each shipping status object until the beginning of the list
			cout << "Status:" << it->_status << "\nLocation:" << it->_location << "\nTime:" << it->_time << endl << endl;
		}
		else if (it == mylist.end())
			break;
		
	}
	
}

//print all updates from the current update you are viewing to the last update in the tracking chain
void PackageTracking::m_printFollowingUpdates()
{
	if (mylist.empty()) throw std::length_error("List is empty!");		//Checks if list is empty, if empty throws error message
	list<ShippingStatus>::iterator it = temp;				//Creates local iterator and initializes to location of temp
	while (it != mylist.begin())
	{
		//Outputs values at each shipping status object until it reaches the end of the list
		cout << "Status:" << it->_status << "\nLocation:" << it->_location << "\nTime:" << it->_time << endl << endl;
		it--;
	}
		//Outputs the last shipping status object
	cout << "Status:" << it->_status << "\nLocation:" << it->_location << "\nTime:" << it->_time << endl;
}

void PackageTracking::m_printFullTracking()//print all the updates in the tracking chain.
{
	if (mylist.empty()) throw std::length_error("List is empty!");
	list<ShippingStatus>::iterator it = mylist.begin();
	while (it != mylist.end())
	{
		//Outputs entire shipping status history for a tracking number
		cout << "Status:" << it->_status << "\nLocation:" << it->_location << "\nTime:" << it->_time << endl <<endl;
		it++;
	}

}

bool PackageTracking::m_setCurrent(const time_t& timeUpdated)//view an update.
{
	if (mylist.empty()) throw std::length_error("List is empty!");
	temp = mylist.begin();
	while (temp != mylist.end())			//Iterates to find specific shipping status by time
	{
		if (timeUpdated == temp->_time)
		{
			return true;
		}
		else
			temp++;
	}
	return false;
}


bool PackageTracking::m_readTrackingFile(string fileName) //Reads from a text file with provided tracking number to get status, location, and time
{
	string line;
	ifstream myfile(fileName);
	string location;
	string status;
	time_t time;
	if (myfile.is_open())
	{
		while (getline(myfile, line))//parses a line in the text file and puts it into the variable of type string called line
		{
			if (line == "new")//checks if the string line is equal to new if so it will enter the if statement
			{
				getline(myfile, status, ';');//checks the line after "new" and takes that line puts it into a string called status
							     //and once it hits the semicolon it will stop.
				getline(myfile, location, ';');//after the semicolon it will put all of the remaining line into the string called
							       //location until the next semicolon
				myfile >> time;//after the semicolon it will put the remaining of the line of text in to the time_t variable called time
					       //and will go to the next line once the new line char is read.
				m_addUpdate(status, location, time);//updates the linked list with status, location, and time.
			}

			else if (line == "forward")
			{
				m_moveForward();//if line is equal to "forward" this function will be called to move the iterator forward
			}

			else if (line == "back")
			{
				m_moveBackward();//if line is equal to "back" this function will be called to move the iterator back
			}

		}

		myfile.close();
		return true;
	}

	else
	{
		throw invalid_argument("Could not open file " + fileName);
		return false;
	}
}

