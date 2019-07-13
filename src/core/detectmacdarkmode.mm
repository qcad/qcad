#include "detectmacdarkmode.h"
#include <QDebug>

#import <AppKit/NSWindow.h>

bool isMacDarkMode() {
    NSNumber* plistRequiresAquaAppearance = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"NSRequiresAquaSystemAppearance"];
    if (plistRequiresAquaAppearance==nil) {
        qDebug() << "no value in Info.plist";
        // no value in plist:
        // detect OS dark mode:
        NSString* style = [[NSUserDefaults standardUserDefaults] stringForKey:@"AppleInterfaceStyle"];
        if (style==nil) {
            qDebug() << "style is nil: no dark mode";
            return false;
        }
        qDebug() << "style not nil: got dark mode";
        return true;
    }
    else {
        qDebug() << "dark mode: " << ![plistRequiresAquaAppearance boolValue];
        return ![plistRequiresAquaAppearance boolValue];
    }
}
