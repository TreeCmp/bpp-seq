//
// File: SequenceApplicationTools.cpp
// Created by: Julien Dutheil
// Created on: Fri Oct 21 13:13
// from file old ApplicationTools.h created on Sun Dec 14 09:36:26 2003
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

#include "SequenceApplicationTools.h"
#include "SiteTools.h"
#include "ioseq"
#include "WordAlphabet.h"

//From Utils:
#include <Utils/ApplicationTools.h>
#include <Utils/TextTools.h>
#include <Utils/KeyvalTools.h>

using namespace bpp;

/******************************************************************************/

Alphabet * SequenceApplicationTools::getAlphabet(
  map<string, string> & params,
  const string& suffix,
  bool suffixIsOptional,
  bool verbose,
  bool allowGeneric) throw (Exception)
{
  Alphabet* chars;
  string alphtt = ApplicationTools::getStringParameter("alphabet", params, "DNA", suffix, suffixIsOptional);

  string alphabet = "";
  map<string, string> args;

  KeyvalTools::parseProcedure(alphtt, alphabet, args);
  unsigned int lg = 1;
  
  if (alphabet == "Word")
  {
    if (args.find("length") == args.end())
      throw Exception("Missing length parameter for Word alphabet");
    lg = TextTools::to<unsigned int>(args["length"]);
    if (args.find("letter") == args.end())
      throw Exception("Missing letter alphabet for Word alphabet");
    alphabet = args["letter"];
  }
  
  if (alphabet == "DNA")
    chars = new DNA();
  else if (alphabet == "RNA")
    chars = new RNA();
  else if (alphabet == "Protein")
    chars = new ProteicAlphabet();
  else if (allowGeneric && alphabet == "Generic")
    chars = new DefaultAlphabet();
  else
  {
    string suff = "";
    if (alphabet.find("CodonAlphabet") != string::npos)
      suff = "CodonAlphabet";
    
    if (suff == "")
      throw Exception("Alphabet not known: " + alphabet);

    if (args.find("letter") == args.end())
      throw Exception("Missing alphabet in Codon : " + alphabet);

    string alphn = args["letter"];

    NucleicAlphabet* pnalph;
    if (alphn == "RNA")
      pnalph = new RNA();
    else if (alphn == "DNA")
      pnalph = new DNA();
    else
      throw Exception("Alphabet not known in Codon : " + alphn);
    
    if (alphabet.find("EchinodermMitochondrial") != string::npos)
      chars = new EchinodermMitochondrialCodonAlphabet(pnalph);
    else if (alphabet.find("InvertebrateMitochondrial") != string::npos)
      chars = new InvertebrateMitochondrialCodonAlphabet(pnalph);
    else if (alphabet.find("Standard") != string::npos)
      chars = new StandardCodonAlphabet(pnalph);
    else if (alphabet.find("VertebrateMitochondrial") != string::npos)
      chars = new VertebrateMitochondrialCodonAlphabet(pnalph);
    else
      throw Exception("Unknown Alphabet : " + alphabet);
    alphabet = alphabet + "(" + alphn + ")";
  }

  if (lg > 1)
  {
    chars = new WordAlphabet(chars, lg);
    string al=" ";
    for (unsigned i = 0; i < lg; i++)
      al += alphabet + " ";
    alphabet = "Word(" + al + ")";
  }

  if (verbose) ApplicationTools::displayResult("Alphabet type ", alphabet);
  return chars;
}

/******************************************************************************/

GeneticCode* SequenceApplicationTools::getGeneticCode(
    const NucleicAlphabet* alphabet,
    const string& description) throw (Exception)
{
  GeneticCode* geneCode;
  if (description == "EchinodermMitochondrial")
    geneCode = new EchinodermMitochondrialGeneticCode(alphabet);
  else if (description == "InvertebrateMitochondrial")
    geneCode = new InvertebrateMitochondrialGeneticCode(alphabet);
  else if (description == "Standard")
    geneCode = new StandardGeneticCode(alphabet);
  else if (description == "VertebrateMitochondrial")
    geneCode = new VertebrateMitochondrialGeneticCode(alphabet);
  else
    throw Exception("Unknown GeneticCode: " + description);
  return geneCode;
}

/******************************************************************************/

