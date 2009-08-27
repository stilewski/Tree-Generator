#include <stdlib.h>
#include <gtk/gtk.h>
#include <gtk/gtkgl.h>
#include <gdk/gdk.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <sstream>
#include "CPlant.h"
#include "TextureMgr.h"
#include <cstring>
#include "keysyms.h"
#include "LabelledWidget.h"
#include "Scene.h"


GtkWidget*          Window;
GtkWidget*          da;

GtkTextBuffer*      buffer;
GtkTextIter*        iter;
GtkWidget* bar;

WidgetWithLabel *EditBox0;
WidgetWithLabel *EditBox1, *EditBox2, *EditBox3, *EditBox4;
WidgetWithLabel *SpinWidth, *SpinLen, *SpinQ, *SpinIter;
GtkWidget       *checkBoxRandom, *checkBoxTexture, *checkBoxLighting, *checkBoxTris;

GLuint dl_index = 0;

float Xtrans = 0.0f;
float Ytrans = 0.0f;
float Ztrans = 0.0f;
float YRot = 0.0f;
bool rolling = false;
bool dragging = false;
gdouble last_x = -1;
gdouble last_y = -1;
CPlant* plant;

GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };


bool InitGL();
void regeneratePlant();

void render( void )
{
    glClearColor( 0.0, 0.0, 0.0, 1.0 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glPushMatrix();
    glColor3f( 1.0f, 1.0f, 1.0f );

    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, TextureMgr::GetInstance().m_Textures[ 2 ].texID );
    glBegin( GL_QUADS );
        glTexCoord2d(0.0,0.0); glVertex3f( -80.0f, -40.0f, -80.0f );
        glTexCoord2d(1.0,0.0); glVertex3f( 80.0f, -40.0f, -80.0f );
        glTexCoord2d(1.0,1.0); glVertex3f( 80.0f, 40.0f, -80.0f );
        glTexCoord2d(0.0,1.0); glVertex3f( -80.0f, 40.0f, -80.0f );
    glEnd();
    glPopMatrix();

    glTranslatef( Xtrans, Ytrans, -8.0f + Ztrans );
    glRotatef( YRot, 0.0f, 1.0f, 0.0f );

    glBindTexture( GL_TEXTURE_2D, TextureMgr::GetInstance().m_Textures[ 3 ].texID );
    glBegin( GL_QUADS );
        glTexCoord2d(0.0,0.0); glVertex3f( -6.0f, -4.0f, -8.0f );
        glTexCoord2d(1.0,0.0); glVertex3f( 6.0f, -4.0f, -8.0f );
        glTexCoord2d(1.0,1.0); glVertex3f( 6.0f, -4.0f, 8.0f );
        glTexCoord2d(0.0,1.0); glVertex3f( -6.0f, -4.0f, 8.0f );

        glTexCoord2d(0.0,0.0); glVertex3f( -6.0f, -4.0f, -8.0f );
        glTexCoord2d(1.0,0.0); glVertex3f( 6.0f, -4.0f, -8.0f );
        glTexCoord2d(1.0,1.0); glVertex3f( 8.0f, -6.0f, -10.0f );
        glTexCoord2d(0.0,1.0); glVertex3f( -8.0f, -6.0f, -10.0f );

        glTexCoord2d(0.0,0.0); glVertex3f( -6.0f, -4.0f, 8.0f );
        glTexCoord2d(1.0,0.0); glVertex3f( 6.0f, -4.0f, 8.0f );
        glTexCoord2d(1.0,1.0); glVertex3f( 8.0f, -6.0f, 10.0f );
        glTexCoord2d(0.0,1.0); glVertex3f( -8.0f, -6.0f, 10.0f );

        glTexCoord2d(0.0,0.0); glVertex3f( -6.0f, -4.0f, 8.0f );
        glTexCoord2d(1.0,0.0); glVertex3f( -6.0f, -4.0f, -8.0f );
        glTexCoord2d(1.0,1.0); glVertex3f( -8.0f, -6.0f, -10.0f );
        glTexCoord2d(0.0,1.0); glVertex3f( -8.0f, -6.0f, 10.0f );

        glTexCoord2d(0.0,0.0); glVertex3f( 6.0f, -4.0f, 8.0f );
        glTexCoord2d(1.0,0.0); glVertex3f( 6.0f, -4.0f, -8.0f );
        glTexCoord2d(1.0,1.0); glVertex3f( 8.0f, -6.0f, -10.0f );
        glTexCoord2d(0.0,1.0); glVertex3f( 8.0f, -6.0f, 10.0f );
    glEnd();
    glDisable( GL_TEXTURE_2D );

    plant->DrawPlantFromBuffer3dStrips();
}

