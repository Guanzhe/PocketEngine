//
//  Cloner.hpp
//  PocketEditor
//
//  Created by Jeppe Nielsen on 17/09/16.
//  Copyright © 2016 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include <string>
#include <vector>
#include "GameObjectHandle.hpp"
#include "TypeInfo.hpp"

namespace Pocket {
    class Cloner {
    public:
        GameObjectHandle Source;
        TYPE_FIELDS_BEGIN
        TYPE_FIELD(Source)
        TYPE_FIELDS_END
    };
}