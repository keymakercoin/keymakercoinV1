// Copyright (c) 2022 The Keymaker Coin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <checkpoints.h>

#include <chain.h>
#include <chainparams.h>
#include <reverse_iterator.h>
#include <validation.h>

#include <stdint.h>


namespace Checkpoints {

    CBlockIndex* GetLastCheckpoint(const CCheckpointData& data)
    {
        const MapCheckpoints& checkpoints = data.mapCheckpoints;

        for (const MapCheckpoints::value_type& i : reverse_iterate(checkpoints))
        {
            const uint256& hash = i.second;
            BlockMap::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return nullptr;
    }

    bool LoadCheckpoints() {
        Checkpoints::CDynamicCheckpointDB cCheckPointDB;
        std::map<int, Checkpoints::CDynamicCheckpointData> values;

        if (cCheckPointDB.LoadCheckPoint(values)) {
            std::map<int, Checkpoints::CDynamicCheckpointData>::iterator it = values.begin();
            while (it != values.end()) {
                Checkpoints::CDynamicCheckpointData data = it->second;
                Params().AddCheckPoint(data.GetHeight(), data.GetHash());
                it++;
            }
        }
        return true;
    }




    uint256 GetLatestHardenedCheckpoint()
    {
        const MapCheckpoints& checkpoints = Params().Checkpoints().mapCheckpoints;
        return (checkpoints.rbegin()->second);
    }

} // namespace Checkpoints
