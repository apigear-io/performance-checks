# Lifecycle
ApiGear delivers implementation for Olink protocol and related classes to help you start using your interface over the network with our ready to use classes.
You can find Olink Core library which contains:
 - registry for client (ClientRegistry) and server (RemoteRegistry) that keeps track of currently used endpoint nodes, sinks or sources
 - endpoint nodes (ClientNode and RemoteNode) which are abstraction above the network layer
 These classes are independent from network implementation. They also provide interface for sink and source which are abstraction for your interface network adapters.
 
 generated apigear feature contains Olink Implementation for network service:
 - adapters for network services (using poco implementation) OlinkConnection and OlinkHost:
Classes that take care of setting up connection for client and server. They use Olink core registry and nodes.

generated olink feature contains Interface dependent adapters: 
 - "YourInterface"Client for client side which is a Sink object
 - "YourInterface"Service for server side which is a Source object
 
To have a better overview of classes responsibilities and protocol implementation we provide a sequence diagram for lifecycle messages.

## Client side sequence diagram

### Setup scenario

```mermaid
sequenceDiagram

actor User
participant ClientRegistry
participant OlinkConnection
participant ClientNode 
participant ObjectSink
actor network

User ->> ClientRegistry :create
User->> OlinkConnection :create
OlinkConnection ->> ClientNode :create
User ->> ObjectSink : create(OlinkConnector)
ObjectSink ->> OlinkConnection: connectAndLinkObject(this)
OlinkConnection ->> ClientRegistry : addObject(ObjectSink)
OlinkConnection ->> ClientRegistry : setNode(node ObjectSinkId)
alt network connection was already set up at some point
	OlinkConnection ->> ClientNode : linkRemote(ObjectSinkId)
	ClientNode ->> network :  link message
else  user triggered (re)connection
	User ->> OlinkConnection : ConnectToHost
	Note right of OlinkConnection : set up web socket & run & on connected
	OlinkConnection ->> ClientNode : linkRemoteForAllSinks
	loop all sinks using node
		ClientNode ->> network : link message
    end
end
network ->> OlinkConnection : Receive frame from server side
OlinkConnection ->> ClientNode : handleMessage
Note right of ClientNode : translate message and find target sink
ClientNode ->> ObjectSink : olinkOnInit(name, properties, this)
```

### Tear down scenario: Disconnect OlinkConnection.
User calls disconnect on OlinkConnection while connection is running and SinkObject (InterfaceClient) is attached.

```mermaid
sequenceDiagram

actor User
participant ClientRegistry
participant OlinkConnection
participant ClientNode 
participant ObjectSink
actor network

User ->> OlinkConnection : disconnect
OlinkConnection->>ClientNode: unlinkRemoteForAllSinks
loop objects using this objects node
	ClientNode ->> ObjectSink : olinkOnRelease(objectId)
	ClientNode->>network: unlink message
end
OlinkConnection ->> network: send close frame
OlinkConnection ->> OlinkConnection: close socket
```
Note: Node is not removed from the sinks in the registry, it is necessary for reconnect.


### Tear down scenario: The ObjectSink (InterfaceClient) is destroyed.
```mermaid
sequenceDiagram

actor User
participant ClientRegistry
participant OlinkConnection
participant ClientNode 
participant ObjectSink
actor network

User ->> ObjectSink : destroy
ObjectSink ->> OlinkConnection : disconnectAndUnlink(objectId)
OlinkConnection->>ClientNode: unlinkRemote(objectId)
ClientNode ->> ObjectSink : olinkOnRelease(objectId)
ClientNode->>network: unlink message
OlinkConnection ->> ClientRegistry : removeObject
```

### Tear down scenario: OlinkConnection object is destroyed without call disconnect.
```mermaid
sequenceDiagram

actor User
participant ClientRegistry
participant OlinkConnection
participant ClientNode 
participant ObjectSink
actor network

User ->> OlinkConnection : destroy
OlinkConnection ->>ClientNode : destroy
loop objects using this objects node
	ClientNode ->> ObjectSink : olinkOnRelease(objectId)
	ClientNode ->> network : unlink message
	ClientNode->>ClientRegistry: unsetNode(node, objectId)
	OlinkConnection->>ClientRegistry: removeObject(objectId)
end
OlinkConnection->>network: send close frame
```

