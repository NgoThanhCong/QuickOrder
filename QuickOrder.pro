#-------------------------------------------------------------------------------
# Make options
#-------------------------------------------------------------------------------

UI_DIR = uic
MOC_DIR = moc
RCC_DIR = qrc
OBJECTS_DIR = obj

CONFIG += c++11

#-------------------------------------------------------------------------------
# Qt configuration
#-------------------------------------------------------------------------------

TEMPLATE = app
TARGET = QtApp

CONFIG += qtc_runnable
CONFIG += resources_big
CONFIG += qtquickcompiler

QT += xml
QT += svg
QT += core
QT += quick
QT += quickcontrols2
QT += sql
QT += concurrent

QTPLUGIN += qsvg qsvgicon

#-------------------------------------------------------------------------------
# Compiler options
#-------------------------------------------------------------------------------

*g++*: {
    QMAKE_CXXFLAGS_RELEASE -= -O
    QMAKE_CXXFLAGS_RELEASE *= -O3
}

*msvc*: {
    QMAKE_CXXFLAGS_RELEASE -= /O
    QMAKE_CXXFLAGS_RELEASE *= /O2
}

#-------------------------------------------------------------------------------
# Deploy options
#-------------------------------------------------------------------------------

win32* {

}

linux:!android {
    TARGET = EagleEyeEdge

    target.path = /usr/bin
    icon.path = /usr/share/pixmaps
    desktop.path = /usr/share/applications
    icon.files += deploy/linux/*.png
    desktop.files += deploy/linux/*.desktop

    INSTALLS += target desktop icon
}

#-------------------------------------------------------------------------------
# Import source code
#-------------------------------------------------------------------------------

INCLUDEPATH += $$PWD/src

RESOURCES += \
    assets/assets.qrc

DISTFILES += \
    assets/fonts/Noto_Sans/NotoSans-Black.ttf \
    assets/fonts/Noto_Sans/NotoSans-BlackItalic.ttf \
    assets/fonts/Noto_Sans/NotoSans-Bold.ttf \
    assets/fonts/Noto_Sans/NotoSans-BoldItalic.ttf \
    assets/fonts/Noto_Sans/NotoSans-ExtraBold.ttf \
    assets/fonts/Noto_Sans/NotoSans-ExtraBoldItalic.ttf \
    assets/fonts/Noto_Sans/NotoSans-ExtraLight.ttf \
    assets/fonts/Noto_Sans/NotoSans-ExtraLightItalic.ttf \
    assets/fonts/Noto_Sans/NotoSans-Italic.ttf \
    assets/fonts/Noto_Sans/NotoSans-Light.ttf \
    assets/fonts/Noto_Sans/NotoSans-LightItalic.ttf \
    assets/fonts/Noto_Sans/NotoSans-Medium.ttf \
    assets/fonts/Noto_Sans/NotoSans-MediumItalic.ttf \
    assets/fonts/Noto_Sans/NotoSans-Regular.ttf \
    assets/fonts/Noto_Sans/NotoSans-SemiBold.ttf \
    assets/fonts/Noto_Sans/NotoSans-SemiBoldItalic.ttf \
    assets/fonts/Noto_Sans/NotoSans-Thin.ttf \
    assets/fonts/Noto_Sans/NotoSans-ThinItalic.ttf \
    assets/icons/ic_add.png \
    assets/icons/ic_bubble_tea.png \
    assets/icons/ic_check.png \
    assets/icons/ic_chevron_left.png \
    assets/icons/ic_close.png \
    assets/icons/ic_cloud.png \
    assets/icons/ic_edit.png \
    assets/icons/ic_export.png \
    assets/icons/ic_group.png \
    assets/icons/ic_home.png \
    assets/icons/ic_inspection.png \
    assets/icons/ic_inspection_pause.png \
    assets/icons/ic_logout.png \
    assets/icons/ic_maximize.png \
    assets/icons/ic_minimize.png \
    assets/icons/ic_report.png \
    assets/icons/ic_settings.png \
    assets/icons/ic_wifi.png \
    assets/images/img_layer.png \
    assets/images/select_avt.png \
    lib/printer.sdk.dll

TRANSLATIONS += \
    assets/translations/en.ts

HEADERS += \
    src/Components/Controllers/icontroller.h \
    src/Components/Controllers/logincontroller.h \
    src/Components/Controllers/menucontroller.h \
    src/Components/Controllers/navigationbarcontroller.h \
    src/Components/Controllers/ordercontroller.h \
    src/Components/Controllers/reportcontroller.h \
    src/Components/Controllers/settingscontroller.h \
    src/Components/Controllers/titlebarcontroller.h \
    src/Components/Controllers/usercontroller.h \
    src/Components/Controllers/vouchercontroller.h \
    src/Components/Database/entity/entitycategory.h \
    src/Components/Database/entity/entitymenuitem.h \
    src/Components/Database/entity/entityorder.h \
    src/Components/Database/entity/entityorderitem.h \
    src/Components/Database/entity/entitytransaction.h \
    src/Components/Database/entity/entityuser.h \
    src/Components/Database/entity/entityvoucher.h \
    src/Components/Database/entity_statistic/entitybestseller.h \
    src/Components/Database/entity_statistic/entitycategorystatistic.h \
    src/Components/Database/entity_statistic/entitydatevalue.h \
    src/Components/Database/entity_statistic/entityinfo.h \
    src/Components/Database/entity_statistic/entitystatisticelement.h \
    src/Components/Database/qocategorytable.h \
    src/Components/Database/qomenuitemtable.h \
    src/Components/Database/qoorderitemtable.h \
    src/Components/Database/qoordertable.h \
    src/Components/Database/qotransactiontable.h \
    src/Components/Database/qousertable.h \
    src/Components/Database/qovouchertable.h \
    src/Components/Database/sqlitetablebase.h \
    src/Components/Models/data/naviitem.h \
    src/Components/Models/data/orderdata.h \
    src/Components/Models/imodel.h \
    src/Components/Models/loginmodel.h \
    src/Components/Models/menumodel.h \
    src/Components/Models/navigationbarmodel.h \
    src/Components/Models/ordermodel.h \
    src/Components/Models/ordermodelview.h \
    src/Components/Models/reportmodel.h \
    src/Components/Models/settingsmodel.h \
    src/Components/Models/titlebarmodel.h \
    src/Components/Models/usermodel.h \
    src/Components/Models/vouchermodel.h \
    src/Components/WrapperServices/iwrapperservice.h \
    src/Components/WrapperServices/printerwrapperservice.h \
    src/Components/const.h \
    src/Components/controllermanager.h \
    src/Components/databasemanager.h \
    src/Components/timemanager.h \
    src/Misc/Utilities.h

SOURCES += \
    src/Components/Controllers/icontroller.cpp \
    src/Components/Controllers/logincontroller.cpp \
    src/Components/Controllers/menucontroller.cpp \
    src/Components/Controllers/navigationbarcontroller.cpp \
    src/Components/Controllers/ordercontroller.cpp \
    src/Components/Controllers/reportcontroller.cpp \
    src/Components/Controllers/settingscontroller.cpp \
    src/Components/Controllers/titlebarcontroller.cpp \
    src/Components/Controllers/usercontroller.cpp \
    src/Components/Controllers/vouchercontroller.cpp \
    src/Components/Database/entity/entitycategory.cpp \
    src/Components/Database/entity/entitymenuitem.cpp \
    src/Components/Database/entity/entityorder.cpp \
    src/Components/Database/entity/entityorderitem.cpp \
    src/Components/Database/entity/entitytransaction.cpp \
    src/Components/Database/entity/entityuser.cpp \
    src/Components/Database/entity/entityvoucher.cpp \
    src/Components/Database/entity_statistic/entitybestseller.cpp \
    src/Components/Database/entity_statistic/entitycategorystatistic.cpp \
    src/Components/Database/entity_statistic/entitydatevalue.cpp \
    src/Components/Database/entity_statistic/entityinfo.cpp \
    src/Components/Database/entity_statistic/entitystatisticelement.cpp \
    src/Components/Database/qocategorytable.cpp \
    src/Components/Database/qomenuitemtable.cpp \
    src/Components/Database/qoorderitemtable.cpp \
    src/Components/Database/qoordertable.cpp \
    src/Components/Database/qotransactiontable.cpp \
    src/Components/Database/qousertable.cpp \
    src/Components/Database/qovouchertable.cpp \
    src/Components/Database/sqlitetablebase.cpp \
    src/Components/Models/data/naviitem.cpp \
    src/Components/Models/data/orderdata.cpp \
    src/Components/Models/imodel.cpp \
    src/Components/Models/loginmodel.cpp \
    src/Components/Models/menumodel.cpp \
    src/Components/Models/navigationbarmodel.cpp \
    src/Components/Models/ordermodel.cpp \
    src/Components/Models/ordermodelview.cpp \
    src/Components/Models/reportmodel.cpp \
    src/Components/Models/settingsmodel.cpp \
    src/Components/Models/titlebarmodel.cpp \
    src/Components/Models/usermodel.cpp \
    src/Components/Models/vouchermodel.cpp \
    src/Components/WrapperServices/iwrapperservice.cpp \
    src/Components/WrapperServices/printerwrapperservice.cpp \
    src/Components/controllermanager.cpp \
    src/Components/databasemanager.cpp \
    src/Components/timemanager.cpp \
    src/Misc/Utilities.cpp \
    src/main.cpp

#-------------------------------------------------------------------------------
# Deploy files
#-------------------------------------------------------------------------------

OTHER_FILES += \

# Specify the source file you want to copy
SOURCE_FILE = lib/printer.sdk.dll

# Specify the destination directory in the build folder
DEST_DIR = $$OUT_PWD/build

# Define the target file name in the destination directory
TARGET_FILE = $$DEST_DIR/printer.sdk.dll
