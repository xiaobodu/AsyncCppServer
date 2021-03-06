#include "ClientManagerCPP.h"
#include "ClientCPP.h"
#include "ServerCPP.h"
#include "UDPManager.h"
#include <TCPConnection.h>
#include <OPacket.h>
#include <iostream>

ClientManagerCPP::ClientManagerCPP(Server* server)
	:ClientManager(server)
{
}

Client* ClientManagerCPP::getClient(boost::asio::ip::udp::endpoint * remoteEP)
{
	for (auto it = clients.begin(); it != clients.end(); it++)
	{
		if (((ClientCPP*)it->second)->getUDPRemoteEP() == remoteEP)
		{
			return it->second;
		}
	}
	return nullptr;
}

void ClientManagerCPP::sendUDP(boost::shared_ptr<OPacket> oPack)
{
	if (((ServerCPP*)server)->getUDPManager() == nullptr)
	{
		return;
	}
	for (int i = 0; i < oPack->getSendToIDs().size(); i++)
	{
		ClientCPP* sendToClient = (ClientCPP*)ClientManager::getClient(oPack->getSendToIDs().at(i));
		((ServerCPP*)server)->getUDPManager()->send(sendToClient->getUDPRemoteEP(), oPack);
	}
}

ClientManagerCPP::~ClientManagerCPP()
{
}
