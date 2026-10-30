/*
    SPDX-FileCopyrightText: 2017 Marco Martin <mart@kde.org>
    SPDX-FileCopyrightText: 2017 The Qt Company Ltd.
    SPDX-FileCopyrightText: 2023 ivan tkachenko <me@ratijas.tk>

    SPDX-License-Identifier: LGPL-3.0-only OR GPL-2.0-or-later
*/

import QtQuick
import QtQuick.Templates as T
import org.kde.kirigami as Kirigami

// A header toolbar joins the window's tools area (Kirigami.ToolsAreaBackground); a footer
// toolbar draws its separator along the top.
Kirigami.ToolsAreaBackground {
    id: root

    required property T.ToolBar control

    implicitHeight: 40
    toolsAreaCandidate: control?.position === T.ToolBar.Header
    separatorEdge: control?.position === T.ToolBar.Header ? Qt.BottomEdge : Qt.TopEdge
}
