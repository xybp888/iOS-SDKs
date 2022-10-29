
#import <Foundation/Foundation.h>

@interface SpeedTestConfig : NSObject

- (void) startDownloadTest:(void (^)(NSString *result))completionHandler;

@end




