#include "detectmacdarkmode.h"

#import <AppKit/NSWindow.h>

bool isMacDarkMode() {
    NSString *osxMode = [[NSUserDefaults standardUserDefaults] stringForKey:@"AppleInterfaceStyle"];
    if (osxMode==nil) {
        return false;
    }
    return true;
}
