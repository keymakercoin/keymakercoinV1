Keymaker 1.1.2

Setup
---------------------
Keymaker Core is the original Keymaker client and it builds the backbone of the network. It downloads and, by default, stores the entire history of Keymaker transactions (which is currently around 500Mbs); depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more.

To download Keymaker Core, visit [GitHub Releases](https://github.com/KeymakerCoin/Keymaker-Coin-Cryptocurrency/releases/latest).

Running
---------------------
The following are some helpful notes on how to run Keymaker on your native platform.

### Unix

Unpack the files into a directory and run:

- `bin/keymaker-qt` (GUI) or
- `bin/keymakerd` (headless)

Data Directory Location:
- Unix: ~/.keymaker

### Windows

Unpack the files into a directory, and then run keymaker-qt.exe.

Data Directory Locations

- Windows < Vista: C:\Documents and Settings\Username\Application Data\Keymaker
- Windows >= Vista: C:\Users\Username\AppData\Roaming\Keymaker

### OS X

Drag Keymaker-Core to your applications folder, and then run Keymaker-Core.

Data Directory Location:
- Mac: ~/Library/Application Support/Keymaker

### Need Help?

* See the documentation at the [Bitcoin Wiki](https://en.bitcoin.it/wiki/Main_Page)
for help and more information. Keymaker is very similar to bitcoin, so you can use their wiki.

Building
---------------------
The following are developer notes on how to build Keymaker on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [Dependencies](dependencies.md)
- [OS X Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [OpenBSD Build Notes](build-openbsd.md)
- [Gitian Building Guide](gitian-building.md)

Development
---------------------
The Keymaker repo's [root README](/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Source Code Documentation (External Link)](none-yet)
- [Translation Process](translation_process.md)
- [Translation Strings Policy](translation_strings_policy.md)
- [Travis CI](travis-ci.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Shared Libraries](shared-libraries.md)
- [BIPS](bips.md)
- [Dnsseed Policy](dnsseed-policy.md)
- [Benchmarking](benchmarking.md)

### Resources
* TODO: add some keymaker resources

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [Files](files.md)
- [Fuzz-testing](fuzzing.md)
- [Reduce Traffic](reduce-traffic.md)
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)
- [ZMQ](zmq.md)

License
---------------------
Distributed under the [MIT software license](/COPYING).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
