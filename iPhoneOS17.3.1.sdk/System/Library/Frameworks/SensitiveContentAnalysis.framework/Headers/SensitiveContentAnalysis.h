//
//  SensitiveContentAnalysis.h
//  SensitiveContentAnalysis
//
//  Copyright (c).2023, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#if (!TARGET_OS_TV && !TARGET_OS_VISION)
#import <SensitiveContentAnalysis/SCSensitivityAnalyzer.h>
#endif // !TARGET_OS_TV
