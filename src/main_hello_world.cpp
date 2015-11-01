﻿////////////////////////////////////////////////////////////////////////////////
//
// Game NET - A Simple Network Tutorial for OpenGL Games
//
// (C) by Sven Forstmann in 2015
//
// License : MIT
// http://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////////////////////////
#include "core.h"
#include "net_rpc.h"
#include "net_client.h"
#include "net_server.h"

////////////////////////////////////////////////////////////////////////////////
// Simple Hello World
////////////////////////////////////////////////////////////////////////////////
// Server Part

NetServer server(12345);

// RPC
void hello_server(uint clientid, string s)
{
	cout << "Client " << clientid << " sends " << s << endl;
	server.call(clientid, "hello_client", "Greetings from Server");
}

// Main
void start_server()
{
	Rpc &r = server.get_rpc();
	rpc_register_remote(r, hello_client);
	rpc_register_local (r, hello_server);
	server.start();
	//server.stop();
}

////////////////////////////////////////////////////////////////////////////////
// Client Part

NetClient client;

// Client RPCs
void hello_client(string s)
{
	cout << "Server sends " << s << endl;
	client.call( "hello_server", "Greetings from Client");
};

// Main
void start_client()
{
	Rpc &r = client.get_rpc();
	rpc_register_local (r, hello_client);
	rpc_register_remote(r, hello_server);
	client.connect("localhost", 12345);
	client.call("hello_server", "Greetings");

	while (1)
	{
		client.process();
		core_sleep(1000);
	}
	//client.disconnect();
}

////////////////////////////////////////////////////////////////////////////////
// Main
int main()
{
	start_server();
	start_client();
	return 0;
}
////////////////////////////////////////////////////////////////////////////////

