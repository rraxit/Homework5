#include <iostream>
#include <array>
#include <ompl/base/ProblemDefinition.h>
#include <ompl/base/goals/GoalState.h>
#include <ompl/base/spaces/SE2StateSpace.h>
#include <ompl/geometric/SimpleSetup.h>
#include <ompl/base/spaces/RealVectorBounds.h>
#include <ompl/base/SpaceInformation.h>
#include <cmath>

namespace ob = ompl::base;
namespace og = ompl::geometric;

bool isStateValid(const ob::State *state)
{
    // a big circular obstacles located at the center (5, 5)
    auto x = 5 - state->as<ompl::base::RealVectorStateSpace::StateType>()->values[0];
    auto y = 5 - state->as<ompl::base::RealVectorStateSpace::StateType>()->values[1];

    auto dist = sqrt(x * x + y * y);
    // std::cout << dist << std::endl;
    return dist > 5;
}

void setup(std::array<double, 2> start_, std::array<double, 2> goal_, double lower_, double upper_)
{
    // Construct the robot state space in which we're planning. We're
    auto space(std::make_shared<ob::RealVectorStateSpace>(2));

    // Construct a space information instance for this state space
    ob::RealVectorBounds bounds(2);
    bounds.setLow(lower_);
    bounds.setHigh(upper_);

    space->setBounds(bounds);

    ob::ScopedState<> start(space);

    // Set our robot's starting state
    start->as<ob::RealVectorStateSpace::StateType>()->values[0] = start_[0];
    start->as<ob::RealVectorStateSpace::StateType>()->values[1] = start_[1];

    // Set our robot's goal state
    ob::ScopedState<> goal(space);
    goal->as<ob::RealVectorStateSpace::StateType>()->values[0] = goal_[0];
    goal->as<ob::RealVectorStateSpace::StateType>()->values[1] = goal_[1];

    og::SimpleSetup ss(space);
    ss.setStartAndGoalStates(start, goal);

    // collision checking
    ss.setStateValidityChecker([&](const ob::State *state)
                               { return isStateValid(state); });

    // allocate planning time
    ob::PlannerStatus solved = ss.solve(5.0);

    if (solved)
    {
        std::cout << "Found solution:" << std::endl;
        // print the path to screen
        ss.simplifySolution();
        ss.getSolutionPath().print(std::cout);
    }
}
int main(int argc, char **argv)
{
    std::cout << "ompl demo!" << std::endl;

    setup({0, 0}, {10, 10}, -1, 11);
    return 0;
}