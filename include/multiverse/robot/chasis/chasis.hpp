#pragma once

#include "concord/types_basic.hpp"
#include "muli/world.h"
#include "multiverse/robot/chasis/hitch.hpp"
#include "multiverse/robot/chasis/karosserie.hpp"
#include "multiverse/robot/chasis/wheel.hpp"
#include "multiverse/types.hpp"
#include "multiverse/utils.hpp"
#include "pigment/types_basic.hpp"

#include <rerun.hpp>
#include <spdlog/spdlog.h>

namespace mvs {
    using namespace muli;

    // --- Global toggles & parameters ----------------
    inline constexpr bool followCam = true;
    inline constexpr bool rotateCam = false;
    inline constexpr bool drawAxis = false;
    inline constexpr float linearDamping = 0.2f;
    inline constexpr float angularDamping = 0.2f;
    inline constexpr float force = 30.0f;
    inline constexpr float torque = 10.0f;
    inline constexpr float friction = 0.4f;
    inline constexpr float maxImpulse = 0.5f;
    inline constexpr float brake = 10.0f;
    inline constexpr float drag = 0.5f;

    class Chasis {
      private:
        std::shared_ptr<rerun::RecordingStream> rec;
        std::shared_ptr<muli::World> world;
        std::vector<Wheel> wheelz;
        std::vector<muli::MotorJoint *> jointz;
        std::vector<muli::AngleJoint *> anglejointz;
        muli::CollisionFilter filter;

      public:
        std::shared_ptr<muli::RigidBody> bodyz;
        std::vector<Karosserie> karosseriez;
        std::vector<Hitch> hitchz;
        RigidBody *body;
        std::string name;
        pigment::RGB color;
        concord::Bound bound;
        concord::Pose pose;
        uint32_t group;

        Chasis(std::shared_ptr<muli::World> world, std::shared_ptr<rerun::RecordingStream> rec, CollisionFilter filter);

        void init(mvs::RobotInfo &robo);

        void tick(float dt);
        void visualize();
        void teleport(concord::Pose);
        void update(std::vector<float> steering, std::vector<float> throttle);
        void wheel_damping(float linearDamping, float angularDamping);
        muli::Transform get_transform() const;
        void toggle_work(std::string karosserie_name);
    };
} // namespace mvs
