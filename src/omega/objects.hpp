#include <memory>
#include <vector>

#include "config.hpp"
#include "vector.hpp"
#include "base_object.hpp"
#include "sphere.hpp"
#include "triangle.hpp"

void create_objects(
        const std::vector<std::shared_ptr<Object>>& raw,
        std::map<std::string,BaseObject*>& out
);
