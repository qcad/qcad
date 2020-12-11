#include "detectmacdarkmode.h"
#include <QDebug>

#import <AppKit/NSWindow.h>

bool isMacDarkMode() {
    qDebug() << "isMacDarkMode";
    
    if (QSysInfo::MacintoshVersion<0x0010 && QSysInfo::MacintoshVersion!=0x0000) {
        qDebug() << "mac version < 0x0010: " << QSysInfo::MacintoshVersion;
        // no dark mode before 10.14 (Mojave):
        // High Sierra reports dark menu bar as dark mode:
        return false;
    }

    // read value from plist file:
    NSNumber* plistRequiresAquaAppearance = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"NSRequiresAquaSystemAppearance"];
    if (plistRequiresAquaAppearance!=nil) {
        // value found in plist file:
        bool darkMode = ![plistRequiresAquaAppearance boolValue];
        if (darkMode) {
            // dark mode enabled if system is in dark mode
            // use system setting
            qDebug() << "dark mode allowed in plist file: use system setting";
        }
        else {
            // dark mode explicitely disabled in plist file:
            qDebug() << "dark mode explicitely disabled in plist file";
            return false;
        }
    }
    else {
        // no value in plist file
        // use system setting
        qDebug() << "no dark mode value in plist file: use app defaults or system setting";
    }

    // read value from "defaults":
    // TODO: does not work
    //CFStringRef orient = (CFBoolea) CFPreferencesCopyAppValue( CFSTR("NSRequiresAquaSystemAppearance"), CFSTR("QCAD-Pro") );
//    Boolean requiresAquaSystemAppearanceIsValid = false;
//    Boolean requiresAquaSystemAppearance = CFPreferencesGetAppBooleanValue( CFSTR("NSRequiresAquaSystemAppearance"), CFSTR("QCAD-Pro"), &requiresAquaSystemAppearanceIsValid );
//    if (requiresAquaSystemAppearanceIsValid) {
//        qDebug() << "app default for dark mode valid";
//    }
//    else {
//        qDebug() << "app default for dark mode NOT valid";
//    }
//    if (requiresAquaSystemAppearance) {
//        // dark mode disabled in app defaults, i.e.:
//        // defaults write -app "QCAD-Pro" NSRequiresAquaSystemAppearance -bool true
//        qDebug() << "dark mode disabled as app default";
//        return false;
//    }
//    else {
//        qDebug() << "dark mode NOT disabled as app default";
//    }

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
