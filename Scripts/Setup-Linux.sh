#!/bin/bash

pushd ..
Vendor/Binaries/Premake/Linux/premake5 --cc=clang --file=Build.lua gmake2
popd

echo "" >> ../Makefile
echo "" >> ../Makefile
echo "run: App" >> ../Makefile
echo -e "\t@echo \"==== Running App ====\"" >> ../Makefile
echo -e "\t@./Binaries/linux-x86_64/\$(config)/App/App" >> ../Makefile

echo "" >> ../Makefile
echo "" >> ../Makefile
echo "test: Tests" >> ../Makefile
echo -e "\t@echo \"==== Running Tests ====\"" >> ../Makefile
echo -e "\t@./Binaries/linux-x86_64/\$(config)/Tests/Tests" >> ../Makefile

echo "" >> ../Makefile
echo "" >> ../Makefile
echo "proto: " >> ../Makefile
echo -e "\t@echo \"==== Generating Protobuf ====\"" >> ../Makefile
echo -e "\t@protoc --proto_path=./App/Protos --cpp_out=./App/Source ./App/Protos/*.proto" >> ../Makefile