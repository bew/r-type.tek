
/**
 * @file ObjectPool.hpp
 * @author Alexis
 * @brief A generic object pool.
 */

#pragma once

#include <vector>
#include <iostream>

/**
 * Namespace of ECS.
 */
namespace ECS {

    /**
     * Namespace of the generic pools used to abstract objects allocation.
     */
    namespace Pools {

	/**
	 * Implement a generic object pool, made for not allocating objects you
	 * need outside the initialisation of the pool. It is safer for memory
	 * management and awesome for real-time programs.
	 * It take as template type T the type you want to allocate, and as F a
	 * simple factory for building the objects with their defaults arguments.
	 * The factory must be a simple fonctor returning an dynamically
	 * allocated object, which will be freed at the end of the pool's life
	 * with the factory method remove.
	 * Each factory must implement this simple interface. See ObjPoolsFactories.hpp.
	 *
	 * The constructor take the initial number of objects in the pool
	 * but don't worry, if you run out it will just make more.
	 * 
	 * NOTHING should be allocated during the exec loop of the game.
	 * We got no time for debugging memory leaks.
	 * If you're working on the ECS, use this!
	 * 
	 */
	template<typename ObjectType, typename Factory>
	class ObjectPool
	{
	public:

	    /**
	     * Constructor. Allocate the objects.
	     * @param nbr The number of initially created objects.
	     */
	    ObjectPool(unsigned nbr)
		: _elems(nbr),
		  _offset(0),
		  _factory(Factory())
		{    
		    for (auto &e : _elems)
			e = _factory();
		}
	    
	    /**
	     * Destructor. Delete the objects.
	     */
	    ~ObjectPool()
		{
		    for (const auto &e : _elems)
			_factory.remove(e);
		}

	    /**
	     * Return an element in the pool.
	     * @param obj The object taken from pool.
	     */
	    void	operator<<(ObjectType *&obj)
		{
		    if (obj && _offset != 0) {
			_offset--;
			_elems[_offset] = obj;
			obj = nullptr;
		    }
		}
	    
	    /**
	     * Insert an element in the pool.
	     * @param obj The object returned in pool.
	     */
	    void	operator>>(ObjectType *&obj)
		{
		    if (_offset == _elems.size())
			_elems.push_back(_factory());
		    obj = _elems[_offset];
		    _elems[_offset] = nullptr;
		    _offset++;
		}
  
	private:
	    /**
	     * Objects contained in the pool.
	     */
	    std::vector<ObjectType *>	_elems;

	    /**
	     * Offset of the last available object of the pool.
	     */
	    unsigned			_offset;

	    /**
	     * Factory for generating the objects.
	     */
	    Factory			_factory;
	};
    }
}
