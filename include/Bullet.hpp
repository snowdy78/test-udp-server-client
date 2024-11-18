#pragma once

#include "decl.hpp"
#include "RigitBody2d.hpp"

class Bullet : public RigitBody2d
{
    inline static rn::StaticTexture texture{"img/bullet_shoot.png"};
public:
    Bullet();
};