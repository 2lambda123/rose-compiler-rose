
#ifndef TASKINTERFACE_H
#define TASKINTERFACE_H

#include <QObject>

class TaskOutputInfo;

class Task : public QObject
{
    Q_OBJECT

    public:

        enum State { BEFORE_START,
                     RUNNING,
                     FINISHED_SUCCESS,
                     FINISHED_ERROR  };

    public:
        /// Returns a parser object, which parses the task-output
        /// and provides (localized) error messages
        virtual TaskOutputInfo * getOutputInfo() =0;


        /// Starts the task (normally done by TaskList)
        virtual void  start() =0;

        /// Returns the state this task is in
        virtual State getState() const =0;


        virtual QString getDescription() const=0;
    signals:
        /// Emitted when task has finished, call getState()
        /// to get status (success /error)
        void finished();
};

class QIODevice;
class TaskList;
class TaskOutputInfo : public QObject
{
    Q_OBJECT

    public:
        TaskOutputInfo(QObject * par = 0) : QObject(par) {}

        /// Setup a widget to show the output of this task
        ///  - use w as parent for your widgets, so they are displayed in w
        ///  - maintain own pointer to them (to update the own widgets)
        ///  - hide is called before w is destroyed (so the own pointer stays valid)
        ///  - second parameter is used to setup the signals for taskclicked correctly
        virtual void showInWidget  (QWidget * w, TaskList * tasklist) = 0;

        /// Delete or reparent your custom widget, which are childs of the
        /// w widget provided in showInWidget()
        virtual void hide(QWidget * w) =0;

    public slots:
        /// Called if new data are available on IO-device
        virtual void readData(QIODevice * dev) = 0;

    signals:
        virtual void itemSelected(const QString & file, int line, int column) = 0;

};



#endif
