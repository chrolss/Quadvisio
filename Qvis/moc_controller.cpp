/****************************************************************************
** Meta object code from reading C++ file 'controller.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "controller.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QvisController[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   33,   33,   33, 0x08,
      34,   33,   33,   33, 0x08,
      54,   33,   33,   33, 0x08,
      73,   33,   33,   33, 0x08,
      95,   33,   33,   33, 0x08,
     106,   33,   33,   33, 0x08,
     116,  159,   33,   33, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QvisController[] = {
    "QvisController\0createTCPThread()\0\0"
    "videoButtonPushed()\0pidButtonClicked()\0"
    "setPIDButtonClicked()\0closeTCP()\0"
    "readTCP()\0displayError(QAbstractSocket::SocketError)\0"
    "socketError\0"
};

void QvisController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QvisController *_t = static_cast<QvisController *>(_o);
        switch (_id) {
        case 0: _t->createTCPThread(); break;
        case 1: _t->videoButtonPushed(); break;
        case 2: _t->pidButtonClicked(); break;
        case 3: _t->setPIDButtonClicked(); break;
        case 4: _t->closeTCP(); break;
        case 5: _t->readTCP(); break;
        case 6: _t->displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QvisController::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QvisController::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QvisController,
      qt_meta_data_QvisController, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QvisController::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QvisController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QvisController::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QvisController))
        return static_cast<void*>(const_cast< QvisController*>(this));
    return QDialog::qt_metacast(_clname);
}

int QvisController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
