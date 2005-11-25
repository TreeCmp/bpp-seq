//
// File OrderedSequenceContainer.h
// Author: Guillaume Deuchst
//         Julien Dutheil
// Last modification : Tuesday August 7 2003
//

/*
Copyright or � or Copr. CNRS, (November 17, 2004)

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

#ifndef _ORDEREDSEQUENCECONTAINER_H_
#define _ORDEREDSEQUENCECONTAINER_H_

#include "Sequence.h"
#include "SequenceContainer.h"

/**
 * @brief The OrderedSequenceContainer interface.
 *
 * Interface to manage indexed containers.
 * Sequences may be accessed via their indice, <i>i.e.</i> their position in the container.
 */
class OrderedSequenceContainer : public virtual SequenceContainer
{
	public:
		OrderedSequenceContainer() {}
		virtual ~OrderedSequenceContainer() {}

	public:
		/**
		 * @brief Get the content of a sequence.
		 *
		 * @param sequenceIndex The position of the sequence.
		 * @return The content of the sequence as a vector of integers.
		 * @throw IndexOutOfBoundsException If the position does not match any sequence in the container.
		 */
		virtual vector<int> getContent(unsigned int sequenceIndex) const throw (IndexOutOfBoundsException) = 0;
		
		/**
		 * @brief Convert a particular sequence to a string.
		 *
		 * @param sequenceIndex The position of the sequence.
		 * @return A string describing the content of the sequence.
		 * @throw IndexOutOfBoundsException If the position does not match any sequence in the container.
		 */
		virtual string toString(unsigned int sequenceIndex) const throw (IndexOutOfBoundsException) = 0;

		/**
		 * @brief Retrieve a sequence object from the container.

		 *
		 * @param sequenceIndex The position of the sequence.
		 * @return A pointer toward the Sequence with corresponding name.
		 * @throw IndexOutOfBoundsException If the position does not match any sequence in the container.
		 */
		virtual const Sequence * getSequence(unsigned int sequenceIndex) const throw (IndexOutOfBoundsException) = 0;

		/**
		 * @brief Replace a sequence in the container.
		 *
		 * @param sequenceIndex The position of the sequence.
		 * @param sequence      The sequence to add.
		 * @param checkName     Tell if the container must check if the name of the sequence
		 * is already used in the container before adding it.
		 * @throw IndexOutOfBoundsException If the position does not match any sequence in the container.
		 * @throw Exception Any other kind of exception.
		 */
		virtual void setSequence(unsigned int sequenceIndex, const Sequence & sequence, bool checkName) throw (Exception) = 0;

		/**
		 * @brief Extract (and remove) a sequence from the container.
		 *
		 * @param sequenceIndex The position of the sequence.
		 * @throw IndexOutOfBoundsException If the name does not match any sequence in
		 * the container.
		 */
		virtual Sequence * removeSequence(unsigned int sequenceIndex) throw (IndexOutOfBoundsException) = 0;

		/**
		 * @brief Delete a sequence of the container.
		 *
		 * @param sequenceIndex The position of the sequence.
		 * @throw IndexOutOfBoundsException If the position does not match any sequence in
		 * the container.
		 */
		virtual void deleteSequence(unsigned int sequenceIndex) throw (IndexOutOfBoundsException) = 0;

		/**
		 * @brief Get the name of a particular sequence.
		 *
		 * @param sequenceIndex The position of the sequence.
		 * @return The name of the sequence at position 'sequenceIndex'.
		 * @throw IndexOutOfBoundsException If the position does not match any sequence in
		 * the container.
		 */
		virtual string getName(unsigned int sequenceIndex) const throw (IndexOutOfBoundsException) = 0;

		/**
		 * @brief Get comments of a particular sequence.
		 *
		 * @param sequenceIndex The position of the sequence.
		 * @return The comments associated to sequence at position 'sequenceIndex'.
		 * @throw IndexOutOfBoundsException If the position does not match any sequence in
		 * the container.
		 */
		virtual Comments getComments(unsigned int sequenceIndex) const throw (IndexOutOfBoundsException) = 0;

		/**
		 * @brief Set the comments of a particular sequence.
		 *
		 * @param sequenceIndex The position of the sequence.
		 * @param comments      The comments to set to sequence with position 'i'.
		 * @throw IndexOutOfBoundsException If the position does not match any sequence in
		 * the container.
		 */
		virtual void setComments(unsigned int sequenceIndex, const Comments & comments) throw (IndexOutOfBoundsException) = 0;
		
		/**
		 * @brief Get the position of a sequence in sequence container from its name.
		 *
		 * @param name The name of the sequence.
		 * @return The position of the sequence with name 'name', if it exists.
		 * @throw SequenceNotFoundException If no sequence with name 'name' could be found.
		 */
		virtual unsigned int getSequencePosition(const string & name) const throw (SequenceNotFoundException) = 0;

	public:
		
		/**
		 * @name SequenceContainer methods.
		 *
		 * @{
		 */
		virtual vector<int> getContent(const string & name) const throw (SequenceNotFoundException) = 0;  
		virtual string toString(const string & name) const throw (SequenceNotFoundException) = 0;  
		virtual const Sequence * getSequence(const string & name) const throw (SequenceNotFoundException) = 0;
		virtual void setSequence(const string & name, const Sequence & sequence, bool checkName) throw (Exception) = 0;
		virtual Sequence * removeSequence(const string & name) throw (SequenceNotFoundException) = 0;
		virtual void deleteSequence(const string & name) throw (SequenceNotFoundException) = 0;
		virtual unsigned int getNumberOfSequences() const = 0;
		virtual vector<string> getSequencesNames() const = 0;
		virtual void setSequencesNames(const vector<string> & names, bool checkNames) throw (Exception) = 0;
		virtual Comments getComments(const string & name) const throw (SequenceNotFoundException) = 0;
		virtual void setComments(const string & name, const Comments & comments) throw (SequenceNotFoundException) = 0;
		/** @} */
};

#endif	//_ORDEREDSEQUENCECONTAINER_H_

