/*fenetre de welcome (_welcome) avec about et quit*/
#include "evolvir.h"


void welcome(void)
{
  setlocale(LC_ALL, "C");
  
  GtkWidget *pWindow_welcome;
  GtkWidget *pVBox_welcome;
  GtkWidget *pImage_welcome;
  GtkWidget *pQuitterBtn_welcome;
  GtkWidget *pAboutBtn_welcome;
  GtkWidget *pOptionsBtn_welcome;
    
  pWindow_welcome = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_move(GTK_WINDOW(pWindow_welcome),0,0);
  gtk_window_set_title(GTK_WINDOW(pWindow_welcome), "Evolvir");
  gtk_window_set_default_size(GTK_WINDOW(pWindow_welcome), 200, 100);
  g_signal_connect(G_OBJECT(pWindow_welcome), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  pVBox_welcome = gtk_vbox_new(FALSE,0);
  gtk_container_add(GTK_CONTAINER(pWindow_welcome),pVBox_welcome);

  pImage_welcome = gtk_image_new_from_file("graph/vih2.png");
  // pImage_welcome = gtk_image_new_from_file("graph/mnhn.gif");
  //	pImage_welcome = gtk_image_new_from_file("vih.png");
    
  gtk_box_pack_start(GTK_BOX(pVBox_welcome), pImage_welcome, TRUE, TRUE,0);

  pAboutBtn_welcome = gtk_button_new_from_stock (GTK_STOCK_INFO);
  gtk_box_pack_start(GTK_BOX(pVBox_welcome), pAboutBtn_welcome, TRUE, TRUE,0);
  g_signal_connect(G_OBJECT(pAboutBtn_welcome), "clicked", G_CALLBACK(OnAboutBtn), (GtkWidget*) pWindow_welcome);

  pOptionsBtn_welcome = gtk_button_new_from_stock (GTK_STOCK_PREFERENCES);
  gtk_box_pack_start(GTK_BOX(pVBox_welcome), pOptionsBtn_welcome, TRUE, TRUE, 0);
  g_signal_connect(G_OBJECT(pOptionsBtn_welcome), "clicked", G_CALLBACK(OnOptionsBtn), (GtkWidget*) pWindow_welcome);

  pQuitterBtn_welcome = gtk_button_new_from_stock (GTK_STOCK_QUIT);
  gtk_box_pack_start(GTK_BOX(pVBox_welcome), pQuitterBtn_welcome, TRUE, TRUE, 0);
  g_signal_connect(G_OBJECT(pQuitterBtn_welcome), "clicked", G_CALLBACK(OnQuitBtn), (GtkWidget*) pWindow_welcome);

  gtk_widget_show_all(pWindow_welcome);
}


void OnAboutBtn(GtkWidget *pBtn, gpointer data)
{
  GtkWidget *pWindow;
  GtkWidget *pVBox;
  GtkWidget *pNotebook;
  GtkWidget *pImage;
    
  GtkWidget *pTextView;
  GtkWidget *pScrolled;
	
  pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(pWindow), "A propos...");
  gtk_window_set_default_size(GTK_WINDOW(pWindow), 420, 300);
  gtk_window_set_position(GTK_WINDOW(pWindow),GTK_WIN_POS_CENTER);
  g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(delete_event), NULL);

  pVBox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(pWindow), pVBox);


  pImage = gtk_image_new_from_file("graph/logo_mnhn.jpg");
  gtk_box_pack_start(GTK_BOX(pVBox), pImage, FALSE, FALSE ,0);

  /* Creation du GtkNotebook */
  pNotebook = gtk_notebook_new();
  gtk_box_pack_start(GTK_BOX(pVBox), pNotebook, TRUE, TRUE, 0);
  /* Position des onglets : en bas */
  gtk_notebook_set_tab_pos(GTK_NOTEBOOK(pNotebook), GTK_POS_BOTTOM);
  /* Ajout des boutons de navigation */
  gtk_notebook_set_scrollable(GTK_NOTEBOOK(pNotebook), TRUE);

  /*creation de l'onglet à propos*/

  GtkWidget *pLabel;
  GtkWidget *pTabLabel;
  gchar *sLabel;
  gchar *sTabLabel;
  gchar *sTitre = "Evolution de la virulence";
    
  sLabel = g_strdup_printf("Les RDV de la Science : des ateliers pour les scolaires… par des chercheurs\n\n\n\n%s",
			   sTitre);
  sTabLabel = g_strdup_printf("à propos");

  /* Creation des differents GtkLabel */
  pLabel = gtk_label_new(sLabel);
  pTabLabel = gtk_label_new(sTabLabel);

  /* Insertion de la page */
  gtk_notebook_append_page(GTK_NOTEBOOK(pNotebook), pLabel, pTabLabel);

  g_free(sLabel);
  g_free(sTabLabel);
    
    

  /*creation de l'onglet objectif*/
  GtkWidget *pImage_objectif;
  pImage_objectif = gtk_image_new_from_file("graph/entete_mnhn.jpg");   
 	
  GtkWidget *pTabLabel1;
  gchar *sTabLabel1;
  sTabLabel1 = g_strdup_printf("objectif");
  pTabLabel1 = gtk_label_new(sTabLabel1);

  /* Insertion de la page */
  gtk_notebook_append_page(GTK_NOTEBOOK(pNotebook), pImage_objectif, pTabLabel1);

  g_free(sTabLabel1);




  /*creation de l'onglet auteurs*/

  GtkWidget *pLabel2;
  GtkWidget *pTabLabel2;
  gchar *sLabel2;
  gchar *sTabLabel2;

  sLabel2 = g_strdup_printf("Sébastien Ballesteros\nsebastien.ballesteros@biologie.ens.fr");
  sTabLabel2 = g_strdup_printf("auteur");

  /* Creation des differents GtkLabel */
  pLabel2 = gtk_label_new(sLabel2);
  pTabLabel2 = gtk_label_new(sTabLabel2);

  /* Insertion de la page */
  gtk_notebook_append_page(GTK_NOTEBOOK(pNotebook), pLabel2, pTabLabel2);

  g_free(sLabel2);
  g_free(sTabLabel2);

  /*creation de l'onglet licence*/

  GtkWidget *pTabLabel3;
  gchar *sTabLabel3;

  sTabLabel3 = g_strdup_printf("licence");
  pTabLabel3 = gtk_label_new(sTabLabel3);


  pScrolled = gtk_scrolled_window_new(NULL, NULL);

  pTextView=gtk_text_view_new();
  gtk_container_add(GTK_CONTAINER(pScrolled), pTextView);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(pScrolled), 
				 GTK_POLICY_AUTOMATIC, 
				 GTK_POLICY_AUTOMATIC);


  GtkTextBuffer *pTextBuffer;
  GtkTextIter iStart, iEnd;
  gchar *sBuffer;

  g_file_get_contents("graph/licence.txt", &sBuffer, NULL, NULL);


  /* Recuperation du buffer */
  pTextBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(pTextView));
  /* Suppression des données du buffer */
  gtk_text_buffer_get_start_iter(pTextBuffer, &iStart);
  gtk_text_buffer_get_end_iter(pTextBuffer, &iEnd);
  gtk_text_buffer_delete(pTextBuffer, &iStart, &iEnd);
  /* Affichage du fichier */
  gtk_text_buffer_get_start_iter(pTextBuffer, &iStart);
  gtk_text_buffer_insert(pTextBuffer, &iStart, sBuffer, -1);
  g_free(sBuffer);


  gtk_notebook_append_page(GTK_NOTEBOOK(pNotebook), pScrolled, pTabLabel3);
  g_free(sTabLabel3);

  gtk_widget_show_all(pWindow);
}

