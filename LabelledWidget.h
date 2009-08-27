/*      @ file:            @ last modified:                    @ author:
 *      gui_labelledwidget.h 31-07-2009 21:21                    Zborowski S.
 *
 *      @ Description:
 *      Labelled widget class interface.
 */

#ifndef GUI_TEXTLABEL_H
#define GUI_TEXTLABEL_H

#include <gtk/gtk.h>
#include <string>

class WidgetWithLabel
{
    public:
    WidgetWithLabel();
    WidgetWithLabel( std::string L );
    WidgetWithLabel( std::string L, std::string E );
    WidgetWithLabel( std::string L, double V );
    WidgetWithLabel( std::string L, int V );
    ~WidgetWithLabel();

    void SetLabel( std::string );

    void SetValue( std::string );
    void SetValue( double );
    const gchar* GetText( void );
    double GetValue( void );

    GtkWidget* GetLabelPtr( void );
    GtkWidget* GetEntryPtr( void );

    private:
    GtkWidget*      m_Label;
    GtkWidget*      m_Widget;
    unsigned char   m_Type;
};

#endif // GUI_TEXTLABEL_H
