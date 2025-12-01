#!/bin/bash

cd /opt/
git clone https://github.com/kagandikmen/upmem-sdk.git
tar -xvf upmem-sdk/2025.1.0/ubuntu-22.04/upmem-2025.1.0-Linux-x86_64.tar.gz
mv upmem-2025.1.0-Linux-x86_64/ /usr/local/bin/
rm -rf upmem-sdk/