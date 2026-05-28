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

#pragma once

#include <cstdint>
#include <vector>

namespace vart {

/**
 * @enum OverlayImplType - Overlay Implementation type
 *
 * @var OPENCV
 *  Based on OpenCV
 */
enum class OverlayImplType { OPENCV };

/**
 * @struct OverlayCoordinates
 *
 * @brief Structure representing Coordinate information
 *
 * @var x
 *  x offset
 *
 * @var y
 *  y offset
 */
typedef struct {
  int32_t x;
  int32_t y;
} OverlayCoordinates;

/**
 * @struct OverlayColorData
 *
 * @brief Structure representing Color information
 *
 * @var red
 *  red channel value
 *
 * @var green
 *  green channel value
 *
 * @var blue
 *  blue channel value
 *
 * @var alpha
 *  Set alpha channel value to have transparency
 */
typedef struct {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t alpha;
} OverlayColorData;

/**
 * @struct OverlayRectParams
 *
 * @brief Structure representing information to draw rectangle on frame.
 *
 * @var points
 *  Co-ordinates of starting point of the rectangle
 *
 * @var width
 *  Width of the rectangle
 *
 * @var height
 *  Height of the rectangle
 *
 * @var thickness
 *  Thickness of edges of rectangle in pixels
 *
 * @var apply_bg_color
 *  Set to non-zero value to fill the rectangle with color information
 *  from ``bg_color`` mentioned below .
 *
 * @var rect_color
 *  Color of edges of the rectangle
 *
 * @var bg_color
 *  Color information of background
 */
typedef struct {
  OverlayCoordinates points;
  uint32_t width;
  uint32_t height;
  uint32_t thickness;
  uint32_t apply_bg_color;
  OverlayColorData rect_color;
  OverlayColorData bg_color;
} OverlayRectParams;

/**
 * @struct OverlayFontData
 *
 * @brief Structure representing Font information
 *
 * @var font_num
 *  Font style number from openCV.
 *  Refer `link
 * <https://docs.opencv.org/4.x/d6/d6e/group__imgproc__draw.html#ga0f9314ea6e35f99bb23f29567fc16e11>`_
 * for more information.
 *
 * @var font_size
 *  font size
 *
 * @var font_color
 *  font color
 */
typedef struct {
  uint32_t font_num;
  float font_size;
  OverlayColorData font_color;
} OverlayFontData;

/**
 * @struct OverlayTextParams
 *
 * @brief Structure representing Text information
 *
 * @var points
 *  Coordinates of the starting point of the rectangle in which text is to be
 * displayed
 *
 * @var disp_text
 *  Text string to be displayed
 *
 * @var bottom_left_origin
 *  Set to non-zero if the ``points`` represents the co-ordinates of bottom left
 * corner of the text rectangle. Set to ``0`` in case the ``points`` represent
 * the co-ordinates of the top-left corner of the text rectangle.
 *
 * @var  apply_bg_color
 *  Set to non-zero if the text box needs to be filled with ``bg_color``
 *
 * @var text_font
 *  Font of the text to be displayed
 *
 * @var bg_color
 *  Background color information
 */
typedef struct {
  OverlayCoordinates points;
  char* disp_text;
  uint32_t bottom_left_origin;
  uint32_t apply_bg_color;
  OverlayFontData text_font;
  OverlayColorData bg_color;
} OverlayTextParams;

/**
 * @struct OverlayLineParams
 *
 * @brief Structure representing Line information
 *
 * @var start_pt
 *  Line start coordinate info
 *
 * @var end_pt
 *  Line end coordinate info
 *
 * @var thickness
 *  Thickness in units of Pixels
 *
 * @var line_color
 *  Color information
 */
typedef struct {
  OverlayCoordinates start_pt;
  OverlayCoordinates end_pt;
  uint32_t thickness;
  OverlayColorData line_color;
} OverlayLineParams;

/**
 * enum OverlayArrowDirection - Structure representing Arrow Direction
 *  information
 *
 * @var ARROW_DIRECTION_START
 *  Arrow direction start
 *
 * @var ARROW_DIRECTION_END
 *  Arrow direction end
 *
 * @var ARROW_DIRECTION_BOTH_ENDS
 *  Arrow direction both ends
 */
typedef enum {
  ARROW_DIRECTION_START,
  ARROW_DIRECTION_END,
  ARROW_DIRECTION_BOTH_ENDS
} OverlayArrowDirection;

/**
 * @struct OverlayArrowParams
 *
 * @brief Structure representing Arrow information
 *
 * @var start_pt
 *  Arrow start coordinate info
 *
 * @var end_pt
 *  Arrow end coordinate info
 *
 * @var arrow_direction
 *  Arrow direction
 *
 * @var thickness
 *  Thickness in units of Pixels
 *
 * @var tipLength
 *  Tip length
 *
 * @var line_color
 *  Color information
 */
typedef struct {
  OverlayCoordinates start_pt;
  OverlayCoordinates end_pt;
  OverlayArrowDirection arrow_direction;
  uint32_t thickness;
  float tipLength;
  OverlayColorData line_color;
} OverlayArrowParams;

/**
 * @struct OverlayCircleParams
 *
 * @brief Structure representing Circle Information
 *
 * @var center_pt
 *  Center co-odinates of the circle.
 *
 * @var thickness
 *  Circle boundary line thickness
 *
 * @var radius
 *  Circle radius
 *
 * @var circle_color
 *  Color of boundary line of the circle.
 */
typedef struct {
  OverlayCoordinates center_pt;
  uint32_t thickness;
  uint32_t radius;
  OverlayColorData circle_color;
} OverlayCircleParams;

/**
 * @struct OverlayPolygonParams
 *
 * @brief Structure representing Polygon information
 *
 * @var poly_pts
 *  Vector of vertex co-ordinates of the polygon.
 *
 * @var thickness
 *  Thickness of the polygon edges
 *
 * @var poly_color
 *  Polygon edge color information
 */
typedef struct {
  std::vector<OverlayCoordinates> poly_pts;
  uint32_t thickness;
  OverlayColorData poly_color;
} OverlayPolygonParams;

/**
 * @struct OverlayShapeInfo
 *
 * @brief Structure representing overlay shape information
 *
 * @var rect_params
 *  Vector of overlay rectangle parameters
 *
 * @var text_params
 *  Vector of overlay text parameters
 *
 * @var line_params
 *  Vector of overlay line parameters
 *
 * @var arrow_params
 *  Vector of overlay arrow parameters
 *
 * @var circle_params
 *  Vector of overlay circle parameters
 *
 * @var polygn_params
 *  Vector of overlay polygon parameters
 */
typedef struct {
  std::vector<OverlayRectParams> rect_params;
  std::vector<OverlayTextParams> text_params;
  std::vector<OverlayLineParams> line_params;
  std::vector<OverlayArrowParams> arrow_params;
  std::vector<OverlayCircleParams> circle_params;
  std::vector<OverlayPolygonParams> polygn_params;
} OverlayShapeInfo;

}  // namespace vart
