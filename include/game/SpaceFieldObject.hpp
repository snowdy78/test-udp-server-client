#pragma once

#include "decl.hpp"

class SpaceFieldObject
{
    friend class SpaceField;
protected:
    SpaceField *field;
	void setField(SpaceField *field);

public:
	SpaceFieldObject(SpaceField *field = nullptr);

};
