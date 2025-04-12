#include "MacAddressManager.h"
#include <algorithm> // std::find
#include <iterator>  //  std::distance


MacAddressManager::MacAddressManager()
{
}

int MacAddressManager::AddMacAddress(Mac_Address mac, int position)
{
    if (position < 0 || position > static_cast<int>(vectorMAs.size()))
    {
        return INVALID_POSITION; // invalid position
    }

    //if the MAC address already exists or matches the monitor address
    for (const auto &existingMac : vectorMAs)
    {
        if (std::equal(std::begin(existingMac.MA), std::end(existingMac.MA), std::begin(mac.MA)) ||
            std::equal(std::begin(monitor.MA), std::end(monitor.MA), std::begin(mac.MA)))
        {
            return DUPLICATE_MAC_ADDRESS; // MAC address is duplicate or matches monitor
        }
    }
    vectorMAs.insert(vectorMAs.begin() + position, mac);
    return CORRECT; // success
}

int MacAddressManager::RemoveMacAddress(int position)
{
    if (position < 0 || position >= static_cast<int>(vectorMAs.size()))
    {
        return INVALID_POSITION;
    }
    vectorMAs.erase(vectorMAs.begin() + position);
    return CORRECT;
}

std::vector<Mac_Address> MacAddressManager::GetVector()
{
    return vectorMAs;
}

PositionMac MacAddressManager::GetPeers(Mac_Address mac)
{
    PositionMac peers = {};

    //find the position 
    auto it = std::find_if(vectorMAs.begin(), vectorMAs.end(), [&](const Mac_Address &addr)
                           { return std::equal(std::begin(addr.MA), std::end(addr.MA), std::begin(mac.MA)); });

    if (it == vectorMAs.end())
    {
        return peers;
    }

    int index = std::distance(vectorMAs.begin(), it);

    if (index > 0)
    {
        std::copy(std::begin(vectorMAs[index - 1].MA), std::end(vectorMAs[index - 1].MA), peers.left);
    }
    if (index < static_cast<int>(vectorMAs.size()) - 1)
    {
        std::copy(std::begin(vectorMAs[index + 1].MA), std::end(vectorMAs[index + 1].MA), peers.right);
    }
   /* if (!vectorMAs.empty())
    {
        std::copy(std::begin(vectorMAs.front().MA), std::end(vectorMAs.front().MA), peers.most_left);
        std::copy(std::begin(vectorMAs.back().MA), std::end(vectorMAs.back().MA), peers.most_right);
    }*/

    return peers;
}