void textFormula( void )
{
    gtk_text_buffer_set_text( buffer, (gchar *)( plant->GetExtendedFormula().c_str() ), -1 );
}

void keyPress( GtkWidget* widget, GdkEventKey* event, gpointer user_data )
{
    printf( "KURWA\n" );
    switch( event->keyval )
    {
        case GDK_a:
            printf( "JEHA" );
        break;

        default: break;
    }
}

static gboolean applyChanges( gpointer user_data )
{
    GtkWidget* da = GTK_WIDGET( user_data );

    gdk_window_invalidate_rect( da->window, &da->allocation, FALSE );
	gdk_window_process_updates( da->window, FALSE );

	return TRUE;
}

static void check_button_cb( GtkWidget* widget, gpointer user_data )
{
    if( widget == checkBoxTris )
    {
        plant->SetOptions( PLANT_SHOW_TRIS );
        regeneratePlant();
    }
    else if( widget == checkBoxRandom )
        plant->SetOptions( PLANT_RANDOM_ANGLES );
    else if( widget == checkBoxLighting )
    {
        scene->ChangeLighting();
        InitGL();
    }
    else if( widget == checkBoxTexture )
    {
        scene->ChangeTexturing();
        regeneratePlant();
    }
}

inline static void mouse_scroll_cb( GtkWidget* widget, GdkEventScroll* event, gpointer user_data )
{
    Ztrans += event->direction == GDK_SCROLL_DOWN ? -0.1f - 0.05f*( Ztrans == 0.0f ? 0.1f : ( Ztrans > 0.0f ? Ztrans : -Ztrans ) ) : 0.1f + 0.05f*( Ztrans == 0.0f ? 0.1f : ( Ztrans > 0.0f ? Ztrans : -Ztrans ) );
}


static void mouse_motion_cb( GtkWidget* widget, GdkEventMotion* event, gpointer user_data )
{
    if( dragging )
    {
        Xtrans += event->x > last_x ? -( last_x - event->x )/ 100.0f : ( event->x - last_x )/ 100.0f;
        Ytrans += event->y > last_y ? -( event->y - last_y )/ 100.0f : ( last_y - event->y )/ 100.0f;
    }
    else if( rolling )
    {
        YRot += event->x > last_x ? 2.0f : -2.0f;
    }

    last_x = event->x;
    last_y = event->y;
}

static void mouse_click_cb( GtkWidget* widget, GdkEventMotion* event, gpointer user_data )
{
    if( event->state & GDK_SHIFT_MASK == GDK_SHIFT_MASK )
        dragging = !dragging;
    else
        rolling = !rolling;

    last_x = event->x;
    last_y = event->y;
}


