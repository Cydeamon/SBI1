TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

HEADERS += \
    resource.h \
    bass.h \
    declarations.h

OTHER_FILES += \
    bass.dll \
    data/users.dat \
    data/settings.dat \
    data/ranks.dat \
    data/menu_image.dat \
    data/highscore.dat \
    data/blackmesa.dat \
    save/save3.sav \
    save/save2.sav \
    save/save1.sav \
    save/save0.sav \
    sounds/select.mp3 \
    sounds/miss.mp3 \
    sounds/menu.mp3 \
    sounds/damaged.mp3 \
    sounds/already_atacked.mp3 \
    rs.rc \
    icon.ico

RC_FILE += rs.rc
