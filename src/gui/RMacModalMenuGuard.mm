/**
 * Copyright (c) 2011-2026 by Andrew Mustun. All rights reserved.
 *
 * This file is part of the QCAD project.
 *
 * QCAD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QCAD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */

#include "RMacModalMenuGuard.h"

#import <AppKit/AppKit.h>
#import <objc/runtime.h>
#import <objc/message.h>

#include <QDebug>
#include <QGuiApplication>

/*
 * Background (Qt 6 Cocoa platform plugin):
 *
 * Qt's menu items have no target and the action qt_itemFired:. AppKit
 * resolves the target through the responder chain of the key window.
 * If a Qt window is key, the chain ends in Qt's view, which validates the
 * item and disables it while a (Qt) modal dialog is active. If a native
 * panel (NSSavePanel, NSOpenPanel, NSAlert, ...) is key, the chain ends
 * in the application delegate (QCocoaApplicationDelegate), which only
 * checks the enabled state of the QAction. The key equivalent typed into
 * the panel thus triggers the application action.
 *
 * The guard wraps the two methods of the application delegate that
 * AppKit calls in that case (validateMenuItem: and qt_itemFired:). While
 * a native modal panel is key, items are reported as disabled, so that
 * AppKit passes the key stroke on to the panel, except for the standard
 * editing shortcuts, which are validated against and forwarded to the
 * responder chain of the panel (as a menu item with the standard action
 * and no target would be).
 */

namespace {

typedef BOOL (*ValidateMenuItemImp)(id, SEL, NSMenuItem*);
typedef void (*ItemFiredImp)(id, SEL, NSMenuItem*);

ValidateMenuItemImp originalValidateMenuItem = NULL;
ItemFiredImp originalItemFired = NULL;

const NSUInteger modifierMask =
    NSEventModifierFlagCommand | NSEventModifierFlagShift |
    NSEventModifierFlagOption | NSEventModifierFlagControl;

/**
 * \return True if the given window is a window of Qt (QNSWindow / QNSPanel).
 */
bool isQtWindow(NSWindow* window) {
    if (window == nil) {
        return false;
    }

    static Protocol* qtWindowProtocol = NSProtocolFromString(@"QNSWindowProtocol");
    if (qtWindowProtocol != nil) {
        return [window conformsToProtocol:qtWindowProtocol];
    }

    // fallback: Qt windows have a Qt content view:
    return [NSStringFromClass([window.contentView class]) hasPrefix:@"QNSView"];
}

/**
 * \return The standard editing action which a native application would
 * bind to the key equivalent of the given menu item or NULL.
 */
SEL standardEditAction(NSMenuItem* item) {
    if (item == nil) {
        return NULL;
    }

    NSString* key = item.keyEquivalent;
    if (key == nil || key.length != 1) {
        return NULL;
    }

    NSUInteger modifiers = item.keyEquivalentModifierMask & modifierMask;

    // upper case key equivalent implies shift:
    unichar c = [key characterAtIndex:0];
    if (c >= 'A' && c <= 'Z') {
        c = c - 'A' + 'a';
        modifiers |= NSEventModifierFlagShift;
    }

    if (modifiers == NSEventModifierFlagCommand) {
        switch (c) {
        case 'x':
            return @selector(cut:);
        case 'c':
            return @selector(copy:);
        case 'v':
            return @selector(paste:);
        case 'a':
            return @selector(selectAll:);
        case 'z':
            return @selector(undo:);
        default:
            break;
        }
    }
    else if (modifiers == (NSEventModifierFlagCommand | NSEventModifierFlagShift)) {
        if (c == 'z') {
            return @selector(redo:);
        }
    }

    return NULL;
}

/**
 * \return The object which would receive the given standard action from a
 * menu item without target or nil (AppKit lookup: responder chain of the
 * key window including supplemental targets, e.g. the proxy of a panel
 * hosted in another process (NSRemoteView), then the main window chain,
 * the application and its delegate).
 */
id targetForStandardEditAction(SEL action, NSMenuItem* item) {
    return [NSApp targetForAction:action to:nil from:item];
}

/**
 * \return True if the given responder would enable a menu item with the
 * given action (standard menu item validation).
 */
BOOL validateStandardEditAction(id responder, SEL action, NSMenuItem* item) {
    if (responder == nil) {
        return NO;
    }

    // item with the standard action, as a native application would have it:
    NSMenuItem* probe = [[[NSMenuItem alloc] initWithTitle:item.title action:action keyEquivalent:@""] autorelease];
    probe.target = nil;
    probe.tag = item.tag;

    if ([responder respondsToSelector:@selector(validateMenuItem:)]) {
        return ((BOOL (*)(id, SEL, NSMenuItem*))objc_msgSend)(responder, @selector(validateMenuItem:), probe);
    }
    if ([responder respondsToSelector:@selector(validateUserInterfaceItem:)]) {
        return ((BOOL (*)(id, SEL, id))objc_msgSend)(responder, @selector(validateUserInterfaceItem:), probe);
    }

    return YES;
}

BOOL guardedValidateMenuItem(id self, SEL _cmd, NSMenuItem* item) {
    if (RMacModalMenuGuard::isNativeModalPanelActive()) {
        SEL action = standardEditAction(item);
        if (action == NULL) {
            // application action: not available while a native panel is shown.
            // AppKit passes the key stroke on to the panel:
            return NO;
        }

        // standard editing action: let the panel decide:
        id responder = targetForStandardEditAction(action, item);
        return validateStandardEditAction(responder, action, item);
    }

    if (originalValidateMenuItem == NULL) {
        return item.enabled;
    }
    return originalValidateMenuItem(self, _cmd, item);
}

void guardedItemFired(id self, SEL _cmd, NSMenuItem* item) {
    if (RMacModalMenuGuard::isNativeModalPanelActive()) {
        SEL action = standardEditAction(item);
        if (action == NULL) {
            // application action: never triggered behind a native panel:
            return;
        }

        // forward standard editing action to the panel (cut:, copy:, ...):
        [NSApp sendAction:action to:nil from:item];
        return;
    }

    if (originalItemFired != NULL) {
        originalItemFired(self, _cmd, item);
    }
}

/**
 * Replaces the implementation of the given instance method of the given
 * class (the method must be implemented by that class, not inherited).
 *
 * \return Previous implementation or NULL.
 */
IMP replaceMethod(Class cls, SEL selector, IMP replacement) {
    Method method = class_getInstanceMethod(cls, selector);
    if (method == NULL) {
        return NULL;
    }

    // never patch an implementation inherited from a super class:
    Class superClass = class_getSuperclass(cls);
    if (superClass != Nil && class_getInstanceMethod(superClass, selector) == method) {
        return NULL;
    }

    return method_setImplementation(method, replacement);
}

} // namespace

