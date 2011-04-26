/*****************************************************************
File: XmlElement.h
Author: Jordan Charette
Created: 1/20/09
*****************************************************************/

#ifndef XML_ELEMENT_H_
#define XML_ELEMENT_H_

#include <map>
#include <string>
#include <vector>

using std::map;
using std::pair;
using std::string;
using std::vector;

//!Describes a XML element (attributes, values, children elements)
class XmlElement
{
public:
	//!Typedef for a collection of attribute values with names of the attributes as keys.
	typedef map< string, string > AttributeCollection;
	//!Typedef for a collection of XmlElements.
	typedef vector<XmlElement*> ElementCollection;
	//!Typedef for a collection of ElementCollections with the names of the elements as keys.
	typedef map< string, ElementCollection* > ElementNodes;

private:
	//!Used for the return type of map::find() method.
	typedef pair< map< string, string>::iterator, bool > AttributeRet;
	//!Used for the return type of map::find() method.
	typedef pair< map< string, ElementCollection* >::iterator, bool > ElementRet;

	//!Used to store the attributes for this XmlElement.
	AttributeCollection* attributes;
	//!Used to store the child elements for this XmlElement.
	ElementNodes* elements;
	//!Stores the name of this XmlElement
	string name;
	//!Stores the parent XmlElement for this XmlElement. This value will be NULL if this element is the root element.
	XmlElement* parent;
	//!Stores the value/string content for this XmlElement.
	string value;

public:
	//!Creates a XmlElement.
	XmlElement();
	//!Creates a XmlElement with a specified name.
	/*
	*	\param name Name of the XmlElement.
	*/
	XmlElement(string name);
	//!Destroys the XmlElement and any children elements.
	~XmlElement();
	//!Adds a child element to this XmlElement.
	/*
	*	\param element The child element to add.
	*/
	void AddElement(XmlElement* element);
	//!Adds an attribute to this XmlElement.
	/*
	*	\param attributeName Name of the attribute.
	*	\param value Value of the attribute.
	*	\return Returns true if attribute was added successfully.
	*/
	bool AddAttribute(string attributeName, string value);
	//!Get all the attributes for this XmlElement.
	/*
	*	\return Returns an AttributeCollection containing all the attributes for this XmlElement.
	*/
	AttributeCollection* Attributes();
	//!Gets an attribute by name and its associated value for this XmlElement.
	/*
	*	\param attributeName Name of attribute.
	*	\param value Value of the attribute.
	*	\return Returns true if the attribute exists.
	*/
	bool GetAttribute(string attributeName, string* value);
	//!Gets a the children elements for this XmlElement.
	/*
	*	\return Returns a collection of the children nodes (names of nodes for keys).
	*/
	ElementNodes* GetChildrenElements();
	//!Gets a collection of a child element by name
	/*
	*	Gets a collection of a child element by name.  Note: This method is useful if there is an expectation
	*	of more than one occurence of the same kind of element.
	*	\param localName The Name of the child element to look for.
	*	\param first Iterator that will point to the first child element found with the localName specified.
	*	\param last Iterator that will point one past the last child element found with the localName specified.
	*	\return Returns true if the element with the specified localName exists.
	*/
	bool GetElement(string localName, XmlElement::ElementCollection::iterator &first, XmlElement::ElementCollection::iterator &last);
	//!Get the number of occurences an element appears in this XmlElement.
	/*
	*	\param localName The Name of the element to get number of occurences for.
	*	\param count Initialized to hold the number of occurences for an element. The passed in value cannot be NULL.
	*/
	void GetElementCount(string localName, int* count);
	//!Returns a child XmlElement by name.
	/*
	*	\param localName The Name of the child element to look for.
	*	\param index The index of the element to use, if there is more than one occurence.
	*	\return returns the child XmlElement with the specified localName and index,
	*		if the element does not exist, this method will return NULL.
	*/
	XmlElement* GetElement(string localName, int index = 0);
	//!Sets the name for this XmlElement.
	/*
	*	\param name The name to set for this XmlElement.
	*/
	void Name(string name);
	//!Gets the name for this XmlElement.
	/*
	*	\return The name for this XmlElement.
	*/
	string Name();
	//!Gets the parent element for this XmlElement.
	/*
	*	\return Returns the parent for this XmlElement, this value will be NULL if this is a root element.
	*/
	XmlElement* Parent();
	//!Sets the string content for this XmlElement.
	/*
	*	\param The value of the content for this element.
	*/
	void Value(string value);
	//!Gets the content value for this XmlElement.
	/*
	*	\return The content value for this XmlElement.
	*/
	string Value();

};

#endif