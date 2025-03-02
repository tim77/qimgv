#ifndef NEWLOADER_H
#define NEWLOADER_H

#include <QThreadPool>
#include <QtConcurrent>
#include "components/cache/thumbnailcache.h"
#include "loaderrunnable.h"

class Loader : public QObject {
    Q_OBJECT
public:
    explicit Loader();
    std::shared_ptr<Image> load(QString path);
    void loadAsyncPriority(QString path);
    void loadAsync(QString path);

    void clearTasks();
    bool isBusy();
private:
    QHash<QString, LoaderRunnable*> tasks;
    QThreadPool *pool;    
    void clearPool();
    void doLoadAsync(QString path, int priority);

signals:
    void loadFinished(std::shared_ptr<Image>);
    void loadFailed(QString path);

private slots:
    void onLoadFinished(std::shared_ptr<Image>, QString);
};

#endif // NEWLOADER_H
