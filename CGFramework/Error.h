#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#define SHOW_ERROR(s,f,l) char buf[1024]; sprintf_s( buf, "File: %s\nLine: %d\n%s",f,l,s); MessageBox( 0, buf, "Error", MB_OK );

#endif