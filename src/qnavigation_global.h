#ifndef SRC_GLOBAL_H
#define SRC_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QNAVIGATION_LIBRARY)
#  define QNAVIGATION_SHARED_EXPORT Q_DECL_EXPORT
#else
#  define QNAVIGATION_SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SRC_GLOBAL_H
