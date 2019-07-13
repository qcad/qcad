#include "detectmacdarkmode.h"
#include <QDebug>

#import <AppKit/NSWindow.h>

bool isMacDarkMode() {
    NSNumber* plistRequiresAquaAppearance = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"NSRequiresAquaSystemAppearance"];
    if (plistRequiresAquaAppearance!=nil) {
        // value found in plist file:
        bool darkMode = ![plistRequiresAquaAppearance boolValue];
        if (darkMode) {
            // dark mode enabled if system is in dark mode
            // use system setting
            qDebug() << "dark mode on in plist file: use system setting";
        }
        else {
            // dark mode explicitely disabled in plist file:
            qDebug() << "dark mode off in plist file";
            return false;
        }
    }
    else {
        // no value in plist file
        // use system setting
        qDebug() << "no dark mode value in plist file: use system setting";
    }

    // no value in plist or dark mode enabled in plist:
    // detect OS dark mode:
    NSString* style = [[NSUserDefaults standardUserDefaults] stringForKey:@"AppleInterfaceStyle"];
    if (style==nil) {
        qDebug() << "style is nil: no dark mode";
        return false;
    }
    qDebug() << "style not nil: got dark mode";
    return true;
}
