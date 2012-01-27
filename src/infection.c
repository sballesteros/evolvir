#include "evolvir.h"

void anim_infection(void)
{
  GtkWidget *window;
  GtkWidget *drawing_area;
  GtkWidget *vbox, *hbox;
  GtkWidget *button, *button2;

  int i,j;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (window, "Test Input");
  gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(window), "evolvir");
  
  vbox = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (window), vbox);
  gtk_widget_show (vbox);

  //  g_signal_connect (G_OBJECT (window), "destroy",G_CALLBACK (quit), NULL);
  g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (gtk_widget_destroy), NULL);

  /* Create the drawing area */

  drawing_area = gtk_drawing_area_new ();
  gtk_widget_set_size_request (GTK_WIDGET (drawing_area), DIM*PIXEL, DIM*PIXEL);
  gtk_box_pack_start (GTK_BOX (vbox), drawing_area, TRUE, TRUE, 0);

  gtk_widget_show (drawing_area);

  /* Signals used to handle backing pixmap */

  g_signal_connect (G_OBJECT (drawing_area), "expose_event",
		    G_CALLBACK (expose_event), NULL);
  g_signal_connect (G_OBJECT (drawing_area),"configure_event",
		    G_CALLBACK (configure_event), NULL);

  /* Event signals */

  g_signal_connect (G_OBJECT (drawing_area), "motion_notify_event",
		    G_CALLBACK (motion_notify_event), NULL);
  g_signal_connect (G_OBJECT (drawing_area), "button_press_event",
		    G_CALLBACK (button_press_event), NULL);

  gtk_widget_set_events (drawing_area, GDK_EXPOSURE_MASK
			 | GDK_LEAVE_NOTIFY_MASK
			 | GDK_BUTTON_PRESS_MASK
			 | GDK_POINTER_MOTION_MASK
			 | GDK_POINTER_MOTION_HINT_MASK);

  /* .. And start and stop buttons within a hbox */
  hbox = gtk_hbox_new (TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);
  gtk_widget_show (hbox);

  button = gtk_button_new_with_label ("Start");
  gtk_box_pack_start (GTK_BOX (hbox), button, TRUE, TRUE, 0);
  gtk_widget_show (button);
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(OnStart), drawing_area);

  button2 = gtk_button_new_with_label ("Quit");
  gtk_box_pack_start (GTK_BOX (hbox), button2, TRUE, TRUE, 0);
  gtk_widget_show (button2);

  g_signal_connect_swapped (G_OBJECT (button2), "clicked",
			    G_CALLBACK (gtk_widget_destroy),
			    G_OBJECT (window));


  //  condition_initial();
  for(i=0;i<DIM;i++)
    {
      for(j=0;j<DIM;j++)
	{
	  state[i][j]=S;
	  timer[i][j]=0;
	}
    }

  gtk_widget_show (window);
  information(GTK_WINDOW(window));
  
}

/*fonctions----------------------------------------*/

void information(GtkWindow *parent)
{
  GtkWidget *Info;

  if(flag1==1 || flag1==2)
    {
      Info=gtk_message_dialog_new(parent,
				  GTK_DIALOG_MODAL,
				  GTK_MESSAGE_INFO,
				  GTK_BUTTONS_OK,
				  "Cliquez pour placer les individus\n infectieux (rouge) sur la grille\n puis appuyez sur start pour demmarer");
    }
  else
    {
      Info=gtk_message_dialog_new(parent,
				  GTK_DIALOG_MODAL,
				  GTK_MESSAGE_INFO,
				  GTK_BUTTONS_OK,
				  "Un click gauche pour placer les individus infectieux (rouge)\n et un click droit pour placer les mutants (vert)");      
    }
  
  gtk_dialog_run(GTK_DIALOG(Info));
  gtk_widget_destroy(Info);
}




/*callback start et stop*/
void OnStart(GtkWidget *button, gpointer data)
{
  /*compare 2 chaines de characteres*/
  if(strcmp(gtk_button_get_label(GTK_BUTTON(button)),"Start")==0)
    {
      global_stop=TRUE;

      switch(flag1)
	{
	case 1:
	  g_timeout_add(gglobal_speed, (GSourceFunc) time_handler, (gpointer) data);
	  /*premier argument interval: the time between calls to the function, in milliseconds (1/1000ths of a second) */
	  break;
	case 2:
	  g_timeout_add(gglobal_speed, (GSourceFunc) time_handler_gm, (gpointer) data);	  
	  break;
	case 3:
	  g_timeout_add(gglobal_speed, (GSourceFunc) time_handler_mut, (gpointer) data);	  
	  break;
	case 4:
	  g_timeout_add(gglobal_speed, (GSourceFunc) time_handler_mut_gm, (gpointer) data);	  
	  break;
	case 5:
	  g_timeout_add(gglobal_speed, (GSourceFunc) time_handler_mut, (gpointer) data);	  
	  break;
	}

      gtk_button_set_label(GTK_BUTTON(button),"Pause");
    }
  else
    {
      global_stop=FALSE;
      gtk_button_set_label(GTK_BUTTON(button),"Start");
    }
  
}

