#include "mzgl.h"
#include <algorithm>

VOID mzgl::model::DrawDAE( mzgl::anim *Ani, DBL Size )
{
  for (auto &x : Pr)
    {
      bufIbm->Apply();
      bufMatr->Apply();
      Ani->Draw(x, mzgl::matr().Scale(mzgl::vec3(Size)));
    }
}

VOID mzgl::model::SetDAE( mzgl::anim *Ani )
{
  bufIbm = Ani->BufferCreate(Name + "Buffer IBM", 0, sizeof(mzgl::matr) * IBM.size(), IBM.data());

  bufMatr = Ani->BufferCreate(Name + "Buffer Matr", 1, sizeof(mzgl::matr) * MatrData.size(), MatrData.data());
}

VOID mzgl::model::ResponseTime( DBL Time )
{
  for (INT i = 0; i < AnimsJt.size(); i++)
  {
    DBL MaxTime = AnimsJt[i].TimePoints[AnimsJt[i].TimePoints.size() - 1];
    DBL CurTime = (Time - MaxTime * INT(Time / MaxTime));


    if (AnimsJt[i].TimePoints.size() <= 0)
      continue;


    for (INT k = 0; k < AnimsJt[i].TimePoints.size(); k++)
    {
      if (abs(CurTime - AnimsJt[i].TimePoints[k]) <= 0.1)
      {
        INT c = k * AnimsJt[i].Stride - 1;

        std::vector<std::string> data = SplitBy(AnimsJt[i].Target, '/');

        std::string id = data[0];
        std::string target = data[1];

        std::vector<std::string> all_target = SplitBy(target, '.');
        
        joint *Node = FindJointById(id);

        SidMatr *m = FindMatrBySid(Node, all_target[0]);

        if (all_target[0] == "translation")
          m->M = matr().Translate(vec3(AnimsJt[i].DataToChange[c + 1], AnimsJt[i].DataToChange[c + 2], AnimsJt[i].DataToChange[c + 3]));
        else if (all_target[0] == "scale")          
          m->M = matr().Scale(vec3(AnimsJt[i].DataToChange[c + 1], AnimsJt[i].DataToChange[c + 2], AnimsJt[i].DataToChange[c + 3]));
        else if (all_target[0] == "rotateX")
        {
          if (all_target.size() <= 1 || all_target[1] == "ANGLE")
            m->M = matr().Rotate(AnimsJt[i].DataToChange[c + 1], vec3(1, 0, 0));    
        }
        else if (all_target[0] == "rotateY")
        {
          if (all_target.size() <= 1 || all_target[1] == "ANGLE")
            m->M = matr().Rotate(AnimsJt[i].DataToChange[c + 1], vec3(0, 1, 0));            
        }
        else if (all_target[0] == "rotateZ")
        {
          if (all_target.size() <= 1 || all_target[1] == "ANGLE")
            m->M = matr().Rotate(AnimsJt[i].DataToChange[c + 1], vec3(0, 0, 1));
        }

        EvalJointMatrix();
        break;
      }
    }
  }

  SetMatrixs();
  bufIbm->Update(0, 0, IBM.data());
  bufMatr->Update(0, 0, MatrData.data());
}

VOID mzgl::model::ToDrawDAE( mzgl::anim *Ani, DBL Size )
{
  for (auto &x : Pr)
  {
    Ani->PrimsToDraw.push_back(x);
    Ani->MatrsToDraw.push_back(mzgl::matr().Scale(mzgl::vec3(Size)));
  }
}

