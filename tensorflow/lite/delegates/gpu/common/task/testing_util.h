/* Copyright 2020 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef TENSORFLOW_LITE_DELEGATES_GPU_COMMON_TASK_TESTING_UTIL_H_
#define TENSORFLOW_LITE_DELEGATES_GPU_COMMON_TASK_TESTING_UTIL_H_

#include <vector>

#include "tensorflow/lite/delegates/gpu/common/gpu_info.h"
#include "tensorflow/lite/delegates/gpu/common/precision.h"
#include "tensorflow/lite/delegates/gpu/common/shape.h"
#include "tensorflow/lite/delegates/gpu/common/task/gpu_operation.h"
#include "tensorflow/lite/delegates/gpu/common/task/tensor_desc.h"
#include "tensorflow/lite/delegates/gpu/common/tensor.h"

namespace tflite {
namespace gpu {

class TestExecutionEnvironment {
 public:
  TestExecutionEnvironment() = default;
  virtual ~TestExecutionEnvironment() = default;

  virtual std::vector<CalculationsPrecision> GetSupportedPrecisions() const = 0;
  virtual std::vector<TensorStorageType> GetSupportedStorages() const = 0;
  // returns storage types that support zero clamping when reading OOB in HW
  // (Height/Width) dimensions.
  virtual std::vector<TensorStorageType>
  GetSupportedStoragesWithHWZeroClampSupport() const = 0;

  virtual const GpuInfo& GetGpuInfo() const = 0;

  virtual absl::Status ExecuteGPUOperation(
      const std::vector<TensorFloat32>& src_cpu,
      std::unique_ptr<GPUOperation>&& operation,
      const std::vector<BHWC>& dst_sizes,
      const std::vector<TensorFloat32*>& dst_cpu) = 0;
};

}  // namespace gpu
}  // namespace tflite

#endif  // TENSORFLOW_LITE_DELEGATES_GPU_COMMON_TASK_TESTING_UTIL_H_
