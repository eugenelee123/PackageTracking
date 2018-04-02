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

PackageTracking::PackageTracking(const string& strnum) 
{
	m_readTrackingFile(strnum);
}

// add a new update
void PackageTracking::m_addUpdate(const string& status, const string& location, const time_t& timeUpdated) 
{
	ShippingStatus s(status, location, timeUpdated);
	mylist.push_front(s); 
	temp = mylist.begin();
	n++;
}

bool PackageTracking::m_moveBackward()//move iterator one step earlier in time
{
	//to be completed
	if (mylist.empty())
	{
		throw std::length_error("List is empty!");
		return false;
	}

	else if (temp == mylist.end())
	{
		throw std::invalid_argument("You are at the earliest shipping update!");
		return false;
	}

	else
	{
		temp++;
		return true;
	}
	
	
}

bool PackageTracking::m_moveForward()//move iterator one step forward in time
{
	//to be completed
	if (temp == mylist.begin())
	{
		throw std::invalid_argument("You are at the most recent shipping update!");
		return false;
	}

	else if (mylist.empty())
	{
		throw std::length_error("List is empty!");
		return false;
	}
	else
	{
		temp--;
		return true;
	}
}

string PackageTracking::m_getLocation()//return the location of the current update
{
	//to be completed
	if (mylist.empty()) throw std::length_error("List is empty!");
	return temp->_location;
}

time_t PackageTracking::m_getTime()//return the time of the current update
{
	//to be completed
	if (mylist.empty()) throw std::length_error("List is empty!");
	return temp->_time;
}

string PackageTracking::m_getStatus()//return the status of the current update
{
	//to be completed
	if (mylist.empty()) throw std::length_error("List is empty!");
	return temp->_status;
}

int PackageTracking::m_getNumofUpdate() const // get the total numbers of shipping status updates
{
	//to be completed
	return n;

}

void PackageTracking::m_printPreviousUpdates() //print all previous updates in the shipping chain when the package was shipped, all the way up to (but not including) the current update you are viewing (may not be the most recent update)
{
	//to be completed
	if (mylist.empty()) throw std::length_error("List is empty!");
	list<ShippingStatus>::iterator it = temp;
	while (it != mylist.end())
	{
		it++;
		if (it != mylist.end())
		{
			
			cout << "Status:" << it->_status << "\nLocation:" << it->_location << "\nTime:" << it->_time << endl << endl;
		}
		else if (it == mylist.end())
			break;
		
	}
	
}

//print all updates from the current update you are viewing to the last update in the tracking chain
void PackageTracking::m_printFollowingUpdates()
{
	//to be completed
	if (mylist.empty()) throw std::length_error("List is empty!");
	list<ShippingStatus>::iterator it = temp;
	while (it != mylist.begin())
	{
		it--;
		cout << "Status:" << it->_status << "\nLocation:" << it->_location << "\nTime:" << it->_time << endl << endl;
	}

}

void PackageTracking::m_printFullTracking()//print all the updates in the tracking chain.
{
	//to be completed
	if (mylist.empty()) throw std::length_error("List is empty!");
	temp = mylist.begin();
	while (temp != mylist.end())
	{
		cout << "Status:" << temp->_status << "\nLocation:" << temp->_location << "\nTime:" << temp->_time << endl <<endl;
		temp++;
	}

}

bool PackageTracking::m_setCurrent(const time_t& timeUpdated)//view an update.
{
	//to be completed
	if (mylist.empty()) throw std::length_error("List is empty!");
	temp = mylist.begin();
	while (temp != mylist.end())
	{
		if (timeUpdated == temp->_time)
		{
			cout << "\nStatus:" << temp->_status << "\nLocation:" << temp->_location << "\nTime:" << temp->_time << endl << endl;
			return true;
		}
		else
			temp++;
	}
	return false;
}


bool PackageTracking::m_readTrackingFile(string fileName) 
{
	string line;
	ifstream myfile(fileName);
	string location;
	string status;
	time_t time;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (line == "new")
			{
				getline(myfile, status, ';');
				getline(myfile, location, ';');
				myfile >> time;
				cout << "Your status is: " << status << endl;
				cout << "Your location is: " << location << endl;
				cout << "Your time is: " << time << endl << endl;
				m_addUpdate(status, location, time);
			}

			else if (line == "forward")
			{
				m_moveForward();
			}

			else if (line == "back")
			{
				m_moveBackward();
			}

		}

		myfile.close();
		return true;
	}

	else
		return false;
}
