#include "XmlElement.h"

XmlElement::XmlElement()
{
	this->name = "";
	elements = NULL;
	attributes = NULL;
	parent = NULL;
}

XmlElement::XmlElement(string name)
{
	this->name = name;
	elements = NULL;
	attributes = NULL;
	parent = NULL;
}

XmlElement::~XmlElement()
{
	if(elements != NULL)
	{
		for(ElementNodes::iterator elementIter = elements->begin();
			elementIter != elements->end(); ++elementIter)
		{
			if(elementIter->second != NULL)
			{
				for(ElementCollection::iterator iter = elementIter->second->begin();
					iter != elementIter->second->end(); ++iter)
				{
					delete (*iter);
				}

				delete elementIter->second;
			}
		}

		delete elements;
	}
	if(attributes != NULL)
		delete attributes;
}

void XmlElement::AddElement(XmlElement* element)
{
	if(elements == NULL)
	{
		elements = new ElementNodes();
	}

	ElementNodes::iterator findIter;
	string localName = element->Name();
	if((findIter = elements->find(localName)) == elements->end())
	{
		ElementCollection* elementCollection = new ElementCollection();
		ElementRet ret = elements->insert(make_pair(localName, elementCollection));
		findIter = ret.first;
	}

	element->parent = this;
	findIter->second->push_back(element);
}

bool XmlElement::AddAttribute(string attributeName, string value)
{
	if(attributes == NULL)
	{
		attributes = new map<string, string>();
	}

	AttributeRet ret = attributes->insert(make_pair(attributeName, value));
	return ret.second;
}

XmlElement::AttributeCollection* XmlElement::Attributes()
{
	return attributes;
}

bool XmlElement::GetAttribute(string attributeName, string* value)
{
	if(attributes == NULL)
		return false;

	AttributeCollection::iterator attribIter = attributes->find(attributeName);

	if(attribIter == attributes->end())
		return false;

	(*value) = attribIter->second;
	return true;
}

XmlElement::ElementNodes* XmlElement::GetChildrenElements()
{
	return elements;
}

bool XmlElement::GetElement(string localName, XmlElement::ElementCollection::iterator &first,
							XmlElement::ElementCollection::iterator &last)
{
	if(elements == NULL)
		return false;

	ElementNodes::iterator elementIter = elements->find(localName);

	if(elementIter == elements->end())
		return false;

	XmlElement::ElementCollection* elementInstances = elementIter->second;

	first = elementInstances->begin();
	last = elementInstances->end();

	return true;
}

XmlElement* XmlElement::GetElement(string localName, int index)
{
	if(elements == NULL)
		return NULL;

	ElementNodes::iterator iter = elements->find(localName);
	if(iter == elements->end())
		return NULL;

	return (*elements->find(localName)->second)[index];
}
	
void XmlElement::GetElementCount(string localName, int* count)
{
	if(elements == NULL)
		(*count) = 0;
	else
		(*count) = elements->find(localName)->second->size();
}

void XmlElement::Name(string name)
{
	this->name = name;
}
string XmlElement::Name()
{
	return name;
}

XmlElement* XmlElement::Parent()
{
	return parent;
}

void XmlElement::Value(string value)
{
	this->value = value;
}

string XmlElement::Value()
{
	return value;
}
