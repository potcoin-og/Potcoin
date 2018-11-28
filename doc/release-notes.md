Potcoin Core version 0.9.5 is now available from:

  https://www.potcoin.com/#Wallets

This is a new minor version release of Potcoin,
Previously, the original and sunsequent versions of Potcoin were taken from a fork of Litecoin.
With the release of Potcoin V0.9.5, is now based directly from a fork Bitcoin.
This allows for better source control and feature implementaion from upstream changes

Upgrading to this release is recommended.

Please report bugs using the issue tracker at github:

  https://github.com/potcoin/potcoin/issues

How to Upgrade
===============

If you are running an older version of Potcoin, shut it down. Wait until it has completely
shut down (which might take a few minutes for older versions), then run the
installer (on Windows) or just copy over /Applications/Potcoin-Qt (on Mac) or
potcoind/potcoin-qt (on Linux).

Start wallet

Notable changes
================

Core base code
------------------------------------

Potcoin v0.9.5 was forked from Bitcoin v0.9.5

Staking and relay policy enhancements
------------------------------------

To implement BIP66, Potcoin Core's block templates are now for version 4 blocks only.
When BIP66 concensus (Supermajority 6120/7200) is reached, only v4 blocks will be accepted by the network.
and any staking

OP_Return and data in the blockchain
------------------------------------
Potcoin allows storing 80bytes of arbitary data in the blockchain

0.9.5 changelog
===============
- 605d1fa - John Nash, 2018-01-21 : tools: update parameters for linearize.py
- d74b4079 - John Nash, 2018-01-20 : build: re-add AM_LDFLAGS where it's overridden
- 4b5bc89 - John Nash, 2018-01-20 : build: fix win32 static linking after libtool merge
- 8f41ec0 - John Nash, 2018-01-20 : build: adding LIBTOOLIZE
- 787ee7e - John Nash, 2018-01-20 : build: Bump version, update release notes, update copyright year
- c5fac37 - John Nash, 2018-01-20 : build update configure to initialize libtool and correct rpath insertion
- 6bf33b1 - John Nash, 2017-12-23 : Bump version Add release notes
- fafc567 - John Nash, 2017-12-23 : Add additional dnsseed nodes
- 47abb78 - Henry Young, 2017-01-08 : Corrected two string literal Bitcoin references to Redecoin
- f88a2e5 - Stoner19, 2017-01-05 : Update bitcoind.cpp
- dbbfd6f - John Nash, 2016-11-30 : build: don't let libtool insert rpath into binaries
- 2ab6541 - John Nash, 2016-11-27 : build: fix newer boost build with c++11
- 81b7112 - John Nash, 2016-11-26 : add support for miniupnpc api version 14
- e69213e - John Nash, 2016-11-25 : Clearer meaning to error messages High Fee warning and Not enough inputs
- 20bda36 - Erkan Yilmaz, 2016-08-18 : typo
- 87fa337 - John Nash, 2016-08-18 : #89 Improve layout of splash screen Update text layout and adjust background for readability
- 02572a6 - John Nash, 2016-08-16 : #87 Update Debian installation instructions Add details how to install URI support on Debian Add updated graphic icons
- cc5cf5b - Sjolus, 2016-08-15 : Update rpcrawtransaction.cpp


Credits
--------

Thanks to everyone who contributed to coding, testing and feedback for this release, notably:

- @Deadpool
- @bmp02050
- @lionzeye
- @stoner19
- @henryyoung
- Erkan Yilmaz
- @Sjolus


As well as everyone that helped translating on [Transifex](https://www.transifex.com/potcoin/potcoin/).
- @Serkan34
- @Syar
- @ricklopez
- @hyoung
- @elcryptotrader
- @Maxamus
- @Erkan_Yilmaz
- @tecopos
- @xDeadp00lx
- @clickerz
- @Kasvain
- @collab
- @lionzeye
- @Ragnarice

