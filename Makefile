GPPPARAMS=-g -std=c++11 -Iinclude -Iinclude/WeightEngine/external_libraries -Wno-macro-redefined -Wno-deprecated-declarations -Wno-null-conversion -Wno-deprecated-declarations
objects=obj/WeightEngine/utils/log.o \
				obj/WeightEngine/utils/utils.o \
				obj/WeightEngine/utils/maths_utils.o \
				obj/WeightEngine/utils/time.o \
				obj/WeightEngine/utils/random.o \
				obj/WeightEngine/utils/audio_utils.o \
				obj/WeightEngine/utils/profiling.o \
				obj/WeightEngine/window.o \
				obj/WeightEngine/event_system.o \
				obj/WeightEngine/audio/listener.o \
				obj/WeightEngine/audio/source.o \
				obj/WeightEngine/audio/music_manager.o \
				obj/WeightEngine/audio/dialogue.o \
				obj/WeightEngine/render_engine/shader.o \
				obj/WeightEngine/render_engine/shaders/basic_shader.o \
				obj/WeightEngine/render_engine/shaders/Particle2D_shader.o \
				obj/WeightEngine/render_engine/shaders/Light2D_shader.o \
				obj/WeightEngine/render_engine/shaders/text_shader.o \
				obj/WeightEngine/render_engine/orthographic_camera.o \
				obj/WeightEngine/render_engine/orthographic_camera_controller.o \
				obj/WeightEngine/render_engine/2D/2D.o \
				obj/WeightEngine/render_engine/2D/2DAnimation.o \
				obj/WeightEngine/render_engine/2D/2DParticleSystem.o \
				obj/WeightEngine/render_engine/2D/2DLight.o \
				obj/WeightEngine/render_engine/2D/2DLightSystem.o \
				obj/WeightEngine/render_engine/texture_atlas.o \
				obj/WeightEngine/render_engine/font.o \
				obj/WeightEngine/render_engine/text_renderer.o \
				obj/WeightEngine/render_engine/gui/widget.o \
				obj/WeightEngine/render_engine/gui/label.o \
				obj/WeightEngine/render_engine/gui/image.o \
				obj/WeightEngine/render_engine/gui/button.o \
				obj/WeightEngine/render_engine/gui/gui_renderer.o \
				obj/WeightEngine/render_engine/scene.o \
				obj/WeightEngine/render_engine/scene_manager.o \
				obj/WeightEngine/render_engine/renderer.o \
				obj/WeightEngine/Application.o

