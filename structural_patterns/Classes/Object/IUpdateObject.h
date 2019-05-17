#ifndef GAME_IUPDATEOBJECT_H
#define GAME_IUPDATEOBJECT_H


#include "IObject.h"

class IUpdateObject: public IObject {
public:
	explicit IUpdateObject();;
	virtual void Update() = 0;
};


#endif //GAME_IUPDATEOBJECT_H
