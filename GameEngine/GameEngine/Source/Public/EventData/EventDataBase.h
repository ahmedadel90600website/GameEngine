#pragma once
#include "Public/Core.h"

struct GameEngine_API FEventDataBase
{
    FEventDataBase() : bHasBeenHandled(false){}
    virtual ~FEventDataBase() {}

    bool bHasBeenHandled : 1;
};