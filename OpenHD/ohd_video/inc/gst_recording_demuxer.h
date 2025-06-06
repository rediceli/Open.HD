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

#ifndef OPENHD_GST_RECORDING_DEMUXER_H
#define OPENHD_GST_RECORDING_DEMUXER_H

#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

// Simple util class / namespace for demuxing .mkv air recording files
// uses gstreamer & command line util
class GstRecordingDemuxer {
 public:
  ~GstRecordingDemuxer();
  // Find all files that end in .mkv in the openhd videos (air recording)
  // directory and then spawns a new thread to demux the file (unless it is
  // already being demuxed)
  void demux_all_remaining_mkv_files_async();
  // demux a specific .mkv file (async) unless it is already being demuxed
  // thread-safe
  void demux_mkv_file_async_threadsafe(std::string filename);
  static GstRecordingDemuxer& instance();

 private:
  struct DeMuxOperation {
    std::string filename;
    std::shared_ptr<std::thread> thread;
  };
  std::vector<DeMuxOperation> m_demux_ops{};
  // makes sure we spawn exactly one demux thread per file
  std::mutex m_demux_ops_mutex;
};

#endif  // OPENHD_GST_RECORDING_DEMUXER_H
