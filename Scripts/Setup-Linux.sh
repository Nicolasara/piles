#!/bin/bash

pushd ..
Vendor/Binaries/Premake/Linux/premake5 --cc=clang --file=Build.lua gmake2
popd

echo "" >> ../Makefile
echo "" >> ../Makefile
echo "run: App" >> ../Makefile
echo -e "\t@echo \"==== Running App ====\"" >> ../Makefile
echo -e "\t@./Binaries/linux-x86_64/\$(config)/App/App" >> ../Makefile