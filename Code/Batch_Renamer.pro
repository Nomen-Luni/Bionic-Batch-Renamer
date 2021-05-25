QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -lKF5KExiv2

SOURCES += \
    main.cpp \
    MainWindow/mainwindow.cpp \
    TransformEngine/transformengine.cpp \
    TransformProviders/transformprovider.cpp \
    TransformProviders/transformprovider_case.cpp \
    TransformProviders/transformprovider_datetime.cpp \
    TransformProviders/transformprovider_insertoverwrite.cpp \
    TransformProviders/transformprovider_numbering.cpp \
    TransformProviders/transformprovider_removechars.cpp \
    TransformProviders/transformprovider_searchreplace.cpp \
    AboutDialog/aboutdialog.cpp \
    FileSystemOverlay/filesystemoverlay.cpp
    
HEADERS += \
    version.h\
    MainWindow/mainwindow.h \
    TransformEngine/transformengine.h \
    TransformProviders/enum_transformScope.h \
    TransformProviders/transformprovider.h \
    TransformProviders/transformprovider_case.h \
    TransformProviders/transformprovider_datetime.h \
    TransformProviders/transformprovider_insertoverwrite.h \
    TransformProviders/transformprovider_numbering.h \
    TransformProviders/transformprovider_removechars.h \
    TransformProviders/transformprovider_searchreplace.h \
    AboutDialog/aboutdialog.h \
    FileSystemOverlay/filesystemoverlay.h
    
FORMS += \
    MainWindow/mainwindow.ui \
    TransformProviders/transformprovider_case.ui \
    TransformProviders/transformprovider_datetime.ui \
    TransformProviders/transformprovider_insertoverwrite.ui \
    TransformProviders/transformprovider_numbering.ui \
    TransformProviders/transformprovider_removechars.ui \
    TransformProviders/transformprovider_searchreplace.ui \
    AboutDialog/aboutdialog.ui
    
TRANSLATIONS += \
    Translations/Batch_Renamer_en_GB.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Translations/Batch_Renamer_nl.ts




