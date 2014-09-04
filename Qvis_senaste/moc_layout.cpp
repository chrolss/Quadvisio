/****************************************************************************
** Meta object code from reading C++ file 'layout.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "layout.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'layout.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QvisLayout[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   29,   35,   35, 0x05,

 // slots: signature, parameters, type, tag, flags
      36,   35,   35,   35, 0x08,
      47,   35,   35,   35, 0x08,
      62,   35,   35,   35, 0x08,
      77,   35,   35,   35, 0x08,
      94,   35,   35,   35, 0x08,
     113,   35,   35,   35, 0x08,
     130,   35,   35,   35, 0x08,
     150,   35,   35,   35, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QvisLayout[] = {
    "QvisLayout\0valueChanged(int)\0value\0\0"
    "saveData()\0createAccBox()\0createAngBox()\0"
    "createPowerBox()\0createConnectBox()\0"
    "createVideoBox()\0createMovementBox()\0"
    "createControls()\0"
};

void QvisLayout::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QvisLayout *_t = static_cast<QvisLayout *>(_o);
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->saveData(); break;
        case 2: _t->createAccBox(); break;
        case 3: _t->createAngBox(); break;
        case 4: _t->createPowerBox(); break;
        case 5: _t->createConnectBox(); break;
        case 6: _t->createVideoBox(); break;
        case 7: _t->createMovementBox(); break;
        case 8: _t->createControls(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QvisLayout::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QvisLayout::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QvisLayout,
      qt_meta_data_QvisLayout, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QvisLayout::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QvisLayout::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QvisLayout::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QvisLayout))
        return static_cast<void*>(const_cast< QvisLayout*>(this));
    return QDialog::qt_metacast(_clname);
}

int QvisLayout::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void QvisLayout::valueChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
