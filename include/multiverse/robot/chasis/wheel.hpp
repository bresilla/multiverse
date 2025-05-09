#pragma once

#include "concord/types_basic.hpp"
#include "muli/world.h"
#include "pigment/types_basic.hpp"
#include <rerun.hpp>

namespace mvs {
    using namespace muli;
    // --- Utility functions ---
    inline float DegToRad(float deg) { return deg * static_cast<float>(M_PI) / 180.0f; }

    class Wheel {
      public:
        std::shared_ptr<rerun::RecordingStream> rec;
        std::shared_ptr<muli::World> world;
        std::string name;
        pigment::RGB color;
        concord::Bound bound;
        muli::CollisionFilter filter;

        RigidBody *wheel;
        Vec2 forward, normal;
        float force, torque;
        float brake, drag;
        float friction, maxImpulse;

        Wheel() = default;
        Wheel(std::shared_ptr<muli::World> world, std::shared_ptr<rerun::RecordingStream> rec, CollisionFilter filter);
        void init(const pigment::RGB &color, std::string name, concord::Bound parent, concord::Bound bound,
                  float linearDamping, float angularDamping, float _force, float _friction, float _maxImpulse,
                  float _brake, float _drag);

        muli::Transform shift(concord::Bound parent, concord::Bound child);
        // void set(concord::Bound chasus_boud, concord::Bound bound);

        void tick(float dt);
        void visualize();
        void teleport(concord::Pose pose);
        void update(float steering, float throttle, MotorJoint *joint);
    };
} // namespace mvs
