/* FILE NAME   : scanner.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.09.2023
 * PURPOSE     : dae compression project.
 *               scanner header file.
 */

#ifndef __scanner_h_
#define __scanner_h_

#include "def.h"
#include <map>
#include <vector>

/* Project namespace */
namespace dae
{
  /* Token class */
  class token
  {
  public:
    std::fstream File;
    INT16 Tok;
  public:
    /* Class constructor */
    token() : Tok(0)
    {    
    }

    /* Open function.
     * ARGUMENTS:
     *	- File name:
     *	    const std::string &Fn;
     * RETURNS:
     *	(BOOL) success of opening.
     */
    BOOL Open( const std::string &Fn )
    {
      Close();
      File = std::fstream(Fn, std::fstream::in);
      return (bool)File;
    } /* End of 'Open' function */

    INT16 ParseSym( VOID )
    {
      Tok = File.get();
      return Tok;
    }

    /* Close function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Close( VOID )
    {
      if (File.is_open())
        File.close();
    } /* End of 'Close' function */

    /* Class destructor */
    ~token()
    {    
    }
  }; /* End of 'token' class */

  /* Scanner class */
  class scanner
  {
  public:
    token Token;
  public:
    /* Class constructor */
    scanner()
    {
      
    }

    /* Open function.
     * ARGUMENTS:
     *	- File name:
     *	    const std::string &Fn;
     * RETURNS:
     *	(BOOL) success of opening.
     */
    BOOL Open( const std::string &Fn )
    {
      return Token.Open(Fn);
    } /* End of 'Open' function */

    VOID Scan( std::vector<std::string> &Lexems )
    {
      INT16 sym;
      std::string word = "";
      CHAR flag = -1;
      BOOL is_open = FALSE;
      INT i;

      while (TRUE)
      {
        sym = Token.ParseSym();
        if (sym == EOF)
        {
          if (word != "")
          {
            for (i = 0; i < word.length(); i++)
              if (word[i] != ' ' && word[i] != '\n')
                break;

            if (i < word.length())
              Lexems.push_back(word);
          }
          word = "";
          break;
        }

        if (sym == '<')
        {
          flag = 0;
          if (word != "")
          {
            for (i = 0; i < word.length(); i++)
              if (word[i] != ' ' && word[i] != '\n')
                break;

            if (i < word.length())
              Lexems.push_back(word);
          }
          word = "";
          Lexems.push_back(std::string(1, sym));
          continue;
        }
        else if (sym == '>')
        {
          flag = 1;
          if (word != "")
          {
            for (i = 0; i < word.length(); i++)
              if (word[i] != ' ' && word[i] != '\n')
                break;

            if (i < word.length())
              Lexems.push_back(word);
          }
          word = "";
          Lexems.push_back(std::string(1, sym));
          continue;
        }
        else if (sym == '"' || sym == '\'')
        {
          if (is_open == TRUE)
            is_open = FALSE;
          else
            is_open = TRUE;

          continue;
        }

        if (flag == 1)
        {
          if (sym != '\n')
            word += sym;
        }
        else if (flag == 0)
        {
          if (is_open)
            word += sym;
          else
          {
            if (sym == ' ' || sym == '\n' || sym == '=' || sym == '/' || sym == '?')
            {
              if (word != "")
              {
                for (i = 0; i < word.length(); i++)
                  if (word[i] != ' ' && word[i] != '\n')
                    break;

                if (i < word.length())
                  Lexems.push_back(word);
              }
              word = "";  

              if (sym != ' ' && sym != '\n')
                Lexems.push_back(std::string(1, sym));
            }
            else
              word += sym;
          }
        }
      }
    }

    /* Close function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Close( VOID )
    {
      Token.Close();
    } /* End of 'Close' function */

    /* Class destructor */
    ~scanner()
    {
      
    }
  }; /* End of 'scanner' class */
} /* end of 'dae' namespace */


#endif /* __scanner_h_ */

/* END OF 'scanner.h' FILE */