void regeneratePlant()
{
    std::stringstream msg;

    if( plant->CheckFormula() )
    {
        plant->set( EditBox0->GetText(), EditBox2->GetText(), EditBox1->GetText(), EditBox3->GetText(), EditBox4->GetText() );
        plant->ExpandFormula( SpinIter->GetValue() );

        //plant->GeneratePlant( Vector3d( 0.0f, -4.0f, 0.0f ), gtk_spin_button_get_value( GTK_SPIN_BUTTON( SpinLen->GetEntryPtr() ) ), gtk_spin_button_get_value( GTK_SPIN_BUTTON( SpinWidth->GetEntryPtr() ) ), 90.0f, 0.0f );
        plant->GeneratePlantB( Vector3d( 0.0f, -4.0f, 0.0f ), gtk_spin_button_get_value( GTK_SPIN_BUTTON( SpinLen->GetEntryPtr() ) ), gtk_spin_button_get_value( GTK_SPIN_BUTTON( SpinWidth->GetEntryPtr() ) ), 90.0f, 0.0f );

        plant->Simplify();
        plant->GenerateDisplayList();
        textFormula();

        msg << "Plant generated. " << plant->GetRootsNumber() << " roots, " << plant->GetLeafsNumber() << " leafs. " << plant->GetRootsNumber()*16 << " triangles.";
    }
    else
    {
        msg << " ** FATAL: Formula is invalid! Cannot generate a plant! ";
    }

    gtk_statusbar_push( GTK_STATUSBAR( bar ), gtk_statusbar_get_context_id( GTK_STATUSBAR( bar ), "message1" ), msg.str().c_str() );
}

static void helloWorld (GtkWidget *wid, GtkWidget *win)
{
  GtkWidget *dialog = NULL;

  dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "test" );
  gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}



static gboolean expose( GtkWidget* da, GdkEventConfigure* event, gpointer user_data )
{
	GdkGLContext *GLcontext = gtk_widget_get_gl_context( da );
	GdkGLDrawable* GLdrawable = GDK_GL_DRAWABLE( gtk_widget_get_gl_window( da ) );

	if( !gdk_gl_drawable_gl_begin( GLdrawable, GLcontext ) )
        g_assert_not_reached();

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glPushMatrix();
	glShadeModel( GL_FLAT );

    glCallList( dl_index );
	render();

	glPopMatrix();

	if( gdk_gl_drawable_is_double_buffered( GLdrawable) )
        gdk_gl_drawable_swap_buffers( GLdrawable );
    else
        glFlush();

    gdk_gl_drawable_gl_end( GLdrawable );
    return TRUE;
}

bool InitGL( void )
{
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LESS );
    glShadeModel(GL_SMOOTH);
    glEnable( GL_LINE_SMOOTH );
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearDepth( 1.0 );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glViewport( 0, 0, da->allocation.width, da->allocation.height );
    gluPerspective( 45.0f, (GLfloat)da->allocation.width/(GLfloat)da->allocation.height, 0.1f, 100.0f);

    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);

    //glColorMaterial ( GL_FRONT_AND_BACK, GL_EMISSION ) ;
    glEnable( GL_COLOR_MATERIAL );

    //static GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
    //static GLfloat red[]    = {1.0, 0.0, 0.0, 0.5};

    glLightfv (GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
    glLightfv (GL_LIGHT0, GL_POSITION, LightPosition);

    if( scene->IsLighting() )
    {
        glEnable( GL_LIGHTING );
        glEnable( GL_LIGHT1 );
    }
    else
    {
        glDisable( GL_LIGHTING );
        glDisable( GL_LIGHT1 );
    }


    //glBindTexture(GL_TEXTURE_2D, textures[0].texID);

    return true;
}

static gboolean configure( GtkWidget* da, GdkEventConfigure* event, gpointer user_data )
{
	GdkGLContext *GLcontext = gtk_widget_get_gl_context( da );
	GdkGLDrawable *GLdrawable = GDK_GL_DRAWABLE( gtk_widget_get_gl_window( da ) );

	if( !gdk_gl_drawable_gl_begin( GLdrawable, GLcontext ) )
        g_assert_not_reached();

    InitGL();
    gdk_gl_drawable_gl_end( GLdrawable );
    return TRUE;
}

static void realize_main( GtkWidget* w )
{
    GdkGLContext* glContext = gtk_widget_get_gl_context( w );
    GdkGLDrawable* glDrawable = GDK_GL_DRAWABLE( gtk_widget_get_gl_window( w ) );

	if( !gdk_gl_drawable_gl_begin( glDrawable, glContext ) )
        g_assert_not_reached();

    TextureMgr::GetInstance().LoadTGA( "leaf.tga" );
    TextureMgr::GetInstance().LoadTGA( "tree.tga" );
    TextureMgr::GetInstance().LoadTGA( "sky.tga" );
    TextureMgr::GetInstance().LoadTGA( "grass.tga" );

    InitGL();
    gdk_gl_drawable_gl_end( glDrawable );
}

