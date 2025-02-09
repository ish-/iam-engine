#pragma once

#include <memory>
#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>
#include <typeindex>
#include <cmath>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>

// #include "common/memory.hpp"
#include "common/file.hpp"
#include "common/json.hpp"
#include "common/LOG.hpp"
#include "common/MACRO.hpp"
#include "common/math.hpp"
#include "common/random.hpp"
#include "common/Symbol.hpp"

#include <glad/glad.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_timer.h>