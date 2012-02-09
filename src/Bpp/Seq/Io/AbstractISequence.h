//
// File: AbstractISequence.h
// Created by: Julien Dutheil
// Created on: ?
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

#ifndef _ABSTRACTISEQUENCE_H_
#define _ABSTRACTISEQUENCE_H_

#include "ISequence.h"
#include "../Container/VectorSequenceContainer.h"
#include "../Alphabet/Alphabet.h"

// From the STL:
#include <string>
#include <iostream>
#include <fstream>

namespace bpp
{

/**
 * @brief Partial implementation of the ISequence interface.
 */
class AbstractISequence:
  public virtual ISequence
{

  public: 
    AbstractISequence() {}
    virtual ~AbstractISequence() {}

  public:

    /**
     * @name ISequence methods:
     *
     * @{
     */ 
    
  public:
    /**
     * @brief Add sequences to a container from a stream.
     *
     * @param input  The input stream to read.
     * @param sc     The sequence container to update.
     * @throw Exception If the file is not in the specified format.
     */
    virtual void read(std::istream& input, SequenceContainer& sc) const throw (Exception)
    {
      appendFromStream(input, sc);
    }
    
  protected:
    /**
     * @brief Append sequences to a container from a stream.
     * 
     * This is the unique method to implement!
     * 
     * @param input  The input stream to read.
     * @param sc     The sequence container to update.
     * @throw Exception If the file is not in the specified format.
     */
    virtual void appendFromStream(std::istream& input, SequenceContainer& sc) const throw (Exception) = 0;
  
  public:
    /**
     * @brief Add sequences to a container from a file.
     *
     * @param path  The path to the file to read.
     * @param sc    The sequence container to update.
     * @throw Exception If the file is not in the specified format.
     */
    virtual void read(const std::string& path, SequenceContainer& sc) const throw (Exception)
    {
      appendFromFile(path, sc);
    }
    
  protected:
    /**
     * @brief Append sequences to a container from a file.
     *
     * @param path  The path to the file to read.
     * @param sc    The sequence container to update.
     * @throw Exception If the file is not in the specified format.
     */
    virtual void appendFromFile(const std::string& path, SequenceContainer& sc) const throw (Exception)
    {
      std::ifstream input(path.c_str(), std::ios::in);
      read(input, sc);
      input.close();
    }

  public:
    virtual
#if defined(NO_VIRTUAL_COV)
    SequenceContainer*
#else
    VectorSequenceContainer*
#endif
    read(std::istream& input, const Alphabet* alpha) const throw (Exception)
    {
      return readFromStream(input, alpha);
    }

  protected:
    /**
     * @brief Read sequences from a stream.
     * 
     * @param input  The input stream to read.
     * @param alpha  The alphabet to use.
     * @return A sequence container.
     * @throw Exception If the file is not in the specified format.
     */
    virtual
#if defined(NO_VIRTUAL_COV)
    SequenceContainer*
#else
    VectorSequenceContainer*
#endif
    readFromStream(std::istream& input, const Alphabet* alpha) const throw (Exception)
    {
      VectorSequenceContainer* vsc = new VectorSequenceContainer(alpha);
      appendFromStream(input, *vsc);
      return vsc;
    }

  public:
    virtual
#if defined(NO_VIRTUAL_COV)
    SequenceContainer*
#else
    VectorSequenceContainer*
#endif
    read(const std::string& path , const Alphabet* alpha) const throw (Exception)
    {
      VectorSequenceContainer* vsc = new VectorSequenceContainer(alpha);
      read(path, *vsc);
      return vsc;
    }
  
  protected:
    /**
     * @brief Append sequences to a container from a file.
     *
     * @param path  The path to the file to read.
     * @param alpha The alphabet to use.
     * @throw Exception If the file is not in the specified format.
     */
    virtual
#if defined(NO_VIRTUAL_COV)
    SequenceContainer*
#else
    VectorSequenceContainer*
#endif
    readFromFile(const std::string& path , const Alphabet* alpha) const throw (Exception)
    {
      VectorSequenceContainer* vsc = new VectorSequenceContainer(alpha);
      appendFromFile(path, *vsc);
      return vsc;
    }
    /** @} */
};

} //end of namespace bpp.

#endif //_ABSTRACTISEQUENCE_H_
