//
// Created by Pierre Rousselle on 18/11/2016.
//

#ifndef CONCEPTION_RTYPE_LIBHELLO_H
#define CONCEPTION_RTYPE_LIBHELLO_H

#include "libraryUtils.hh"

class Libhello : public IGenerator {
public:
  Libhello(void);
  virtual const std::string &getName(void) const;
private:
    std::string _plugin_name;
};

#endif //CONCEPTION_RTYPE_LIBHELLO_H
