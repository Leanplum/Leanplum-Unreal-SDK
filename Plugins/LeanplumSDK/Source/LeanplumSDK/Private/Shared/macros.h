//
//  macros.h
//  Leanplum-SDK
//
//  Created by Milos Jakovljevic.
//  Copyright © 2021 Leanplum, Inc. All rights reserved.
//

#ifndef leanplum_macros_h
#define leanplum_macros_h

#include "CoreMinimal.h"
#include <string>

DECLARE_LOG_CATEGORY_EXTERN(LogLeanplumSDK, Log, All);

struct private_data
{
	std::string app_id;
	std::string development_key;
	std::string production_key;
};

namespace kinds
{
	extern std::string INT;
	extern std::string FLOAT;
	extern std::string STRING;
	extern std::string BOOLEAN;
	extern std::string FILE;
	extern std::string GROUP;
	extern std::string ARRAY;
	extern std::string COLOR;
	extern std::string ACTION;
};

#endif /* leanplum_macros_h */
