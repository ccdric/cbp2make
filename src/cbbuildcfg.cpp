/*
    cbp2make : Makefile generation tool for the Code::Blocks IDE
    Copyright (C) 2010-2023 Mirai Computing (mirai.computing@gmail.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

//------------------------------------------------------------------------------
#include <iostream>
//------------------------------------------------------------------------------
#include "cbbuildcfg.h"
#include "stlconvert.h"
#include "tinyXml2Port.h"
//------------------------------------------------------------------------------

CCodeBlocksBuildConfig::CCodeBlocksBuildConfig(void)
{
 Clear();
}

CCodeBlocksBuildConfig::~CCodeBlocksBuildConfig(void)
{
 Clear();
}

void CCodeBlocksBuildConfig::Clear(void)
{
 m_Platforms.Clear();
 m_ToolChains.Clear();
 m_GlobalVariables.Clear();
 m_DefaultOptions.Clear();
 m_Targets.Clear();
 m_TargetNameCase = CASE_KEEP;
 m_MacroVariableCase = CASE_KEEP;
 m_QuotePathMode = QUOTE_AUTO;
 m_NumericToolchainSuffix = true;
 m_FlatObjectNames = false;
 m_FlatObjectPaths = false;
 m_MultilineObjects = false;
 m_MultilineOptions = false;
 m_IncludeDependencies = false;
 m_KeepObjectDirectories = false;
 m_KeepOutputDirectories = false;
 m_BeQuiet = false;
 m_BeVerbose = false;
}

bool CCodeBlocksBuildConfig::Load(const CString& FileName)
{
 Clear();
 m_ToolChains.AddDefault();
 m_GlobalVariables.AddDefault();
 //
 TiXmlDocument cfg;
 if (!cfg.LoadFile(FileName.GetCString())) return false;
 const TiXmlElement *root = cfg.RootElement();
 if (0==strcmp(root->Value(),"cbp2make"))
 {
  const TiXmlNode *_platforms = root->FirstChildElement("platforms");
  if (0!=_platforms)
  {
   const TiXmlElement *platforms = _platforms->ToElement();
   if (0!=platforms)
   {
    m_Platforms.Read(platforms);
   }
  }
  const TiXmlNode *_toolchains = root->FirstChildElement("toolchains");
  if (0!=_toolchains)
  {
   const TiXmlElement *toolchains = _toolchains->ToElement();
   if (0!=toolchains)
   {
    m_ToolChains.Read(toolchains);
   }
  }
  const TiXmlNode *_globvars = root->FirstChildElement("globalvariables");
  if (0!=_globvars)
  {
   const TiXmlElement *globvars = _globvars->ToElement();
   if (0!=globvars)
   {
    m_GlobalVariables.Read(globvars);
   }
  }
  const TiXmlNode *_options = root->FirstChildElement("options");
  if (0!=_options)
  {
   const TiXmlElement *options = _options->ToElement();
   if (0!=options)
   {
    char *value = 0;
    if ((value = (char *)options->Attribute("default")))
    {
     m_DefaultOptions = value;
    }
   }
  }
 }
 return true;
}

bool CCodeBlocksBuildConfig::Save(const CString& FileName)
{
 m_ToolChains.AddDefault();
 m_GlobalVariables.AddDefault();
 //
 TiXmlDocument cfg;
 cfg.NewDeclaration();
//	cfg.LinkEndChild(xmld);
	TiXmlElement *root = cfg.NewElement("cbp2make");
//	cfg.LinkEndChild(root);
	TiXmlElement *platforms = root->InsertNewChildElement("platforms");
//	root->LinkEndChild(platforms);
 m_Platforms.Write(platforms);
	TiXmlElement *toolchains = root->InsertNewChildElement("toolchains");
//	root->LinkEndChild(toolchains);
 m_ToolChains.Write(toolchains);
	TiXmlElement *globvars = root->InsertNewChildElement("globalvariables");
//	root->LinkEndChild(globvars);
 m_GlobalVariables.Write(globvars);
 TiXmlElement *options = root->InsertNewChildElement("options");
// root->LinkEndChild(options);
 options->SetAttribute("default",m_DefaultOptions.GetCString());
 return cfg.SaveFile(FileName.GetCString());
}

void CCodeBlocksBuildConfig::Show(void)
{
 m_Platforms.Show();
 m_ToolChains.Show();
 m_GlobalVariables.Show();
}

//------------------------------------------------------------------------------
