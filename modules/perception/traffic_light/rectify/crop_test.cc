/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include "gtest/gtest.h"
#include "modules/perception/traffic_light/rectify/cropbox.h"

namespace apollo {
namespace perception {
namespace traffic_light {

class CropBoxTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    _crop_scale = 3;
    _min_crop_size = 270;
    _crop_local = new CropBox(_crop_scale, _min_crop_size);
  }
  ~CropBoxTest() {
    delete (_crop_local);
  }

 protected:
  IGetBox *_crop_local;
  float _crop_scale;
  int _min_crop_size;
};

TEST_F(CropBoxTest, crop0) {
  std::vector<LightPtr> hd_box(1);
  hd_box[0].reset(new Light);
  hd_box[0]->region.projection_roi = cv::Rect(1920, 1080, 21, 177);
  cv::Size size(1920, 1080);
  cv::Rect cbox;
  _crop_local->GetCropBox(size, hd_box, &cbox);
  cv::Rect rect(0, 0, 0, 0);
  ASSERT_TRUE(rect == cbox);
}

TEST_F(CropBoxTest, crop1) {
  std::vector<LightPtr> hd_box(1);
  hd_box[0].reset(new Light);
  hd_box[0]->region.projection_roi = cv::Rect(1898, 798, 21, 177);
  cv::Size size(1920, 1080);
  cv::Rect cbox;
  _crop_local->GetCropBox(size, hd_box, &cbox);
  cv::Rect rect(1643, 621, 276, 458);
  ASSERT_TRUE(rect == cbox) << rect << cbox;

  hd_box[0]->region.projection_roi = cv::Rect(1011, 503, 21, 177);
  _crop_local->GetCropBox(size, hd_box, &cbox);
  rect = cv::Rect(756, 326, 531, 531);
  ASSERT_TRUE(rect == cbox) << rect << cbox;
}

TEST_F(CropBoxTest, crop2) {
  std::vector<LightPtr> hd_box(2);
  hd_box[0].reset(new Light);
  hd_box[0]->region.projection_roi = cv::Rect(1439, 743, 30, 192);
  hd_box[1].reset(new Light);
  hd_box[1]->region.projection_roi = cv::Rect(1620, 743, 27, 192);
  cv::Size size(1920, 1080);
  cv::Rect cbox;
  _crop_local->GetCropBox(size, hd_box, &cbox);
  cv::Rect rect(1231, 527, 624, 552);
  ASSERT_TRUE(rect == cbox) << rect << cbox;
}
}  // namespace traffic_light
}  // namespace perception
}  // namespace apollo