AlphabetIndex2<double>* SequenceApplicationTools::getAADistance(const string& description)
  throw (Exception)
{
  AlphabetIndex2<double>* distance=0;
  if (description == "BLOSUM50")
    distance = new BLOSUM50();
  else if (description == "GranthamAAChemicalDistance"){
    distance = new GranthamAAChemicalDistance();
    ((GranthamAAChemicalDistance*) distance)->setSymmetric(1);
  }
  else if (description == "MiyataAAChemicalDistance"){
    distance = new MiyataAAChemicalDistance();
    ((MiyataAAChemicalDistance*)distance)->setSymmetric(1);    
  }
  else
    throw Exception("Unknown AA distance: " + description);
  return distance;
}

/******************************************************************************/
SequenceContainer* SequenceApplicationTools::getSequenceContainer(
  const Alphabet* alpha,
  map<string, string>& params,
  const string& suffix,
  bool suffixIsOptional,
  bool verbose)
{
  string sequenceFilePath = ApplicationTools::getAFilePath("input.sequence.file",params, true, true, suffix, suffixIsOptional);
  string sequenceFormat = ApplicationTools::getStringParameter("input.sequence.format", params, "Fasta()", suffix, suffixIsOptional);
  string format = "";
  map<string, string> args;
  KeyvalTools::parseProcedure(sequenceFormat, format, args);
  if (verbose) ApplicationTools::displayResult("Sequence format " + suffix, format);
  ISequence* iSeq = NULL;
  if (format == "Mase")
  {
    iSeq = new Mase();
  }
  else if (format == "Phylip")
  {
    bool sequential = true, extended = true;
    string split = "  ";
    if (args.find("order") != args.end())
    {
           if (args["order"] == "sequential" ) sequential = true;
      else if (args["order"] == "interleaved") sequential = false;
      else ApplicationTools::displayWarning("Argument '" +
             args["order"] +
             "' for argument 'Phylip#order' is unknown. " +
             "Default used instead: sequential.");
    }
    else ApplicationTools::displayWarning("Argument 'Phylip#order' not found. Default used instead: sequential.");
    if (args.find("type") != args.end())
    {
      if (args["type"] == "extended")
      {
        extended = true;
        split = ApplicationTools::getStringParameter("split", args, "spaces", "", true, false);
        if (split == "spaces") split = "  ";
        else if (split == "tab") split = "\t";
        else throw Exception("Unknown option for Phylip#split: " + split);
      }
      else if (args["type"] == "classic" ) extended = false;
      else ApplicationTools::displayWarning("Argument '" +
             args["type"] + "' for parameter 'Phylip#type' is unknown. " +
             "Default used instead: extended.");
    }
    else ApplicationTools::displayWarning("Argument 'Phylip#type' not found. Default used instead: extended.");
    iSeq = new Phylip(extended, sequential, 100, true, split);
  }
  else if (format == "Fasta")
  {
    iSeq = new Fasta();
  }
  else if (format == "Clustal")
  {
    unsigned int extraSpaces = ApplicationTools::getParameter<unsigned int>("extraSpaces", args, 0, "", true, false);
    iSeq = new Clustal(true, extraSpaces);
  }
  else if (format == "Dcse")
  {
    iSeq = new DCSE();
  }
  else if (format == "GenBank")
  {
    iSeq = new GenBank();
  }
  else if (format == "Nexus")
  {
    iSeq = new NexusIOSequence();
  }
  else
  {
    ApplicationTools::displayError("Unknown sequence format.");
    exit(-1);
  }
  SequenceContainer * sequences = iSeq->read(sequenceFilePath, alpha);
  delete iSeq;
  
  if (verbose) ApplicationTools::displayResult("Sequence file " + suffix, sequenceFilePath);

  return sequences;
}

/******************************************************************************/