static void realize_sub( GtkWidget* w )
{
    GdkGLContext* glContext = gtk_widget_get_gl_context( w );
    GdkGLDrawable* glDrawable = GDK_GL_DRAWABLE( gtk_widget_get_gl_window( w ) );

	if( !gdk_gl_drawable_gl_begin( glDrawable, glContext ) )
        g_assert_not_reached();

    InitGL();
    gdk_gl_drawable_gl_end( glDrawable );
}

GtkWidget* construct_side_panel( void )
{
    EditBox0 = new WidgetWithLabel( "Formuła:", "PL" );

    EditBox1 = new WidgetWithLabel( "(L) Liść:", "[LL]P[L][L][L]" );
    EditBox2 = new WidgetWithLabel( "(P) Pień:", "PP" );
    EditBox3 = new WidgetWithLabel( "([) Gałąź:", "[" );
    EditBox4 = new WidgetWithLabel( "(]):", "]" );

    SpinLen = new WidgetWithLabel( "Długość", 0.5f );
    SpinWidth = new WidgetWithLabel( "Grubość", 0.15f );
    SpinQ = new WidgetWithLabel( "Dokładność", 1 );
    SpinIter = new WidgetWithLabel( "Złożoność", 3 );

    GtkWidget*              vbox, *formula_hbox;
    GtkWidget*              button;
    GtkWidget*              regTable, *addTable;
    GtkWidget*              frameGL, *vframeGL;
    GtkWidget*              frameReg, *vframeReg;
    GtkWidget*              frameAdd, *vframeAdd;

    vbox = gtk_vbox_new( FALSE, 6 );
    gtk_container_add( GTK_CONTAINER( Window ), vbox );
    /// formuła
    formula_hbox = gtk_hbox_new( FALSE, 6 );
    gtk_box_pack_start( GTK_BOX( formula_hbox ), EditBox0->GetLabelPtr(), TRUE, TRUE, 0 );
    gtk_box_pack_start( GTK_BOX( formula_hbox ), EditBox0->GetEntryPtr(), TRUE, TRUE, 0 );
    gtk_box_pack_start( GTK_BOX( vbox ), formula_hbox, TRUE, TRUE, 0 );

    /// opcje reguł
    frameReg = gtk_frame_new( "Reguły tworzenia" );
    vframeReg = gtk_vbox_new( FALSE, 6 );
    regTable = gtk_table_new( 4, 2, FALSE );
    gtk_table_attach_defaults( GTK_TABLE( regTable ), EditBox1->GetLabelPtr(), 0, 1, 0, 1 );
    gtk_table_attach_defaults( GTK_TABLE( regTable ), EditBox2->GetLabelPtr(), 0, 1, 1, 2 );
    gtk_table_attach_defaults( GTK_TABLE( regTable ), EditBox3->GetLabelPtr(), 0, 1, 2, 3 );
    gtk_table_attach_defaults( GTK_TABLE( regTable ), EditBox4->GetLabelPtr(), 0, 1, 3, 4 );

    gtk_table_attach_defaults( GTK_TABLE( regTable ), EditBox1->GetEntryPtr(), 1, 2, 0, 1 );
    gtk_table_attach_defaults( GTK_TABLE( regTable ), EditBox2->GetEntryPtr(), 1, 2, 1, 2 );
    gtk_table_attach_defaults( GTK_TABLE( regTable ), EditBox3->GetEntryPtr(), 1, 2, 2, 3 );
    gtk_table_attach_defaults( GTK_TABLE( regTable ), EditBox4->GetEntryPtr(), 1, 2, 3, 4 );

    gtk_box_pack_start( GTK_BOX( vframeReg ), regTable, TRUE, TRUE, 0 );
    gtk_container_add( GTK_CONTAINER( frameReg ), vframeReg );
    gtk_box_pack_start( GTK_BOX( vbox ), frameReg, TRUE, TRUE, 0 );

    /// opcje dodatkowe
    frameAdd = gtk_frame_new( "Odwzorowywanie" );
    vframeAdd = gtk_vbox_new( FALSE, 6 );
    addTable = gtk_table_new( 4, 2, FALSE );
    gtk_table_attach_defaults( GTK_TABLE( addTable ), SpinLen->GetLabelPtr(), 0, 1, 0, 1 );
    gtk_table_attach_defaults( GTK_TABLE( addTable ), SpinWidth->GetLabelPtr(), 0, 1, 1, 2 );
    gtk_table_attach_defaults( GTK_TABLE( addTable ), SpinQ->GetLabelPtr(), 0, 1, 2, 3 );
    gtk_table_attach_defaults( GTK_TABLE( addTable ), SpinIter->GetLabelPtr(), 0, 1, 3, 4 );

    gtk_table_attach_defaults( GTK_TABLE( addTable ), SpinLen->GetEntryPtr(), 1, 2, 0, 1 );
    gtk_table_attach_defaults( GTK_TABLE( addTable ), SpinWidth->GetEntryPtr(), 1, 2, 1, 2 );
    gtk_table_attach_defaults( GTK_TABLE( addTable ), SpinQ->GetEntryPtr(), 1, 2, 2, 3 );
    gtk_table_attach_defaults( GTK_TABLE( addTable ), SpinIter->GetEntryPtr(), 1, 2, 3, 4 );

    gtk_box_pack_start( GTK_BOX( vframeAdd ), addTable, TRUE, TRUE, 0 );

    checkBoxRandom = gtk_check_button_new_with_label( "Wprowadzaj czynnik losowy" );
    g_signal_connect( G_OBJECT( checkBoxRandom ), "toggled", G_CALLBACK( check_button_cb ), (gpointer)Window );

    gtk_box_pack_start( GTK_BOX( vframeAdd ), checkBoxRandom, TRUE, TRUE, 0 );

    gtk_container_add( GTK_CONTAINER( frameAdd ), vframeAdd );
    gtk_box_pack_start( GTK_BOX( vbox ), frameAdd, TRUE, TRUE, 0 );


    /// przycisk GENEROWANIA
    button = gtk_button_new_with_label( "Stwórz roślinkę" );
    g_signal_connect( G_OBJECT( button ), "clicked", G_CALLBACK( regeneratePlant ), (gpointer)Window );
    gtk_box_pack_start( GTK_BOX( vbox ), button, TRUE, TRUE, 0 );

    /// opcje wyświetlania
    frameGL = gtk_frame_new( "Wyświetlanie" );
    vframeGL = gtk_vbox_new( FALSE, 6 );
    checkBoxTexture = gtk_check_button_new_with_label( "Włącz tekstury" );
    g_signal_connect( G_OBJECT( checkBoxTexture ), "toggled", G_CALLBACK( check_button_cb ), (gpointer)Window );
    gtk_box_pack_start( GTK_BOX( vframeGL ), checkBoxTexture, TRUE, TRUE, 0 );
    checkBoxLighting = gtk_check_button_new_with_label( "Włącz oświetlenie" );
    g_signal_connect( G_OBJECT( checkBoxLighting ), "toggled", G_CALLBACK( check_button_cb ), (gpointer)Window );
    gtk_box_pack_start( GTK_BOX( vframeGL ), checkBoxLighting, TRUE, TRUE, 0 );
    checkBoxTris = gtk_check_button_new_with_label( "Wyświetl siatkę" );
    g_signal_connect( G_OBJECT( checkBoxTris ), "toggled", G_CALLBACK( check_button_cb ), (gpointer)Window );
    gtk_box_pack_start( GTK_BOX( vframeGL ), checkBoxTris, TRUE, TRUE, 0 );
    gtk_container_add( GTK_CONTAINER( frameGL ), vframeGL );
    gtk_box_pack_start( GTK_BOX( vbox ), frameGL, TRUE, TRUE, 0 );


    button = gtk_button_new_with_label( "Wyjdź" );
    g_signal_connect( G_OBJECT( button ), "clicked", G_CALLBACK( helloWorld ), (gpointer)Window );
    gtk_box_pack_start( GTK_BOX( vbox ), button, TRUE, TRUE, 0 );

    return vbox;
}