bool RMacModalMenuGuard::isNativeModalPanelActive() {
    NSWindow* keyWindow = NSApp.keyWindow;
    if (keyWindow == nil || isQtWindow(keyWindow)) {
        return false;
    }

    // panel run by AppKit (-[NSApplication runModalForWindow:], used by
    // QFileDialog::exec(), NSAlert, ...):
    if (NSApp.modalWindow != nil) {
        return true;
    }

    // sheet attached to a window (window modal file dialog):
    if (keyWindow.sheet) {
        return true;
    }

    // Qt knows about a modal window but a native window is key:
    return QGuiApplication::modalWindow() != NULL;
}

void RMacModalMenuGuard::install() {
    static bool installed = false;
    if (installed) {
        return;
    }
    installed = true;

    if (QGuiApplication::platformName() != "cocoa") {
        return;
    }

    Class delegateClass = NSClassFromString(@"QCocoaApplicationDelegate");
    if (delegateClass == Nil) {
        qWarning("RMacModalMenuGuard::install: application delegate class not found");
        return;
    }

    SEL validateSel = @selector(validateMenuItem:);
    SEL firedSel = NSSelectorFromString(@"qt_itemFired:");

    IMP validateImp = replaceMethod(delegateClass, validateSel, (IMP)guardedValidateMenuItem);
    if (validateImp == NULL) {
        qWarning("RMacModalMenuGuard::install: cannot patch menu item validation");
        return;
    }
    originalValidateMenuItem = (ValidateMenuItemImp)validateImp;

    IMP firedImp = replaceMethod(delegateClass, firedSel, (IMP)guardedItemFired);
    if (firedImp == NULL) {
        qWarning("RMacModalMenuGuard::install: cannot patch menu item activation");
        // restore validation to keep menu behavior consistent:
        replaceMethod(delegateClass, validateSel, validateImp);
        originalValidateMenuItem = NULL;
        return;
    }
    originalItemFired = (ItemFiredImp)firedImp;
}
