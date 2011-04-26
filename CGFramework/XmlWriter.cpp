#include "XmlWriter.h"

#pragma comment(lib, "Third Party/libxml/lib/Release/LibXML.lib")

XmlWriter::XmlWriter()
{	
	xmlWriter = NULL;
	fileName = "";
}

XmlWriter::~XmlWriter()
{
	xmlFreeTextWriter(xmlWriter);
	xmlWriter = NULL;
}

bool XmlWriter::Flush()
{
	if(XML_FAILED((result = xmlTextWriterFlush(xmlWriter))))
	{
		XML_ERROR("Error, Method: Flush");
		return false;
	}

	xmlFreeTextWriter(xmlWriter);
	xmlWriter = NULL;

	return true;
}

bool XmlWriter::Open(string fileName, int compression)
{
	this->fileName = fileName;
	if(xmlWriter != NULL)
	{
		xmlFreeTextWriter(xmlWriter);
		xmlWriter = NULL;
	}
	
	xmlWriter = xmlNewTextWriterFilename(fileName.c_str(), compression);

	if(xmlWriter == NULL)
	{
		XML_ERROR("Error Opening File");
		fileName = "";
		return false;
	}

#if defined(XML_INDENT)
	xmlTextWriterSetIndent(xmlWriter, true);
	xmlTextWriterSetIndentString(xmlWriter, XML_STRING(XML_INDENT_STRING));
#endif

	return true;
}

bool XmlWriter::WriteAttributeString(const string* prefix, const string* localName, const string* namespaceUri, const string* value)
{
	if(XML_FAILED((result = xmlTextWriterWriteAttributeNS(
		xmlWriter,
		XML_STRING(prefix), 
		XML_STRING(localName), 
		XML_STRING(namespaceUri), 
		XML_STRING(value)))))
	{
		XML_ERROR("Error, Method: WriteAttributeString");
		return false;
	}

	return true;
}

bool XmlWriter::WriteCData(const string* text)
{
	if(XML_FAILED((result = xmlTextWriterWriteCDATA(xmlWriter, XML_STRING(text)))))
	{
		XML_ERROR("Error, Method: WriteCData");
		return false;
	}
	return true;
}

bool XmlWriter::WriteCharEntity(char character)
{
	//TODO
	return false;
}

bool XmlWriter::WriteChars(const string* characters, int count)
{
	//TODO
	return false;
}

bool XmlWriter::WriteComment(const string* comment)
{
	if(XML_FAILED((result = xmlTextWriterWriteComment(xmlWriter, XML_STRING(comment)))))
	{
		XML_ERROR("Error, Method: WriteComment");
		return false;
	}

	return true;
}

bool XmlWriter::WriteDocType(const string* name, const string* publicId, const string* systemId, const string* subset)
{
	if(XML_FAILED((result = xmlTextWriterWriteDTD(
		xmlWriter,
		XML_STRING(name), 
		XML_STRING(publicId), 
		XML_STRING(systemId), 
		XML_STRING(subset)))))
	{
		XML_ERROR("Error, Method: WriteDocType");
		return false;
	}

	return true;
}

bool XmlWriter::WriteElementString(const string* prefix, const string* localName, const string* namespaceUri, const string* value)
{
	if(XML_FAILED((result = xmlTextWriterWriteElementNS(
		xmlWriter,
		XML_STRING(prefix), 
		XML_STRING(localName), 
		XML_STRING(namespaceUri), 
		XML_STRING(value)))))
	{
		XML_ERROR("Error, Method: WriteElementString");
		return false;
	}

	return true;
}

bool XmlWriter::WriteEndDocument()
{
	if(XML_FAILED((result = xmlTextWriterEndDocument(xmlWriter))))
	{
		XML_ERROR("Error, Method: WriteEndDocument");
		return false;
	}
	return true;
}

bool XmlWriter::WriteEndElement()
{
	if(XML_FAILED((result = xmlTextWriterEndElement(xmlWriter))))
	{
		XML_ERROR("Error, Method: WriteEndElement");
		return false;
	}
	return true;
}

bool XmlWriter::WriteEntityRef (bool paramEntity, const string* name)
{
	if(XML_FAILED((result = xmlTextWriterStartDTDEntity(xmlWriter, paramEntity, XML_STRING(name)))))
	{
		XML_ERROR("Error, Method: WriteEntityRef");
		return false;
	}

	return true;
}

