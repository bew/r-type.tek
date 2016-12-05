#ifndef _MAKE_DEPENDENT_HPP
#define _MAKE_DEPENDENT_HPP

#include <memory>

/**
 * This class allow for safe use of object that depend on another, whose lifecycle is not fully controlled.
 * The responsability of deleting taregt goes to Dependent_ptr
 * Also, the responsability of deleting dependence goes to the shared_ptr wrappig it passed at ctor.
 */
template<class Target, class Dependence>
class Dependent_ptr {
public:
  Dependent_ptr(Target *target, const std::shared_ptr<Dependence> &dependence) :
    _target(new std::shared_ptr<Target>(target)),
    _dependence(new std::shared_ptr<Dependence>(dependence)) {
  };

  Dependent_ptr(const Dependent_ptr &toCopy) :
    _target(new std::shared_ptr<Target>(*(toCopy._target))),
    _dependence(new std::shared_ptr<Dependence>(*(toCopy._dependence))) {
  };

  Dependent_ptr &operator=(const Dependent_ptr &toCopy) {
    _target = new std::shared_ptr<Target>(*(toCopy._target));
    _dependence = new std::shared_ptr<Dependence>(*(toCopy._dependence));
  }
  
  ~Dependent_ptr(void) {
    delete _target;
    delete _dependence;
  };
  
  Target *operator->(void) {
    return _target->get();
  };
  
public:
  std::shared_ptr<Target> *_target;
  const std::shared_ptr<Dependence> *_dependence;
};

#endif
