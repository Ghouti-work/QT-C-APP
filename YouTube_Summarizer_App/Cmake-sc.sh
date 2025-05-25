rm -rf build # if you're using a build directory
mkdir build && cd build
cmake ..
make

mv -f YoutubeSummarizer ../
cd ..
