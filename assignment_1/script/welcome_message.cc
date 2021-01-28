#include <gazebo/gazebo.hh>

namespace gazebo
{
  class welcome_message : public WorldPlugin
  {
    public: welcome_message() : WorldPlugin()
            {
              printf("Welcome to my world\n");
            }

    public: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf)
            {
            }
  };
  GZ_REGISTER_WORLD_PLUGIN(welcome_message)
}
