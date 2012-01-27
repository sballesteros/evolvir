#include "evolvir.h"

/*fenetre de selection type de modele*/

void selecao(void)
{
  GtkWidget *pWindow_selecao;
  GtkWidget *pVBox_selecao;
  GtkWidget *pRadio1_selecao;
  GtkWidget *pRadio2_selecao;
  GtkWidget *pRadio3_selecao;
  GtkWidget *pRadio4_selecao;
  GtkWidget *pRadio5_selecao;
  GtkWidget *pValider_selecao;
  GtkWidget *pLabel_selecao;
    
  pWindow_selecao = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(pWindow_selecao),GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(pWindow_selecao), "selection du modele");
  gtk_window_set_default_size(GTK_WINDOW(pWindow_selecao), 320, 200);

  pVBox_selecao = gtk_vbox_new(TRUE, 0);
  gtk_container_add(GTK_CONTAINER(pWindow_selecao),pVBox_selecao);

  pLabel_selecao = gtk_label_new("Votre choix :");
  gtk_box_pack_start(GTK_BOX(pVBox_selecao), pLabel_selecao, FALSE, FALSE, 0);

  /* Creation du premier bouton radio */
  pRadio1_selecao = gtk_radio_button_new_with_label(NULL, "1-une souche, contacts locaux");
  gtk_box_pack_start(GTK_BOX (pVBox_selecao), pRadio1_selecao, FALSE, FALSE, 0);
  /* Ajout du deuxieme */
  pRadio2_selecao = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON (pRadio1_selecao), "2-une souche, contacts globaux");
  gtk_box_pack_start(GTK_BOX (pVBox_selecao), pRadio2_selecao, FALSE, FALSE, 0);
  /* Ajout du troisieme */
  pRadio3_selecao = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON (pRadio1_selecao), "3-évolution : contacts locaux");
  gtk_box_pack_start(GTK_BOX (pVBox_selecao), pRadio3_selecao, FALSE, FALSE, 0);
  /* Ajout du quatrieme */
  pRadio4_selecao = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON (pRadio1_selecao), "4-évolution : contacts globaux");
  gtk_box_pack_start(GTK_BOX (pVBox_selecao), pRadio4_selecao, FALSE, FALSE, 0);
  /* Ajout du cinquieme */
  pRadio5_selecao = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON (pRadio1_selecao), "5-évolution : compromis evolutif");
  gtk_box_pack_start(GTK_BOX (pVBox_selecao), pRadio5_selecao, FALSE, FALSE, 0);

  /* Ajout du bouton de validation */
  pValider_selecao = gtk_button_new_from_stock(GTK_STOCK_OK);
  gtk_box_pack_start(GTK_BOX (pVBox_selecao), pValider_selecao, FALSE, FALSE, 0);

  /* Connexion des signaux */
  g_signal_connect(G_OBJECT(pWindow_selecao), "destroy", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(G_OBJECT(pValider_selecao), "clicked", G_CALLBACK(OnValider), pRadio1_selecao);

  gtk_widget_show_all(pWindow_selecao);
}


/*quand l'utilisateur valide le choix du modele*/

void OnValider(GtkWidget *pBtn, gpointer data)
{
  setlocale(LC_ALL, "C");
  GSList *pList;

  const gchar *sLabel=NULL;

  /* Recuperation de la liste des boutons */
  pList = gtk_radio_button_get_group(GTK_RADIO_BUTTON(data));

  /* Parcours de la liste */
  while(pList)
    {
      /* Le bouton est il selectionne */
      if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pList->data)))
        {
	  /* OUI -> on copie le label du bouton */
	  sLabel = gtk_button_get_label(GTK_BUTTON(pList->data));
	  /* On met la liste a NULL pour sortir de la boucle */
	  pList = NULL;
        }
      else
        {
	  /* NON -> on passe au bouton suivant */
	  pList = g_slist_next(pList);
        }
    }

  
  flag1=atoi(sLabel); /*on recupere 1,2,3 ou 4*/

  if(flag1==1) select_param();
  if(flag1==2) select_param();
  if(flag1==3) select_param_mut();
  if(flag1==4) select_param_mut();
  if(flag1==5) select_param_mut_tradeoff();       
}


