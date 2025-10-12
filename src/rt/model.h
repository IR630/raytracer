/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : box.h
 * PURPOSE     : Ray tracing.
 *               Ray tracing box handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Reznikov Ivan (IR6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __model_h_
#define __model_h_

#if 0
/* Load primitive from '*.OBJ' file function.
 * ARGUMENTS:
 *   - pointer to primitive to load:
 *       IR6PRIM *Pr;
 *   - '*.OBJ' file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL PrimLoad( ir6PRIM *Pr, CHAR *FileName )
{
  FILE *F;
  ir6VERTEX *V;
  INT *Ind = 0;
  INT nv = 0, nf = 0, size;
  static CHAR Buf[10000];

  memset(Pr, 0, sizeof(ir6PRIM));
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;
 
  /* Count vertices and indices */
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0;
      CHAR *ptr = Buf + 2, old = ' ';
 
      while (*ptr != 0)
        n += *ptr != ' ' && old == ' ', old = *ptr++;
      nf += n - 2;
    }

  size = nv * sizeof(ir6VERTEX) + sizeof(INT) * nf * 3;

  if ((V = malloc(size)) == NULL)
  {
    fclose(F);
    return FALSE;
  }

  Ind = (INT *)(V + nv);
  memset(V, 0, size);

  /* Read model data */
  rewind(F);
  nv = nf = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      FLT x, y, z;
 
      sscanf(Buf + 2, "%f %f %f", &x, &y, &z);
      V[nv].C = Vec4Set(0.47, 0.30, 1, 0.5);
      V[nv++].P = VecSet(x, y, z);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0, c = 0, c0 = 0, c1 = 0, c2 = 0;
      CHAR *ptr = Buf + 2, old = ' ';
 
      while (*ptr != 0)
      {
        if (*ptr != ' ' && old == ' ')
        {
          sscanf(ptr, "%d", &c);
          if (c < 0)
            c = nv + c;
          else
            c--;
 
          if (n == 0)
            c0 = c;
          else if (n == 1)
            c1 = c;
          else
          {
            /* add new triangle */
            Ind[nf++] = c0;
            Ind[nf++] = c1;
            Ind[nf++] = c;
            c1 = c;
          }
          n++;
        }
        old = *ptr++;
      }
    }


  fclose(F);

  IR6_RndPrimAutoNormals(V, nv, Ind, nf);
  IR6_RndPrimCreate(Pr, V, Pr->Type, nv, Ind, nf);

  free(V);
  return TRUE;
} /* End of 'IR6_RndPrimLoad' function */
#endif /* 0 */

#endif /* __model_h_ */

/* END OF 'model.h' FILE */
