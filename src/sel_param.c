#include "evolvir.h"

void select_param (void)
{
  GtkWidget *window,  *vbox, *hbox, *valider, *button;
  GtkWidget *frame_b, *frame_v;
  //GtkWidget  *scale_param; variable globale
   
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "paramètres");
  gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);
  gtk_widget_set_size_request (window, 400, 300);
  g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (gtk_widget_destroy), NULL);

  /* Create a scale that scrolls integers and one that scrolls floating point. */
  scale_param[0] = gtk_hscale_new_with_range (1.0, 10.0, 0.1);
  scale_param[1] = gtk_hscale_new_with_range (0.0, 100.0, 1.0);
  /* Set the number of decimal places to display for each widget. */
  gtk_scale_set_digits (GTK_SCALE (scale_param[0]), 1);
  gtk_scale_set_digits (GTK_SCALE (scale_param[1]), 0);
  /* Set the position of the value with respect to the widget. */
  gtk_scale_set_value_pos (GTK_SCALE (scale_param[0]), GTK_POS_RIGHT);
  gtk_scale_set_value_pos (GTK_SCALE (scale_param[1]), GTK_POS_RIGHT);

  /*agencement*/
  vbox = gtk_vbox_new (TRUE, 0);
  gtk_container_add (GTK_CONTAINER (window), vbox);

  frame_b = gtk_frame_new("b : transmission");
  gtk_container_add(GTK_CONTAINER(frame_b), scale_param[0]);
  gtk_box_pack_start(GTK_BOX(vbox), frame_b, FALSE, FALSE, 0);

  frame_v = gtk_frame_new("v : virulence (temps avant mort)");
  gtk_container_add(GTK_CONTAINER(frame_v), scale_param[1]);
  gtk_box_pack_start(GTK_BOX(vbox), frame_v, FALSE, FALSE, 0);

  /*on rajoute bouttons valider et default*/
  hbox = gtk_hbox_new (TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

  button = gtk_button_new_with_label ("Default");
  gtk_box_pack_start (GTK_BOX (hbox), button, TRUE, TRUE, 0);

  valider = gtk_button_new_from_stock(GTK_STOCK_OK);
  gtk_box_pack_start(GTK_BOX (hbox), valider, TRUE, TRUE, 0);

  /*connection des signaux*/
  g_signal_connect(G_OBJECT(scale_param[0]), "value-changed", G_CALLBACK(OnValueChange_select_param), frame_b);
  g_signal_connect(G_OBJECT(scale_param[1]), "value-changed", G_CALLBACK(OnValueChange_select_param), frame_v);
  g_signal_connect(G_OBJECT(valider), "clicked", G_CALLBACK(OnValidate_select_param), window);
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(OnDefault_select_param), NULL);

  gtk_widget_show_all (window);
}


void select_param_mut (void)
{
  GtkWidget *window,  *hbox, *valider, *button;
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
  scale_param[0] = gtk_hscale_new_with_range (1.0, 10.0, 0.1);
  scale_param[1] = gtk_hscale_new_with_range (0.0, 200.0, 1.0);
  scale_param[2] = gtk_hscale_new_with_range (1.0, 10.0, 0.1);
  scale_param[3] = gtk_hscale_new_with_range (0.0, 200.0, 1.0);
  /* Set the number of decimal places to display for each widget. */
  gtk_scale_set_digits (GTK_SCALE (scale_param[0]), 1);
  gtk_scale_set_digits (GTK_SCALE (scale_param[1]), 0);
  gtk_scale_set_digits (GTK_SCALE (scale_param[2]), 1);
  gtk_scale_set_digits (GTK_SCALE (scale_param[3]), 0);
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
  frame_V = gtk_frame_new("V : virulence (temps avant mort)");
  gtk_container_add(GTK_CONTAINER(frame_V), scale_param[3]);
  gtk_box_pack_start(GTK_BOX(vbox[2]), frame_V, FALSE, FALSE, 0);


  /*on rajoute bouttons valider et default*/
  hbox = gtk_hbox_new (TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vbox[0]), hbox, FALSE, FALSE, 0);

  button = gtk_button_new_with_label ("Default");
  gtk_box_pack_start (GTK_BOX (hbox), button, TRUE, TRUE, 0);

  valider = gtk_button_new_from_stock(GTK_STOCK_OK);
  gtk_box_pack_start(GTK_BOX (hbox), valider, TRUE, TRUE, 0);

  /*connection des signaux*/
  g_signal_connect(G_OBJECT(scale_param[0]), "value-changed", G_CALLBACK(OnValueChange_select_param), frame_b);
  g_signal_connect(G_OBJECT(scale_param[1]), "value-changed", G_CALLBACK(OnValueChange_select_param), frame_v);
  g_signal_connect(G_OBJECT(scale_param[2]), "value-changed", G_CALLBACK(OnValueChange_select_param), frame_B);
  g_signal_connect(G_OBJECT(scale_param[3]), "value-changed", G_CALLBACK(OnValueChange_select_param), frame_V);
  g_signal_connect(G_OBJECT(valider), "clicked", G_CALLBACK(OnValidate_select_param), window);
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(OnDefault_select_param), NULL);
  
  gtk_widget_show_all (window);

}




