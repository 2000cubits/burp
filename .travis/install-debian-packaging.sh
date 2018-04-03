#!/bin/bash

apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get -y --no-install-recommends install git ssh-client dh-make build-essential autoconf autotools-dev devscripts fakeroot
