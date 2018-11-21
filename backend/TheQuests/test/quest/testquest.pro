TARGET = testquest
 TEMPLATE = app
 CONFIG += console debug c++11
 CONFIG -= app_bundle
 QT += network sql testlib
 QT -= gui
 DEFINES += TF_DLL
 INCLUDEPATH += ../..
 LIBS += -L../../lib -lmodel
 include(../../appbase.pri)
 SOURCES = testquest.cpp    # Specifying the file name
# SOURCES = testusers.cpp ../../models/userscollection.cpp