//gcc -Wall `pkg-config --libs --cflags gtk+-2.0` welcome.c sel_param.c sel_param_tradeoff.c evolvir.h infection.c localmixing.c globalmixing.c selecao.c main.c

#include <stdio.h>
#include <time.h> 
#include <unistd.h>
#include <locale.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <math.h>
#include <string.h>

#define DIM 120
#define PIXEL 4

#define S 0
#define E 1
#define EMUT 5
#define I 2
#define IMUT 4
#define R 3

#define TIME_E 0
#define TIME_EMUT 0
#define TIME_I 70
#define TIME_IMUT 120
#define TIME_R 100

#define TRANSMISSION 1.8
#define TRANSMISSION_MUT 1.8

#define DELTA_T 0.01
#define INFLECTION 30.0
#define B_MAX 5.8

/*variable globle*/
int state[DIM][DIM];
int timer[DIM][DIM];
gboolean global_stop;
gint flag1;
gdouble par_b;
gdouble par_v;
gdouble par_B;
gdouble par_V;
GtkWidget *scale_param[4];

/* Backing pixmap for drawing area */
GdkPixmap *pixmap;

/*vitesse d'animation	  g_timeout_add
premier argument interval: the time between calls to the function, in milliseconds (1/1000ths of a second)*/
guint gglobal_speed;


/*declaration des fonctions*/

/*welcome.c*/
void welcome(void);
void OnAboutBtn(GtkWidget *pBtn, gpointer data);
void OnQuitBtn(GtkWidget* widget, gpointer data);
void OnOptionsBtn(GtkWidget* widget, gpointer data);
void select_speed(void);
void OnValueChange_speed(GtkWidget *pWidget, gpointer data);
void OnValidate_speed(GtkWidget *widget, gpointer data);



gint delete_event(GtkWidget *Widget, GdkEvent *event, gpointer data);


/*selecao.c*/
void selecao(void);
void OnValider(GtkWidget *pBtn, gpointer data);

/*localmixing.c*/
void SpreadDisease(void);
void ChangeStates(GtkWidget *widget);
void infection(int x, int y, int xt, int yt, int xb, int yb, int xl, int yl, int xr, int yr);
void SpreadDiseaseMut(void);
void ChangeStatesMut(GtkWidget *widget);
void InfectionMut(int x, int y, int xt, int yt, int xb, int yb, int xl, int yl, int xr, int yr);

/*globalmixing.c*/
void countI_gm(int *cntI, int *cntImut);
void SpreadDisease_gm(void);
void SpreadDiseaseMut_gm(void);
void infection_gm(int x, int y, int cntI, int cntImut);
void InfectionMut_gm(int x, int y, int cntI, int cntImut);

/*infection.c*/
void anim_infection(void);
void OnStart(GtkWidget *button, gpointer data);
void information(GtkWindow *parent);


gboolean configure_event( GtkWidget *widget, GdkEventConfigure *event );
gboolean expose_event( GtkWidget *widget, GdkEventExpose *event );
void draw_brush( GtkWidget *widget, gdouble x, gdouble y);
void draw_brush_mut( GtkWidget *widget, gdouble x, gdouble y);
void draw_R(GtkWidget *widget, gdouble x, gdouble y);
void draw_S( GtkWidget *widget, gdouble x, gdouble y);
void draw_I( GtkWidget *widget, gdouble x, gdouble y);
void draw_Imut( GtkWidget *widget, gdouble    x, gdouble    y);
gboolean button_press_event( GtkWidget *widget, GdkEventButton *event );
gboolean motion_notify_event( GtkWidget *widget, GdkEventMotion *event);
gboolean time_handler(GtkWidget *widget);
gboolean time_handler_gm(GtkWidget *widget);
gboolean time_handler_mut(GtkWidget *widget);
gboolean time_handler_mut_gm(GtkWidget *widget);
void quit ();

/*sel_param.c*/
void select_param (void);
void select_param_mut (void);
void OnValidate_select_param(GtkWidget *widget, gpointer data);
void OnValueChange_select_param(GtkWidget *pWidget, gpointer data);
void OnDefault_select_param(GtkWidget *widget, gpointer data);

void select_param_mut_tradeoff (void);
void OnValueChange_select_param_tradeoff(GtkWidget *pWidget, gpointer data);
void OnGraph_select_param(GtkWidget *Widget, gpointer data);
