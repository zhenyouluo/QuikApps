#ifndef MIME_TYPES_H
#define MIME_TYPES_H

#include "apptypes.h"

extern  MapStrStr *contentType;

void setupContentTypes();
QString identifyContentType( char *url );


#endif
