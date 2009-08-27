/*      @ file:            @ last modified:                    @ author:
 *      gui_labelledwidget.c 31-07-2009 21:21                    Zborowski S.
 *
 *      @ Description:
 *      Class implementation.
 */
//x
#include "LabelledWidget.h"
#include <string>
#include <gtk/gtk.h>

WidgetWithLabel::WidgetWithLabel()
{
    m_Label = gtk_label_new( "Label:" );
    m_Widget = gtk_entry_new();
    m_Type = 1;
}

WidgetWithLabel::WidgetWithLabel( std::string L )
{
    m_Label = gtk_label_new( (gchar *)( L.c_str() ) );
    m_Widget = gtk_entry_new();
    m_Type = 1;
}

WidgetWithLabel::WidgetWithLabel( std::string L, std::string E )
{
    m_Label = gtk_label_new( (gchar *)( L.c_str() ) );
    m_Widget = gtk_entry_new();
    gtk_entry_set_text( GTK_ENTRY( m_Widget ), (gchar *)( E.c_str() ) );
    m_Type = 1;
}

WidgetWithLabel::WidgetWithLabel( std::string L, double V )
{
    m_Label = gtk_label_new( (gchar *)( L.c_str() ) );
    m_Widget = gtk_spin_button_new_with_range( 0.0, 100.0, 0.05 );
    gtk_spin_button_set_value( GTK_SPIN_BUTTON( m_Widget ), V );
    m_Type = 2;
}

WidgetWithLabel::WidgetWithLabel( std::string L, int V )
{
    m_Label = gtk_label_new( (gchar *)( L.c_str() ) );
    m_Widget = gtk_spin_button_new_with_range( 0, 5, 1 );
    gtk_spin_button_set_value( GTK_SPIN_BUTTON( m_Widget ), V );
    m_Type = 3;
}

WidgetWithLabel::~WidgetWithLabel()
{
    delete m_Label;
    delete m_Widget;
}

const gchar* WidgetWithLabel::GetText( void )
{
    return m_Type == 1 ? gtk_entry_get_text( GTK_ENTRY( m_Widget ) ) : NULL;
}

double WidgetWithLabel::GetValue( void )
{
    return ( m_Type == 2 || m_Type == 3 ) ? gtk_spin_button_get_value( GTK_SPIN_BUTTON( m_Widget ) ) : 0;
}

GtkWidget* WidgetWithLabel::GetLabelPtr( void )
{
    return m_Label;
}

GtkWidget* WidgetWithLabel::GetEntryPtr( void )
{
    return m_Widget;
}
