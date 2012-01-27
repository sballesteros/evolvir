#include "evolvir.h"

int main( int   argc, 
          char *argv[] )
{

  gtk_init (&argc, &argv);

  /*penser à mettre une seed pour le generateur de nombre aleatoire*/
  gglobal_speed=10; /*vitesse par default*/

  /*fenetre de welcome (_welcome) avec about et quit*/
  welcome();

  selecao();

  gtk_main ();

  return 0;
}
