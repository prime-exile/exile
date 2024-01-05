#bin/bash

if [ ! -d "./build" ]
	then
		mkdir build;
fi

cd build;

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DEXILE_DEFAULT_ULP_STDOUT=ON -DEXILE_ENABLE_TESTS=ON ..

