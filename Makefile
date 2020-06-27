BUILD_TYPE_FLAG=WEIGHT_DEBUG #Or WEIGHT_DISTRIBUTE
GPPPARAMS=-g -O3 -std=c++11 -D $(BUILD_TYPE_FLAG) -Iinclude -Iinclude/WeightEngine/external_libraries -Wno-macro-redefined -Wno-deprecated-declarations -Wno-null-conversion -Wno-deprecated-declarations
objects=obj/WeightEngine/utils/log.o \
				obj/WeightEngine/utils/utils.o \
				obj/WeightEngine/utils/maths_utils.o \
				obj/WeightEngine/utils/time.o \
				obj/WeightEngine/utils/random.o \
				obj/WeightEngine/utils/audio_utils.o \
				obj/WeightEngine/utils/profiling.o \
				obj/WeightEngine/android_wrappers/android_native_app_glue.o \
				obj/WeightEngine/window.o \
				obj/WeightEngine/event_system.o \
				obj/WeightEngine/audio/listener.o \
				obj/WeightEngine/audio/source.o \
				obj/WeightEngine/audio/music_manager.o \
				obj/WeightEngine/audio/dialogue.o \
				obj/WeightEngine/physics/physics_engine.o \
				obj/WeightEngine/physics/physics_object.o \
				obj/WeightEngine/render_engine/frame_buffer.o \
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
				obj/WeightEngine/external_libraries/box2d/collision/b2_broad_phase.o \
				obj/WeightEngine/external_libraries/box2d/collision/b2_chain_shape.o \
				obj/WeightEngine/external_libraries/box2d/collision/b2_circle_shape.o \
				obj/WeightEngine/external_libraries/box2d/collision/b2_collide_circle.o \
				obj/WeightEngine/external_libraries/box2d/collision/b2_collide_edge.o \
				obj/WeightEngine/external_libraries/box2d/collision/b2_collide_polygon.o \
				obj/WeightEngine/external_libraries/box2d/collision/b2_collision.o \
				obj/WeightEngine/external_libraries/box2d/collision/b2_distance.o \
				obj/WeightEngine/external_libraries/box2d/collision/b2_dynamic_tree.o \
				obj/WeightEngine/external_libraries/box2d/collision/b2_edge_shape.o \
				obj/WeightEngine/external_libraries/box2d/collision/b2_polygon_shape.o \
				obj/WeightEngine/external_libraries/box2d/collision/b2_time_of_impact.o \
				obj/WeightEngine/external_libraries/box2d/common/b2_block_allocator.o \
				obj/WeightEngine/external_libraries/box2d/common/b2_draw.o \
				obj/WeightEngine/external_libraries/box2d/common/b2_math.o \
				obj/WeightEngine/external_libraries/box2d/common/b2_settings.o \
				obj/WeightEngine/external_libraries/box2d/common/b2_stack_allocator.o \
				obj/WeightEngine/external_libraries/box2d/common/b2_timer.o \
				obj/WeightEngine/external_libraries/box2d/dynamics/b2_body.o \
				obj/WeightEngine/external_libraries/box2d/dynamics/b2_chain_circle_contact.o \
				obj/WeightEngine/external_libraries/box2d/dynamics/b2_chain_polygon_contact.o \
				obj/WeightEngine/external_libraries/box2d/dynamics/b2_circle_contact.o \
				obj/WeightEngine/external_libraries/box2d/dynamics/b2_contact.o \
				obj/WeightEngine/external_libraries/box2d/dynamics/b2_contact_manager.o \
				obj/WeightEngine/external_libraries/box2d/dynamics/b2_contact_solver.o \
				obj/WeightEngine/external_libraries/box2d/dynamics/b2_distance_joint.o \
				obj/WeightEngine/external_libraries/box2d/dynamics/b2_edge_circle_contact.o \
				obj/WeightEngine/external_libraries/box2d/dynamics/b2_edge_polygon_contact.o \
				obj/WeightEngine/external_libraries/box2d/dynamics/b2_fixture.o \
				obj/WeightEngine/external_libraries/box2d/dynamics/b2_friction_joint.o \
				obj/WeightEngine/external_libraries/box2d/dynamics/b2_gear_joint.o \
				obj/WeightEngine/external_libraries/box2d/dynamics/b2_island.o \
				obj/WeightEngine/external_libraries/box2d/dynamics/b2_joint.o \
				obj/WeightEngine/external_libraries/box2d/dynamics/b2_motor_joint.o \
				obj/WeightEngine/external_libraries/box2d/dynamics/b2_mouse_joint.o \
				obj/WeightEngine/external_libraries/box2d/dynamics/b2_polygon_circle_contact.o \
				obj/WeightEngine/external_libraries/box2d/dynamics/b2_polygon_contact.o \
				obj/WeightEngine/external_libraries/box2d/dynamics/b2_prismatic_joint.o \
				obj/WeightEngine/external_libraries/box2d/dynamics/b2_pulley_joint.o \
				obj/WeightEngine/external_libraries/box2d/dynamics/b2_revolute_joint.o \
				obj/WeightEngine/external_libraries/box2d/dynamics/b2_rope_joint.o \
				obj/WeightEngine/external_libraries/box2d/dynamics/b2_weld_joint.o \
				obj/WeightEngine/external_libraries/box2d/dynamics/b2_wheel_joint.o \
				obj/WeightEngine/external_libraries/box2d/dynamics/b2_world.o \
				obj/WeightEngine/external_libraries/box2d/dynamics/b2_world_callbacks.o \
				obj/WeightEngine/external_libraries/box2d/rope/b2_rope.o

obj/%.o: src/%.cpp
	mkdir -p $(@D)
	g++ $(GPPPARAMS) -o $@ -c $<

obj/%.o: src/%.c
	mkdir -p $(@D)
	gcc -g -O3 -Iinclude -Iinclude/WeightEngine/external_libraries -Iinclude/WeightEngine/external_libraries/FreeType -Wno-macro-redefined -Wno-deprecated-declarations -Wno-null-conversion -o $@ -c $<

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
	g++ -std=c++11 -Iinclude -Iinclude/WeightEngine/external_libraries -Wno-macro-redefined -Wno-deprecated-declarations -Wno-null-conversion -Wno-deprecated-declarations -Lsrc/WeightEngine/external_libraries -lexternal_libraries -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit test_file.cpp -o test_file && ./test_file
	rm -rf test_file

commit:
	git add .
	git commit -m "$(m)"
	git push origin master

push:
	git push origin master

.PHONY: clean
clean:
	rm -rf obj libWeightEngine.dylib WeightEngine.a WeightEngineTest/example