gboolean time_handler(GtkWidget *widget)
{
  if (widget->window == NULL) return FALSE;

  SpreadDisease();
  ChangeStates(widget);  

  /*on essaye d'empecher le freezing efficace pour large matrice*/
  while (gtk_events_pending())
  gtk_main_iteration();

  return global_stop;
  /*si retourne FALSE on detruit le timer*/
}

gboolean time_handler_gm(GtkWidget *widget)
{
  if (widget->window == NULL) return FALSE;

  SpreadDisease_gm();
  ChangeStates(widget);  

  /*on essaye d'empecher le freezing efficace pour large matrice*/
  while (gtk_events_pending())
  gtk_main_iteration();

  return global_stop;
  /*si retourne FALSE on detruit le timer*/
}

gboolean time_handler_mut(GtkWidget *widget)
{
  if (widget->window == NULL) return FALSE;

  SpreadDiseaseMut();
  ChangeStatesMut(widget);  

  /*on essaye d'empecher le freezing efficace pour large matrice*/
  while (gtk_events_pending())
  gtk_main_iteration();

  return global_stop;
  /*si retourne FALSE on detruit le timer*/
}


gboolean time_handler_mut_gm(GtkWidget *widget)
{
  if (widget->window == NULL) return FALSE;

  SpreadDiseaseMut_gm();
  ChangeStatesMut(widget);  

  /*on essaye d'empecher le freezing efficace pour large matrice*/
  while (gtk_events_pending())
  gtk_main_iteration();

  return global_stop;
  /*si retourne FALSE on detruit le timer*/
}

/* Create a new backing pixmap of the appropriate size */
gboolean configure_event( GtkWidget         *widget,
			  GdkEventConfigure *event )
{
  if (pixmap)
    g_object_unref (pixmap);

  pixmap = gdk_pixmap_new (widget->window,
			   widget->allocation.width,
			   widget->allocation.height,
			   -1);
  gdk_draw_rectangle (pixmap,
		      widget->style->white_gc,
		      TRUE,
		      0, 0,
		      widget->allocation.width,
		      widget->allocation.height);

  return TRUE;
}

/* Redraw the screen from the backing pixmap */
gboolean expose_event( GtkWidget      *widget,
                              GdkEventExpose *event )
{
  gdk_draw_drawable (widget->window,
		     widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
		     pixmap,
		     event->area.x, event->area.y,
		     event->area.x, event->area.y,
		     event->area.width, event->area.height);

  return FALSE;
}


/* Draw a rectangle on the screen */
void draw_brush( GtkWidget *widget,
                        gdouble    x,
                        gdouble    y)
{
  GdkRectangle update_rect;
 
  // set up colors and some GCs
  GdkColor red;
  GdkGC *gc;
  gc = gdk_gc_new(widget->window); // regular GC for the window
  // init the various aspects/qualities of the GCs
  red.red = 65535; red.green = 0; red.blue = 0; // red
  gdk_gc_set_rgb_fg_color(gc, &red);
 
  gint xx,yy;
  xx= (gint) floor(x/((double) PIXEL));
  yy= (gint) floor(y/((double) PIXEL));

  /*on controle qu'on clique bien dans la matrice*/ 
  if(xx<0) xx=0;
  if(xx>=DIM) xx=DIM-1;
  if(yy<0) yy=0;
  if(yy>=DIM) yy=DIM-1;
  
  //  printf("coordonne %g\t%g\n",floor(x/((double) PIXEL)), floor(y/((double) PIXEL)));
  state[xx][yy]=I;
  timer[xx][yy]=TIME_I;

  update_rect.x = xx*PIXEL ;
  update_rect.y = yy*PIXEL ;
  update_rect.width = PIXEL;
  update_rect.height = PIXEL;
  gdk_draw_rectangle (pixmap,
		      gc,
		      TRUE,
		      update_rect.x, update_rect.y,
		      update_rect.width, update_rect.height);
  gtk_widget_queue_draw_area (widget, 
		              update_rect.x, update_rect.y,
		              update_rect.width, update_rect.height);
}


/* Draw a rectangle on the screen */
void draw_brush_mut( GtkWidget *widget, gdouble x, gdouble y)
{
  GdkRectangle update_rect;
 
  // set up colors and some GCs
  GdkColor red;
  GdkGC *gc;
  gc = gdk_gc_new(widget->window); // regular GC for the window
  // init the various aspects/qualities of the GCs
  red.red = 0; red.green = 65535; red.blue = 0; // red
  gdk_gc_set_rgb_fg_color(gc, &red);
 
  gint xx,yy;
  xx= (gint) floor(x/((double) PIXEL));
  yy= (gint) floor(y/((double) PIXEL));

  /*on controle qu'on clique bien dans la matrice*/ 
  if(xx<0) xx=0;
  if(xx>=DIM) xx=DIM-1;
  if(yy<0) yy=0;
  if(yy>=DIM) yy=DIM-1;
  
  //  printf("coordonne %g\t%g\n",floor(x/((double) PIXEL)), floor(y/((double) PIXEL)));
  state[xx][yy]=IMUT;
  timer[xx][yy]=TIME_IMUT;

  update_rect.x = xx*PIXEL ;
  update_rect.y = yy*PIXEL ;
  update_rect.width = PIXEL;
  update_rect.height = PIXEL;
  gdk_draw_rectangle (pixmap,
		      gc,
		      TRUE,
		      update_rect.x, update_rect.y,
		      update_rect.width, update_rect.height);
  gtk_widget_queue_draw_area (widget, 
		              update_rect.x, update_rect.y,
		              update_rect.width, update_rect.height);
}



