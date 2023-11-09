/* FILE NAME   : xml.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.09.2023
 * PURPOSE     : dae compression project.
 *               xml header file.
 */

#ifndef __xml_h_
#define __xml_h_

#include "def.h"

#include "../parser/parser.h"
#include "../parser/scanner.h"
#include <string>
#include <iostream>

/* Project namespace */
namespace dae
{
  /* Xml class */
  class xml
  {
  private:
    scanner sc;
    parser ps;
    std::vector<std::string> tokens;
    std::vector<tag> Tags;
  public:

    /* Class constructor */
    xml()
    {
    }

    /* Class constructor */
    xml( std::string &in )
    {
      Load(in);
    }

    /* Class destructor */
    ~xml()
    {
    }

    BOOL Load( const std::string &in )
    {
      if (!sc.Open(in))
        return FALSE;

      sc.Scan(tokens);

      ps.Open(tokens);
      ps.Parse(Tags);

      sc.Close();  

      return TRUE;
    }

    VOID Display( VOID )
    {
      for (INT i = 0; i < Tags.size(); i++)
        DisplayRec(Tags[i], 0);
    }

    std::vector<tag *> FindByAttribVal(const std::string &Att, const std::string &Val)
    {
      std::vector<tag *> Ans;

      for (INT i = 0; i < Tags.size(); i++)
        FindByAttribValRec(Ans, Att, Val, &Tags[i]);

      return Ans;
    }

    std::vector<tag *> FindByName( const std::string &Name )
    {
      std::vector<tag *> Ans;

      for (INT i = 0; i < Tags.size(); i++)
        FindByNameRec(Ans, Name, &Tags[i]);

      return Ans;
    }

    std::vector<tag *> FindByNameFrom( tag *Start, const std::string &Name )
    {
      std::vector<tag *> Ans;

      FindByNameRec(Ans, Name, Start);

      return Ans;
    }

    std::vector<tag *> FindByNameNotRec( tag *Start, const std::string &Name )
    {
      std::vector<tag *> Ans;

      for (INT i = 0; i < Start->Tags.size(); i++)
        if (Start->Tags[i].Name == Name)
          Ans.push_back(&Start->Tags[i]);

      return Ans;
    }

  private:
    VOID FindByAttribValRec( std::vector<tag *> &A, const std::string &At, const std::string &Val, tag *Cur )
    {
      if (Cur->Tags.size() > 0)
        for (INT i = 0; i < Cur->Tags.size(); i++)
          FindByAttribValRec(A, At, Val, &Cur->Tags[i]);

      if (Cur->Attribs.find(At) == Cur->Attribs.end())
        return;
      else if (Cur->Attribs[At] == Val)
        A.push_back(Cur);
    }

    VOID FindByNameRec( std::vector<tag *> &A, const std::string &Name, tag *Cur )
    {
      if (Cur->Tags.size() > 0)
        for (INT i = 0; i < Cur->Tags.size(); i++)
          FindByNameRec(A, Name, &Cur->Tags[i]);

      if (Cur->Name != Name)
        return;

      A.push_back(Cur);
    }

    VOID DisplayRec( tag &V, INT RecLevel )
    {
      std::string word;

      if (V.Tags.size() == 0)
      {
        word = "";
        for (INT i = 0; i < RecLevel; i++)
          word += "  ";
        std::cout << word << "<" << V.Name << " ";
        for (auto &i : V.AttribsNames)
          std::cout << i << "=" << V.Attribs[i] << ";";
        std::cout << ">";

        std::cout << "(";
        for (auto &x : V.Text)
          std::cout << x;
        std::cout << ")\n";


        return;
      }

      word = "";
      for (INT i = 0; i < RecLevel; i++)
        word += "  ";
      std::cout << word << "<" << V.Name << " ";
      for (auto &i : V.AttribsNames)
        std::cout << i << "=" << V.Attribs[i] << ";";
      std::cout << ">";

      std::cout << "(";
        for (auto &x : V.Text)
          std::cout << x;
        std::cout << ")\n";

      for (INT j = 0; j < V.Tags.size(); j++)
        DisplayRec(V.Tags[j], RecLevel + 1);
    }
  };  /* End of 'xml' class */
} /* end of 'dae' namespace */


#endif /* __xml_h_ */

/* END OF 'xml.h' FILE */
