#include "evolvir.h"

void select_param_mut_tradeoff (void)
{
  setlocale(LC_ALL, "C");

  GtkWidget *window,  *hbox, *valider, *button, *graph;
  GtkWidget  *frame_res, *frame_mut, *frame_b, *frame_v, *frame_B, *frame_V;
  GtkWidget *vbox[3];
  
  //GtkWidget  *scale_param; variable globale
   
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "paramètres");
  gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);
  gtk_widget_set_size_request (window, 400, 300);
  g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (gtk_widget_destroy), NULL);

  /* Create a scale that scrolls integers and one that scrolls floating point. */
  scale_param[0] = gtk_hscale_new_with_range (0.0, B_MAX, 0.01);
  scale_param[1] = gtk_hscale_new_with_range (0.0, 200.0, 0.01);
  scale_param[2] = gtk_hscale_new_with_range (0.0, B_MAX, 0.01);
  scale_param[3] = gtk_hscale_new_with_range (0.0, 200.0, 0.01);
  /* Set the number of decimal places to display for each widget. */
  gtk_scale_set_digits (GTK_SCALE (scale_param[0]), 2);
  gtk_scale_set_digits (GTK_SCALE (scale_param[1]), 2);
  gtk_scale_set_digits (GTK_SCALE (scale_param[2]), 2);
  gtk_scale_set_digits (GTK_SCALE (scale_param[3]), 2);
  /* Set the position of the value with respect to the widget. */
  gtk_scale_set_value_pos (GTK_SCALE (scale_param[0]), GTK_POS_RIGHT);
  gtk_scale_set_value_pos (GTK_SCALE (scale_param[1]), GTK_POS_RIGHT);
  gtk_scale_set_value_pos (GTK_SCALE (scale_param[2]), GTK_POS_RIGHT);
  gtk_scale_set_value_pos (GTK_SCALE (scale_param[3]), GTK_POS_RIGHT);

  /*agencement*/

  vbox[0] = gtk_vbox_new (TRUE, 0);
  gtk_container_add (GTK_CONTAINER (window), vbox[0]);

  frame_res = gtk_frame_new("Resident");
  vbox[1] = gtk_vbox_new (TRUE, 0);
  gtk_container_add(GTK_CONTAINER(frame_res), vbox[1]);
  gtk_box_pack_start(GTK_BOX(vbox[0]), frame_res, FALSE, FALSE, 0);

  frame_b = gtk_frame_new("b : transmission");
  gtk_container_add(GTK_CONTAINER(frame_b), scale_param[0]);
  gtk_box_pack_start(GTK_BOX(vbox[1]), frame_b, FALSE, FALSE, 0);
  frame_v = gtk_frame_new("v : virulence (temps avant mort)");
  gtk_container_add(GTK_CONTAINER(frame_v), scale_param[1]);
  gtk_box_pack_start(GTK_BOX(vbox[1]), frame_v, FALSE, FALSE, 0);


  frame_mut = gtk_frame_new("Mutant");
  vbox[2] = gtk_vbox_new (TRUE, 0);
  gtk_container_add(GTK_CONTAINER(frame_mut), vbox[2]);
  gtk_box_pack_start(GTK_BOX(vbox[0]), frame_mut, FALSE, FALSE, 0);

  frame_B = gtk_frame_new("B : transmission");
  gtk_container_add(GTK_CONTAINER(frame_B), scale_param[2]);
  gtk_box_pack_start(GTK_BOX(vbox[2]), frame_B, FALSE, FALSE, 0);
  frame_V = gtk_frame_new("V : virulence");
  gtk_container_add(GTK_CONTAINER(frame_V), scale_param[3]);
  gtk_box_pack_start(GTK_BOX(vbox[2]), frame_V, FALSE, FALSE, 0);


  /*on rajoute bouttons valider, graph et default*/
  hbox = gtk_hbox_new (TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vbox[0]), hbox, FALSE, FALSE, 0);

  button = gtk_button_new_with_label ("Default");
  gtk_box_pack_start (GTK_BOX (hbox), button, TRUE, TRUE, 0);

  graph = gtk_button_new_with_label ("Graph");
  gtk_box_pack_start (GTK_BOX (hbox), graph, TRUE, TRUE, 0);

  valider = gtk_button_new_from_stock(GTK_STOCK_OK);
  gtk_box_pack_start(GTK_BOX (hbox), valider, TRUE, TRUE, 0);

  /*connection des signaux*/
  g_signal_connect(G_OBJECT(scale_param[0]), "value-changed", G_CALLBACK(OnValueChange_select_param_tradeoff), frame_b);
  g_signal_connect(G_OBJECT(scale_param[1]), "value-changed", G_CALLBACK(OnValueChange_select_param_tradeoff), frame_v);
  g_signal_connect(G_OBJECT(scale_param[2]), "value-changed", G_CALLBACK(OnValueChange_select_param_tradeoff), frame_B);
  g_signal_connect(G_OBJECT(scale_param[3]), "value-changed", G_CALLBACK(OnValueChange_select_param_tradeoff), frame_V);
  g_signal_connect(G_OBJECT(valider), "clicked", G_CALLBACK(OnValidate_select_param), window);
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(OnDefault_select_param), NULL);
  g_signal_connect(G_OBJECT(graph), "clicked", G_CALLBACK(OnGraph_select_param), NULL);
  
  gtk_widget_show_all (window);

  /*on met la virulence a sa valeur minimal*/
  gtk_range_set_value(GTK_RANGE(scale_param[1]), 20.0);
  gtk_range_set_value(GTK_RANGE(scale_param[3]), 20.0);
}


