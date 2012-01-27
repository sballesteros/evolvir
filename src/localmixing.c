#include "evolvir.h"

void SpreadDisease(void)
{
  int i,j;
  /*on traite le coeur de la grille*/
  for(i=1;i<(DIM-1);i++)
    {
      for(j=1;j<(DIM-1);j++)
	{
	  if( (state[i][j]== S) ) infection(i,j,i-1,j,i+1,j,i,j-1,i,j+1);
	}
    }
  
  /*on traite les condition de bords ici on suppose un torre*/
  /*4 corners*/
  if( (state[0][0] == S) ) infection(0,0,DIM-1,0,1,0,0,DIM-1,0,1);
  if( (state[0][DIM-1] == S) ) infection(0,DIM-1,DIM-1,DIM-1,1,DIM-1,0,DIM-2,0,0);
  if( (state[DIM-1][0] == S) ) infection(DIM-1,0,DIM-2,0,0,0,0,DIM-1,0,1);
  if( (state[DIM-1][DIM-1] == S) ) infection(DIM-1,DIM-1,DIM-2,DIM-1,0,DIM-1,DIM-1,DIM-2,DIM-1,0);

  /*ligne haut*/
  for(j=1;j<(DIM-1);j++)
    {
      if( (state[0][j] == S) ) infection(0,j,DIM-1,j,1,j,0,j-1,0,j+1);
    }

  /*ligne bas*/
  for(j=1;j<(DIM-1);j++)
    {
      if( (state[DIM-1][j] == S) ) infection(DIM-1,j,DIM-2,j,0,j,DIM-1,j-1,DIM-1,j+1);
    }
  
  /*colonne gauche*/
  for(i=1;i<(DIM-1);i++)
    {
      if( (state[i][0] == S) ) infection(i,0,i-1,0,i+1,0,i,DIM-1,i,1);
    }

  /*colonne droite*/
  for(i=1;i<(DIM-1);i++)
    {
      if( (state[i][DIM-1] == S) ) infection(i,DIM-1,i-1,DIM-1,i+1,DIM-1,i,DIM-2,i,0);
    }
}

void infection(int x, int y, int xt, int yt, int xb, int yb, int xl, int yl, int xr, int yr)
{
  /*la cellule, celle en haut t, en bas b, a gauche l, a droite r*/
  int cnt=0;
  if(state[xt][yt]==I) cnt=1;
  if(state[xb][yb]==I) cnt +=1;
  if(state[xl][yl]==I) cnt +=1;
  if(state[xr][yr]==I) cnt +=1;

  if(cnt)
    {
      if(drand48() < (1.0-exp(-((double) cnt)*par_b*DELTA_T)) )
	{
	  state[x][y]=E;
	  timer[x][y]=TIME_E;
	}
    }
}

void ChangeStates(GtkWidget *widget)
{
  int i,j;
  
  for(i=0;i<DIM;i++)
    {
      for(j=0;j<DIM;j++)
	{  
	  switch(state[i][j])
	    {
	    case E:
	      state[i][j]=I;
	      timer[i][j]=par_v;
	      draw_I(widget,i,j);
	      break;

	    case I:
	      timer[i][j]--;
	      if(timer[i][j]==0)
		{
		  state[i][j]=R;
		  timer[i][j]=TIME_R;
		  draw_R(widget,i,j);
		}
	      break;

	    case R:
	      timer[i][j]--;
	      if(timer[i][j]==0)
		{
		  state[i][j]=S;
		  draw_S(widget,i,j);
		}
	      break;

	    }
	}
    }
}

/*----------------------------------------------------*/
/*----------------------------------------------------*/
/*----------------------------------------------------*/
/*mutation*/
/*----------------------------------------------------*/
/*----------------------------------------------------*/
/*----------------------------------------------------*/

