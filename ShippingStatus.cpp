//
//  ShippingStatus.cpp
//  Project2
//
//  Created by Han, Wenlin on 2/13/18.
//  Copyright © 2018 Han, Wenlin. All rights reserved.
//

#include "ShippingStatus.h"

//Default constructor initializes values to empty strings and time 0
ShippingStatus::ShippingStatus() {
  _location = " ";
  _status = " ";
  _time = 0;
}

//Sets ShippingStatus private variables
ShippingStatus::ShippingStatus(const string& status, const string& location, const time_t& timeUpdated) {
  _location= location;
  _status= status;
  _time=timeUpdated;
}

string ShippingStatus::m_getStatus(){
  return _status;
}

string ShippingStatus::m_getLocation(){
   return _location;
}

time_t ShippingStatus::m_getTime() {
    return _time;
}
