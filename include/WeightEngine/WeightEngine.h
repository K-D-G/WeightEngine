#ifndef WEIGHT_ENGINE__WEIGHT_ENGINE_H
#define WEIGHT_ENGINE__WEIGHT_ENGINE_H

#include <WeightEngine/core.h>

#include <WeightEngine/utils/audio_utils.h>
#include <WeightEngine/utils/keycodes.h>
#include <WeightEngine/utils/log.h>
#include <WeightEngine/utils/maths_utils.h>
#include <WeightEngine/utils/random.h>
#include <WeightEngine/utils/time.h>
#include <WeightEngine/utils/profiling.h>
#include <WeightEngine/utils/utils.h>

#include <WeightEngine/audio/source.h>
#include <WeightEngine/audio/listener.h>
#include <WeightEngine/audio/dialogue.h>
#include <WeightEngine/audio/music_manager.h>

#include <WeightEngine/physics/physics_engine.h>
#include <WeightEngine/physics/physics_object.h>

#include <WeightEngine/render_engine/shaders/basic_shader.h>
#include <WeightEngine/render_engine/shaders/Light2D_shader.h>
#include <WeightEngine/render_engine/shaders/Particle2D_shader.h>
#include <WeightEngine/render_engine/shaders/text_shader.h>

#include <WeightEngine/render_engine/gui/widget.h>
#include <WeightEngine/render_engine/gui/label.h>
#include <WeightEngine/render_engine/gui/image.h>
#include <WeightEngine/render_engine/gui/button.h>
#include <WeightEngine/render_engine/gui/gui_renderer.h>

#include <WeightEngine/render_engine/2D/2DLight.h>
#include <WeightEngine/render_engine/2D/2DLightSystem.h>
#include <WeightEngine/render_engine/2D/2DParticleSystem.h>
#include <WeightEngine/render_engine/2D/2DAnimation.h>
#include <WeightEngine/render_engine/2D/2D.h>

#include <WeightEngine/render_engine/vertex.h>
#include <WeightEngine/render_engine/shader.h>
#include <WeightEngine/render_engine/frame_buffer.h>
#include <WeightEngine/render_engine/font.h>
#include <WeightEngine/render_engine/texture_atlas.h>
#include <WeightEngine/render_engine/scene_manager.h>
#include <WeightEngine/render_engine/scene.h>
#include <WeightEngine/render_engine/orthographic_camera.h>
#include <WeightEngine/render_engine/orthographic_camera_controller.h>
#include <WeightEngine/render_engine/text_renderer.h>
#include <WeightEngine/render_engine/renderer.h>

#include <WeightEngine/event_system.h>
#include <WeightEngine/window.h>
#include <WeightEngine/Application.h>
#include <WeightEngine/entrypoint.h>

#endif
