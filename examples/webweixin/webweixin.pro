TEMPLATE = app

QT += qml quick widgets network

SOURCES += main.cpp 

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = ./qml

# Default rules for deployment.
include(deployment.pri)
include(../../src/qmlio/qmlio.pri)
include(../../src/qmlnetwork/qmlnetwork.pri)


