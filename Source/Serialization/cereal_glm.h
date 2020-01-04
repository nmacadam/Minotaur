#pragma once
#include <glm/glm.hpp>

// A (incomplete!) set of cereal serialization functions for glm data types
namespace cereal
{
    template<class Archive>
    void serialize(Archive& archive,
        glm::vec2& v)
    {
        archive(v.x, v.y);
    }

    template<class Archive>
    void serialize(Archive& archive,
        glm::vec3& v)
    {
        archive(v.x, v.y, v.z);
    }

    template<class Archive>
    void serialize(Archive& archive,
        glm::vec4& v)
    {
        archive(v.x, v.y, v.z, v.w);
    }

    template<class Archive>
    void serialize(Archive& archive,
        glm::mat2& m)
    {
        archive(m[0], m[1]);
    }

    template<class Archive>
    void serialize(Archive& archive,
        glm::mat3& m)
    {
        archive(m[0], m[1], m[2]);
    }

    template<class Archive>
    void serialize(Archive& archive,
        glm::mat4& m)
    {
        archive(m[0], m[1], m[2], m[3]);
    }

	// todo: add other glm data types!
}