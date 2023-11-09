/* FILE NAME   : model.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 02.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               Models's and font's manager handle module.
 */

#ifndef __model_h_
#define __model_h_

#include "def.h"

#include "res_manager.h"
#include "material.h"
#include "primitives.h"
#include "resource.h"
#include "../render.h"
#include "anim/anim.h"
#include "../../../dae/dae.h"
#include <sstream>

#include <iostream>

/* Project namespace */
namespace mzgl
{
  class render;
  class anim;
  class xml;
  class buffer;

  class model : public resource
  {
    /* NEED TO MAKE INTERPOLATION BETWEEN FRAMES */
    struct SidMatr
    {
      std::string Sid;
      mzgl::matr M;

      SidMatr(const std::string &S, mzgl::matr Ma ) : Sid(S), M(Ma)
      {
      }
    };

    struct joint
    {
      std::string Name;
      INT Number;
      std::string Id;
      mzgl::matr IBM, MatrNode, MatrParent;
      std::vector<joint> SubJoints;
      std::vector<SidMatr> AllMatrs;
    };

    struct animation
    {
      std::string Sampler;
      std::string Target;
      std::vector<FLT> TimePoints;
      std::vector<FLT> DataToChange;
      INT Stride;
    };

    friend class render;
  public:
    std::string Name; 

    std::vector<prim *> Pr;
    std::vector<joint> Jt;
    std::vector<animation> AnimsJt;
    std::vector<matr> IBM;
    std::vector<matr> MatrData; 

    buffer *bufIbm;
    buffer *bufMatr;

    std::vector<std::string> NamesJoints;

    VOID DrawDAE( mzgl::anim *Ani, DBL Size );
    VOID SetDAE( mzgl::anim *Ani );

    VOID ToDrawDAE( mzgl::anim *Ani, DBL Size );

    VOID SetMatrixs( VOID )
    {
      IBM.clear();
      MatrData.clear();
      for (INT i = 0; i < NamesJoints.size(); i++)
      {
        joint *j = FindJointById(NamesJoints[i]);

        IBM.push_back(j->IBM);
        MatrData.push_back(j->MatrNode);
      }
    }

    joint * FindJointByIdRec( joint *J, std::string Id )
    {
      if (J->Id == Id)
        return J;
      else
        for (INT i = 0; i < J->SubJoints.size(); i++)
        {
          joint *j = FindJointByIdRec(&J->SubJoints[i], Id);
          if (j != nullptr)
            return j;
        }

      return nullptr;
    }

    joint * FindJointById( std::string Id )
    {
      for (INT i = 0; i < Jt.size(); i++)
      {
        joint *j = FindJointByIdRec(&Jt[i], Id);
        if (j != nullptr)
          return j;
      }

      return nullptr;
    }

    SidMatr * FindMatrBySid( joint *j, std::string Sid )
    {
      for (INT i = 0; i < j->AllMatrs.size(); i++)
        if (j->AllMatrs[i].Sid == Sid)
          return &j->AllMatrs[i];

      return nullptr;
    }

    VOID ResponseTime( DBL Time );


    std::vector<std::string> SplitBy( const std::string &str, const CHAR s )
    {
      std::vector<std::string> Res;

      std::string cur = "";
      for (INT i = 0; i < str.length(); i++)
      {
        if (str[i] == s)
        {
          Res.push_back(cur);
          cur = "";
          continue;
        }

        cur += str[i];
      }

      if (cur != "")
      {
        Res.push_back(cur);
        cur = "";
      }

      return Res;
    }

    VOID DrawJoints( prim *Pr, anim *An, matr Extra )
    {
      for (INT i = 0; i < Jt.size(); i++)
        DrawJointsRec(Pr, An, Extra, &Jt[i]);
    }

    VOID EvalJointMatrix(VOID)
    {
      for (INT i = 0; i < Jt.size(); i++)
        EvalJointMatrixRec(&Jt[i], mzgl::matr().Identity());
    }

  private:

    DBL abs( DBL x )
    {
      if (x < 0)
        return -x;

      return x;
    }

    VOID EvalJointMatrixRec( joint *j, mzgl::matr ParentM)
    {
      mzgl::matr m = mzgl::matr().Identity();
      for (INT k = j->AllMatrs.size() - 1; k >= 0; k-- )
        m = m * j->AllMatrs[k].M;

      j->MatrNode = m * ParentM;
      j->MatrParent = ParentM;

      for (INT i = 0; i < j->SubJoints.size(); i++)
        EvalJointMatrixRec(&j->SubJoints[i], j->MatrNode);
    }
    VOID DrawJointsRec( prim *Pr, anim *An, matr Extra, joint *j );

    std::vector<INT> ParseStringToVectorInt( std::string data_array )
    {
      std::string cur = "";
      std::vector<INT> Arr;

      for (INT i = 0; i < data_array.size(); i++)
      {
        if (data_array[i] == ' ')
        {
          if (cur != "")
            Arr.push_back(std::stoi(cur));

          cur = "";
          continue;
        }

        cur += data_array[i];
      }
      if (cur != "")
        Arr.push_back(std::stoi(cur));

      return Arr;
    }

