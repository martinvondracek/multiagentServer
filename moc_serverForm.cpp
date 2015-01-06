/****************************************************************************
** Meta object code from reading C++ file 'serverForm.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "serverForm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serverForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_serverForm[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      33,   11,   11,   11, 0x0a,
      55,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_serverForm[] = {
    "serverForm\0\0startServerClicked()\0"
    "startMappingClicked()\0stopMappingClicked()\0"
};

void serverForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        serverForm *_t = static_cast<serverForm *>(_o);
        switch (_id) {
        case 0: _t->startServerClicked(); break;
        case 1: _t->startMappingClicked(); break;
        case 2: _t->stopMappingClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData serverForm::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject serverForm::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_serverForm,
      qt_meta_data_serverForm, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &serverForm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *serverForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *serverForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_serverForm))
        return static_cast<void*>(const_cast< serverForm*>(this));
    return QDialog::qt_metacast(_clname);
}

int serverForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
