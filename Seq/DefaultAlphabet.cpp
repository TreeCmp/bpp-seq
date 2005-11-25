//
// File: DefaultAlphabet.cpp
// Created by: Julien Dutheil
// Created on: 2005
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


#include "DefaultAlphabet.h"

// From Utils:
#include <Utils/TextTools.h>

const string DefaultAlphabet::chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890?";

// class constructor
DefaultAlphabet::DefaultAlphabet()
{
	// Alphabet size definition
	alphabet.resize(chars.size() + 1);

	// Alphabet content definition
	alphabet[0].num = -1;
	alphabet[0].letter = "-";
	alphabet[0].abbr = "GAP";
	alphabet[0].name = "Gap";

	for(unsigned int i = 0; i < chars.size(); i++) {
		alphabet[i+1].num = i;
		alphabet[i+1].letter = TextTools::toString(chars[i]);
		alphabet[i+1].abbr = "";
		alphabet[i+1].name = "";
	}
}

