/*****************************************************************
File: XmlReader.h
Author: Jordan Charette
Created: 1/14/09
*****************************************************************/

#ifndef XML_READER_H_
#define XML_READER_H_

#pragma warning(disable : 4996)

#pragma comment(lib, "Third Party/libxml/lib/Release/LibXML.lib")

#include <cstdio>
#include <stack>
#include <string>
#include <libxml/xmlreader.h>
#include "XmlElement.h"
#include "XmlMacros.h"

using std::stack;
using std::string;

//!Responsible for reading XML files.
class XmlReader
{
private:
	//!Used to store name of the currently opened file.
	string fileName;
	//!Used to store the result of IXmlReader method calls.
	int result;
	//!Pointer to an XmlReader object.
	xmlTextReaderPtr xmlReader;

public:

	//!Enumeration for xml parsing options.
	enum XmlParseOptions
	{
		//!Recover on errors.
		Recover = 1,
		//!Substitute entities.
		NoEntities = 2, 
		//!Load the external subset.
		DTDLoad = 4,
		//!Default DTD attributes.
		DTDAttributes = 8, 
		 //!Validate with the DTD.
		DTDValidate = 16,
		//!Suppress error reports.
		NoErrors = 32,
		//!Suppress warning reports.
		NoWarnings = 64, 
		//!Pedantic error reporting.
		PedanticErrors = 128, 
		//!Remove blank nodes.
		NoBlanks = 256, 
		//!Use the SAX1 interface internally.
		Sax1 = 512,
		//!Implement XInclude substitition.
		XInclude = 1024,
		//!Forbid network access.
		NoNetwork = 2048, 
		//!Do not reuse the context dictionnary.
		NoDictionary = 4096, 
		//!Remove redundant namespaces declarations.
		NamespaceClean = 8192, 
		//!Merge CDATA as text nodes.
		NoCData = 16384, 
		//!Do not generate XINCLUDE START/END nodes.
		NoXInclude = 32768, 
		//!Compact small text nodes; no modification of the tree allowed afterwards.
		Compact = 65536, 
		//!Parse using XML-1.0 before update 5.
		OldXml = 131072, 
		//!Do not fixup XINCLUDE xml:base uris.
		NoBaseFix = 262144,
		//!Relax any hardcoded limit from the parser.
		Huge = 524288,
		//!Parse using SAX2 interface from before 2.7.0.
		OldSax = 1048576
	};

	//!Enumeration of the types of nodes the xml reader reads.
	enum XmlNodeType
	{
		None = XML_READER_TYPE_NONE,
		//!Xml element node.
		Element = XML_READER_TYPE_ELEMENT,
		//!Xml attribute node.
		Attribute = XML_READER_TYPE_ATTRIBUTE,
		//!Xml text node.
		Text = XML_READER_TYPE_TEXT,
		//!Xml CData node.
		CData = XML_READER_TYPE_CDATA,
		//!Xml MeshRep reference node.
		EntityReference = XML_READER_TYPE_ENTITY_REFERENCE,
		//!Xml entity node
		Entity = XML_READER_TYPE_ENTITY,
		//!Xml processing instruction node.
		ProcessingInstruction = XML_READER_TYPE_PROCESSING_INSTRUCTION,
		//!Xml comment node.
		Comment = XML_READER_TYPE_COMMENT,
		//!Xml document node.
		Document = XML_READER_TYPE_DOCUMENT,
		//!Xml document type node.
		DocumentType = XML_READER_TYPE_DOCUMENT_TYPE,
		//!Xml document fragment node.
		DocumentFragment = XML_READER_TYPE_DOCUMENT_FRAGMENT,
		//!Xml notation node.
		Notation = XML_READER_TYPE_NOTATION,
		//!Xml whitespace node.
		Whitespace = XML_READER_TYPE_WHITESPACE,
		//!Xml significant white space node. 
		SignificantWhitespace = XML_READER_TYPE_SIGNIFICANT_WHITESPACE,
		//!Xml end element node.
		EndElement = XML_READER_TYPE_END_ELEMENT,
		//!Xml end entity node.
		EndEntity = XML_READER_TYPE_END_ENTITY,
		//!Xml declaration node.
		XmlDeclaration = XML_READER_TYPE_XML_DECLARATION
	};

