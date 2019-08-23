//
//  INCarAirCirculationMode.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef INCarAirCirculationMode_h
#define INCarAirCirculationMode_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INCarAirCirculationMode) {
    INCarAirCirculationModeUnknown = 0,
    INCarAirCirculationModeFreshAir,
    INCarAirCirculationModeRecirculateAir,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macosx);

#endif // INCarAirCirculationMode_h