void SpreadDiseaseMut(void)
{
  int i,j;
  /*on traite le coeur de la grille*/
  for(i=1;i<(DIM-1);i++)
    {
      for(j=1;j<(DIM-1);j++)
	{
	  if( (state[i][j]== S) ) InfectionMut(i,j,i-1,j,i+1,j,i,j-1,i,j+1);
	}
    }
  
  /*on traite les condition de bords ici on suppose un torre*/
  /*4 corners*/
  if( (state[0][0] == S) ) InfectionMut(0,0,DIM-1,0,1,0,0,DIM-1,0,1);
  if( (state[0][DIM-1] == S) ) InfectionMut(0,DIM-1,DIM-1,DIM-1,1,DIM-1,0,DIM-2,0,0);
  if( (state[DIM-1][0] == S) ) InfectionMut(DIM-1,0,DIM-2,0,0,0,0,DIM-1,0,1);
  if( (state[DIM-1][DIM-1] == S) ) InfectionMut(DIM-1,DIM-1,DIM-2,DIM-1,0,DIM-1,DIM-1,DIM-2,DIM-1,0);

  /*ligne haut*/
  for(j=1;j<(DIM-1);j++)
    {
      if( (state[0][j] == S) ) InfectionMut(0,j,DIM-1,j,1,j,0,j-1,0,j+1);
    }

  /*ligne bas*/
  for(j=1;j<(DIM-1);j++)
    {
      if( (state[DIM-1][j] == S) ) InfectionMut(DIM-1,j,DIM-2,j,0,j,DIM-1,j-1,DIM-1,j+1);
    }
  
  /*colonne gauche*/
  for(i=1;i<(DIM-1);i++)
    {
      if( (state[i][0] == S) ) InfectionMut(i,0,i-1,0,i+1,0,i,DIM-1,i,1);
    }

  /*colonne droite*/
  for(i=1;i<(DIM-1);i++)
    {
      if( (state[i][DIM-1] == S) ) InfectionMut(i,DIM-1,i-1,DIM-1,i+1,DIM-1,i,DIM-2,i,0);
    }

}

void InfectionMut(int x, int y, int xt, int yt, int xb, int yb, int xl, int yl, int xr, int yr)
{
  /*la cellule, celle en haut t, en bas b, a gauche l, a droite r*/
  int cnt=0;
  int cntmut=0;
  
  if(state[xt][yt]==I) cnt=1;
  if(state[xb][yb]==I) cnt +=1;
  if(state[xl][yl]==I) cnt +=1;
  if(state[xr][yr]==I) cnt +=1;

  if(state[xt][yt]==IMUT) cntmut=1;
  if(state[xb][yb]==IMUT) cntmut +=1;
  if(state[xl][yl]==IMUT) cntmut +=1;
  if(state[xr][yr]==IMUT) cntmut +=1;


  /* la proba de devenir infecté (peut importe par qui vaut :
     1.0-exp( -( ((double) cnt)*par_b + ((double) cntmut)*par_B ) *DELTA_T) */ 

  /*ensuite, sachant que l'on est infecté on peut etre soit :
    -infecté par le resident
        ou
    -infécté par le mutant
    on calcul ca par le ratio : ( ((double) cnt)*par_b / ( ((double) cnt)*par_b + ((double) cntmut)*par_B ) )*/

if(cnt >0 || cntmut>0)
  {
    double ran=drand48();
    
    if(ran < ( (1.0-exp( -( ((double) cnt)*par_b + ((double) cntmut)*par_B ) *DELTA_T))* ( ((double) cnt)*par_b / ( ((double) cnt)*par_b + ((double) cntmut)*par_B ) )  ) )
      {
	state[x][y]=E;
	timer[x][y]=TIME_E;
      }
    else
      {
	if(ran < (1.0-exp( -( ((double) cnt)*par_b + ((double) cntmut)*par_B ) *DELTA_T) ) ) /*la
	  somme des deux ratio vaut 1 donc il reste que la proba
	  d'être infecté quand on cumule*/
	  {
	    state[x][y]=EMUT;
	    timer[x][y]=TIME_EMUT;
	  }
      }
   }

}

void ChangeStatesMut(GtkWidget *widget)
{
  int i,j;
  
  for(i=0;i<DIM;i++)
    {
      for(j=0;j<DIM;j++)
	{  
	  switch(state[i][j])
	    {
	    case E:
	      state[i][j]=I;
	      timer[i][j]=par_v;
	      draw_I(widget,i,j);
	      break;

	    case EMUT:
	      state[i][j]=IMUT;
	      timer[i][j]=par_V;
	      draw_Imut(widget,i,j);
	      break;

	    case I:
	      timer[i][j]--;
	      if(timer[i][j]==0)
		{
		  state[i][j]=R;
		  timer[i][j]=TIME_R;
		  draw_R(widget,i,j);
		}
	      break;

	    case IMUT:
	      timer[i][j]--;
	      if(timer[i][j]==0)
		{
		  state[i][j]=R;
		  timer[i][j]=TIME_R;
		  draw_R(widget,i,j);
		}
	      break;

	    case R:
	      timer[i][j]--;
	      if(timer[i][j]==0)
		{
		  state[i][j]=S;
		  draw_S(widget,i,j);
		}
	      break;

	    }
	}
    }
}
