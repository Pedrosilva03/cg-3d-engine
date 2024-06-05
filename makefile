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
	./FASE2/build/Release/generator.exe sphere 1 8 8 FASE2/out/sphere_1_8_8.3d
	@echo "Sphere_1_8_8 done"
	./FASE2/build/Release/generator.exe sphere 1 10 10 FASE2/out/planet.3d
	@echo "Planet done"
	./FASE2/build/Release/generator.exe sphere 1 25 25 FASE2/out/sun.3d
	@echo "Sun done"
	./FASE2/build/Release/generator.exe ring 1.5 2 40 FASE2/out/ring.3d
	@echo "Ring done"

build_f3:
	cmake -B FASE3/build -S FASE3/src -A Win32
	cmake --build FASE3/build/ --config Release
	@echo "Build FASE3 done"
	./FASE3/build/Release/generator.exe patch FASE3/patches/teapot.patch 10 FASE3/out/bezier_10.3d
	@echo "Bezier done"
	./FASE3/build/Release/generator.exe patch FASE3/patches/comet.patch 2 FASE3/out/comet_2.3d
	@echo "Comet done"

build_f4:
	cmake -B FASE4/build -S FASE4/src -A Win32
	cmake --build FASE4/build/ --config Release

	./FASE4/build/Release/generator.exe plane 2 3 FASE4/out/plane_2_3.3d
	@echo "Plane done"
	./FASE4/build/Release/generator.exe box 2 3 FASE4/out/box_2_3.3d
	@echo "Box done"
	./FASE4/build/Release/generator.exe cone 1 2 4 3 FASE4/out/cone_1_2_4_3.3d
	@echo "Cone done"
	./FASE4/build/Release/generator.exe sphere 1 10 10 FASE4/out/sphere_1_10_10.3d
	@echo "Sphere done"

	./FASE4/build/Release/generator.exe sphere 1 8 8 FASE4/out/sphere_1_8_8.3d
	@echo "Sphere_1_8_8 done"
	./FASE4/build/Release/generator.exe sphere 1 10 10 FASE4/out/planet.3d
	@echo "Planet done"
	./FASE4/build/Release/generator.exe sphere 1 25 25 FASE4/out/sun.3d
	@echo "Sun done"
	./FASE4/build/Release/generator.exe ring 1.5 2 40 FASE4/out/ring.3d
	@echo "Ring done"

	./FASE4/build/Release/generator.exe patch FASE4/patches/teapot.patch 10 FASE4/out/bezier_10.3d
	@echo "Bezier done"
	./FASE4/build/Release/generator.exe patch FASE4/patches/comet.patch 2 FASE4/out/comet_2.3d
	@echo "Comet done"

	@echo "Build FASE4 done"

clean:
ifeq ($(OS),Windows_NT)
	@if exist "FASE1/build" rmdir /S /Q "FASE1/build"
	@if exist "FASE2/build" rmdir /S /Q "FASE2/build"
	@if exist "FASE3/build" rmdir /S /Q "FASE3/build"
	@if exist "FASE4/build" rmdir /S /Q "FASE4/build"
else
	@if [ -d "FASE1/build" ]; then rm -rf FASE1/build; fi
	@if [ -d "FASE2/build" ]; then rm -rf FASE2/build; fi
	@if [ -d "FASE3/build" ]; then rm -rf FASE3/build; fi
	@if [ -d "FASE4/build" ]; then rm -rf FASE4/build; fi
endif

	