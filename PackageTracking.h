//
//  PackageTracking.h
//  Project2
//
//  Created by Han, Wenlin on 2/13/18.
//  Copyright © 2018 Han, Wenlin. All rights reserved.
//

#ifndef PackageTracking_h
#define PackageTracking_h

#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <sstream>
#include <stdexcept>
#include "ShippingStatus.h"

using namespace std;

class PackageTracking {
public:
    PackageTracking(const string& strnum);
    
    void m_addUpdate( const string& status, const string& location, const time_t& timeUpdated); // add a new update
    
    bool m_moveBackward();//move iterator one step back in time; return false if not possible (true otherwise)
    bool m_moveForward();//move iterator one step forward in time; return false if not possible (true otherwise)

    string m_getLocation( );//return the location of the current update
    time_t m_getTime( );//return the time of the current update
    string m_getStatus( );//return the status of the current update
    int m_getNumofUpdate() const; // get the total numbers of shipping status updates
    
    bool m_setCurrent(const time_t& timeUpdated);//set current update to given time; return false if time is not found (true otherwise)
    
    void m_printPreviousUpdates();  //print all previous updates in the shipping chain from beginning, all the way up to (but not including) the current update you are viewing (may not be the most recent update).
    void m_printFollowingUpdates();//print all updates from the current update you are viewing to the last update in the tracking chain.
    void m_printFullTracking();//print all the status updates in the tracking chain.
    
	//read the full tracking chain from a file and follow the commands as specified in the file
	//return false if there is an error reading file (true otherwise)
	bool m_readTrackingFile(string fileName);
	    
    
private:
list<ShippingStatus> mylist; 		//Creates list of ShippingStatus objects
list<ShippingStatus>::iterator temp;	//Creates iterator for index maneuverability 
int n = 0;				//Counts number of updates

};

#endif /* PackageTracking_h */

