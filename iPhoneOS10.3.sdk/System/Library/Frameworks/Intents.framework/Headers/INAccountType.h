//
//  INAccountType.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef INAccountType_h
#define INAccountType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INAccountType) {
    INAccountTypeUnknown = 0,
    INAccountTypeChecking,
    INAccountTypeCredit,
    INAccountTypeDebit,
    INAccountTypeInvestment,
    INAccountTypeMortgage,
    INAccountTypePrepaid,
    INAccountTypeSaving,
} API_AVAILABLE(ios(10.3), watchos(3.2)) API_UNAVAILABLE(macosx);

#endif // INAccountType_h
