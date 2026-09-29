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

#include "RMacMenuAccessibility.h"

#import <AppKit/AppKit.h>
#import <objc/runtime.h>
#import <objc/message.h>

#include <QRegularExpression>

QString RMacMenuAccessibility::getSpokenTitle(const QString& title) {
    QString ret = title;

    // trailing key code, added by RGuiAction::initTexts on macOS:
    // "Delete (ER)", "Zoom In (+)":
    QString code;
    static const QRegularExpression rxCode("\\s\\(([A-Z0-9+\\-*/.,;:<>=]{1,6})\\)$");
    QRegularExpressionMatch mCode = rxCode.match(ret);
    if (mCode.hasMatch()) {
        code = mCode.captured(1);
        ret = ret.left(mCode.capturedStart(0));
    }

    // undo / redo: "[-]" (nothing to undo) or "[transaction text]":
    static const QRegularExpression rxUndo("\\s\\[([^\\]]*)\\]");
    QRegularExpressionMatch mUndo = rxUndo.match(ret);
    if (mUndo.hasMatch()) {
        QString desc = mUndo.captured(1).trimmed();
        ret = ret.left(mUndo.capturedStart(0)) + ret.mid(mUndo.capturedEnd(0));
        if (!desc.isEmpty() && desc != "-") {
            ret += ": " + desc;
        }
    }

    if (!code.isEmpty()) {
        // spell the key code ("ER" -> "E R"):
        QString spelled;
        for (int i = 0; i < code.length(); i++) {
            if (i > 0) {
                spelled += " ";
            }
            spelled += code.at(i);
        }
        ret += ", " + spelled;
    }

    return ret.simplified();
}

namespace {

// key of the associated object that remembers the label we set on an item:
char spokenLabelKey;

// NSMenuItemImageVisibilityVisible (macOS 27 SDK):
const NSInteger imageVisibilityVisible = 1;

/**
 * macOS 27 hides menu item images by default (preferredImageVisibility
 * Automatic). Qt only sets the image of an item if icons in menus are
 * enabled (Qt::AA_DontShowIconsInMenus, MenuBar/ShowIcons), so every item
 * with an image asks for it to be visible. Called through the runtime to
 * compile with older SDKs, no-op before macOS 27.
 */
void updateMenuItemImageVisibility(NSMenuItem* item) {
    if (item.image == nil) {
        return;
    }
    static const SEL getter = NSSelectorFromString(@"preferredImageVisibility");
    static const SEL setter = NSSelectorFromString(@"setPreferredImageVisibility:");
    if (![item respondsToSelector:setter]) {
        return;
    }
    // setting the value posts NSMenuDidChangeItemNotification again:
    if (((NSInteger (*)(id, SEL))objc_msgSend)(item, getter) == imageVisibilityVisible) {
        return;
    }
    ((void (*)(id, SEL, NSInteger))objc_msgSend)(item, setter, imageVisibilityVisible);
}

void updateMenuItem(NSMenuItem* item) {
    if (item == nil || item.isSeparatorItem) {
        return;
    }
    updateMenuItemImageVisibility(item);
    QString title = QString::fromNSString(item.title);
    QString spoken = RMacMenuAccessibility::getSpokenTitle(title);

    // Never read item.accessibilityLabel here: the getter runs
    // -[NSMenu(Accessibility) _openForInspection:], which simulates opening
    // the menu and sends the menu opening notification. Qt's menu delegate
    // then emits QMenu::aboutToShow synchronously, from inside
    // -[NSMenu insertItem:atIndex:] (QWidget::addAction). Scripts that
    // rebuild a menu in aboutToShow (e.g. layer states) re-enter their own
    // rebuild and delete the action that is being added: crash
    // (RGuiAction::addToWidget) or "Cannot call method 'connect' of
    // undefined". The label we set last is remembered in an associated
    // object instead:
    NSString* previous = objc_getAssociatedObject(item, &spokenLabelKey);
    if (spoken == title) {
        // nothing to translate: default (title):
        if (previous != nil) {
            item.accessibilityLabel = nil;
            objc_setAssociatedObject(item, &spokenLabelKey, nil, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
        }
        return;
    }
    if (previous == nil || spoken != QString::fromNSString(previous)) {
        NSString* label = spoken.toNSString();
        item.accessibilityLabel = label;
        objc_setAssociatedObject(item, &spokenLabelKey, label, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    }
}

} // namespace

@interface RMacMenuAccessibilityObserver : NSObject
- (void)menuItemChanged:(NSNotification*)notification;
@end

@implementation RMacMenuAccessibilityObserver
- (void)menuItemChanged:(NSNotification*)notification {
    NSMenu* menu = notification.object;
    NSNumber* index = notification.userInfo[@"NSMenuItemIndex"];
    if (menu == nil || index == nil) {
        return;
    }
    NSInteger i = index.integerValue;
    if (i < 0 || i >= menu.numberOfItems) {
        return;
    }
    updateMenuItem([menu itemAtIndex:i]);
}
@end

void RMacMenuAccessibility::install() {
    static RMacMenuAccessibilityObserver* observer = nil;
    if (observer != nil) {
        return;
    }
    observer = [[RMacMenuAccessibilityObserver alloc] init];
    NSNotificationCenter* nc = [NSNotificationCenter defaultCenter];
    [nc addObserver:observer selector:@selector(menuItemChanged:) name:NSMenuDidAddItemNotification object:nil];
    [nc addObserver:observer selector:@selector(menuItemChanged:) name:NSMenuDidChangeItemNotification object:nil];
}
