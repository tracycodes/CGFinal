/*****************************************************************
File: XmlWriter.h
Author: Jordan Charette
Created: 1/14/09
*****************************************************************/

#ifndef XML_WRITER_H_
#define XML_WRITER_H_

#pragma warning(disable : 4996)

#include <string>
#include "XmlElement.h"
#include "XmlMacros.h"
#include <stdio.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>

using std::string;

#define XML_INDENT
#define XML_INDENT_STRING (&string(3, ' '))
#define STANDALONE_YES (&string("yes"))
#define STANDALONE_NO (&string("no"))
#define STANDALONE_DEFAULT NULL
#define VERSION_DEFAULT (&string("1.0"))
#define ENCODING_DEFAULT NULL

//!Responsible for writing XML files.
class XmlWriter
{
private:
	//!holds the name of the file that is currently opened.
	string fileName;
	//!holds the result of IXmlWriter method calls.
	intptr_t result;
	//!pointer to an IXmlWriter. 
	xmlTextWriterPtr xmlWriter;

public:
	//!Initializes a XmlWriter object for writing XML files.
	XmlWriter();
	//!Destroys and cleans up a XmlWriter object.
	~XmlWriter();
	//!Flushes whatever is in the buffer to the underlying stream, then flushes the underlying stream.
	/*!
	*	\return Returns true if no errors are generated.	
	*/
	bool Flush();
	//!Opens a file stream to write XML to.
	/*!
	*	\param fileName Name of the file to open/create.
	*	\param compression Compress the output?
	*	\return Returns true if no errors are generated.
	*/
	bool Open(string fileName, int compression = 0);
	//!Writes an attribute.
	/*!
	*	\param prefix The namespace prefix for the attribute.
	*	\param localName The local name of the attribute.
	*	\param namespaceUri The namespace URI for the attribute.
	*	\param value The value of the attribute.
	*	\return Returns true if no errors are generated.
	*/
	bool WriteAttributeString(const string* prefix, const string* localName, const string* namespaceUri, const string* value);
	//!Writes out a CDATA section that contains the specified text. 
	/*!
	*	\param text The content of the CDATA section 
	*	\return Returns true if no errors are generated.
	*/
	bool WriteCData(const string* text);
	//!Writes a character entity for the provided Unicode character value. This method writes the character entity in hexadecimal format.
	/*!
	*	\param character The character to write.
	*	\return Returns true if no errors are generated.
	*/
	bool WriteCharEntity(char character);
	//!Writes out the specified text content, escaping markup.
	/*!
	*	\param characters The characters to write. NULL is only valid if count is zero.
	*	\param count The number of characters to be written.
	*	\return Returns true if no errors are generated.
	*/
	bool WriteChars(const string* characters, int count);
	//!Writes out a comment that contains the specified text.
	/*!
	*	\param comment The text of the comment.
	*	\return Returns true if no errors are generated.
	*/
	bool WriteComment(const string* comment);
	//!Writes out the <!DOCTYPE ...> declaration with the specified name and optional attributes.
	/*!
	*	\param name The name of the DOCTYPE. This parameter cannot be empty or NULL.
	*	\param publicId If non-NULL, this method writes PUBLIC "pubid" "sysid" 
	*		where pubid and sysid are replaced with the value of the specified arguments. 
	*		NULL indicates that the public ID is to be omitted; this is not equivalent to an empty string.
	*	\param systemId If publicId is NULL and systemId is non-NULL, the method writes SYSTEM "sysid" 
	*		where sysid is replaced with the value of this argument. 
	*		NULL indicates that the system ID is to be omitted; this is not equivalent to an empty string.
	*	\param subset If non-NULL, the method writes [subset] where subset is replaced with the value of this argument. 
	*		If this parameter is NULL, no subset is written out. If no subset is written, the square brackets are not written either. 
	*		NULL is not equivalent to an empty string; an empty string argument will cause the brackets to be written.
	*	\return Returns true if no errors are generated.
	*/
	bool WriteDocType(const string* name, const string* publicId, const string* systemId, const string* subset);
	//!Writes out an element with the specified prefix, name, namespace, and value.
	/*!
	*	\param prefix The namespace prefix of the element.
	*	\param localName The local name of the element.
	*	\param namespaceUri The local name of the element.
	*	\param value The value of the element. An empty string indicates that this element has an empty value.
	*	\return Returns true if no errors are generated.
	*/
	bool WriteElementString(const string* prefix, const string* localName, const string* namespaceUri, const string* value);
	//!This method closes any open elements or attributes, then closes the current document.
	/*!
	*	\return Returns true if no errors are generated.
	*/
	bool WriteEndDocument();
	//!Closes one element.
	/*!
	*	Closes one element. If the element contains no content, 
	*	this method writes a short end tag ("/>"). Otherwise, this method writes the full end tag. 
	*	\return Returns true if no errors are generated.
	*/
	bool WriteEndElement();
	//!Writes out an entity reference with the specified name.
	/*!
	*	\param paramEntity True if this is a parameter entity, false if not.
	*	\param name The name of the entity reference.
	*	\return Returns true if no errors are generated.
	*/
	bool WriteEntityRef (bool paramEntity, const string* name);
	//!Closes one element and pops the corresponding namespace scope. This method always writes the full end tag.
	/*!
	*	\return Returns true if no errors are generated.
	*/
	bool WriteFullEndElement();	
	//!	Writes out the specified name, ensuring that the name is valid according to the XML specification
	/*!
	*	\param name The name to write.
	*	\return Returns true if no errors are generated.
	*/
	bool WriteName(const string* name);
	//!Writes out the specified name, ensuring that the name is a valid NmToken according to the XML specification.
	/*!
	*	\param nmToken The name to write.
	*	\return Returns true if no errors are generated.
	*/
	bool WriteNmToken(const string* nmToken);
	//!Writes a processing instruction.
	/*!
	*	\param name The name of the processing instruction.
	*	\param text The text content of the processing instruction.
	*	\return Returns true if no errors are generated.
	*/
	bool WriteProcessingInstruction(const string* name, const string* text);
	//!Writes out the specified namespace-qualified name by looking up the prefix that is in scope for the specified namespace.
	/*!
	*	\param localName  The local name to write.
	*	\param namespaceUri  The namespace URI of the name to write.
	*	\return Returns true if no errors are generated.
	*/
	bool WriteQualifiedName(const string* localName,const string* namespaceUri);
	//!This method allows the caller to write out raw markup manually. 
	/*!
	*	This method allows the caller to write out raw markup manually. 
	*	You can avoid creating entities for special characters by using this method.
	*	\param data The data to write.
	*	\return Returns true if no errors are generated.
	*/
	bool WriteRaw(const string* data);
	//!Writes out raw markup manually. Using this method allows an application to avoid creating entities for special characters.
	/*!
	*	\param characters  characters to write.
	*	\param count The number of characters to write.
	*	\return Returns true if no errors are generated.
	*/
	bool WriteRawChars(const string* characters, int count);
	//!Writes out the XML declaration...
	/*!
	*	Writes out the XML declaration with the version, encoding, and standalone information. 
	*	\param version The XML version to use.  Default is 1.0
	*	\param encoding The encoding to use. Default is UTF-8.
	*	\param standalone If XmlStandalone_Omit does not write a standalone attribute in the XML declaration, one of the following occurs:
	*		If XmlStandalone_No, the writer writes standalone="no".
	*		If XmlStandalone_Yes, the writer writes standalone="yes".
	*	\return Returns true if no errors are generated.
	*/
	bool WriteStartDocument(const string* version = VERSION_DEFAULT, const string* encoding = ENCODING_DEFAULT, const string* standalone = STANDALONE_DEFAULT);
	//!	Writes out the specified start tag and associates it with the specified namespace.
	/*!
	*	\param prefix The namespace prefix of the element.
	*	\param localName The local name of the element.
	*	\param namespaceUri  The namespace URI of the element.
	*	\return Returns true if no errors are generated.
	*/
	bool WriteStartElement (const string* prefix, const string* localName, const string* namespaceUri);
	//!Writes out the specified text content, escaping any markup in the content.
	/*!
	*	\param text  The text to write.
	*	\return Returns true if no errors are generated.
	*/
	bool WriteString (const string* text);
	//!Forces the generation of a surrogate character entity for the specified string value.
	/*!
	*	\param lowChar Low-surrogate for the pair. The code value must be in the range U+DC00 - U+DFFF.
	*	\param highChar High-surrogate for the pair. The code value must be in the range U+D800 - U+DBFF.
	*	\return Returns true if no errors are generated.
	*/
	bool WriteSurrogateCharEntity(char lowChar, char highChar);
	//!Writes out the specified white space.
	/*!
	*	\param whitespace  The white space to write.
	*	\return Returns true if no errors are generated.
	*/
	bool WriteWhitespace(const string* whitespace);
	//!Writes an XML document based off a XmlElement tree.
	/*!
	*	\param rootElement Parent of a XmlElement tree. 
	*	\return Returns true if no errors are generated.
	*/
	bool WriteXmlElement(XmlElement* rootElement);

};

#endif