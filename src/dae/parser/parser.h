/* FILE NAME   : parser.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.09.2023
 * PURPOSE     : dae compression project.
 *               parser header file.
 */

#ifndef __parser_h_
#define __parser_h_

#include "def.h"
#include <map>
#include <vector>

/* Project namespace */
namespace dae
{
  /* Tag class */
  class tag
  {
  public:
    std::string Name;
    std::vector<tag> Tags;
    std::map<std::string, std::string> Attribs;
    std::vector<std::string> AttribsNames;
    std::vector<std::string> Text;
  public:
    /* Class constructor */
    tag()
    {
    
    }

    /* Class destructor */
    ~tag()
    {
    
    }
  }; /* End of 'tag' class */

  /* parser class */
  class parser
  {
  private:
    std::vector<std::string> Lexems;
    size_t LexemSize;
  public:
    /* Class constructor */
    parser()
    {
      
    }

    VOID Open( std::vector<std::string> &L )
    {
      Lexems = L;
      LexemSize = L.size();
    }

    BOOL ParseLexem( std::string &l )
    {
      static INT cnt = 0;

      if (cnt >= LexemSize)
        return FALSE;

      l = Lexems[cnt];
      cnt++;

      return TRUE;
    }

    VOID Parse( std::vector<tag> &Tags )
    {
      std::string CurLex;
      std::vector <tag *> Stack;

      while (TRUE)
      {
        if (!ParseLexem(CurLex))
          return;

        /*
        
        IDEA: Create a stack of pointers to last parent tag.

        If new tag -> push to stack;
        if close tag -> pop from stack;
        if single tag -> do nothing with stack;

        Pointers in stack -> from vector of tags and vector of subtags of this tags;
          
        */

        if (CurLex == "<")
        {
          ParseLexem(CurLex);
          if (CurLex == "/")
          {
            ParseLexem(CurLex); // Name
            ParseLexem(CurLex); // >
            Stack.pop_back();
          }
          else if (CurLex == "?")
          {
            tag Header;

            ParseLexem(CurLex);
            Header.Name = CurLex;

            ParseLexem(CurLex);
            while (CurLex != "?")
            {
              std::string eq, val;

              ParseLexem(eq);
              ParseLexem(val);

              Header.Attribs[CurLex] = val;
              Header.AttribsNames.push_back(CurLex);
              ParseLexem(CurLex);
            }

            ParseLexem(CurLex);
            Tags.push_back(Header);
          }
          else
          {
            tag NewTag;

            NewTag.Name = CurLex;
            ParseLexem(CurLex);
            while (CurLex != "/" && CurLex != ">")
            {
              std::string eq, val;

              ParseLexem(eq);
              ParseLexem(val);

              NewTag.Attribs[CurLex] = val;
              NewTag.AttribsNames.push_back(CurLex);
              ParseLexem(CurLex);
            }

            if (CurLex == "/")
            {
              ParseLexem(CurLex);
              if (Stack.size() == 0)
                Tags.push_back(NewTag);
              else
                Stack[Stack.size() - 1]->Tags.push_back(NewTag);
            }
            else
            {
              if (Stack.size() == 0)
              {
                Tags.push_back(NewTag);
                Stack.push_back(&Tags[Tags.size() - 1]);
              }
              else
              {
                Stack[Stack.size() - 1]->Tags.push_back(NewTag);
                Stack.push_back(&Stack[Stack.size() - 1]->Tags[Stack[Stack.size() - 1]->Tags.size() - 1]);
              }
            }
          }
        }
        else
        {
          if (Stack.size() == 0)
            Tags[Tags.size() - 1].Text.push_back(CurLex);
          else
            Stack[Stack.size() - 1]->Text.push_back(CurLex);
        }
      }
    }

    /* Class destructor */
    ~parser()
    {
      
    }
  }; /* End of 'parser' class */
} /* end of 'dae' namespace */


#endif /* __parser_h_ */

/* END OF 'parser.h' FILE */