mzgl::model & mzgl::model::LoadModelDAE( const std::string &M, mzgl::material *Mfd )
{
  dae::xml tree;

  tree.Load(M);
  std::vector<prim *> Prims;
  static INT counter = 0;

  tag_list triangles = tree.FindByName("triangles");
  //tag_list polylists = tree.FindByName("polylist");
  //triangles.insert(triangles.end(), polylists.begin(), polylists.end());

  for (auto &i : triangles)
  {
    counter++;
    if (std::stoi(i->Attribs["count"]) == 0)
      continue;
    topology::base<vertex::std> topo;
    topo.Type = prim_type::TRIMESH;

    std::vector<INT> p_array;

    std::vector<vec3> Normals;
    std::vector<vec3> Positions;
    std::vector<vec2> Textures;
    std::string ImagePrim;

    INT n_offset = 0, p_offset = 0, all_inputs = 0, t_offset = -1;

    for (INT x = 0; x < i->Tags.size(); x++)
    {
      dae::tag &c = i->Tags[x];

      if (c.Name == "p")
        p_array = ParseStringToVectorInt(c.Text[0]);      
      else if (c.Name == "input")
      {
        all_inputs++;
        if (c.Attribs["semantic"] == "NORMAL")
        {
          std::string src = c.Attribs["source"];
          n_offset = std::stoi(c.Attribs["offset"]);
          std::vector<FLT> n_data = ParseStringToVectorFloat(tree.FindByAttribVal("id", src.substr(1) + "-array")[0]->Text[0]);
          for (INT j = 0; j < n_data.size(); j += 3)
          {
            vec3 tmp = vec3(n_data[j], n_data[j + 1], n_data[j + 2]);
            Normals.push_back(tmp);
          }
        }
        else if (c.Attribs["semantic"] == "VERTEX")
        {
          std::string src = c.Attribs["source"];
          p_offset = std::stoi(c.Attribs["offset"]);

          dae::tag *vertices = tree.FindByAttribVal("id", src.substr(1))[0];
          std::string src_2 = "";
          for (auto &h : vertices->Tags)
          {
            if (h.Name == "input" && h.Attribs["semantic"] == "POSITION")
              src_2 = h.Attribs["source"].substr(1);
          }

          std::vector<FLT> p_data = ParseStringToVectorFloat(tree.FindByAttribVal("id", src_2 + "-array")[0]->Text[0]);
          for (INT j = 0; j < p_data.size(); j += 3)
            Positions.push_back(vec3(p_data[j], p_data[j + 1], p_data[j + 2]));
        }
        else if (c.Attribs["semantic"] == "TEXCOORD" && t_offset == -1)
        {
          std::string src = c.Attribs["source"];

          if (i->Attribs.find("material") == i->Attribs.end())
            continue;

          std::string pre_material = i->Attribs["material"];
          std::string target = tree.FindByAttribVal("symbol", pre_material)[0]->Attribs["target"].substr(1);

          dae::tag *material = tree.FindByAttribVal("id", target)[0];
          std::string effect_name = material->Tags[0].Attribs["url"].substr(1);

          dae::tag *effect = tree.FindByAttribVal("id", effect_name)[0];

          tag_list all_surfaces = tree.FindByNameFrom(effect, "surface");
          if (all_surfaces.size() <= 0)
            continue;

          dae::tag *surface = all_surfaces[0];

          std::string img_name = tree.FindByNameFrom(surface, "init_from")[0]->Text[0];

          dae::tag *image = tree.FindByAttribVal("id", img_name)[0];
          std::string img = tree.FindByNameFrom(image, "init_from")[0]->Text[0];

          if (img.length() > 1 && img[0] == '.' && img[1] == '/')
            img = img.substr(2);

          ImagePrim = img;

          std::vector<FLT> t_data = ParseStringToVectorFloat(tree.FindByAttribVal("id", src.substr(1) + "-array")[0]->Text[0]);
          for (INT j = 0; j < t_data.size(); j += 2)
          {
            vec2 tmp = vec2(t_data[j], t_data[j + 1]);
            Textures.push_back(tmp);
          }

          t_offset = std::stoi(c.Attribs["offset"]);
        }
      }
    }

    std::vector<vertex::std> BufferVert;

    /* START VERTEX WEIGHTS */

    tag_list vertex_weights = tree.FindByName("vertex_weights");

    dae::tag *vw = vertex_weights[0];

    std::vector<FLT> weights;
    std::vector<INT> vcount, v;

    for (auto &a : vw->Tags)
      if (a.Attribs["semantic"] == "WEIGHT")
      {
        std::string src = a.Attribs["source"].substr(1) + "-array";
        weights = ParseStringToVectorFloat(tree.FindByAttribVal("id", src)[0]->Text[0]);
        break;
      }

    vcount = ParseStringToVectorInt(tree.FindByNameFrom(vw, "vcount")[0]->Text[0]);
    v = ParseStringToVectorInt(tree.FindByNameFrom(vw, "v")[0]->Text[0]);

    /* END VERTEX WEIGHTS */


    std::vector<vec2> vec2V;

    for (INT m = 0; m < v.size(); m += 2)
    {
      vec2V.push_back(vec2(v[m], v[m + 1]));
    }

    INT counter = 0;

    std::vector<vec4> gms;
    std::vector<vec4> gws;

    for (INT m = 0; m < Positions.size(); m++)
    {
      INT c = vcount[m];
      
      std::vector<vec2> tmp;
      vec4 ws(-1), ms(-1);

      for (INT u = counter; u < counter + c; u++)
        tmp.push_back(vec2(vec2V[u][0], weights[vec2V[u][1]]));

      std::sort(tmp.begin(), tmp.end(), [](const vec2 &l, const vec2 &r){ return l[1] > r[1]; });

      INT max = (tmp.size() > 4) ? 4 : tmp.size();

      for (INT u = 0; u < max; u++)
      {
        ms[u] = tmp[u][0];
        ws[u] = tmp[u][1];
      }

      gms.push_back(ms);
      gws.push_back(ws);

      counter += c;
    }

    for (INT m = 0; m < p_array.size(); m += all_inputs)
    {
      vertex::std V;
      V.C = vec4(rand() / (FLT)RAND_MAX, rand() / (FLT)RAND_MAX, rand() / (FLT)RAND_MAX, 1);
      V.P = Positions[p_array[m + p_offset]];
      V.N = Normals[p_array[m + n_offset]];
      V.GM = gms[p_array[m + p_offset]];
      V.GW = gws[p_array[m + p_offset]];
  
      if (t_offset != -1)
        V.T = Textures[p_array[m + t_offset]];
      else
        V.T = vec2(0, 0);

      BufferVert.push_back(V);
    }

    topo.V = BufferVert;

    material *NewMtl = Rnd->MtlCreate(M + std::to_string(counter), vec3(Mfd->MtlData.Ka4[0], Mfd->MtlData.Ka4[1], Mfd->MtlData.Ka4[2]), 
                                 vec3(Mfd->MtlData.KdTrans[0], Mfd->MtlData.KdTrans[1], Mfd->MtlData.KdTrans[2]),
                                 vec3(Mfd->MtlData.KsPh[0], Mfd->MtlData.KsPh[1], Mfd->MtlData.KsPh[2]),
                                 Mfd->MtlData.KsPh[3], Mfd->MtlData.KdTrans[3], Mfd->MtlPat);
 

    if (t_offset != -1)
    {
      std::string path = "bin\\textures\\" + ImagePrim;
      NewMtl->AddTexture(Rnd->TxtLoadAll(path, NewMtl->Name + "Txt"));
    }

    Prims.push_back(Rnd->PrimCreate<vertex::std>(NewMtl, topo));
  }

  Pr = Prims;

  /* START NODES (JOINTS) */

  tag_list allJoints = tree.FindByName("joints");
  if (allJoints.size() <= 0)
    return *this;

  tag_list allVisualScenes = tree.FindByName("visual_scene");
  if (allVisualScenes.size() <= 0)
    return *this;

  /* START TAG JOINTS NEED TO FIX */
  dae::tag *Joints = allJoints[0]; // JOINTS ARE FOR EVERY PRIMITIVE
  dae::tag *VisualScene = allVisualScenes[0];

  tag_list Node_Tree = tree.FindByNameNotRec(VisualScene, "node");

  std::vector<std::string> Joint_Names;
  std::vector<mzgl::matr> Joint_IBM;

  tag_list inputs = tree.FindByNameFrom(Joints, "input");

  for (INT h = 0; h < inputs.size(); h++)
  {
    if (inputs[h]->Attribs["semantic"] == "JOINT")
    {
      std::string target = inputs[h]->Attribs["source"].substr(1) + "-array";

      Joint_Names = ParseStringToVectorString(tree.FindByAttribVal("id", target)[0]->Text[0]);
    }
    else if (inputs[h]->Attribs["semantic"] == "INV_BIND_MATRIX")
    {
      std::string target = inputs[h]->Attribs["source"].substr(1) + "-array";

      std::vector<FLT> data = ParseStringToVectorFloat(tree.FindByAttribVal("id", target)[0]->Text[0]);

      for (INT l = 0; l < data.size(); l += 16)
      {
        mzgl::matr t(data[l], data[l + 1], data[l + 2], data[l + 3],
                     data[l + 4], data[l + 5], data[l + 6], data[l + 7],
                     data[l + 8], data[l + 9], data[l + 10], data[l + 11],
                     data[l + 12], data[l + 13], data[l + 14], data[l + 15]);

        t = t.Transpose();

        Joint_IBM.push_back(t);
      }
    }
  }

  /* END TAG JOINTS NEED TO FIX */

  std::vector<joint> JointTree;
  for (INT q = 0; q < Node_Tree.size(); q++)
    this->JointTree(JointTree, Node_Tree[q], mzgl::matr().Identity(), Joint_Names, Joint_IBM);

  Jt = JointTree;

  this->NamesJoints = Joint_Names;

  SetMatrixs();

  /* END NODES (JOINTS) */

  /* START DO ANIMATION */

  tag_list all_library_anim = tree.FindByName("library_animations");
  if (all_library_anim.size() <= 0)
    return *this;

  dae::tag *library_anim = all_library_anim[0];


  tag_list anims = tree.FindByNameFrom(library_anim, "animation");

  for (INT k = 0; k < anims.size(); k++)
  {
    animation cur_ani;

    dae::tag *Channel = tree.FindByNameFrom(anims[k], "channel")[0];

    cur_ani.Sampler = Channel->Attribs["source"].substr(1);
    cur_ani.Target = Channel->Attribs["target"];

    dae::tag *Sampler = tree.FindByAttribVal("id", cur_ani.Sampler)[0];

    for (auto &b : Sampler->Tags)
    {
      if (b.Attribs["semantic"] == "INPUT")
      {
        std::string id = b.Attribs["source"].substr(1);

        cur_ani.TimePoints = ParseStringToVectorFloat(tree.FindByAttribVal("id", id +  + "-array")[0]->Text[0]); 
      }                                             
      else if (b.Attribs["semantic"] == "OUTPUT")
      {
        std::string id = b.Attribs["source"].substr(1);
        cur_ani.DataToChange = ParseStringToVectorFloat(tree.FindByAttribVal("id", id +  + "-array")[0]->Text[0]);
        cur_ani.Stride = std::stoi(tree.FindByAttribVal("source", "#" + id + "-array")[0]->Attribs["stride"]);
      }
    }

    AnimsJt.push_back(cur_ani);
  }

  /* END DO ANIMATION */

  return *this;
}
VOID mzgl::model::DrawJointsRec( mzgl::prim *Pr, mzgl::anim *An, mzgl::matr Extra, mzgl::model::joint *j )
{
  An->Draw(Pr, j->MatrNode * Extra);

  for (INT i = 0; i < j->SubJoints.size(); i++)
    DrawJointsRec(Pr, An, Extra, &j->SubJoints[i]);
}