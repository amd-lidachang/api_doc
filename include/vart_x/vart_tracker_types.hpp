/*
 * Copyright 2024 Advanced Micro Devices Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef VART_TRACKER_TYPES_HPP
#define VART_TRACKER_TYPES_HPP

/* Tracker default config */
#define TRACKER_ALGO_DEFAULT                       (TRACKER_ALGO_KCF)
#define TRACKER_DISTANCE_FUNC_DEFAULT              (DIST_IOU_WITH_COLOR)
#define TRACKER_IOU_USE_COLOR_FEATURE              (1)
#define TRACKER_USE_MATCHING_COLOR_SPACE           (TRACKER_USE_HSV)
#define TRACKER_FEATURE_LENGTH_DEFAULT             (31)
#define TRACKER_SEARCH_SCALE_DEFAULT               (SEARCH_SCALE_ALL)
#define TRACKER_INACTIVE_WAIT_INTERVAL_DEFAULT     (200)
#define TRACKER_MIN_OBJECT_WIDTH_DEFAULT           (20)
#define TRACKER_MIN_OBJECT_HEIGHT_DEFAULT          (60)
#define TRACKER_MAX_OBJECT_WIDTH_DEFAULT           (200)
#define TRACKER_MAX_OBJECT_HEIGHT_DEFAULT          (360)
#define TRACKER_NUM_FRAMES_CONFIDENCE_DEFAULT      (3)
#define TRACKER_MATCHING_SEARCH_REGION_DEFAULT     (1.5)
#define TRACKER_RELATIVE_SEARCH_REGION_DEFAULT     (1.5)
#define TRACKER_CORRELATION_THRESHOLD_DEFAULT      (0.7)
#define TRACKER_OVERLAP_THRESHOLD_DEFAULT          (0.0)
#define TRACKER_SCALE_CHANGE_THRESHOLD_DEFAULT     (0.7)
#define TRACKER_CORRELATION_WEIGHT_DEFAULT         (0.7)
#define TRACKER_OVERLAP_WEIGHT_DEFAULT             (0.2)
#define TRACKER_SCALE_CHANGE_WEIGHT_DEFAULT        (0.1)
#define TRACKER_OCCLUSION_THRESHOLD_DEFAULT        (0.4)
#define TRACKER_CONFIDENCE_SCORE_THRESHOLD_DEFAULT (0.25)
#define TRACKER_SKIP_INACTIVE_OBJS_DEFAULT         (true)

