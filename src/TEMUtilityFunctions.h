//
//  TEMUtilityFunctions.h
//  dvm-dos-tem
//
//  Created by Tobey Carman on 4/10/14.
//  Copyright (c) 2014 Spatial Ecology Lab. All rights reserved.
//

#ifndef TEMUtilityFunctions_H
#define TEMUtilityFunctions_H

#include <string>
#include <json/value.h>

namespace temutil {

  bool onoffstr2bool(const std::string &s);

  std::string file2string(const char *filename);

  Json::Value parse_control_file(const std::string &filepath);

}

#endif /* TEMUtilityFunctions_H */