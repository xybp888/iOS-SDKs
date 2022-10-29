//
//  CellularDataDiagnosticsSuiteController.h
//  Diagnostic-8374
//
//  Created by Mahak Goindani on 8/16/21.
//  
//

#import <DiagnosticsKit/DiagnosticsKit.h>
#import "SpeedTestConfig.h"

// Define status codes for the extension
// Typically: 0 = pass, negative = test failure, positive = issues found
typedef NS_ENUM(NSUInteger, DiagExtensionSampleStatusCode) {
    DiagExtensionSpeedTestFailed = -1,
    DiagExtensionErrorUnknown = 1,
    DiagExtensionSpeedTestSuccess = 0,
};

@interface CellularDataDiagnosticsSuiteController : DKDiagnosticController

@end
