build_f1:
	cmake -B FASE1/build -S FASE1/src -A Win32
	cmake --build FASE1/build/ --config Release
	@echo "Build FASE1 done"
	./FASE1/build/Release/generator.exe plane 2 3 FASE1/out/plane_2_3.3d
	@echo "Plane done"
	./FASE1/build/Release/generator.exe box 2 3 FASE1/out/box_2_3.3d
	@echo "Box done"
	./FASE1/build/Release/generator.exe cone 1 2 4 3 FASE1/out/cone_1_2_4_3.3d
	@echo "Cone done"
	./FASE1/build/Release/generator.exe sphere 1 10 10 FASE1/out/sphere_1_10_10.3d
	@echo "Sphere done"

build_f2:
	cmake -B FASE2/build -S FASE2/src -A Win32
	cmake --build FASE2/build/ --config Release
	@echo "Build FASE2 done"
	