## Server side sequence diagram

Poco implementation is simplified here to one class POCO_HTTPServer. It processes the request, calls the custom Poco::Net::HTTPRequestHandler, which makes a WebSocket for each connection.
This WebSocket is passed back to a class that manages the connections and used for implementation of sending and receiving messages - here OlinkRemote class.
The POCO_HTTPServer appears only in set up scenario as it is relevant for creating connection and not interesting in later interactions. 

### Set up scenario

The connection cannot exist without a service. So first the Source Object must be created and added to Registry, then it is allowed to create a nodes to serve the connection.
Otherwise the node won't accept the LinkMessage and the client won't be served.

```mermaid
sequenceDiagram

actor User
actor network
participant OlinkHost
participant OlinkRemote
participant RemoteNode
participant RemoteRegistry
participant ObjectSource
participant POCO_HTTPServer

User ->> OlinkHost : create
User ->>ObjectSource : create
ObjectSource ->> RemoteRegistry : AddSource(this)
User ->> OlinkHost: listen
OlinkHost ->> POCO_HTTPServer: create("move" RequestHandlerFactory)
network ->> POCO_HTTPServer : connection request
POCO_HTTPServer ->> OlinkHost : creates listening socket
OlinkHost ->>+ OlinkRemote : create
OlinkRemote ->> RemoteNode : create
network ->> RemoteNode: receive link
RemoteNode ->> RemoteRegistry : addNodeForSource(name, this)
RemoteNode ->>ObjectSource : olinkLinked
RemoteNode ->>ObjectSource : olinkCollectProperties
RemoteNode ->>OlinkRemote : write (initMessage)
OlinkRemote ->> network : initMessage
```
### Tear down scenario: Close OlinkHost.
Close all connections with OlinkHost, while server is running and clients are attached.

```mermaid
sequenceDiagram

actor User
actor network
participant OlinkHost
participant OlinkRemote
participant RemoteNode
participant RemoteRegistry
participant ObjectSource

User ->> OlinkHost : close()
loop all connections
	OlinkHost ->> OlinkRemote : destroy
	OlinkRemote ->> network : send close frame and close socket
	OlinkRemote ->> RemoteNode : destroy
	loop all source that use this node
		RemoteNode ->> RemoteRegistry : removeNodeFromSource
	end
end
```
### Tear down scenario: Destroy source.

```mermaid
sequenceDiagram

actor User
actor network
participant OlinkHost
participant OlinkRemote
participant RemoteNode
participant RemoteRegistry
participant ObjectSource


User ->> ObjectSource : destroy
ObjectSource ->> RemoteRegistry : removeSource
```

### Tear down scenario: Unlink Source message from client.

```mermaid
sequenceDiagram

actor User
actor network
participant OlinkHost
participant OlinkRemote
participant RemoteNode
participant RemoteRegistry
participant ObjectSource

network ->>OlinkRemote : receive Unlink message
OlinkRemote ->>RemoteNode : handleMessage
loop all source that use this node
	RemoteNode ->> RemoteRegistry : removeNodeFromSource
end
RemoteNode ->> ObjectSource : olinkUnlinked
```
Object serving a connection: OlinkRemote and RemoteNode are not destroyed, they may serve other services(sources) for client.

### Tear down scenario: Receive close frame for a connection.
```mermaid
sequenceDiagram

actor User
actor network
participant OlinkHost
participant OlinkRemote
participant RemoteNode
participant RemoteRegistry
participant ObjectSource

network ->> OlinkRemote : receive closeFrame
OlinkRemote ->>OlinkRemote : close connection
OlinkRemote ->> RemoteNode: destroy
loop all source that use this node
	RemoteNode ->> RemoteRegistry : removeNodeFromSource
end
OlinkRemote ->> OlinkHost: notifyConnectionClosed
OlinkHost ->> OlinkRemote: destroy
```
