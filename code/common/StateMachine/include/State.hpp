/**
 * @file State.hpp
 * @author Tookie
 * @brief State use to create a StateMachine
 */

#pragma once

#include <map>
#include <list>
#include <string>

/**
 * namespace for state machin
 */
namespace state_machine
{

    /**
     * represents one state
     * @tparam Edge type of the transitional links
     */
    template<typename Edge>
    class State
    {
    public:
        State(const State &) = delete;

        State &operator=(const State &) = delete;

        /**
         * Constructor of State
         * @param name name of the state
         */
        State(const std::string &name) :
                _name(name)
        {};

        /**
         * Destructor of State
         */
        ~State()
        {};

        /**
         * add a link at this State
         * @param e the edge use to transition
         * @param nameNextState name of the next state
         */
        void addLink(const Edge &e, const std::string &nameNextState)
        {
            _nextLinks[e] = nameNextState;
        }

        /**
         * add a link at this State
         * @param e the edge use to transition
         * @param nextState the next state
         */
        void addLink(const Edge &e, const State<Edge> &nextState)
        {
            _nextLinks[e] = nextState.getName();
        }

        /**
         * return the name of the next state link with this edge
         * @param e edge use to find the next state
         * @return the name of the next state
         * @throw out_of_range if edge does not in the map
         */
        const std::string &getLink(const Edge &e) const
        {
            if (_nextLinks.find(e) == _nextLinks.end())
                throw std::out_of_range("edge does not match with any key");
            return _nextLinks.find(e)->second;
        }

        /**
         * getter for the name of the state
         * @return the name of the state
         */
        const std::string &getName() const
        {
            return _name;
        }

        /**
         * getter for all edge linked
         * @return list of all edge linked
         */
        std::list<Edge> getEdges() const
        {
            std::list<Edge> edges;
            for (auto &pair : _nextLinks)
                edges.push_back(pair.first);
            return edges;
        }

        /**
         * test if the state has an edge as transition
         * @param e edge to test
         * @return true if the state has this edge, else false
         */
        bool has(const Edge &e) const
        {
            return _nextLinks.find(e) != _nextLinks.end();
        }

        /**
         * operator == to compare two states
         * @param rhs state to compare
         * @return true if the states are equals, else false
         */
        bool operator==(const State<Edge> &rhs)
        {
            return _name == rhs._name && _nextLinks == rhs._nextLinks;
        }

    private:
        /**
         * name of the state
         */
        std::string _name;

        /**
         * contains all links of this state
         */
        std::map<Edge, std::string> _nextLinks;
    };

}