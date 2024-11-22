#pragma once

#include "decl.hpp"

class DamageDealer
{
    float damage;
protected:
	void setDamage(float damage);
public:
	DamageDealer(float damage = 0.f);
	float getDamage() const;
};
using init_dmg = DamageDealer;