void OnValueChange_select_param(GtkWidget *pWidget, gpointer data)
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
      break;
    case 'v' :
      par_v = iValue;
      printf("v %g\n",par_v);
      break;
    case 'B' :
      par_B = iValue;
      printf("B %g\n",par_B);
      break;
    case 'V' :
      par_V = iValue;
      printf("V %g\n",par_V);
      break;
    }
}


void OnValidate_select_param(GtkWidget *widget, gpointer data)
{
    setlocale(LC_ALL, "C");

   anim_infection();
   
   gtk_widget_destroy(GTK_WIDGET(data));
   
}


void OnDefault_select_param(GtkWidget *widget, gpointer data)
{
   setlocale(LC_ALL, "C");
      switch(flag1)
	{
	case 1:
	  par_b=TRANSMISSION;
	  par_v=TIME_I;
	  gtk_range_set_value(GTK_RANGE(scale_param[0]), TRANSMISSION);
	  gtk_range_set_value(GTK_RANGE(scale_param[1]), TIME_I);
	  break;
	case 2:
	  par_b=TRANSMISSION;
	  par_v=TIME_I;
	  gtk_range_set_value(GTK_RANGE(scale_param[0]), TRANSMISSION);
	  gtk_range_set_value(GTK_RANGE(scale_param[1]), TIME_I);
	  break;
	case 3:
	  par_b=TRANSMISSION;
	  par_v=TIME_I;
	  par_B=TRANSMISSION_MUT;
	  par_V=TIME_IMUT;
	  gtk_range_set_value(GTK_RANGE(scale_param[0]), TRANSMISSION);
	  gtk_range_set_value(GTK_RANGE(scale_param[1]), TIME_I);
	  gtk_range_set_value(GTK_RANGE(scale_param[2]), TRANSMISSION_MUT);
	  gtk_range_set_value(GTK_RANGE(scale_param[3]), TIME_IMUT);
	  break;
	case 4:
	  par_b=TRANSMISSION;
	  par_v=TIME_I;
	  par_B=TRANSMISSION_MUT;
	  par_V=TIME_IMUT;
	  gtk_range_set_value(GTK_RANGE(scale_param[0]), TRANSMISSION);
	  gtk_range_set_value(GTK_RANGE(scale_param[1]), TIME_I);
	  gtk_range_set_value(GTK_RANGE(scale_param[2]), TRANSMISSION_MUT);
	  gtk_range_set_value(GTK_RANGE(scale_param[3]), TIME_IMUT);
	  break;
	case 5:
	  par_b=TRANSMISSION;
	  par_v=TIME_I;
	  par_B=TRANSMISSION_MUT;
	  par_V=TIME_IMUT;
	  gtk_range_set_value(GTK_RANGE(scale_param[0]), TRANSMISSION);
	  gtk_range_set_value(GTK_RANGE(scale_param[1]), TIME_I);
	  gtk_range_set_value(GTK_RANGE(scale_param[2]), TRANSMISSION_MUT);
	  gtk_range_set_value(GTK_RANGE(scale_param[3]), TIME_IMUT);
	  break;
	}
   

}
