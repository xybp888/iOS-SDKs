//
//  INWorkoutLocationType.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef INWorkoutLocationType_h
#define INWorkoutLocationType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INWorkoutLocationType) {
    INWorkoutLocationTypeUnknown = 0,
    INWorkoutLocationTypeOutdoor,
    INWorkoutLocationTypeIndoor,
} API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

#endif // INWorkoutLocationType_h
