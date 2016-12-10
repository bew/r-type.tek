
/**
 * @file ObjPoolFactories.hpp
 * @author Alexis
 * @brief The factories needed for the object pool go there.
 * According to ObjectPool.hpp,
 * here's what a string factory with the default argument "jej" should look like
 * class StringFactory
 * {
 * public:
 *     StringFactory() : _arg("jej") {}
 *     ~StringFactory() {}
 *     
 *     std::string *operator() ()
 * 	{
 * 	    return new std::string(_arg);
 * 	}
 *     
 *     void remove(std::string *str)
 * 	{
 * 	    delete str;
 * 	}
 * 
 * private:
 *     const std::string	_arg;
 * };
 * This file will only be included in WorldPools.hh.
 * Thus, there is no need for separate implementation.
 */

#pragma once

#include "WorldPools.hh"

/**
 * Namespace of ECS.
 */
namespace ECS {

    /**
     * Namespace of the generic pools used to abstract objects allocation.
     */
    namespace Pools {
   
        /**
	 * Common factory for generating objects requiring no argument in constructor,
	 * nor additional operations after initialization.
	 */
	template<typename T>
	class CommonFactory
	{
	public:
            /**
	     * Constructor.
	     */ 
	    CommonFactory(WorldPools &pools)
		: _pools(pools)
		{}

	    /**
	     * Destructor.
	     */
	    ~CommonFactory() {}

	    /**
	     * allocator.
	     * @return Pointer to the new object.
	     */
	    T *operator()()
		{
		    return new T(this->_pools);
		}

	    /**
	     * desallocator.
	     * @param stuff The object to be deleted.
	     */
	    void remove(T *stuff)
		{
		    delete stuff;
		}

	private:
	    /**
	     * Worldpool needed for created objects to manage their owned poolable objects.
	     */
	    WorldPools	&_pools;
	};

    }
}
