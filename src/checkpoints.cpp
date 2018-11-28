// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

#include <stdint.h>

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    // How many times we expect transactions after the last checkpoint to
    // be slower. This number is a compromise, as it can't be accurate for
    // every system. When reindexing from a fast disk with a slow CPU, it
    // can be up to 20, while when downloading from a slow network with a
    // fast multicore CPU, it won't be much higher than 1.
    static const double SIGCHECK_VERIFICATION_FACTOR = 5.0;

    struct CCheckpointData {
        const MapCheckpoints *mapCheckpoints;
        int64_t nTimeLastCheckpoint;
        int64_t nTransactionsLastCheckpoint;
        double fTransactionsPerDay;
    };

    bool fEnabled = true;

    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
                ( 10, uint256("0xc2818dc9bf6fd7fb692cc0886d39a724bb4e86fad095a62266bd015b9fbae04f"))
                ( 17, uint256("0x6c8818dd77bcaee6c3c775a34c0a84f349cc4db99e2c8b40ed7adb83b0184606"))
                ( 22, uint256("0x592cc1502043365de34d8c806fa2355e8f2ca47bfd568812c77547b4b72df744"))
                ( 27, uint256("0x49fc54fa7fe3939e57b83a468cb40333177b8e1ae1648a641ccc79d47ca68834"))
                ( 35, uint256("0x697905a9b6822eb09a6e3eecb82133cde24f15e5c400368b65bdc9b2cc7943c7"))
                ( 50, uint256("0x6a5411cbcbe8d69dd3cc85af05ad7439fc2c02acd8d5861471ea32a1b59ce271"))
                ( 55, uint256("0xe2586f641a9a61699eb7890911cac54d855493bd0bf9769b9c3a206e8f60bfee"))
                ( 80000, uint256("0x0def72391fd1db25297478048a8b1b5feca86061d614146ea8e875d27be1f41f"))
                (120000, uint256("0xa6d147731bb021c5365ba44264e7faffd47aaf806861278a4227deac33f78207"))
                (258805, uint256("0x74133722e84132005691a21a8092f0c590da7ab5744f3bdf8113089cc6d55051"))
                //(458580, uint256("0x51fe53e2091ee1f2e8244cf500027a1900e05cd01427a5258dfac8c3d759e7fe"))
                (564890, uint256("0x1230d31d9b93651e02c877776e01158496fbac59dd3d898d9b86b76a8e6beb83"))
                (3000000, uint256("0xe7d79c01f26fbfaab1cc7ee878055ffee3bc8830ee82312100ea62a78b8ff687"))
        ;
    static const CCheckpointData data = {
        &mapCheckpoints,
        1420681312, // * UNIX timestamp of last checkpoint block
        1297477,    // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        4500.0      // * estimated number of transactions per day after checkpoint
    };

    static MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        //( 0, uint256("0xa12ac9bd4cd26262c53a6277aafc61fe9dfe1e2b05eaa1ca148a5be8b394e35a"))
        (      0, uint256("0xa12ac9bd4cd26262c53a6277aafc61fe9dfe1e2b05eaa1ca148a5be8b394e35a"))
        (  40320, uint256("0xd6455e345f00791a76ccb8159efa7bd92c24dc89183f2c8db46735b121af4abd"))
        (  80640, uint256("0xba509693115a82fc2f6282034dc587f28d4d160f87a477d78653fcf4ea7e8d48"))
        ( 120960, uint256("0x419ad8a5f1797c338caf42306141baa82789e36bbc340d9a4a6bd91a7c24a7ad"))
        ( 161280, uint256("0x0099cf9699e240d7426b4b8dc35a8cdab13e945d9108300fbb43772b3432a2b0"))
        ;
    static const CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1456668199, // * UNIX timestamp of last checkpoint block
        322625,     // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        2000        // * estimated number of transactions per day after checkpoint
    };

    static MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of
        ( 0, uint256("0x0472dc040de80ded8bd385a2b6bc6e4e05cb6432047efa07692724c6ccef40ac"))
        ;
    static const CCheckpointData dataRegtest = {
        &mapCheckpointsRegtest,
        1401051600,
        1,
        10
    };

    const CCheckpointData &Checkpoints() {
        if (Params().NetworkID() == CChainParams::TESTNET)
            return dataTestnet;
        else if (Params().NetworkID() == CChainParams::MAIN)
            return data;
        else
            return dataRegtest;
    }

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (!fEnabled)
            return true;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    // Guess how far we are in the verification process at the given block index
    double GuessVerificationProgress(CBlockIndex *pindex, bool fSigchecks) {
        if (pindex==NULL)
            return 0.0;

        int64_t nNow = time(NULL);

        double fSigcheckVerificationFactor = fSigchecks ? SIGCHECK_VERIFICATION_FACTOR : 1.0;
        double fWorkBefore = 0.0; // Amount of work done before pindex
        double fWorkAfter = 0.0;  // Amount of work left after pindex (estimated)
        // Work is defined as: 1.0 per transaction before the last checkpoint, and
        // fSigcheckVerificationFactor per transaction after.

        const CCheckpointData &data = Checkpoints();

        if (pindex->nChainTx <= data.nTransactionsLastCheckpoint) {
            double nCheapBefore = pindex->nChainTx;
            double nCheapAfter = data.nTransactionsLastCheckpoint - pindex->nChainTx;
            double nExpensiveAfter = (nNow - data.nTimeLastCheckpoint)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore;
            fWorkAfter = nCheapAfter + nExpensiveAfter*fSigcheckVerificationFactor;
        } else {
            double nCheapBefore = data.nTransactionsLastCheckpoint;
            double nExpensiveBefore = pindex->nChainTx - data.nTransactionsLastCheckpoint;
            double nExpensiveAfter = (nNow - pindex->nTime)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore + nExpensiveBefore*fSigcheckVerificationFactor;
            fWorkAfter = nExpensiveAfter*fSigcheckVerificationFactor;
        }

        return fWorkBefore / (fWorkBefore + fWorkAfter);
    }

    int GetTotalBlocksEstimate()
    {
        if (!fEnabled)
            return 0;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (!fEnabled)
            return NULL;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