bool XmlWriter::WriteFullEndElement()
{
	if(XML_FAILED((result = xmlTextWriterFullEndElement(xmlWriter))))
	{
		XML_ERROR("Error, Method: WriteFullEndElement");
		return false;
	}
	return true;
}

bool XmlWriter::WriteName(const string* name)
{
	//TODO
	return false;
}

bool XmlWriter::WriteNmToken(const string* nmToken)
{
	//TODO
	return false;
}

bool XmlWriter::WriteProcessingInstruction(const string* name, const string* text)
{
	if(XML_FAILED((result = xmlTextWriterWritePI(xmlWriter, XML_STRING(name), XML_STRING(text)))))
	{
		XML_ERROR("Error, Method: WriteNode");
		return false;
	}
	return true;
}

bool XmlWriter::WriteQualifiedName(const string* localName,const string* namespaceUri)
{
	//TODO
	return false;
}

bool XmlWriter::WriteRaw(const string* data)
{
	if(XML_FAILED((result = xmlTextWriterWriteRaw(xmlWriter, XML_STRING(data)))))
	{
		XML_ERROR("Error, Method: WriteRaw");
		return false;
	}
	return true;
}

bool XmlWriter::WriteRawChars(const string* characters, int count)
{
	if(XML_FAILED((result = xmlTextWriterWriteRawLen(xmlWriter, XML_STRING(characters), count))))
	{
		XML_ERROR("Error, Method: WriteRawChars");
		return false;
	}
	return true;
}

bool XmlWriter::WriteStartDocument(const string* version, const string* encoding, const string* standalone)
{
	if(XML_FAILED((result = xmlTextWriterStartDocument(
		xmlWriter, 
		(const char*)XML_STRING(version), 
		(const char*)XML_STRING(encoding), 
		(const char*)XML_STRING(standalone)))))
	{
		XML_ERROR("Error, Method: WriteStartDocument");
		return false;
	}
	return true;
}

bool XmlWriter::WriteStartElement (const string* prefix, const string* localName, const string* namespaceUri)
{
	if(XML_FAILED((result = xmlTextWriterStartElementNS(
		xmlWriter, 
		XML_STRING(prefix), 
		XML_STRING(localName), 
		XML_STRING(namespaceUri)))))
	{
		XML_ERROR("Error, Method: WriteStartElement");
		return false;
	}

	return true;
}

bool XmlWriter::WriteString (const string* text)
{
	if(XML_FAILED((result = xmlTextWriterWriteString(xmlWriter, XML_STRING(text)))))
	{
		XML_ERROR("Error, Method: WriteString");
		return false;
	}

	return true;
}

bool XmlWriter::WriteSurrogateCharEntity(char lowChar, char highChar)
{
	//TODO
	return false;
}

bool XmlWriter::WriteWhitespace(const string* whitespace)
{
	//TODO
	return false;
}

bool XmlWriter::WriteXmlElement(XmlElement *rootElement)
{	
	if(!this->WriteStartElement(NULL, &rootElement->Name(), NULL))
		return false;

	XmlElement::ElementNodes* children = rootElement->GetChildrenElements();
	XmlElement::AttributeCollection* attributes = rootElement->Attributes();

	string value = rootElement->Value();

	if(attributes != NULL)
	{
		for(XmlElement::AttributeCollection::iterator iter = attributes->begin(); iter != attributes->end(); ++iter)
		{
			if(!this->WriteAttributeString(NULL, &iter->first, NULL, &iter->second))
				return false;
		}
	}

	if(value != "")
	{
		if(!this->WriteString(&value))
			return false;
	}

	if(children != NULL)
	{
		for(XmlElement::ElementNodes::iterator iter = children->begin(); iter != children->end(); ++iter)
		{
			XmlElement::ElementCollection* instances = iter->second;
			for(XmlElement::ElementCollection::iterator instanceIter = instances->begin(); 
				instanceIter != instances->end(); ++instanceIter)
			{
				WriteXmlElement((*instanceIter));
			}
		}
	}

	if(!this->WriteEndElement())
		return false;

	return true;
}
