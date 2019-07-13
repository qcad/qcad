#include "detectmacdarkmode.h"

#import <AppKit/NSWindow.h>

bool isMacDarkMode() {
    NSNumber *plistRequiresAquaAppearance = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"NSRequiresAquaSystemAppearance"];
    if (plistRequiresAquaAppearance==nil) {
        // no value in plist:
        // detect OS dark mode:
        NSString *osxMode = [[NSUserDefaults standardUserDefaults] stringForKey:@"AppleInterfaceStyle"];
        if (osxMode==nil) {
            return false;
        }
        return true;
    }
    else {
        return ![plistRequiresAquaAppearance boolValue];
    }
}
