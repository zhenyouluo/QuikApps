#ifndef LIBERTYPLUGIN_GLOBAL_H
#define LIBERTYPLUGIN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBERTYPLUGIN_LIBRARY)
#  define LIBERTYPLUGINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBERTYPLUGINSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBERTYPLUGIN_GLOBAL_H