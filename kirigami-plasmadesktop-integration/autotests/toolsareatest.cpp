/*
    SPDX-FileCopyrightText: 2026 Joseph Crowell <joseph.w.crowell@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

// What the platform theme publishes on the application (_sonic_tools_area_*) reaches
// Kirigami.Theme.toolsArea, live; without it, the defaults stay.

#include <QPalette>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QTest>

#include "common.h"

class ToolsAreaTest : public QObject {
    Q_OBJECT

private Q_SLOTS:
    void initTestCase();
    void testWithoutToolsArea();
    void testPublishedValuesReachTheTheme();

private:
    static void publish(bool on);
    QObject* root() const;

    QQmlApplicationEngine engine;
};

void ToolsAreaTest::initTestCase()
{
    Common::initTestCase();
    engine.load(QFINDTESTDATA(u"toolsareatest.qml"_s));
    QCOMPARE(engine.rootObjects().size(), 1);
}

QObject* ToolsAreaTest::root() const
{
    return engine.rootObjects().constFirst();
}

void ToolsAreaTest::publish(bool on)
{
    static int serial = 0;
    QPalette palette;
    QColor active(10, 20, 30);
    active.setAlphaF(0.5);
    palette.setColor(QPalette::Active, QPalette::Window, active);
    palette.setColor(QPalette::Inactive, QPalette::Window, QColor(40, 50, 60));
    qApp->setProperty("_sonic_tools_area_headerColors", on ? QVariant::fromValue(palette) : QVariant());
    qApp->setProperty("_sonic_tools_area_separatorColor", on ? QVariant::fromValue(QColor(1, 2, 3)) : QVariant());
    qApp->setProperty("_sonic_tools_area_blurBehind", on ? QVariant(true) : QVariant());
    qApp->setProperty("_sonic_tools_area_opaqueWhenMaximized", on ? QVariant(true) : QVariant());
    qApp->setProperty("_sonic_tools_area_titleBarHidden", on ? QVariant(true) : QVariant());
    qApp->setProperty("_sonic_tools_area_translucent", on ? QVariant(true) : QVariant());
    qApp->setProperty("_sonic_tools_area_serial", ++serial);
}

void ToolsAreaTest::testWithoutToolsArea()
{
    QCOMPARE(root()->property("active").toBool(), false);
    QVERIFY(!root()->property("separatorColor").value<QColor>().isValid());
    QCOMPARE(root()->property("blurBehind").toBool(), false);
}

void ToolsAreaTest::testPublishedValuesReachTheTheme()
{
    publish(true);
    QTRY_COMPARE(root()->property("active").toBool(), true);
    QColor active(10, 20, 30);
    active.setAlphaF(0.5);
    QCOMPARE(root()->property("backgroundColor").value<QColor>(), active);
    QCOMPARE(root()->property("inactiveBackgroundColor").value<QColor>(), QColor(40, 50, 60));
    QCOMPARE(root()->property("separatorColor").value<QColor>(), QColor(1, 2, 3));
    QCOMPARE(root()->property("blurBehind").toBool(), true);
    QCOMPARE(root()->property("titleBarHidden").toBool(), true);
    // Translucent only with an alpha channel for windows.
    QCOMPARE(root()->property("translucent").toBool(), QQuickWindow::hasDefaultAlphaBuffer());

    // Unpublished: back to the defaults, live.
    publish(false);
    QTRY_COMPARE(root()->property("active").toBool(), false);
    QVERIFY(!root()->property("separatorColor").value<QColor>().isValid());
}

QTEST_MAIN(ToolsAreaTest)

#include "toolsareatest.moc"
