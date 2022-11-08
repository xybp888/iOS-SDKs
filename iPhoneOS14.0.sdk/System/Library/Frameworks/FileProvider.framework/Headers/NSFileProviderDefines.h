//
//  NSFileProviderDefines.h
//  FileProvider
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#ifndef PREPROCESS_AVAILABILITY_MACROS

// changing anything here? be sure to also change process-header.sh!

#define FILEPROVIDER_SPI_AVAILABILITY API_UNAVAILABLE(watchos, tvos)

#define FILEPROVIDER_CLASS_AVAILABILITY API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, macCatalyst) API_UNAVAILABLE(watchos, tvos)
#define FILEPROVIDER_API_AVAILABILITY_V2 API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, macCatalyst) API_UNAVAILABLE(watchos, tvos)

#define FILEPROVIDER_API_AVAILABILITY_V3 API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macos, macCatalyst)
#define FILEPROVIDER_API_DEPRECATED_V3(message) API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(tvos, watchos) API_UNAVAILABLE(macos, macCatalyst)

#else
// This file intentionally left blank.
#endif