external_objects=obj/WeightEngine/external_libraries/glad.o \
				obj/WeightEngine/external_libraries/stb_image.o \
				obj/WeightEngine/external_libraries/alhelpers.o \
				obj/WeightEngine/external_libraries/alut/alutBufferData.o \
				obj/WeightEngine/external_libraries/alut/alutCodec.o \
				obj/WeightEngine/external_libraries/alut/alutError.o \
				obj/WeightEngine/external_libraries/alut/alutInit.o \
				obj/WeightEngine/external_libraries/alut/alutInputStream.o \
				obj/WeightEngine/external_libraries/alut/alutLoader.o \
				obj/WeightEngine/external_libraries/alut/alutOutputStream.o \
				obj/WeightEngine/external_libraries/alut/alutUtil.o \
				obj/WeightEngine/external_libraries/alut/alutVersion.o \
				obj/WeightEngine/external_libraries/alut/alutWaveform.o \
				obj/WeightEngine/external_libraries/FreeType/FreeTypeAmalgam.o \
				obj/WeightEngine/external_libraries/boost/converter/arg_to_python_base.o \
				obj/WeightEngine/external_libraries/boost/converter/builtin_converters.o \
				obj/WeightEngine/external_libraries/boost/converter/from_python.o \
				obj/WeightEngine/external_libraries/boost/converter/registry.o \
				obj/WeightEngine/external_libraries/boost/converter/type_id.o \
				obj/WeightEngine/external_libraries/boost/numpy/dtype.o \
				obj/WeightEngine/external_libraries/boost/numpy/matrix.o \
				obj/WeightEngine/external_libraries/boost/numpy/ndarray.o \
				obj/WeightEngine/external_libraries/boost/numpy/numpy.o \
				obj/WeightEngine/external_libraries/boost/numpy/scalars.o \
				obj/WeightEngine/external_libraries/boost/numpy/ufunc.o \
				obj/WeightEngine/external_libraries/boost/object/class.o \
				obj/WeightEngine/external_libraries/boost/object/enum.o \
				obj/WeightEngine/external_libraries/boost/object/function_doc_signature.o \
				obj/WeightEngine/external_libraries/boost/object/function.o \
				obj/WeightEngine/external_libraries/boost/object/inheritance.o \
				obj/WeightEngine/external_libraries/boost/object/iterator.o \
				obj/WeightEngine/external_libraries/boost/object/life_support.o \
				obj/WeightEngine/external_libraries/boost/object/pickle_support.o \
				obj/WeightEngine/external_libraries/boost/object/stl_iterator.o \
				obj/WeightEngine/external_libraries/boost/dict.o \
				obj/WeightEngine/external_libraries/boost/errors.o \
				obj/WeightEngine/external_libraries/boost/exec.o \
				obj/WeightEngine/external_libraries/boost/import.o \
				obj/WeightEngine/external_libraries/boost/list.o \
				obj/WeightEngine/external_libraries/boost/long.o \
				obj/WeightEngine/external_libraries/boost/module.o \
				obj/WeightEngine/external_libraries/boost/object_operators.o \
				obj/WeightEngine/external_libraries/boost/object_protocol.o \
				obj/WeightEngine/external_libraries/boost/slice.o \
				obj/WeightEngine/external_libraries/boost/str.o \
				obj/WeightEngine/external_libraries/boost/tuple.o \
				obj/WeightEngine/external_libraries/boost/wrapper.o \

obj/%.o: src/%.cpp
	mkdir -p $(@D)
	g++ $(GPPPARAMS) -o $@ -c $<

obj/%.o: src/%.c
	mkdir -p $(@D)
	gcc -g -Iinclude -Iinclude/WeightEngine/external_libraries -Iinclude/WeightEngine/external_libraries/FreeType -Wno-macro-redefined -Wno-deprecated-declarations -Wno-null-conversion -o $@ -c $<

#Compiling static library on OSX: https://stackoverflow.com/questions/47656942/how-to-build-a-portable-static-c-library-for-macos
external_libraries:$(external_objects)
	libtool -static -o src/WeightEngine/external_libraries/libexternal_libraries.a $(external_objects) -framework OpenAL

WeightEngine:$(objects)
	g++ $(objects) -o libWeightEngine.dylib -Lsrc/WeightEngine/external_libraries -lexternal_libraries -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework OpenAL -undefined suppress -dynamiclib -flat_namespace

example_app:
	clear
	make WeightEngine
	g++ -g WeightEngineTest/main.cpp -Wno-macro-redefined -L. -lWeightEngine -Iinclude -Iinclude/WeightEngine/external_libraries -o WeightEngineTest/example -std=c++11
	rm -rf WeightEngineTest/WeightEngineResources
	cp -r WeightEngineResources WeightEngineTest/WeightEngineResources
	WeightEngineTest/example

recompile_example:
	g++ -g WeightEngineTest/main.cpp -Wno-macro-redefined -L. -lWeightEngine -Iinclude -Iinclude/WeightEngine/external_libraries -o WeightEngineTest/example -std=c++11
	WeightEngineTest/example

run_app:
	WeightEngineTest/example

debug:
	gdb WeightEngineTest/example

update_shaders:
	rm -rf WeightEngineTest/WeightEngineResources
	cp -r WeightEngineResources WeightEngineTest/WeightEngineResources

test_file:
	g++ $(GPPPARAMS) -Lsrc/WeightEngine/external_libraries -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit test_file.cpp -o test_file && ./test_file
	rm -rf test_file

commit:
	git add .
	git commit -m $(m)
	git push origin master

.PHONY: clean
clean:
	rm -rf obj libWeightEngine.dylib WeightEngine.a WeightEngineTest/example
