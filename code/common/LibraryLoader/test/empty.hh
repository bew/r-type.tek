//
// Created by Pierre Rousselle on 18/11/2016.
//

#ifndef GENERATOR_EMPTY_H
#define GENERATOR_EMPTY_H

#include "libraryUtils.hh"

class Empty : public IGenerator {
public:
  Empty(void);
  virtual const std::string &getName(void) const;
  virtual void update(ECS::WorldData &world);
private:
    std::string _generator_name;
};

#endif