/* Draw a rectangle on the screen */
void draw_R( GtkWidget *widget,
                        gdouble    x,
                        gdouble    y)
{
  GdkRectangle update_rect;

  update_rect.x = x*PIXEL;
  update_rect.y = y*PIXEL;
  update_rect.width = PIXEL;
  update_rect.height = PIXEL;
  gdk_draw_rectangle (pixmap,
		      widget->style->black_gc,
		      TRUE,
		      update_rect.x, update_rect.y,
		      update_rect.width, update_rect.height);
  gtk_widget_queue_draw_area (widget, 
		              update_rect.x, update_rect.y,
		              update_rect.width, update_rect.height);
}

/* Draw a rectangle on the screen */
void draw_S( GtkWidget *widget,
                        gdouble    x,
                        gdouble    y)
{
  GdkRectangle update_rect;

  update_rect.x = x*PIXEL;
  update_rect.y = y*PIXEL;
  update_rect.width = PIXEL;
  update_rect.height = PIXEL;
  gdk_draw_rectangle (pixmap,
		      widget->style->white_gc,
		      TRUE,
		      update_rect.x, update_rect.y,
		      update_rect.width, update_rect.height);
  gtk_widget_queue_draw_area (widget, 
		              update_rect.x, update_rect.y,
		              update_rect.width, update_rect.height);
}


/* Draw a rectangle on the screen */
void draw_I( GtkWidget *widget, gdouble    x, gdouble    y)
{
  // set up colors and some GCs
  GdkColor red;
  GdkGC *gc;

  gc = gdk_gc_new(widget->window); // regular GC for the window

  // init the various aspects/qualities of the GCs
  red.red = 65535; red.green = 0; red.blue = 0; // red

  gdk_gc_set_rgb_fg_color(gc, &red);

  GdkRectangle update_rect;

  update_rect.x = x*PIXEL;
  update_rect.y = y* PIXEL;
  update_rect.width = PIXEL;
  update_rect.height = PIXEL;
  gdk_draw_rectangle (pixmap,
		      gc,
		      TRUE,
		      update_rect.x, update_rect.y,
		      update_rect.width, update_rect.height);
  gtk_widget_queue_draw_area (widget, 
		              update_rect.x, update_rect.y,
		              update_rect.width, update_rect.height);
}


/* Draw a rectangle on the screen */
void draw_Imut( GtkWidget *widget, gdouble    x, gdouble    y)
{
  // set up colors and some GCs
  GdkColor red;
  GdkGC *gc;

  gc = gdk_gc_new(widget->window); // regular GC for the window

  // init the various aspects/qualities of the GCs
  red.red = 0; red.green = 65535; red.blue = 0; // red

  gdk_gc_set_rgb_fg_color(gc, &red);

  GdkRectangle update_rect;

  update_rect.x = x*PIXEL;
  update_rect.y = y* PIXEL;
  update_rect.width = PIXEL;
  update_rect.height = PIXEL;
  gdk_draw_rectangle (pixmap,
		      gc,
		      TRUE,
		      update_rect.x, update_rect.y,
		      update_rect.width, update_rect.height);
  gtk_widget_queue_draw_area (widget, 
		              update_rect.x, update_rect.y,
		              update_rect.width, update_rect.height);
}


gboolean button_press_event( GtkWidget *widget, GdkEventButton *event )
{
  if (event->button == 1 && pixmap != NULL)
    {
      draw_brush (widget, event->x, event->y);
    }

  /*click droit*/
  if ((event->button == 3) && (pixmap != NULL) && (flag1>2))
    {
      draw_brush_mut (widget, event->x, event->y);
    }

  return TRUE;
}

gboolean motion_notify_event( GtkWidget *widget,
                                     GdkEventMotion *event )
{
  int x, y;
  GdkModifierType state;

  if (event->is_hint)
    gdk_window_get_pointer (event->window, &x, &y, &state);
  else
    {
      x = event->x;
      y = event->y;
      state = event->state;
    }
  
  /*pour dessiner en restant cliqué*/  
//  if (state & GDK_BUTTON1_MASK && pixmap != NULL)
//    {
//      switch(flag1)
//	{
//	case 1:
//	  draw_brush (widget, x, y);
//	  break;
//	case 2:
//	  draw_brush (widget, x, y);
//	  break;
//	case 3:
//	  draw_brush_mut (widget, x, y);
//	  break;
//	case 4:
//	  draw_brush_mut (widget, x, y);
//	  break;
//	}
//    }
  
  return TRUE;
}


void quit ()
{
  exit (0);
}

