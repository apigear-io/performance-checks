

#include <QtCore>
#include "apigear/olink/olinkhost.h"
#include "olink/remoteregistry.h"
#include "olink/clientregistry.h"
#include "api/olink/olinktestapi0.h"
#include "api/olink/olinktestapi0adapter.h"
#include "api/apifactory.h"
#include "api/olink/olinkfactory.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "olink/olinkhost.h"
#include "olink/olinkclient.h"
#include <QtQml>

#include "api/api/qmltestapi0.h"
#include <memory>
#include <iostream>

#include <QtPlugin>

// Example uses Olink Client as a backend for Qml Interface Wrappers
// It sets up the server with InterfaceImplemenation and wrappes it with Olink Service Adapters
// The connection is set up, and you can observe changes of your qml class by changing an interface instance.
// Normally server (with InterfaceImplemenation and Olink Service Adapter) would be in separate app
// And your UI containing the factory and a client.





int main(int argc, char *argv[]){


    qmlRegisterType<api::QmlTestApi0>("plugin_api", 1, 0, "ApiTestApi0");
    // Prepare Factory before app is created.
    ApiGear::ObjectLink::ClientRegistry client_registry;
    ApiGear::ObjectLink::OLinkClient client(client_registry);
    api::OLinkFactory factory(client);
    api::ApiFactory::set(&factory);

    // Create main app
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QGuiApplication app(argc, argv);

    // Hardcoded path to plugins for runtime app, works only in this folder structure
    // You may want to try out setting QML_IMPORT_PATH and QML2_IMPORT_PATH variables instead of following line.
    app.addLibraryPath(app.applicationDirPath() + "../../imports");
    QQmlApplicationEngine engine;

    engine.load(url);

    // With services ready connect the client - all qml olink clients will be linked
    client.connectToHost(QUrl("ws://127.0.0.1:8182/ws"));

    auto result = app.exec();

    return result;
}
