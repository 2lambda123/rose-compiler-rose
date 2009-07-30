
#ifndef QRTREEBOXCREATOR_H
#define QRTREEBOXCREATOR_H

#include "WidgetCreatorInterface.h"

class QWidget;
class QEvent;

class QRTreeBoxCreator
    : public WidgetCreatorInterface
{
    Q_OBJECT

    public:
        QRTreeBoxCreator()
            : WidgetCreatorInterface( QIcon( ":/util/WidgetIcons/Rose.gif" ), "QRTreeBox" )
        {}

    protected:
        virtual QWidget *createWidget( QWidget *parent = NULL );
};

#endif