VectorSiteContainer * SequenceApplicationTools::getSiteContainer(
  const Alphabet * alpha,
  map<string, string> & params,
  const string & suffix,
  bool suffixIsOptional,
  bool verbose)
{
  string sequenceFilePath = ApplicationTools::getAFilePath("input.sequence.file", params, true, true, suffix, suffixIsOptional);
  string sequenceFormat = ApplicationTools::getStringParameter("input.sequence.format", params, "Fasta()", suffix, suffixIsOptional);
  string format = "";
  map<string, string> args;
  KeyvalTools::parseProcedure(sequenceFormat, format, args);

  if (verbose) ApplicationTools::displayResult("Sequence format " + suffix, format);
  ISequence * iSeq = NULL;
  if (format == "Mase")
  {
    iSeq = new Mase();
  }
  else if (format == "Phylip")
  {
    bool sequential = true, extended = true;
    string split = "  ";
    if (args.find("order") != args.end())
    {
           if (args["order"] == "sequential" ) sequential = true;
      else if (args["order"] == "interleaved") sequential = false;
      else ApplicationTools::displayWarning("Argument '" +
             args["order"] +
             "' for argument 'Phylip#order' is unknown. " +
             "Default used instead: sequential.");
    }
    else ApplicationTools::displayWarning("Argument 'Phylip#order' not found. Default used instead: sequential.");
    if (args.find("type") != args.end())
    {
      if (args["type"] == "extended")
      {
        extended = true;
        split = ApplicationTools::getStringParameter("split", args, "spaces", "", true, false);
        if (split == "spaces") split = "  ";
        else if (split == "tab") split = "\t";
        else throw Exception("Unknown option for Phylip#split: " + split);
      }
      else if (args["type"] == "classic" ) extended = false;
      else ApplicationTools::displayWarning("Argument '" +
             args["type"] + "' for parameter 'Phylip#type' is unknown. " +
             "Default used instead: extended.");
    }
    else ApplicationTools::displayWarning("Argument 'Phylip#type' not found. Default used instead: extended.");
    iSeq = new Phylip(extended, sequential, 100, true, split);
  }
  else if (format == "Fasta")
  {
    iSeq = new Fasta();
  }
  else if (format == "Clustal")
  {
    unsigned int extraSpaces = ApplicationTools::getParameter<unsigned int>("extraSpaces", args, 0, "", true, false);
    iSeq = new Clustal(true, extraSpaces);
  }
  else if (format == "Dcse")
  {
    iSeq = new DCSE();
  }
  else if (format == "Nexus")
  {
    iSeq = new NexusIOSequence();
  }
  else
  {
    ApplicationTools::displayError("Unknown sequence format: " + format);
    exit(-1);
  }
  const SequenceContainer* seqCont = iSeq->read(sequenceFilePath, alpha);
  VectorSiteContainer* sites = new VectorSiteContainer(* dynamic_cast<const OrderedSequenceContainer *>(seqCont));
  delete seqCont;
  delete iSeq;
  
  if (verbose) ApplicationTools::displayResult("Sequence file " + suffix, sequenceFilePath);

  // Look for site selection:
  if (format == "Mase")
  {
    //getting site set:
    string siteSet = ApplicationTools::getStringParameter("siteSelection", args, "none", suffix, suffixIsOptional, false);
    if (siteSet != "none")
    {
      VectorSiteContainer * selectedSites;
      try
      {
        selectedSites = dynamic_cast<VectorSiteContainer *>(MaseTools::getSelectedSites(* sites, siteSet));
        if (verbose) ApplicationTools::displayResult("Set found", TextTools::toString(siteSet) + " sites.");
      }
      catch(IOException ioe)
      {
        ApplicationTools::displayError("Site Set '" + siteSet + "' not found.");
        exit(-1);
      }
      if (selectedSites->getNumberOfSites() == 0)
      {
        ApplicationTools::displayError("Site Set '" + siteSet + "' is empty.");
        exit(-1);
      }
      delete sites;
      sites = selectedSites;
    }
  }
  return sites;
}

/******************************************************************************/

