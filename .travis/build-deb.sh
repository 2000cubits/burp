#!/bin/bash

set -ex

# Only binary package and clean after finish
debuild -b -tc -uc -us

mkdir -p build

mv ../burp*.* build/
