#!/bin/bash

cd /opt/
git clone https://github.com/kagandikmen/upmem-sdk.git
tar -xvf upmem-sdk/upmem-2024.2.0-Linux-x86_64.tar.gz
mv upmem-2024.2.0-Linux-x86_64/ /usr/local/bin/
rm -rf upmem-sdk/