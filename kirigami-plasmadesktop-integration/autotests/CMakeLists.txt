# SPDX-FileCopyrightText: 2023 Fushan Wen <qydwhotmail@gmail.com>
# SPDX-License-Identifier: BSD-3-Clause

if (NOT BUILD_TESTING)
    return()
endif()

ecm_add_test(
    animationspeedmodifiertest.cpp
    LINK_LIBRARIES Qt::Test Qt::Qml Qt::QuickControls2
)
set_tests_properties(animationspeedmodifiertest PROPERTIES ENVIRONMENT "CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR};CMAKE_SHARED_LIBRARY_SUFFIX=${CMAKE_SHARED_LIBRARY_SUFFIX}")

if (WIN32)
target_link_libraries(animationspeedmodifiertest user32)
else()
target_link_libraries(animationspeedmodifiertest KF6::ConfigCore)
endif()

ecm_add_test(
    toolsareatest.cpp
    LINK_LIBRARIES Qt::Test Qt::Qml Qt::Quick Qt::QuickControls2
)
# The plugin just built, not an installed one.
set_tests_properties(toolsareatest PROPERTIES ENVIRONMENT "CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR};CMAKE_SHARED_LIBRARY_SUFFIX=${CMAKE_SHARED_LIBRARY_SUFFIX};KDECI_BUILD=1;QT_PLUGIN_PATH=${CMAKE_BINARY_DIR}/bin")

if (WIN32)
    return() # Doesn't work in the Windows CI
endif()

ecm_add_test(
    TextFieldContextMenuTest.cpp
    LINK_LIBRARIES Qt::Test Qt::Qml Qt::QuickControls2
)
set_tests_properties(TextFieldContextMenuTest PROPERTIES ENVIRONMENT "CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR};CMAKE_SHARED_LIBRARY_SUFFIX=${CMAKE_SHARED_LIBRARY_SUFFIX}")
