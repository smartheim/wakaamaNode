#!/bin/bash
# Update wakama from git sources
GH_REF="github.com/Openhab-Nodes/libWakaamaEmb.git"
rm -rf tmp
git clone "https://$GH_TOKEN@github.com/eclipse/wakaama.git" tmp --branch master --single-branch --depth 1
cd tmp || exit "Couldn't checkout wakama!"
describe=$(git rev-parse --short HEAD)
if [ ! -d core ]; then
    echo "Expected a core directory in the wakama sources!"
    return
fi;

echo "Update wakama to $describe"
rm -rf ../src/wakaama && mv core ../src/wakaama
cd .. || exit
rm -rf tmp

# Add to repository
git add src/wakaama
git commit --author="Wakaama Update <david.graeff@web.de>" -m "Update wakaama source to revision $describe"

if [ "$GH_TOKEN" != "" ]; then
    if ! git diff HEAD origin/HEAD > /dev/null; then
        git push "https://$GH_TOKEN@$GH_REF" master:master
    fi;
else
    echo "No Github user token found, cannot commit changes!"
fi;
