#include "Common.h"

void Log( const char* pszFormat, ...)
{
	char szBuff[1024];

	va_list ap;
	va_start( ap, pszFormat);
	vsnprintf_s( szBuff, 1024, 1024, pszFormat, ap);
	va_end( ap);

	OutputDebugString( szBuff);
	OutputDebugString( "\n");
}