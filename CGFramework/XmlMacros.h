#ifndef XML_MACROS_H_
#define XML_MACROS_H_

#include <libxml/xmlversion.h>
#include <libxml/parser.h>

//!Macro for determining the size of the error message buffer.
#define XML_BUFFER_SIZE 256

//!Global character buffer used for error messages.
extern char cBuffer[XML_BUFFER_SIZE];

//!Macro for outputing error messages related to the XML library.
#define XML_ERROR(errorMessage) \
sprintf(cBuffer, "%s\nFile: %s", errorMessage, fileName.c_str()); \
	fprintf(stderr, cBuffer);

#define XML_STRING(pString) (pString == NULL ? NULL : BAD_CAST pString->c_str())

//!Macro for describing a failed XML result.
#define XML_FAILED(result) (result == -1)

//!Macro for describing a successful XML result.
#define XML_SUCCEEDED(result) (result == 1)

//!Initializes the XML parsing library. Call this before using any XML related classes.
void InitializeXml();

//!Releases the resources used by the XML parsing library.  Call this when finished with XML library.
void ReleaseXml();

#endif
