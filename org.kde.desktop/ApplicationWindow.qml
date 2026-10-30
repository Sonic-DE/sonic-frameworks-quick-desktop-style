/*
    SPDX-FileCopyrightText: 2026 Joseph Crowell <joseph.w.crowell@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

import QtQuick
import QtQuick.Templates as T
import org.kde.kirigami as Kirigami

// The Basic style's window, plus the tools area: while it is translucent the window
// colour is painted everywhere but there, so it shows what is behind the window.
T.ApplicationWindow {
    id: window

    readonly property bool __translucentToolsArea: Kirigami.Theme.toolsArea.active && Kirigami.Theme.toolsArea.translucent

    color: __translucentToolsArea ? "transparent" : window.palette.window

    background: Kirigami.ToolsAreaWindowBackground {
        visible: window.__translucentToolsArea
        color: window.palette.window
    }
}
