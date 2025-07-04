#pragma once

#include "muli/math.h"
#include "muli/polygon.h"
#include "muli/rigidbody.h"
#include "muli/settings.h"
#include "muli/world.h"

#include "flatsim/exceptions.hpp"
#include "flatsim/robot.hpp"
#include "flatsim/types.hpp"
#include "flatsim/utils.hpp"
#include "flatsim/world/layer.hpp"

namespace fs {
    class WorldSettings : public muli::WorldSettings {
      private:
        concord::Datum world_datum_;
        concord::Size world_size_;

      public:
        WorldSettings() = default;
        void init(concord::Datum datum, concord::Size world_size) {
            world_datum_ = datum;
            world_size_ = world_size;
            this->world_bounds =
                muli::AABB(muli::Vec2(-world_size.x / 2.0f, -world_size.y / 2.0f), muli::Vec2(world_size.x / 2.0f, world_size.y / 2.0f));
        }
        concord::Datum get_datum() const { return world_datum_; }
        concord::Size get_world_size() const { return world_size_; }
    };

    class World {
      private:
        WorldSettings settings;
        std::shared_ptr<rerun::RecordingStream> rec;
        std::shared_ptr<muli::World> world;
        concord::Rectangle world_bounds;

      public:
        std::vector<std::shared_ptr<Layer>> layers;
        World(std::shared_ptr<rerun::RecordingStream> rec);
        ~World();
        void adjust_word();

        void init(concord::Datum datum, concord::Size world_size);
        void tick(float dt);
        void tock();
        concord::Point at(std::string name, uint x, uint y) const;

        std::shared_ptr<muli::World> get_world() const { return world; }
        const WorldSettings &get_settings() const { return settings; }
    };
} // namespace fs
