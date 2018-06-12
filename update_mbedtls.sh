#!/bin/bash
die () {
    echo "$@" 1>&2 ;
    cdir=${PWD##*/};
    if [ "$cdir" == "tmp" ]; then cd..; fi;
    rm -rf tmp;
    exit 1;
}

GH_REF="github.com/Openhab-Nodes/WakaamaNode.git"
GH_SRC="https://github.com/ARMmbed/mbedtls.git"
TITLE="Update mbedTLS source to revision"
AUTHOR="David Graeff <david.graeff@web.de>"

rm -rf tmp
git clone "$GH_SRC" tmp --branch master --single-branch --depth 1
cd tmp || die "Couldn't checkout repository!"
describe=$(git rev-parse --short HEAD)

# Check checkout
if [ ! -d include/mbedtls ]; then die "Expected a include/mbedtls directory in the mbedtls sources!"; fi;
if [ ! -d library ]; then die "Expected a library directory in the mbedtls sources!"; fi;

# Remove old sources
echo "$TITLE $describe"
cp ../src/network/mbedtls/include/mbedtls/config.h include/mbedtls/ || die "Couldn't copy configuration file"
rm -rf include/mbedtls/net.h include/mbedtls/net_sockets.h include/mbedtls/compat-1.3.h
rm -rf library/CMakeLists.txt library/Makefile library/net_sockets.c library/timing.c library/threading.c library/platform.c library/memory_buffer_alloc.c
rm -rf ../src/network/mbedtls/include/mbedtls/* && mv include/mbedtls/* ../src/network/mbedtls/include/mbedtls/ || die "Couldn't copy header files"
rm -rf ../src/network/mbedtls/library/* && mv library/* ../src/network/mbedtls/library/ || die "Couldn't copy library files"
cd .. || exit
rm -rf tmp

# Add to repository
git add src/network/mbedtls
git commit --author="$AUTHOR" -m "$TITLE $describe"

if [ "$GH_TOKEN" != "" ]; then
    if ! git diff HEAD origin/HEAD > /dev/null; then
        git push "https://$GH_TOKEN@$GH_REF" master:master
    fi;
else
    echo "No Github user token found, cannot commit changes!"
fi;
