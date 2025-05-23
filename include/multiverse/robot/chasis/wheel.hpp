#pragma once

#include "concord/types_basic.hpp"
#include "muli/world.h"
#include "multiverse/utils.hpp"
#include "pigment/types_basic.hpp"
#include <rerun.hpp>
#include <spdlog/spdlog.h>

namespace mvs {
    using namespace muli;
    // --- Utility functions ---
    inline float DegToRad(float deg) { return deg * static_cast<float>(M_PI) / 180.0f; }

    class Wheel {
      public:
        std::shared_ptr<rerun::RecordingStream> rec;
        std::shared_ptr<muli::World> world;
        std::string name;
        std::string parent_name;
        pigment::RGB color;
        concord::Bound bound;
        concord::Pose pose;
        muli::CollisionFilter filter;

        RigidBody *wheel;
        Vec2 forward, normal;
        float force, torque;
        float brake, drag;
        float friction, maxImpulse;

        float throttle_val = 0.0f, steering_val = 0.0f;
        float steering_max, throttle_max;

        Wheel() = default;
        Wheel(std::shared_ptr<muli::World> world, std::shared_ptr<rerun::RecordingStream> rec, CollisionFilter filter);
        void init(const pigment::RGB &color, std::string parent_name, std::string name, concord::Bound bound,
                  concord::Bound parent_bound, float _force, float _friction, float _maxImpulse, float _brake,
                  float _drag, float throttle_max, float steering_max);

        void tick(float dt);
        void visualize();
        void teleport(concord::Pose pose);
        void update(float steering, float throttle, MotorJoint *joint);

        concord::Bound get_bound() const { return bound; }
    };
} // namespace mvs
