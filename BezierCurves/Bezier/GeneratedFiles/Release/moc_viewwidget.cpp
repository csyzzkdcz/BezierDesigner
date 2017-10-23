/****************************************************************************
** Meta object code from reading C++ file 'viewwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../viewwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'viewwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ViewWidget_t {
    QByteArrayData data[20];
    char stringdata0[263];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ViewWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ViewWidget_t qt_meta_stringdata_ViewWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ViewWidget"
QT_MOC_LITERAL(1, 11, 13), // "setDrawStatus"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 14), // "delete_Polygon"
QT_MOC_LITERAL(4, 41, 10), // "Open_Curve"
QT_MOC_LITERAL(5, 52, 10), // "Save_Curve"
QT_MOC_LITERAL(6, 63, 14), // "Subdivision_op"
QT_MOC_LITERAL(7, 78, 1), // "t"
QT_MOC_LITERAL(8, 80, 12), // "Elevation_op"
QT_MOC_LITERAL(9, 93, 9), // "Insert_op"
QT_MOC_LITERAL(10, 103, 15), // "Delete_point_op"
QT_MOC_LITERAL(11, 119, 13), // "Evaluation_op"
QT_MOC_LITERAL(12, 133, 15), // "Intersection_op"
QT_MOC_LITERAL(13, 149, 19), // "Check_Draw_Polygon_"
QT_MOC_LITERAL(14, 169, 2), // "bv"
QT_MOC_LITERAL(15, 172, 18), // "Check_Draw_Bezier_"
QT_MOC_LITERAL(16, 191, 13), // "Check_Simple_"
QT_MOC_LITERAL(17, 205, 18), // "Check_Design_name_"
QT_MOC_LITERAL(18, 224, 18), // "Check_Interpolate_"
QT_MOC_LITERAL(19, 243, 19) // "Check_Intersection_"

    },
    "ViewWidget\0setDrawStatus\0\0delete_Polygon\0"
    "Open_Curve\0Save_Curve\0Subdivision_op\0"
    "t\0Elevation_op\0Insert_op\0Delete_point_op\0"
    "Evaluation_op\0Intersection_op\0"
    "Check_Draw_Polygon_\0bv\0Check_Draw_Bezier_\0"
    "Check_Simple_\0Check_Design_name_\0"
    "Check_Interpolate_\0Check_Intersection_"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ViewWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x0a /* Public */,
       3,    0,   95,    2, 0x0a /* Public */,
       4,    0,   96,    2, 0x0a /* Public */,
       5,    0,   97,    2, 0x0a /* Public */,
       6,    1,   98,    2, 0x0a /* Public */,
       8,    0,  101,    2, 0x0a /* Public */,
       9,    0,  102,    2, 0x0a /* Public */,
      10,    0,  103,    2, 0x0a /* Public */,
      11,    1,  104,    2, 0x0a /* Public */,
      12,    0,  107,    2, 0x0a /* Public */,
      13,    1,  108,    2, 0x0a /* Public */,
      15,    1,  111,    2, 0x0a /* Public */,
      16,    1,  114,    2, 0x0a /* Public */,
      17,    1,  117,    2, 0x0a /* Public */,
      18,    1,  120,    2, 0x0a /* Public */,
      19,    1,  123,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QPointF, QMetaType::Double,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::Bool,   14,

       0        // eod
};

void ViewWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ViewWidget *_t = static_cast<ViewWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setDrawStatus(); break;
        case 1: _t->delete_Polygon(); break;
        case 2: _t->Open_Curve(); break;
        case 3: _t->Save_Curve(); break;
        case 4: _t->Subdivision_op((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->Elevation_op(); break;
        case 6: _t->Insert_op(); break;
        case 7: _t->Delete_point_op(); break;
        case 8: { QPointF _r = _t->Evaluation_op((*reinterpret_cast< double(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QPointF*>(_a[0]) = _r; }  break;
        case 9: _t->Intersection_op(); break;
        case 10: _t->Check_Draw_Polygon_((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->Check_Draw_Bezier_((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->Check_Simple_((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->Check_Design_name_((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->Check_Interpolate_((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->Check_Intersection_((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ViewWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ViewWidget.data,
      qt_meta_data_ViewWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ViewWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ViewWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ViewWidget.stringdata0))
        return static_cast<void*>(const_cast< ViewWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ViewWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
