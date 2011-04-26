#include "XmlReader.h"

XmlReader::XmlReader()
{
	xmlReader = NULL;
	fileName = "";
}

XmlReader::~XmlReader()
{
	xmlFreeTextReader(xmlReader);
}

bool XmlReader::GetAttributeCount(int* pnAttributeCount)
{
	(*pnAttributeCount) = xmlTextReaderAttributeCount(xmlReader);
	if (XML_FAILED(*pnAttributeCount))
	{
		XML_ERROR("Error, Method GetAttributeCount");
		return false;
	}
	return true;
}

bool XmlReader::GetBaseUri(string* pBaseUri)
{
	const xmlChar* baseUri;
	
	baseUri = xmlTextReaderConstBaseUri(xmlReader);
	if (baseUri == NULL)
		return false;

	(*pBaseUri) = (const char*)(baseUri);
	return true;
}


bool XmlReader::GetDepth(int* pDepth)
{
	(*pDepth) = xmlTextReaderDepth(xmlReader);
	if (XML_FAILED(*pDepth))
	{
		XML_ERROR("Error, Method GetDepth");
		return false;
	}
	return true;
}

bool XmlReader::GetLineNumber(int* pLineNumber)
{
	(*pLineNumber) = xmlTextReaderGetParserLineNumber(xmlReader);
	
	return ((*pLineNumber) != 0);
}

bool XmlReader::GetLinePosition(int* pLinePosition)
{
	(*pLinePosition) = xmlTextReaderGetParserColumnNumber(xmlReader);

	return ((*pLinePosition) != 0);
}

bool XmlReader::GetLocalName(string* pLocalName)
{
	const xmlChar* localName;

	localName = xmlTextReaderConstLocalName(xmlReader);

	if(localName == NULL)
		return false;

	(*pLocalName) = (const char*)localName;
	return true;
}

bool XmlReader::GetNamespaceUri (string* pNamespaceUri)
{
	const xmlChar* namespaceUri;

	namespaceUri = xmlTextReaderConstNamespaceUri(xmlReader);

	if(namespaceUri == NULL)
		return false;
	
	(*pNamespaceUri) = (const char*)namespaceUri;
	return true;
}

bool XmlReader::GetNodeType(XmlNodeType* pXmlNodeType)
{
	(*pXmlNodeType) = (XmlNodeType)xmlTextReaderNodeType(xmlReader);
	if (XML_FAILED(*pXmlNodeType))
	{
		XML_ERROR("Error, Method GetNodeType");
		return false;
	}
	return true;
}

bool XmlReader::GetPrefix(string* pPrefix)
{	
	const xmlChar* prefix;

	prefix = xmlTextReaderConstPrefix(xmlReader);

	if(prefix == NULL)
		return false;
	
	(*pPrefix) = (const char*)prefix;
	return true;
}

bool XmlReader::GetQualifiedName(string* pQualifiedName)
{
	const xmlChar* qualifiedName;

	qualifiedName = xmlTextReaderConstName(xmlReader);

	if(qualifiedName == NULL)
		return false;
	
	(*pQualifiedName) = (const char*)qualifiedName;
	return true;
}

bool XmlReader::GetValue(string* pValue)
{
	const xmlChar* value;

	value = xmlTextReaderConstValue(xmlReader);

	if (value == NULL)
		return false;

	(*pValue) = (const char*)value;
	return true;
}

bool XmlReader::IsDefault()
{	
	return (xmlTextReaderIsDefault(xmlReader) == 1);
}

bool XmlReader::IsEmptyElement()
{
	return (xmlTextReaderIsEmptyElement(xmlReader) == 1);
}

bool XmlReader::MoveToAttributeByName(const string& localName, const string& namespaceUri)
{
	
	if (XML_FAILED((result = xmlTextReaderMoveToAttributeNs(xmlReader, BAD_CAST localName.c_str(), BAD_CAST namespaceUri.c_str()))))
	{
		XML_ERROR("Error, Method MoveToAttributeByName");
		return false;
	}

	return XML_SUCCEEDED(result);
}

bool XmlReader::MoveToElement()
{
	if (XML_FAILED((result = xmlTextReaderMoveToElement(xmlReader))))
	{
		XML_ERROR("Error, Method MoveToElement");
		return false;
	}
	return XML_SUCCEEDED(result);
}

bool XmlReader::MoveToFirstAttribute()
{
	if (XML_FAILED((result = xmlTextReaderMoveToFirstAttribute(xmlReader))))
	{
		XML_ERROR("Error, Method MoveToFirstAttribute");
		return false;
	}
	return XML_SUCCEEDED(result);
}

bool XmlReader::MoveToNextAttribute()
{
	if (XML_FAILED((result = xmlTextReaderMoveToNextAttribute(xmlReader))))
	{
		XML_ERROR("Error, Method MoveToNextAttribute");
		return false;
	}
	return XML_SUCCEEDED(result);
}

bool XmlReader::Open(string fileName, int options)
{
	this->fileName = fileName;
	if(xmlReader == NULL)
	{
		xmlReader = xmlReaderForFile(fileName.c_str(), NULL, options);
	}
	else
	{
		result = xmlReaderNewFile(xmlReader, fileName.c_str(), NULL, options);
	}

	if(xmlReader == NULL || XML_FAILED(result))
	{
		XML_ERROR("Error Opening File");
		fileName = "";
		return false;
	}

	return true;
}

bool XmlReader::Read(XmlElement** root)
{
	static XmlNodeType nodeType;
	static string localName;
	static string value;
	static int attribCount;
	
	XmlElement* headElement = NULL;

	stack<XmlElement*> openNodes;
	
#pragma warning(disable : 4482)

	while(this->Read(&nodeType))
	{
		switch(nodeType)
		{
		case XmlNodeType::Element:
			if (!this->GetLocalName(&localName))
				return false;

			if(headElement == NULL)
			{
				headElement = new XmlElement();
				headElement->Name(localName);
				this->GetAttributeCount(&attribCount);
				for(int i = 0; i < attribCount; ++i)
				{
					this->MoveToNextAttribute();
					this->GetLocalName(&localName);
					this->GetValue(&value);
					headElement->AddAttribute(localName, value);
				}

				(*root) = headElement;
				openNodes.push(headElement);
				break;
			}
			else
			{
				XmlElement* child = new XmlElement();
				child->Name(localName);

				this->GetAttributeCount(&attribCount);
				for(int i = 0; i < attribCount; ++i)
				{
					this->MoveToNextAttribute();
					this->GetLocalName(&localName);
					this->GetValue(&value);
					child->AddAttribute(localName, value);
				}

				openNodes.top()->AddElement(child);

				this->MoveToElement();
				if(!this->IsEmptyElement())
					openNodes.push(child);
			}
			break;
		case XmlNodeType::Text:
			this->GetValue(&value);
			openNodes.top()->Value(value);
			break;
		case XmlNodeType::EndElement:
			openNodes.pop();
			break;
		}
	}

#pragma warning(default : 4482)

	return true;
}

bool XmlReader::Read(XmlNodeType* pXmlNodeType)
{
	if (XML_FAILED((result = xmlTextReaderRead(xmlReader))))
	{
		XML_ERROR("Error, Method Read");
		return false;
	}
	
	(*pXmlNodeType) = (XmlNodeType)xmlTextReaderNodeType(xmlReader);
	return XML_SUCCEEDED(result);
}