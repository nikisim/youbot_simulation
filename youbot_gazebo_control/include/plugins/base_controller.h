//
// Created by josh on 07.07.20.
//

#ifndef SRC_BASE_CONTROLLER_H
#define SRC_BASE_CONTROLLER_H

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <map>

#include <gazebo/common/common.hh>
#include <gazebo/physics/physics.hh>
#include <sdf/sdf.hh>
#include <ignition/math/Pose3.hh>

#include <ignition/math.hh>

#include <geometry_msgs/Twist.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Odometry.h>
#include <ros/advertise_options.h>
#include <ros/callback_queue.h>
#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

namespace gazebo {

    class YoubotBaseController : public ModelPlugin {

    public:
        YoubotBaseController();
        ~YoubotBaseController();
        void Load(physics::ModelPtr parent, sdf::ElementPtr sdf);

    protected:
        virtual void UpdateChild();
        virtual void FiniChild();

    private:
        void publishOdometry(double step_time);

        physics::ModelPtr parent_;
        event::ConnectionPtr update_connection_;

        boost::shared_ptr<ros::NodeHandle> rosnode_;
        ros::Publisher odometry_pub_;
        ros::Subscriber vel_sub_;
        boost::shared_ptr<tf::TransformBroadcaster> transform_broadcaster_;
        nav_msgs::Odometry odom_;
        std::string tf_prefix_;

        boost::mutex lock;

        std::string robot_namespace_;
        std::string command_topic_;
        std::string odometry_topic_;
        std::string odometry_frame_;
        std::string robot_base_frame_;
        double odometry_rate_;

        // Custom Callback Queue
        ros::CallbackQueue queue_;
        boost::thread callback_queue_thread_;
        void QueueThread();

        // command velocity callback
        void cmdVelCallback(const geometry_msgs::Twist::ConstPtr& cmd_msg);

        double x_;
        double y_;
        double rot_;
        bool alive_;
        common::Time last_odom_publish_time_;
        ignition::math::Pose3d last_odom_pose_;

        physics::LinkPtr base_link_;
        std::vector<double> base_kin_inv_;
        std::vector<physics::JointPtr> wheel_joints_;
    };

}


#endif //SRC_BASE_CONTROLLER_H
