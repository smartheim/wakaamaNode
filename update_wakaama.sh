#!/bin/bash
die() { echo "$@" 1>&2 ; exit 1; }

GH_REF="github.com/Openhab-Nodes/WakaamaNode.git"
GH_SRC="https://github.com/eclipse/wakaama.git"
TITLE="Update wakaama source to revision"
AUTHOR="David Graeff <david.graeff@web.de>"

rm -rf tmp
git clone "$GH_SRC" tmp --branch master --single-branch --depth 1
cd tmp || die "Couldn't checkout repository!"
describe=$(git rev-parse --short HEAD)

# Check checkout
if [ ! -d core ]; then die "Expected a core directory in the wakama sources!"; fi;

# Remove old sources
echo "$TITLE $describe"
rm -rf ../src/wakaama && mv core ../src/wakaama
cd .. || exit
rm -rf tmp

# Patch main header file to #include a configuration file.
match='#define _LWM2M_CLIENT_H_'
insert='#include "wakaama_config.h"'
file='src/wakaama/liblwm2m.h'
sed -i "s/$match/$match\n$insert/" $file || die 

# Add to repository
git add src/wakaama
git commit --author="$AUTHOR" -m "$TITLE $describe"

if [ "$GH_TOKEN" != "" ]; then
    if ! git diff HEAD origin/HEAD > /dev/null; then
        git push "https://$GH_TOKEN@$GH_REF" master:master
    fi;
else
    echo "No Github user token found, cannot commit changes!"
fi;
