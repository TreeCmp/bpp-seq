//
// File: CoreSequenceSymbolList.h
// Created by: Laurent Guéguen
// Created on: mardi 11 avril 2017, à 14h 42
//

/*
Copyright or © or Copr. Bio++ Development Team, (November 17, 2004)

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

#ifndef _CORE_SEQUENCE_SYMBOLLIST_H_
#define _CORE_SEQUENCE_SYMBOLLIST_H_

#include "SymbolList.h"
#include "CoreSequence.h"

#include <Bpp/Clonable.h>

// From the STL:
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

namespace bpp
{

  /**
   * @brief The CoreSequenceSymbolList interface.
   *
   */
  template<class T>
  class CoreSequenceSymbolList:
    public virtual CoreSymbolList<T>,
    public virtual CoreSequence
  {

  public: 
    /**
     * @name The Clonable interface
     *
     * @{
     */
    CoreSequenceSymbolList* clone() const = 0;
    /** @} */

    // Class destructor
    virtual ~CoreSequenceSymbolList() {}
    
  };

  typedef CoreSequenceSymbolList<int> IntCoreSequenceSL;
  typedef CoreSequenceSymbolList<std::vector<double> > ProbaCoreSequenceSL;
  

  /**
   * @brief The AbstractSequenceSymbolList virtual class :
   * SymbolList<T> is built, there.
   *
   */
  
  template<class T>
  class AbstractSequenceSymbolList:
    public virtual SymbolList<T>,
    public virtual CoreSequenceSymbolList<T>
  {

  public: 
    /**
     * @name The Clonable interface
     *
     * @{
     */
    AbstractSequenceSymbolList* clone() const = 0;
    /** @} */

    // Class destructor
    virtual ~AbstractSequenceSymbolList() {}
    
  };

  typedef AbstractSequenceSymbolList<int> intAbstractSequenceSL;
  typedef AbstractSequenceSymbolList<std::vector<double> > probaAbstractSequenceSL;

} //end of namespace bpp.

#endif // _CORE_SEQUENCE_SYMBOLLIST_H_

