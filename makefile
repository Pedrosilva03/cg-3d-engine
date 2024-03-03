all: 3DFase1 

fase1:
	rm -r build || echo "build removido"
	cmake -S ./Fase_1/src -B build
	cmake --build build/

3dFase1: fase1
	./build/generator.exe cone 1 2 4 3 ./FASE1/out/cone_1_2_4_3.3d
	./build/generator.exe sphere 1 10 10 ./FASE1/out/sphere_1_10_10.3d 
	./build/generator.exe box 2 3 ./FASE1/out/box_2_3.3d
	./build/generator.exe plane 2 3 ./FASE1/out/plane_2_3.3d

test_1_1:
	cd build/ && ./engine.exe ../FASE1/test_fase1/test_1_1.xml

test_1_2:
	cd build/ && ./engine.exe ../FASE1/test_fase1/test_1_2.xml

test_1_3:
	cd build/ && ./engine.exe ../FASE1/test_fase1/test_1_3.xml

test_1_4:
	cd build/ && ./engine.exe ../FASE1/test_fase1/test_1_4.xml

test_1_5:
	cd build/ && ./engine.exe ../FASE1/test_fase1/test_1_5.xml