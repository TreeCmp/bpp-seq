//
// File: PositionedNamedContainer.h
// Created by: Laurent Guéguen (for template feature)
// Created on: samedi 13 mai 2017, à 22h 15
//

/*
   Copyright or © or Copr. CNRS, (November 17, 2004)

   This software is a computer program whose purpose is to provide classes
   for sequences analysis.

   This software is governed by the CeCILL  license under French law and
   abiding by the rules of distribution of free software.  You can  use,
   modify and/ or redistribute the software under the terms of the CeCILL
   license as circulated by CEA, CNRS and INRIA at the following URL
   "http://www.cecill.info".

   As a counterpart to the access to the source code and  rights to copy,
   modify and redistribute granted by the license, users are provided only
   with a limited warranty  and the software's author,  the holder of the
   economic rights,  and the successive licensors  have only  limited
   liability.

   In this respect, the user's attention is drawn to the risks associated
   with loading,  using,  modifying and/or developing or reproducing the
   software by the user in light of its specific status of free software,
   that may mean  that it is complicated to manipulate,  and  that  also
   therefore means  that it is reserved for developers  and  experienced
   professionals having in-depth computer knowledge. Users are therefore
   encouraged to load and test the software's suitability as regards their
   requirements in conditions enabling the security of their systems and/or
   data to be ensured and,  more generally, to use and operate it in the
   same conditions as regards security.

   The fact that you are presently reading this means that you have had
   knowledge of the CeCILL license and that you accept its terms.
 */

#ifndef POSITIONED_NAMED_CONTAINER_H_
#define POSITIONED_NAMED_CONTAINER_H_

#include "NamedContainer.h"
#include "PositionedContainer.h"

// From the STL library:
#include <string>
#include <vector>
#include <iostream>

namespace bpp
{
/**
 * @brief The template PositionedNamedContainer class.
 *
 *
 */

  template<class T>
  class PositionedNamedContainer :
    private PositionedContainer<T>,
    private NamedContainer<T>
  {
  public:
    /**
     * @name The Clonable interface.
     *
     * @{
     */
    
    virtual PositionedNamedContainer<T>* clone() const = 0;
    
    /** @} */

    virtual ~PositionedNamedContainer() 
    {
    }

  public:
    virtual void addObject(std::shared_ptr<T> object, size_t objectIndex, const std::string& name, bool check = false) = 0;

    virtual void insertObject(std::shared_ptr<T> object, size_t objectIndex, const std::string& name) = 0;

    virtual size_t getObjectPosition(const std::string& name) const = 0;

    virtual std::string getObjectName(size_t objectIndex) const = 0;
    
  };
} // end of namespace bpp.

#endif  // POSITIONED_NAMED_CONTAINER_H_

