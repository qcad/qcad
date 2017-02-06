#include "removemacmenus.h"

#import <AppKit/NSWindow.h>

void removeMacMenus() {
    // Remove (disable) the "Start Dictation..." and "Emoji & Symbols" menu
    // items from the "Edit" menu
    [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"NSDisabledDictationMenuItem"];
    [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"NSDisabledCharacterPaletteMenuItem"];

#ifdef AVAILABLE_MAC_OS_X_VERSION_10_12_AND_LATER
    // Remove (don't allow) the "Show Tab Bar" menu item from the "View" menu,
    // if supported
    if ([NSWindow respondsToSelector:@selector(allowsAutomaticWindowTabbing)])
        NSWindow.allowsAutomaticWindowTabbing = NO;
#endif

    // Remove (don't have) the "Enter Full Screen" menu item from the "View"
    // menu
    [[NSUserDefaults standardUserDefaults] setBool:NO forKey:@"NSFullScreenMenuItemEverywhere"];
}
