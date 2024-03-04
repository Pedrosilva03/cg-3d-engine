all: FASE1 

fase1:
	rm -rf build || echo "build removido"
	cmake -S ./src -B build
	cmake --build build/

FASE1: fase1
	./build/Debug/generator.exe cone 1 2 4 3 ./FASE1/out/cone_1_2_4_3.3d
	./build/Debug/generator.exe sphere 1 10 10 ./FASE1/out/sphere_1_10_10.3d 
	./build/Debug/generator.exe box 2 3 ./FASE1/out/box_2_3.3d
	./build/Debug/generator.exe plane 1 3 ./FASE1/out/plane_1_3.3d

test_1_1:
	cd build/ && ./engine ../FASE1/test_fase1/test_1_1.xml

test_1_2:
	cd build/ && ./engine ../FASE1/test_fase1/test_1_2.xml

test_1_3:
	cd build/ && ./engine ../FASE1/test_fase1/test_1_3.xml

test_1_4:
	cd build/ && ./engine ../FASE1/test_fase1/test_1_4.xml

test_1_5:
	cd build/ && ./engine ../FASE1/test_fase1/test_1_5.xmL