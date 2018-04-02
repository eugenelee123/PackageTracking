//
//  ShippingStatus.h
//  Project2
//
//  Created by Han, Wenlin on 2/13/18.
//  Copyright © 2018 Han, Wenlin. All rights reserved.
//

#ifndef ShippingStatus_h
#define ShippingStatus_h

#pragma once

#include <string>
using namespace std;

class ShippingStatus {
public:
    friend class PackageTracking; //Added friend class to use private variables
    ShippingStatus();             //Default constructor
    ShippingStatus(const string& status, const string& location, const time_t& timeUpdated ); //Constructor with parameters

    string m_getStatus();       //Return status of package
    string m_getLocation();     //Return location of package
    time_t m_getTime();         //Return time of package
    
private: 
    string _location;
    string _status;
    time_t _time;
};


#endif /* ShippingStatus_h */

