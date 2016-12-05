
// written by Alexis Mongin. Started 2016-09-10

/*

HASHTAG NO MEMORY LEAKS

Implement a generic object pool, made for not allocating objects you
  need outside the initialisation of the pool. It is safer for memory
  management and awesome for real-time programs.
  It take as template type T the type you want to allocate, and as F a
  simple factory for building the objects with their defaults arguments.
  The factory must be a simple fonctor returning an dynamically
 allocated object, which will be freed at the end of the pool's life
 with the factory method remove.
 Each factory must implement this simple interface.

 The constructor take the initial number of objects in the pool
 but don't worry, if you run out it will just make more.

Here's what a string factory with the default argument "jej" should look like

class StringFactory
{
public:
    StringFactory() : _arg("jej") {}
    ~StringFactory() {}
    
    std::string *operator() ()
	{
	    return new std::string(_arg);
	}
    
    void remove(std::string *str)
	{
	    delete str;
	}

private:
    const std::string	_arg;
};

NOTHING should be allocated during the exec loop of the game.
We got no time for debugging memory leaks.
If you're working on the ECS, use this!

*/

#pragma once


#include <vector>
#include <iostream>

template<typename T, typename F>
class ObjectPool
{
public:
    ObjectPool(unsigned nbr)
	: _elems(nbr),
	  _offset(0),
	  _factory(F())
	{    
	    for (auto &e : _elems)
		e = _factory();
	}

    ~ObjectPool()
	{
	    for (const auto &e : _elems)
		_factory.remove(e);
	}

    void	operator<<(T *obj)
	{
	    if (obj && _offset != 0) {
		_offset--;
		_elems[_offset] = obj;
	    }
	}

    void	operator>>(T *&obj)
	{
	    if (_offset == _elems.size())
		_elems.push_back(_factory());
	    obj = _elems[_offset];
	    _elems[_offset] = nullptr;
	    _offset++;
	}
  
private:
    std::vector<T *>	_elems;
    unsigned		_offset;
    F			_factory;
};
