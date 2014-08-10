#pragma once

/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "utils/StdString.h"

#include <map>
#include <set>
#include "interfaces/info/InfoBool.h"

// forward definitions
class TiXmlElement;
namespace INFO
{
  class CSkinVariableString;
}

class CGUIIncludes
{
public:
  CGUIIncludes();
  ~CGUIIncludes();

  void ClearIncludes();
  bool LoadIncludes(const CStdString &includeFile);
  bool LoadIncludesFromXML(const TiXmlElement *root);

  /*! \brief Resolve <include>name</include> tags recursively for the given XML element
   Replaces any instances of <include file="foo">bar</include> with the value of the include
   "bar" from the include file "foo".
   \param node an XML Element - all child elements are traversed.
   */
  void ResolveIncludes(TiXmlElement *node, std::map<INFO::InfoPtr, bool>* xmlIncludeConditions = NULL);
  void ResolveIncludes(TiXmlElement *node, std::map<INFO::InfoPtr, bool>* xmlIncludeConditions, std::map<std::string, std::string> &params);
  const INFO::CSkinVariableString* CreateSkinVariable(const CStdString& name, int context);

private:
  void ResolveIncludeForNode(TiXmlElement *parent, TiXmlElement *include, std::map<INFO::InfoPtr, bool>* xmlIncludeConditions, std::map<std::string, std::string> params);
  bool LoadIncludesIfFile(TiXmlElement *include, std::map<INFO::InfoPtr, bool>* xmlIncludeConditions);
  void ResolveDefaultsForNode(TiXmlElement *node);
  void ResolveConstantsForNode(TiXmlElement *node);
  void GetParametersFromIncludeCallAndDefinition(const TiXmlElement *includeCall, const TiXmlElement *includeDef, std::map<std::string, std::string> &params) const;
  void GetParametersForNode(const TiXmlElement *node, std::map<std::string, std::string> &params, bool isIncludeCall = false) const;
  void ResolveParametersForNode(TiXmlElement *node, std::map<std::string, std::string> &params) const;
  bool ResolveParameters(const std::string &strInput, std::string &strOutput, const std::map<std::string, std::string> &params) const;
  CStdString ResolveConstant(const CStdString &constant) const;
  bool HasIncludeFile(const CStdString &includeFile) const;
  std::map<CStdString, TiXmlElement> m_includes;
  std::map<CStdString, TiXmlElement> m_defaults;
  std::map<CStdString, TiXmlElement> m_skinvariables;
  std::map<CStdString, CStdString> m_constants;
  std::vector<CStdString> m_files;
  typedef std::vector<CStdString>::const_iterator iFiles;
  bool GetActualParamName(const char *name, std::string &paramName) const;

  std::set<std::string> m_constantAttributes;
  std::set<std::string> m_constantNodes;

  static const char paramNamespacePrefix[];
  static const char forwardParamsAttributeName[];
  static const std::string eraseParamsValue;
};

