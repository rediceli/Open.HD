/******************************************************************************
 * OpenHD
 *
 * Licensed under the GNU General Public License (GPL) Version 3.
 *
 * This software is provided "as-is," without warranty of any kind, express or
 * implied, including but not limited to the warranties of merchantability,
 * fitness for a particular purpose, and non-infringement. For details, see the
 * full license in the LICENSE file provided with this source code.
 *
 * Non-Military Use Only:
 * This software and its associated components are explicitly intended for
 * civilian and non-military purposes. Use in any military or defense
 * applications is strictly prohibited unless explicitly and individually
 * licensed otherwise by the OpenHD Team.
 *
 * Contributors:
 * A full list of contributors can be found at the OpenHD GitHub repository:
 * https://github.com/OpenHD
 *
 * © OpenHD, All Rights Reserved.
 ******************************************************************************/

#include "config_paths.h"

#include <csignal>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>

#include "openhd_platform.h"
#include "openhd_util_filesystem.h"

// Initial default paths
static char* CONFIG_BASE_PATH = nullptr;
static char* VIDEO_PATH = nullptr;

const char* getConfigBasePath() {
  const auto platform_debug = OHDPlatform::instance();
  if (platform_debug.is_rock()) {
    return "/config/openhd/";
  } else if (platform_debug.is_x20()) {
    return "/config/openhd/";
  } else {
    return "/boot/openhd/";
  }
}

const char* getVideoPath() {
  const auto FILENAME_VIDEO_EXTERNAL = "/Videos/external_video_part.txt";
  const auto FILENAME_VIDEO_EXTERNAL_X20 =
      "/external/Videos/external_video_part.txt";
  if (OHDFilesystemUtil::exists(FILENAME_VIDEO_EXTERNAL)) {
    return VIDEO_PATH ? VIDEO_PATH : "/Videos/";
  } else if (OHDFilesystemUtil::exists(FILENAME_VIDEO_EXTERNAL_X20)) {
    return VIDEO_PATH ? VIDEO_PATH : "/external/Videos/";
  } else {
    OHDFilesystemUtil::create_directories("/home/openhd/Videos/");
    return "/home/openhd/Videos/";
  }
}

void setConfigBasePath(const char* path) {
  if (CONFIG_BASE_PATH) {
    free(CONFIG_BASE_PATH);
  }
  CONFIG_BASE_PATH = static_cast<char*>(malloc(strlen(path) + 1));
  strcpy(CONFIG_BASE_PATH, path);
}

void setVideoPath(const char* path) {
  if (VIDEO_PATH) {
    free(VIDEO_PATH);
  }
  VIDEO_PATH = static_cast<char*>(malloc(strlen(path) + 1));
  strcpy(VIDEO_PATH, path);
}
