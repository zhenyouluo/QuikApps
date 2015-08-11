#ifndef ERROR_H
#define ERROR_H

#include <QFile>
#include <QTextStream>

extern QFile *error;
extern QTextStream *err;
#define ERR (*err)
#ifndef USE_QT5
#define FULLPATH  (QUrl::RemoveUserInfo|QUrl::RemoveAuthority|QUrl::RemoveScheme|QUrl::RemovePort|QUrl::RemovePassword|QUrl::RemoveQuery|QUrl::RemoveFragment)
#define SCHEMEFULLPATH  (QUrl::RemoveUserInfo|QUrl::RemoveAuthority|QUrl::RemovePort|QUrl::RemovePassword|QUrl::RemoveFragment)
#endif
#endif // ERROR_H
