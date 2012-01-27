#include "evolvir.h"

void countI_gm(int *cntI, int *cntImut)
{
  int i,j;
  for(i=0;i<DIM;i++)
    {
      for(j=0;j<DIM;j++)
	{
	  if( (state[i][j]== I) ) *cntI +=1;
	  if( (state[i][j]== IMUT) ) *cntImut +=1;
	}
    }
}

void SpreadDisease_gm(void)
{
  int i,j;
  int cntI=0;
  int cntImut=0;

  countI_gm(&cntI,&cntImut);
  
  for(i=0;i<DIM;i++)
    {
      for(j=0;j<DIM;j++)
	{
	  if( (state[i][j]== S) ) infection_gm(i,j,cntI,cntImut);
	}
    }
} 


void SpreadDiseaseMut_gm(void)
{
  int i,j;
  int cntI=0;
  int cntImut=0;

  countI_gm(&cntI,&cntImut);
  
  for(i=0;i<DIM;i++)
    {
      for(j=0;j<DIM;j++)
	{
	  if( (state[i][j]== S) ) InfectionMut_gm(i,j,cntI,cntImut);
	}
    }
} 


void infection_gm(int x, int y, int cntI, int cntImut)
{
  if(cntI)
    {
      if(drand48() < (1.0-exp(-((double) cntI)*par_b* (((double)PIXEL)/(((double) DIM) * ((double) DIM))) *DELTA_T)) )
	{
	  state[x][y]=E;
	  timer[x][y]=TIME_E;
	}
    }
}

void InfectionMut_gm(int x, int y, int cntI, int cntImut)
{


  /* la proba de devenir infecté (peut importe par qui vaut :
     1.0-exp( -( ((double) cnt)*par_b + ((double) cntmut)*par_B ) *DELTA_T) */ 

  /*ensuite, sachant que l'on est infecté on peut etre soit :
    -infecté par le resident
        ou
    -infécté par le mutant
    on calcul ca par le ratio : ( ((double) cnt)*par_b / ( ((double) cnt)*par_b + ((double) cntmut)*par_B ) )*/

  /*on normalise pour compenser global mixing
    ( 4.0/(pow((double) DIM,2)) )*/

  if(cntI >0 || cntImut>0)
    {
      double ran=drand48();
      
      if(ran < ( (1.0-exp( -( ((double) cntI)*par_b*( 4.0/(pow((double) DIM,2)) ) + ((double) cntImut)*par_B*( 4.0/(pow((double) DIM,2)) ) ) *DELTA_T))* ( ((double) cntI)*par_b*( 4.0/(pow((double) DIM,2)) ) / ( ((double) cntI)*par_b*( 4.0/(pow((double) DIM,2)) ) + ((double) cntImut)*par_B*( 4.0/(pow((double) DIM,2)) ) ) )  ) )
	{
	  state[x][y]=E;
	  timer[x][y]=TIME_E;
	}
      else
	{
	  if(ran < (1.0-exp( -( ((double) cntI)*par_b*( 4.0/(pow((double) DIM,2)) ) + ((double) cntImut)*par_B*( 4.0/(pow((double) DIM,2)) ) ) *DELTA_T) ) ) 
/*la somme des deux ratio vaut 1 donc il resteque la proba d'être infecté quand on cumule*/
	    {
	      state[x][y]=EMUT;
	      timer[x][y]=TIME_EMUT;
	    }
	}
    }
  

}


/*pour ChangeStates , utiliser
  void ChangeStates(GtkWidget *widget) ou,
  void ChangeStatesMut(GtkWidget *widget) dans localmixing.c */