GtkWidget* construct_bottom_panel( void )
{
    GtkWidget*          scroll;
    GtkWidget*          textarea;
    GtkObject*          Vadj, *Hadj;

    Vadj = gtk_adjustment_new( 0, 0, 1000, 1, 10, 5 );
    Hadj = gtk_adjustment_new( 0, 0, 0, 0, 0, 0 );

    textarea = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer( GTK_TEXT_VIEW( textarea ) );
    gtk_text_view_set_wrap_mode( GTK_TEXT_VIEW( textarea ), GTK_WRAP_CHAR );
    gtk_text_view_set_editable( GTK_TEXT_VIEW( textarea ), FALSE );

    scroll = gtk_scrolled_window_new( GTK_ADJUSTMENT( Hadj ), GTK_ADJUSTMENT( Vadj ) );
    gtk_scrolled_window_set_policy( GTK_SCROLLED_WINDOW( scroll ), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS );
    gtk_container_add( GTK_CONTAINER( scroll ), textarea );

    return scroll;
}

GtkWidget* construct_menu( void )
{
    GtkWidget* bar;
    GtkWidget* fileItem, *editItem, *viewItem, *aboutItem;
    GtkWidget* fileMenu, *openItem, *saveItem, *exportOBJItem, *quitItem;
    GtkWidget* exportSubMenu;

    bar = gtk_menu_bar_new();
    fileItem = gtk_menu_item_new_with_label( "Plik" );
        fileMenu = gtk_menu_new();
        openItem = gtk_menu_item_new_with_label( "Otwórz" );
        gtk_menu_shell_append( GTK_MENU_SHELL( fileMenu ), openItem );
        saveItem = gtk_menu_item_new_with_label( "Zapisz" );
        gtk_menu_shell_append( GTK_MENU_SHELL( fileMenu ), saveItem );
        exportOBJItem = gtk_menu_item_new_with_label( "Eksportuj" );
        gtk_menu_shell_append( GTK_MENU_SHELL( fileMenu ), exportOBJItem );
        quitItem = gtk_menu_item_new_with_label( "Zakończ" );
        gtk_menu_shell_append( GTK_MENU_SHELL( fileMenu ), quitItem );
    editItem = gtk_menu_item_new_with_label( "Edycja" );
    viewItem = gtk_menu_item_new_with_label( "Widok" );
    aboutItem = gtk_menu_item_new_with_label( "O programie" );

    gtk_menu_bar_append( bar, fileItem );
    gtk_menu_bar_append( bar, editItem );
    gtk_menu_bar_append( bar, viewItem );
    gtk_menu_bar_append( bar, aboutItem );

    gtk_menu_item_set_submenu( GTK_MENU_ITEM( fileItem ), fileMenu );
    g_signal_connect( G_OBJECT( quitItem ), "activate", (GtkSignalFunc) gtk_main_quit, NULL );

    return bar;
}