    std::vector<FLT> ParseStringToVectorFloat( std::string data_array )
    {
      std::string cur = "";
      std::vector<FLT> Arr;

      for (INT i = 0; i < data_array.size(); i++)
      {
        if (data_array[i] == ' ')
        {
          if (cur != "")
            Arr.push_back(std::stof(cur));

          cur = "";
          continue;
        }

        cur += data_array[i];
      }
      if (cur != "")
        Arr.push_back(std::stof(cur));

      return Arr;
    }

    std::vector<std::string> ParseStringToVectorString( std::string data_array )
    {
      std::string cur = "";
      std::vector<std::string> Arr;

      for (INT i = 0; i < data_array.size(); i++)
      {
        if (data_array[i] == ' ')
        {
          if (cur != "")
            Arr.push_back(cur);

          cur = "";
          continue;
        }

        cur += data_array[i];
      }
      if (cur != "")
        Arr.push_back(cur);

      return Arr;
    }

    typedef std::vector<dae::tag *> tag_list;

    VOID JointTree( std::vector<joint> &J, dae::tag *T, mzgl::matr ParentM, std::vector<std::string> &Names, std::vector<mzgl::matr> &Matrs)
    {
      std::vector<SidMatr> mat;
      std::vector<INT> index;

      for (INT i = 0; i < T->Tags.size(); i++)
      {
        if (T->Tags[i].Name == "translate")
        {
          std::vector<FLT> data = ParseStringToVectorFloat(T->Tags[i].Text[0]);
          mat.push_back(SidMatr(T->Tags[i].Attribs["sid"], mzgl::matr().Translate(mzgl::vec3(data[0], data[1], data[2]))) );
        }
        else if (T->Tags[i].Name == "rotate")
        {
          std::vector<FLT> data = ParseStringToVectorFloat(T->Tags[i].Text[0]);
          mat.push_back(SidMatr(T->Tags[i].Attribs["sid"], mzgl::matr().Rotate(data[3], mzgl::vec3(data[0], data[1], data[2]))));
        }
        else if (T->Tags[i].Name == "scale")
        {
          std::vector<FLT> data = ParseStringToVectorFloat(T->Tags[i].Text[0]);
          mat.push_back(SidMatr(T->Tags[i].Attribs["sid"], mzgl::matr().Scale(mzgl::vec3(data[0], data[1], data[2]))));
        }
        else if (T->Tags[i].Name == "matrix")
        {
          std::stringstream ss_matr(T->Tags[i].Text[0]);

          FLT m[4][4];
          for (INT a = 0; a < 4; a++)
            for (INT b = 0; b < 4; b++)
              ss_matr >> m[b][a];

          mat.push_back(SidMatr(T->Tags[i].Attribs["sid"], mzgl::matr(m)));
        }
        else if (T->Tags[i].Name == "node")
        {
          index.push_back(i);    
        }
      }

      joint j;

      mzgl::matr m = mzgl::matr().Identity();
      for (INT k = mat.size() - 1; k >= 0; k-- )
        m = m * mat[k].M;

      j.MatrNode = m * ParentM;
      j.MatrParent = ParentM;
      j.Name = T->Attribs["name"];
      j.Id = T->Attribs["id"];

      j.AllMatrs = mat;

      j.IBM = mzgl::matr().Identity();
      j.Number = -1;

      for (INT f = 0; f < Names.size(); f++)
        if (Names[f] == j.Id)
        {
          j.IBM = Matrs[f]; /* ???? THERE ARE MORE JOINTS TAG THAN 1 */
          j.Number = f;
          break;
        }

      if (index.size() <= 0)
      {
        J.push_back(j);
        return;
      }

      for (INT w = 0; w < index.size(); w++)
        JointTree(j.SubJoints, &T->Tags[index[w]], j.MatrNode, Names, Matrs);

      J.push_back(j);
    }
  public:
    model & LoadModelDAE( const std::string &M, mzgl::material *Mfd );

    /* font default constructor */
    model( VOID )
    {
      Name = "";
    } /* End of 'font' function */

    model( std::string &N )
    {
      Name = N;
    } /* End of 'font' function */

        
    /* Free font function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID );

  }; /* End of 'font' class */
  
  /* font manager representation type */
  class model_manager : public resource_manager<model, std::string>
  {
  public:
    model_manager( render &Rnd ) : resource_manager(Rnd)
    {
    } /* End of 'font_manager' function */

    /* Font create function.
     * ARGUMENTS:
     *   - File name:
     *       const CHAR *FileName;
     *   - Name:
     *       std::string Name;
     * RETURNS:
     *   (font *) pointer to font.
     */
    model * ModelCreate( const std::string &FileName, std::string Name, mzgl::material *M )
    {
      model *m = resource_manager::Add(model(Name));

      return &m->LoadModelDAE(FileName, M); 
    } /* End of 'FntCreate' function */

    /* Free font function.
     * ARGUMENTS:
     *   - font pointer:
     *       font *Mtl;
     * RETURNS: None.
     */
    VOID ModelFree( model *Fnt )
    {
      resource_manager::Delete(Fnt);
    } /* End of 'FntFree' function */
  }; /* End of 'font_manager' class */

} /* end of 'mzgl' namespace */

#endif /* __model_h_ */

/* END OF 'model.h' FILE */