void OnQuitBtn(GtkWidget* widget, gpointer data)
{
  GtkWidget *pQuestion;

  /* Creation de la boite de message */
  /* Type : Question -> GTK_MESSAGE_QUESTION */
  /* Boutons : 1 OUI, 1 NON -> GTK_BUTTONS_YES_NO */
  pQuestion = gtk_message_dialog_new (GTK_WINDOW(data),
				      GTK_DIALOG_MODAL,
				      GTK_MESSAGE_QUESTION,
				      GTK_BUTTONS_YES_NO,
				      "Voulez vous vraiment\nquitter ce programme?");

  /* Affichage et attente d une reponse */
  switch(gtk_dialog_run(GTK_DIALOG(pQuestion)))
    {
    case GTK_RESPONSE_YES:
      /* OUI -> on quitte l application */
      gtk_main_quit();
      break;
    case GTK_RESPONSE_NO:
      /* NON -> on detruit la boite de message */
      gtk_widget_destroy(pQuestion);
      break;
    }
}

void OnOptionsBtn(GtkWidget* widget, gpointer data)
{
  select_speed();
}


gint delete_event(GtkWidget *Widget, GdkEvent *event, gpointer data)
{
return FALSE;
}

/*vitesse de g_timeout_add*/
void select_speed(void)
{
  
  GtkWidget *window,  *vbox, *valider;
  GtkWidget *frame_speed;
  GtkWidget *scale_par; 
  
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "paramètres");
  gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);
  gtk_widget_set_size_request (window, 400, 200);
  g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (gtk_widget_destroy), NULL);
  
  /* Create a scale that scrolls integers and one that scrolls floating point. */
  /*vitesse d'animation	  g_timeout_add
  premier argument interval: the time between calls to the function, in milliseconds (1/1000ths of a second)*/
  scale_par = gtk_hscale_new_with_range (1.0, 1000.0, 1.0);
  /* Set the number of decimal places to display for each widget. */
  gtk_scale_set_digits (GTK_SCALE (scale_par), 0);
  /* Set the position of the value with respect to the widget. */
  gtk_range_set_value(GTK_RANGE(scale_par), gglobal_speed);
  
  /*agencement*/
  vbox = gtk_vbox_new (TRUE, 0);
  gtk_container_add (GTK_CONTAINER (window), vbox);
  
  frame_speed = gtk_frame_new("vitesse de l'animation \ninterval de rafraichissement en millisecondes");
  gtk_container_add(GTK_CONTAINER(frame_speed), scale_par);
  gtk_box_pack_start(GTK_BOX(vbox), frame_speed, FALSE, FALSE, 0);
  
  /*on rajoute bouttons valider*/
  valider = gtk_button_new_from_stock(GTK_STOCK_OK);
  gtk_box_pack_start(GTK_BOX (vbox), valider, FALSE, FALSE, 10);
  
  /*connection des signaux*/
  g_signal_connect(G_OBJECT(scale_par), "value-changed", G_CALLBACK(OnValueChange_speed), frame_speed);
  g_signal_connect(G_OBJECT(valider), "clicked", G_CALLBACK(OnValidate_speed), window);
  
  gtk_widget_show_all (window);
}

void OnValueChange_speed(GtkWidget *pWidget, gpointer data)
{
  setlocale(LC_ALL, "C");
  
  /* Recuperation de la valeur de la scrollbar */
  //iValue = gtk_range_get_value(GTK_RANGE(pWidget));
  gdouble iValue;
  
  /* Recuperation de la valeur de la scrollbar */
  iValue = gtk_range_get_value(GTK_RANGE(pWidget));
  
  /*on actualise la variable globale par_ modifie*/
  gglobal_speed = (guint) iValue;
  printf("speed %d\n",gglobal_speed);
}


void OnValidate_speed(GtkWidget *widget, gpointer data)
{
    gtk_widget_destroy(GTK_WIDGET(data));
}

