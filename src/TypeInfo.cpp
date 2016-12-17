//============================================================================
// Name        : TypeInfo.cpp
// Date        : 17.12.2016
// Author      : Andrey Popov
// Copyright   : All rights reserved
//============================================================================

#include "TypeInfo.h"

// Операция сравнения.
bool operator<(const TypeInfo& t1, const TypeInfo& t2)
  { return t1.ti.before(t2.ti); }
