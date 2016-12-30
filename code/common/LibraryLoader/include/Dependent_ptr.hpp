/**
 * @file Dependent_ptr.hh
 * @brief Header for dependent_ptr
 * @author Nekhot
 */

#pragma once

#include <memory>

/**
 * This class allow for safe use of object that depend on another, whose lifecycle is not fully controlled.
 * The responsability of deleting taregt goes to Dependent_ptr
 * Also, the responsability of deleting dependence goes to the shared_ptr wrapping it passed at ctor.
 * Exmple:
 * std::shared_ptr<Loader> dep(new Loader());
 * Dependent_ptr<Loader, Loaded> ptr(dep->getNewInstance(), dep);
 * ptr->doSomething();
 * Here you can safely use ptr, even in outer scope, without caring about the Loader.
 */
template<class Target, class Dependence>
class Dependent_ptr {
public:

  /**
   * Default constructor. Build a null pointer.
   */
  Dependent_ptr(void) :
    _target(new std::shared_ptr<Target>(nullptr)),
    _dependence(new std::shared_ptr<Dependence>(nullptr)) {
  };
  
  /**
   * Construct  wrapper for target that is used correclty forbid deletion of dependence before delete of target.
   *
   * @param target The object to wrap.
   * @param dependence A sharedptr wrapping the object that target hold reference to.
   */
  Dependent_ptr(Target *target, const std::shared_ptr<Dependence> &dependence) :
    _target(new std::shared_ptr<Target>(target)),
    _dependence(new std::shared_ptr<Dependence>(dependence)) {
  };

  /*
   * Copy constructor for Dependent_ptr
   * After constrction of B from A, is you want to delete target and dependence, you will need to delete both A and B
   *
   * @param toCopy The Dependent_ptr to copy
   */
  Dependent_ptr(const Dependent_ptr &toCopy) :
    _target(new std::shared_ptr<Target>(*(toCopy._target))),
    _dependence(new std::shared_ptr<Dependence>(*(toCopy._dependence))) {
  };

  /**
   * Set the `this` dependent_ptr target and dependence as toCopy target and instance by copy
   * If `this` dependent ptr is the last reference to target or dependence, they will be deleted. 
   *
   * @param toCopy The Dependent_ptr whose target and dependence will be copied 
   */
  Dependent_ptr &operator=(const Dependent_ptr &toCopy) {
    auto tmp_target = new std::shared_ptr<Target>(*(toCopy._target));
    auto tmp_dependence = new std::shared_ptr<Dependence>(*(toCopy._dependence));
    delete _target;
    delete _dependence;
    _target = tmp_target;
    _dependence = tmp_dependence;
    return *this;
  }

  /**
   * Test if pointer is null
   */
  operator bool() const {
    return (_target->get() != nullptr);
  }

  /**
   *
   * Destructor for Dependent_ptr
   * Note that target and dependence will be truly deleted
   * Only if `this` is their only reference
   */
  ~Dependent_ptr(void) {
    delete _target;
    delete _dependence;
  };

  /**
   * Access the wrapped ptr
   *
   * @return The wrapped ptr.
   */
  Target *operator->(void) {
    return _target->get();
  };
  
public:
  /**
   * The wrapped object
   */
  std::shared_ptr<Target> *_target;

  /**
   * The dependence of the target object
   */
  const std::shared_ptr<Dependence> *_dependence;
};