GtkWidget* construct_statusbar( void )
{


    bar = gtk_statusbar_new();
    gtk_statusbar_push( GTK_STATUSBAR( bar ), gtk_statusbar_get_context_id( GTK_STATUSBAR( bar ), "message1" ), "Plant generated" );

    return bar;
}

int main( int argc, char **argv )
{
    new CScene;
    new TextureMgr;

    GtkWidget*          table;
    GdkGLConfig*        GLconf;
    GdkGLContext*       GLContext;
    GtkWidget*          v_box;

    gtk_init( &argc, &argv );
    gtk_gl_init( &argc, &argv );

    da = gtk_drawing_area_new();
    GLconf = gdk_gl_config_new_by_mode( (GdkGLConfigMode)(GDK_GL_MODE_RGB | GDK_GL_MODE_DEPTH | GDK_GL_MODE_DOUBLE) );
    if( !( GLconf ) || !( gtk_widget_set_gl_capability( da, GLconf, NULL, TRUE, GDK_GL_RGBA_TYPE ) ) )
        g_assert_not_reached();

    g_signal_connect_after( G_OBJECT( da ), "realize", G_CALLBACK( realize_main ), NULL );
    g_signal_connect( da, "configure_event", G_CALLBACK( configure ), NULL );
    g_signal_connect( da, "expose_event", G_CALLBACK( expose ), NULL );

    gtk_widget_show( da );
    gtk_widget_realize( da );
    //GLContext = gtk_widget_get_gl_context( da );

    g_signal_connect_after( G_OBJECT( da ), "realize", G_CALLBACK( realize_sub ), NULL );
    g_signal_connect( da, "configure_event", G_CALLBACK( configure ), NULL );
    g_signal_connect( da, "expose_event", G_CALLBACK( expose ), NULL );

    g_signal_connect( G_OBJECT( da ), "motion_notify_event", G_CALLBACK( mouse_motion_cb ), (gpointer)Window );
    g_signal_connect( G_OBJECT( da ), "button_press_event", G_CALLBACK( mouse_click_cb ), (gpointer)Window );
    g_signal_connect( G_OBJECT( da ), "button_release_event", G_CALLBACK( mouse_click_cb ), (gpointer)Window );
    g_signal_connect( G_OBJECT( da ), "scroll_event", G_CALLBACK( mouse_scroll_cb ), (gpointer)Window );
    g_signal_connect( G_OBJECT( da ), "key_press_event", G_CALLBACK( keyPress ), (gpointer)Window );

    gtk_widget_show ( da );

    Window = gtk_window_new( GTK_WINDOW_TOPLEVEL );                                                             /// WINDOW
    gtk_window_set_default_size( GTK_WINDOW(Window), 800, 500 );
    gtk_window_set_title (GTK_WINDOW (Window), "Stilewski's Plant Generator");
    gtk_window_set_position (GTK_WINDOW (Window), GTK_WIN_POS_CENTER);
    g_signal_connect_swapped( Window, "destroy", G_CALLBACK( gtk_main_quit ), NULL );
    v_box = gtk_vbox_new( FALSE, 0 );
    gtk_container_add( GTK_CONTAINER( Window ), v_box );


    gtk_box_pack_start( GTK_BOX( v_box ), construct_menu(), TRUE, TRUE, 0 );                                    /// MAIN MENU
    table = gtk_table_new( 16, 16, FALSE );                                                                     /// TABLE
    gtk_table_set_col_spacing( GTK_TABLE(table), 11, 8 );
    gtk_table_set_row_spacing( GTK_TABLE(table), 13, 8 );
    gtk_table_attach_defaults( GTK_TABLE(table), da, 0, 12, 0, 14 );                                            /// DRAWING AREA
    gtk_table_attach_defaults( GTK_TABLE(table), construct_side_panel(), 12, 16, 0, 16 );                       /// SIDE PANEL
    gtk_table_attach_defaults( GTK_TABLE(table), construct_bottom_panel(), 0, 12, 14, 16 );                     /// BOTTOM PANEL
    gtk_box_pack_start( GTK_BOX( v_box ), table, TRUE, TRUE, 0 );
    gtk_box_pack_start( GTK_BOX( v_box ), construct_statusbar(), TRUE, TRUE, 0 );                               /// STATUS BAR



    gtk_widget_set_events
    (
        da,
        GDK_EXPOSURE_MASK       |
        GDK_SCROLL_MASK         |
        GDK_POINTER_MOTION_MASK |
        GDK_BUTTON_PRESS_MASK   |
        GDK_BUTTON_RELEASE_MASK |
        GDK_BUTTON_MOTION_MASK  |
        GDK_BUTTON1_MOTION_MASK |
        GDK_KEY_PRESS_MASK
    );
    gtk_toggle_button_set_mode( GTK_TOGGLE_BUTTON( checkBoxRandom ), TRUE );
    gtk_widget_show( Window );

    plant = new CPlant();

    InitGL();
    gtk_widget_show_all( Window );
    g_timeout_add( 1000 / 60, applyChanges, da );
    gtk_main();
}


