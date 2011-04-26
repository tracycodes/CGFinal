#include "XmlMacros.h"

char cBuffer[XML_BUFFER_SIZE];

//!Initializes the XML parsing library. Call this before using any XML related classes.
void InitializeXml()
{
	LIBXML_TEST_VERSION
}

//!Releases the resources used by the XML parsing library.  Call this when finished with XML library.
void ReleaseXml()
{
	xmlCleanupParser();
}