	//!Initializes a XmlReader object for reading XML files.
	XmlReader();
	//!Destroys a XmlReader object and cleans up any resources used.
	~XmlReader();
	//!Returns the number of attributes in the current node.
	/*!
	*	\param pnAttributeCount The number of attributes for the current node. The passed in value cannot be NULL. 
	*	\return Returns true if no errors are generated.
	*/
	bool GetAttributeCount(int* pnAttributeCount);
	//!Gets the base URI of the token, if applicable.
	/*!
	*	\param pBaseUri The base URI of the token.
	*	\return Returns true if no errors are generated.
	*/
	bool GetBaseUri(string* pBaseUri);
	//!Returns the depth of the current node in the document.
	/*!
	*	\param pDepth The depth of the current node. The passed in value cannot be NULL.
	*	\return Returns true if no errors are generated.
	*/
	bool GetDepth(int* pDepth);
	//!Gets the line number where the reader is positioned in the document.
	/*!
	*	\param pLineNumber Returns the line number
	*	\return Returns true if no errors are generated.
	*/
	bool GetLineNumber(int* pLineNumber);
	//!	Gets the line position where the reader is positioned in the document.
	/*!
	*	\param pLinePosition Returns the line position.
	*	\return Returns true if no errors are generated.
	*/
	bool GetLinePosition(int* pLinePosition);
	//!Gets the local name of the node that the reader is currently positioned on.
	/*!
	*	Gets the local name of the node that the reader is currently positioned on. 
	*	If no local name is available, this method returns an empty string.
	*	\param pLocalName The local name of the node that the reader is currently positioned on.
	*	\return Returns true if no errors are generated.
	*/
	bool GetLocalName(string* pLocalName);
	//!Gets the namespace URI of the node that the reader is currently positioned on.
	/*!
	*	Gets the namespace URI of the node that the reader is currently positioned on. 
	*	If no namespace URI is available, returns an empty string.
	*	\param pNamespaceUri The namespace URI of the node that the reader is currently positioned on.
	*	\return Returns true if no errors are generated.
	*/
	bool GetNamespaceUri (string* pNamespaceUri);
	//!Provides the type of the current node.
	/*!
	*	\param pXmlNodeType The type of node that the reader is currently positioned on. This value cannot be NULL.
	*	\return Returns true if no errors are generated.
	*/
	bool GetNodeType(XmlNodeType* pXmlNodeType);
	//!Gets the namespace prefix of the node that the reader is currently positioned on.
	/*!
	*	Gets the namespace prefix of the node that the reader is currently positioned on. 
	*	If no prefix is available, returns an empty string.
	*	\param pPrefix The prefix of the node that the reader is currently positioned on.
	*	\return Returns true if no errors are generated.
	*/
	bool GetPrefix(string* pPrefix);
	//!Returns the specified property. A program can get properties at any time.
	/*!
	*	\param nProperty The enumeration that identifies the property to be retrieved.
	*	\param ppValue Returns the property value. This argument cannot be NULL. 
	*	\return Returns true if no errors are generated.
	*/
	bool GetProperty(int nProperty, int** ppValue);
	//!Gets the qualified name of the node that the reader is currently positioned on. 
	/*!
	*	Gets the qualified name of the node that the reader is currently positioned on. 
	*	If no qualified name is available, returns an empty string.
	*	\param pQualifiedName The qualified name of the node that the reader is currently positioned on.
	*	\return Returns true if no errors are generated.
	*/
	bool GetQualifiedName(string* pQualifiedName);
	//!Returns the value of the current token, if applicable.
	/*!
	*	\param pValue The value of the token. The returned string is always NULL terminated.
	*		The passed in value cannot be NULL.
	*	\return Returns true if no errors are generated.
	*/
	bool GetValue(string* pValue);
	//!Indicates whether the attribute was specified in the source document or implied by the Document Type Definition (DTD).
	/*!
	*	\return Returns true if the attribute was implied by the DTD. 
	*		If the attribute was not implied by the DTD, or the node is not an attribute, returns false.
	*/
	bool IsDefault();
	//!This method allows the client to determine the difference between elements that have a closing tag
	/*!
	*	This method allows the client to determine the difference between elements that have a closing tag, 
	*	but do not contain content, and elements that do not have a closing tag.
	*	\return Returns true if the current element ends with />; otherwise, returns false.
	*/
	bool IsEmptyElement();
	//!Moves the reader to the attribute with the specified name.
	/*!
	*	\param localName The local name of the attribute.
	*	\param namespaceUri The local name of the attribute.
	*	\return Returns true if no errors are generated.
	*/
	bool MoveToAttributeByName(const string& localName, const string& namespaceUri);
	//!Moves to the element that owns the current attribute node. 
	/*!
	*	After navigating through the attributes on an element, 
	*	use this method to move the reader back to the element.
	*	\return Returns true if no errors are generated.
	*/
	bool MoveToElement();
	//!Moves the reader position to the first attribute within the current node. 
	/*!
	*	\return Returns true if no errors are generated.
	*/
	bool MoveToFirstAttribute();
	//!Advances the reader to the next attribute. 
	/*!
	*	\return Returns true if no errors are generated.
	*/
	bool MoveToNextAttribute();
	//!
	/*!
	*	\param fileName Name of file to open for reading.
	*	\param fileMode File mode for the file (default: STGM_READ).
	*	\return Returns true if no errors are generated.
	*/
	bool Open(string fileName, int options = 0);
	//!Reads XML data into a XmlElement tree.
	/*!
	*	\param root Pointer to the initialized XmlElement tree.
	*	\return Returns true if no errors are generated.
	*/
	bool Read(XmlElement** root);
	//!Reads the next node from the stream and returns the type of the node.
	/*!
	*	\param pXmlNodeType Returns the type of node that is read. 
	*		This value can be NULL, in which case the node type will not be returned.
	*	\return Returns true if no errors are generated.
	*/
	bool Read(XmlNodeType* pXmlNodeType);
};

#endif