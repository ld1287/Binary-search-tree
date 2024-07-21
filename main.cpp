#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "bst.h"
#include "bstitem.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<BSTItem>("com.BSTItem",1,0,"BSTItem");
    qmlRegisterType<BST>("com.BST",1,0,"BST");

    QQmlApplicationEngine engine;
    //BST bst;

    //engine.rootContext()->setContextProperty("bst",&bst);

    const QUrl url(u"qrc:/BST/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