/*quand on clique sur graph une image apparait montrant la forme du trade-off transmission virulence*/
void OnGraph_select_param(GtkWidget *Widget, gpointer data)
{
  GtkWidget *pWindow;
  GtkWidget *pVBox;
  GtkWidget *pImage;
  GtkWidget *pQuitBtn;
  
  pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 200);
  gtk_window_set_title(GTK_WINDOW(pWindow), "le compromis...");
  g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_widget_destroy), NULL);

  pVBox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(pWindow), pVBox);
  
  /* Chargement d'une image a partir d'un fichier */
  pImage = gtk_image_new_from_file("graph/tradeoff.png");
  gtk_box_pack_start(GTK_BOX(pVBox), pImage, TRUE, FALSE, 5);
  
  pQuitBtn = gtk_button_new_from_stock(GTK_STOCK_OK);
  gtk_box_pack_start(GTK_BOX(pVBox), pQuitBtn, TRUE, FALSE, 0);
  g_signal_connect_swapped(G_OBJECT(pQuitBtn), "clicked", G_CALLBACK(gtk_widget_destroy), (gpointer) pWindow);

  gtk_widget_show_all(pWindow);
  
}


void OnValueChange_select_param_tradeoff(GtkWidget *pWidget, gpointer data)
{
  setlocale(LC_ALL, "C");

  /* Recuperation de la valeur de la scrollbar */
  //iValue = gtk_range_get_value(GTK_RANGE(pWidget));
  gdouble iValue;
  gchar id;

  id = gtk_frame_get_label(GTK_FRAME(data))[0];

  /* Recuperation de la valeur de la scrollbar */
  iValue = gtk_range_get_value(GTK_RANGE(pWidget));
   
  /*on actualise la variable globale par_ modifie*/
  switch(id) 
    {
    case 'b' :
      par_b = iValue;
      printf("b %g\n",par_b);
      par_v= (gint) (200.0-par_b*INFLECTION/(B_MAX-par_b));
      gtk_range_set_value(GTK_RANGE(scale_param[1]), (200.0-par_b*INFLECTION/(B_MAX-par_b)));
      break;
    case 'v' :
      par_v = (gint) iValue;
      printf("v %g\n",par_v);
      par_b=B_MAX*((gdouble) (200.0-((gdouble) par_v)))/(INFLECTION+((gdouble) (200.0-((gdouble) par_v))));
      gtk_range_set_value(GTK_RANGE(scale_param[0]), par_b);
      break;
    case 'B' :
      par_B = iValue;
      printf("B %g\n",par_B);
      par_V=(gint) (200.0-par_B*INFLECTION/(B_MAX-par_B));
      gtk_range_set_value(GTK_RANGE(scale_param[3]), (200.0-par_B*INFLECTION/(B_MAX-par_B)));
      break;
    case 'V' :
      par_V = (gint) iValue;
      printf("V %g\n",par_V);
      par_B=B_MAX*((gdouble) (200.0-((gdouble) par_V)))/(INFLECTION+((gdouble) (200.0-((gdouble) par_V))));
      gtk_range_set_value(GTK_RANGE(scale_param[2]),par_B);
      break;
    }
}

