#ifndef PROPERTYTREEWIDGET_H
#define PROPERTYTREEWIDGET_H

#include <QTreeView>
#include <QList>
#include <QColor>
#include <QPair>

class PropertyTreeModel;

/**
 * Generic Qt Class for displaying Property-Value pairs
 *
 * The properties can be grouped, each group is displayed in a different color.
 * The view was inspired by the property-editor of Qt-Designer (and uses the same colors)
 *
 * This class doesn't depend on rose, the rose specific version for displaying info's
 * about SgNode is NodeInfoWidget.
 */
class PropertyTreeWidget : public QTreeView
{
	Q_OBJECT

	public:
		PropertyTreeWidget(QWidget * parent=0);
		virtual ~PropertyTreeWidget();


		// Each section has a Background-Col and an alternating Bg-color
		// which is used when alternatingRowColors=true
		int addSection(const QString & sectionName,
				       const QColor & bgColor,
				       const QColor & altBgColor);

		int addSection(const QString & sectionName, int colorNr=-1);

		QModelIndex addEntryToSection(int sectionId,
									  const QString & property,
									  const QVariant & value);

		QModelIndex addEntry (const QModelIndex & parent,
							    const QString & property,
							    const QVariant & value);

		void clear();

	protected:
		//Custom Paint Event to set the colors
		virtual void drawRow (QPainter * p,
							  const QStyleOptionViewItem & viewItem,
							  const QModelIndex & index) const;

		//Stores for each section the main and alternating Color
		QList<QPair<QColor,QColor> > colors;

		PropertyTreeModel * model;

		// PreDefined Colors
		QVector<QPair<QColor,QColor> > predefColors;
};

#endif
