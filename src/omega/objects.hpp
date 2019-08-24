#include <memory>
#include <vector>

#include "config.hpp"
#include "vector.hpp"
#include "matrix.hpp"

Matrix3x3 getRotationMatrix(const std::shared_ptr<Rotation>);

// TODO: move everything from these to here.
#include "base_object.hpp"
#include "sphere.hpp"
#include "triangle.hpp"

void create_objects(
        const std::vector<std::shared_ptr<Object>>& raw,
        std::map<std::string,BaseObject*>& out
);

void apply_transformations(std::map<std::string, BaseObject *> map);

