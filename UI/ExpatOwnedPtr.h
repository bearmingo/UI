#ifndef ExpatOwnedPtr_h__
#define ExpatOwnedPtr_h__

typedef struct XML_ParserStruct *XML_Parser;

namespace WTF {
	void deleteOwnedPtr(XML_Parser ptr);

}

#endif ExpatOwnedPtr_h__