VectorSiteContainer * SequenceApplicationTools::getSitesToAnalyse(
  const SiteContainer & allSites,
  map<string, string> & params,
  string suffix,
  bool suffixIsOptional,
  bool gapAsUnknown,
  bool verbose)
{
  // Fully resolved sites, i.e. without jokers and gaps:
  VectorSiteContainer * sitesToAnalyse;
  
  string option = ApplicationTools::getStringParameter("input.sequence.sites_to_use", params, "complete", suffix, suffixIsOptional);
  if (verbose) ApplicationTools::displayResult("Sites to use", option);
  sitesToAnalyse = new VectorSiteContainer(allSites);
  if (option == "all")
  {
    string maxGapOption = ApplicationTools::getStringParameter("input.sequence.max_gap_allowed", params, "100%", suffix, suffixIsOptional);
    if (maxGapOption[maxGapOption.size()-1] == '%')
    {
      double gapFreq = TextTools::toDouble(maxGapOption.substr(0,maxGapOption.size()-1)) / 100.;
      for (unsigned int i = sitesToAnalyse->getNumberOfSites(); i > 0; i--)
      {
        map<int, double> freq;
        SiteTools::getFrequencies(sitesToAnalyse->getSite(i-1), freq);
        if (freq[-1] > gapFreq) sitesToAnalyse->deleteSite(i-1);
      }
    }
    else
    {
      unsigned int gapNum=TextTools::to<unsigned int>(maxGapOption);
      for (unsigned int i = sitesToAnalyse->getNumberOfSites(); i > 0; i--)
      {
        map<int, unsigned int> counts;
        SiteTools::getCounts(sitesToAnalyse->getSite(i-1), counts);
        if (counts[-1] > gapNum) sitesToAnalyse->deleteSite(i-1);
      }
    }
    if (gapAsUnknown)
    {
      SiteContainerTools::changeGapsToUnknownCharacters(*sitesToAnalyse);
    }
  }
  else if (option == "complete")
  {
    sitesToAnalyse = dynamic_cast<VectorSiteContainer *>(SiteContainerTools::getCompleteSites(allSites));
    int nbSites = sitesToAnalyse->getNumberOfSites();
    if (verbose) ApplicationTools::displayResult("Complete sites", TextTools::toString(nbSites));
  }
  else if (option == "nogap")
  {
    sitesToAnalyse = dynamic_cast<VectorSiteContainer *>(SiteContainerTools::getSitesWithoutGaps(allSites));
    int nbSites = sitesToAnalyse->getNumberOfSites();
    if (verbose) ApplicationTools::displayResult("Sites without gap", TextTools::toString(nbSites));
  }
  else
  {
    ApplicationTools::displayError("Option '" + option + "' unknown in parameter 'sequence.sitestouse'.");
    exit(-1);
  }

  return sitesToAnalyse;
}

/******************************************************************************/

void SequenceApplicationTools::writeSequenceFile(
  const SequenceContainer & sequences,
  map<string, string> & params,
  const string & suffix,
  bool verbose)
{
  string sequenceFilePath = ApplicationTools::getAFilePath("output.sequence.file", params, true, false, suffix, false);
  string sequenceFormat   = ApplicationTools::getStringParameter("output.sequence.format", params, "Fasta", suffix, false, true);
  string format = "";
  map<string, string> args;
  KeyvalTools::parseProcedure(sequenceFormat, format, args);
  unsigned int ncol = ApplicationTools::getParameter<unsigned int>("length", args, 100, "", true, false);
  OSequence * oSeq;
  if (format == "Fasta")
  {
    oSeq = new Fasta(ncol);
  }
  else if (format == "Mase")
  {
    oSeq = new Mase(ncol);
  }
  else if (format == "Phylip")
  {
    bool sequential = true, extended = true;
    string split = "  ";
    if (args.find("order") != args.end())
    {
           if (args["order"] == "sequential" ) sequential = true;
      else if (args["order"] == "interleaved") sequential = false;
      else ApplicationTools::displayWarning("Argument '" +
             args["order"] +
             "' for argument 'Phylip#order' is unknown. " +
             "Default used instead: sequential.");
    }
    else ApplicationTools::displayWarning("Argument 'Phylip#order' not found. Default used instead: sequential.");
    if (args.find("type") != args.end())
    {
      if (args["type"] == "extended")
      {
        extended = true;
        split = ApplicationTools::getStringParameter("split", args, "spaces", "", true, false);
        if (split == "spaces") split = "  ";
        else if (split == "tab") split = "\t";
        else throw Exception("Unknown option for Phylip#split: " + split);
      }
      else if (args["type"] == "classic" ) extended = false;
      else ApplicationTools::displayWarning("Argument '" +
             args["type"] + "' for parameter 'Phylip#type' is unknown. " +
             "Default used instead: extended.");
    }
    else ApplicationTools::displayWarning("Argument 'Phylip#type' not found. Default used instead: extended.");
    oSeq = new Phylip(extended, sequential, ncol, true, split);
  }
  else
  {
    ApplicationTools::displayError("Format '" + format + "' unknown.");
    exit(-1);
  }
  
  if (verbose)
  {
    ApplicationTools::displayResult("Output file format", format);
    ApplicationTools::displayResult("Output file ", sequenceFilePath);
  }

  // Write sequences:
  oSeq->write(sequenceFilePath, sequences, true);
  
  delete oSeq;
}

/******************************************************************************/