namespace vart {

/**
 * @enum TrackerAlgoType
 * @brief Enum representing tracker algorithm type.
 * 
 * @details This enum defines the different types of tracker algorithms that can be used.
 * 
 * @var TRACKER_ALGO_NONE
 * No tracker algorithm will be used. This is set as the default algorithm.
 * 
 * @var TRACKER_ALGO_MOSSE
 * Minimum Output Sum of Squared Error algorithm.
 * 
 * @var TRACKER_ALGO_KCF
 * Kernelized Correlation Filter algorithm.
 */
enum class TrackerAlgoType
{
  TRACKER_ALGO_NONE,
  TRACKER_ALGO_MOSSE,
  TRACKER_ALGO_KCF,
};

/**
 * @enum TrackerMatchColorSpace
 * @brief Enum representing color space used for object matching.
 * 
 * @details This enum defines the different color spaces that can be used for object matching.
 * 
 * @var TRACKER_USE_RGB
 * Use RGB color space for object matching.
 * 
 * @var TRACKER_USE_HSV
 * Use HSV (Hue-Saturation-Value) color space for object matching.
 */
enum class TrackerMatchColorSpace
{
  TRACKER_USE_RGB,
  TRACKER_USE_HSV,
};

/**
 * @enum TrackerDistanceFunc
 * @brief Enum representing distance function used for matching detected objects with tracking objects.
 * 
 * @details This enum defines the different distance functions that can be used for matching detected objects with tracking objects. 
 * The default distance function for bounding boxes is IOU with color, and for points, it is Frobenious distance.
 * 
 * @var DIST_IOU
 * Intersection-Over-Union distance function.
 * 
 * @var DIST_IOU_WITH_COLOR
 * IOU with color histogram as distance function.
 * 
 * @var DIST_FROBENIOUS
 * Frobenious distance function.
 * 
 * @var DIST_MEAN_EUCLIDEAN
 * Average of Euclidean distance function.
 * 
 * @var DIST_MEAN_MANHATTAN
 * Average of Manhattan distance function.
 * 
 * @var DIST_NORMALIZED_MEAN_EUCLIDEAN
 * Euclidean normalized distance average function.
 * 
 * @var DIST_KEYPOINTS_VOTING
 * Distance based on keypoint voting.
 */
enum class TrackerDistanceFunc
{
  DIST_IOU,
  DIST_IOU_WITH_COLOR,
  DIST_FROBENIOUS,
  DIST_MEAN_EUCLIDEAN,
  DIST_MEAN_MANHATTAN,
  DIST_NORMALIZED_MEAN_EUCLIDEAN,
  DIST_KEYPOINTS_VOTING,
};

/**
 * @enum TrackerSearchScale
 * @brief Enum representing search scales to be used for tracking.
 * 
 * @details This enum defines the different search scales that can be used for tracking objects.
 * 
 * @var SEARCH_SCALE_ALL
 * Search for object both in up, same, and down scale.
 * 
 * @var SEARCH_SCALE_UP
 * Search for object in up and same scale only.
 * 
 * @var SEARCH_SCALE_DOWN
 * Search for object in down and same scale only.
 * 
 * @var SEARCH_SCALE_NONE
 * Search for object in the same scale.
 */
enum class TrackerSearchScale
{
  SEARCH_SCALE_ALL,
  SEARCH_SCALE_UP,
  SEARCH_SCALE_DOWN,
  SEARCH_SCALE_NONE,
};

/**
 * @struct Trackerconfig
 * @brief Structure to hold tracker configuration.
 * 
 * @details This structure contains various configuration parameters for the tracker.
 * 
 * @var tracker_type
 * Tracker algorithm to be used.
 * 0: IOU
 * 1: KCF Tracker
 * 2: MOSSE Tracker
 * 
 * @var distance_func
 * Distance function to be used for objects matching.
 * 
 * @var obj_match_color
 * Color space to be used for object matching.
 * 
 * @var search_scales
 * Search scales of object during tracking.
 * 
 * @var fet_length
 * Feature length to be used during KCF based tracking.
 * 
 * @var min_width
 * Minimum width for considering as noise.
 * 
 * @var min_height
 * Minimum height for considering as noise.
 * 
 * @var max_width
 * Maximum width for considering as noise.
 * 
 * @var max_height
 * Maximum height for considering as noise.
 * 
 * @var num_inactive_frames
 * Number of frames to wait for object reappearing before considering as inactive.
 * 
 * @var num_frames_confidence
 * Number of frames of continuous detection before considering for tracking and assigning an ID.
 * 
 * @var padding
 * Extra area surrounding the target to search in tracking.
 * 
 * @var obj_match_search_region
 * Search for nearest object to match.
 * 
 * @var dist_correlation_threshold
 * Objects correlation threshold.
 * 
 * @var dist_overlap_threshold
 * Objects overlap threshold.
 * 
 * @var dist_scale_change_threshold
 * Objects scale change threshold.
 * 
 * @var dist_correlation_weight
 * Weightage for correlation in distance function.
 * 
 * @var dist_overlap_weight
 * Weightage for overlap in distance function.
 * 
 * @var dist_scale_change_weight
 * Weightage for scale change in distance function.
 * 
 * @var occlusion_threshold
 * Occlusion threshold to ignore objects for tracking.
 * 
 * @var confidence_score
 * Tracker confidence threshold for tracking.
 * 
 * @var skip_inactive_objs
 * Flag to enable skipping of inactive objects.
 */
typedef struct {
  TrackerAlgoType tracker_type;
  TrackerDistanceFunc distance_func;
  TrackerMatchColorSpace obj_match_color;
  TrackerSearchScale search_scales;
  unsigned int fet_length;
  unsigned int min_width;
  unsigned int min_height;
  unsigned int max_width;
  unsigned int max_height;
  int num_inactive_frames;
  int num_frames_confidence;
  float padding;
  float obj_match_search_region;
  float dist_correlation_threshold;
  float dist_overlap_threshold;
  float dist_scale_change_threshold;
  float dist_correlation_weight;
  float dist_overlap_weight;
  float dist_scale_change_weight;
  float occlusion_threshold;
  float confidence_score; //confidence score
  bool skip_inactive_objs;
} Trackerconfig;

}  // namespace vart
#endif  // VART_TRACKER_TYPES_HPP